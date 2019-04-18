/*
Copyright (c) 2012, Broadcom Europe Ltd.
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the copyright holder nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*******************************************************************************
* I don't actually know if this copyright disclaimer is necessary anymore,     *
* as I rewrote the whole source code and my functions are pretty different.    *
* The original and my code surely do the same thing and have the same names    *
* (for backward compatibility) but the way I do it is very different.          *
* I would really like to get rid of this copyright disclaimer so if anyone     *
* knows if I could leave it out that would be great!                           *
* The original source code can be found here:                                  *
* https://github.com/raspberrypi/userland/blob/master/host_applications/linux/apps/hello_pi/hello_fft/mailbox.c *
********************************************************************************/

#include "mailbox_mod.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#define perror_inf()	fprintf(stderr, "%s:%d: In function %s:\n", __FILE__,  \
    __LINE__, __func__)

int
mbox_open(void)
{
    int fd;
    if ((fd = open(DEVICE_FILE_NAME, 0)) < 0) {
        perror_inf();
        perror("Can't open device file: /dev/vcio");
        return -1;
    }
    return fd;
}

void
mbox_close(int fd)
{
    close(fd);
}

uint32_t
mbox_alloc(int fd, unsigned int size, unsigned int align, unsigned int flags)
{
    struct request_alloc {
        mbox_buffer_t buffer;
        union {
            uint32_t size;
            uint32_t handle;
        };
        uint32_t alignment;
        uint32_t flags;
        uint32_t end_tag;
    };

    volatile struct request_alloc __attribute__((aligned(16))) request;
    request.buffer.size = sizeof(struct request_alloc);
    request.buffer.req_code = 0;
    request.buffer.tag.id = 0x0003000c;
    request.buffer.tag.data_size = 3 * sizeof(uint32_t);
    request.buffer.tag.req_code = 0;

    request.size = size;
    request.alignment = align;
    request.flags = flags;

    request.end_tag = 0;

    ioctl(fd, IOCTL_MBOX_PROPERTY, &request);
    return request.handle;
}

uint32_t
mbox_free(int fd, uint32_t handle)
{
    struct request_release {
        mbox_buffer_t buffer;
        union {
            uint32_t handle;
            uint32_t status; // 0 on success
        };
        uint32_t end_tag;
    };

    volatile struct request_release __attribute__((aligned(16))) request;
    request.buffer.size = sizeof(struct request_release);
    request.buffer.req_code = 0;
    request.buffer.tag.id = 0x0003000f;
    request.buffer.tag.data_size = sizeof(uint32_t);
    request.buffer.tag.req_code = 0;

    request.handle = handle;

    request.end_tag = 0;

    ioctl(fd, IOCTL_MBOX_PROPERTY, &request);
    return request.status;
}

uint32_t
mbox_lock(int fd, uint32_t handle)
{
    struct request_lock {
        mbox_buffer_t buffer;
        union {
            uint32_t handle;
            uint32_t bus_addr;
        };
        uint32_t end_tag;
    };

    volatile struct request_lock __attribute__((aligned(16))) request;
    request.buffer.size = sizeof(struct request_lock);
    request.buffer.req_code = 0;
    request.buffer.tag.id = 0x0003000d;
    request.buffer.tag.data_size = sizeof(uint32_t);
    request.buffer.tag.req_code = 0;

    request.handle = handle;

    request.end_tag = 0;

    ioctl(fd, IOCTL_MBOX_PROPERTY, &request);
    return request.bus_addr;
}

uint32_t
mbox_unlock(int fd, uint32_t handle)
{
    struct request_unlock {
        mbox_buffer_t buffer;
        union {
            uint32_t handle;
            uint32_t status; // 0 on success
        };
        uint32_t end_tag;
    };

    volatile struct request_unlock __attribute__((aligned(16))) request;
    request.buffer.size = sizeof(struct request_unlock);
    request.buffer.req_code = 0;
    request.buffer.tag.id = 0x0003000e;
    request.buffer.tag.data_size = sizeof(uint32_t);
    request.buffer.tag.req_code = 0;

    request.handle = handle;

    request.end_tag = 0;

    ioctl(fd, IOCTL_MBOX_PROPERTY, &request);
    return request.status;
}

void *
mbox_map(uint32_t addr, unsigned int size)
{
    unsigned int offset = addr % PAGE_SIZE; // maps must align to 4096
    addr -= offset;
    size += offset;

    int fd;
    if ((fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0) {
        perror_inf();
        perror("Failed to open \"/dev/mem\"");
		return NULL;
    }

    void *map = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, addr);
    if (map == MAP_FAILED) {
        perror_inf();
		perror("Failed mmaping peripheral");
        close(fd);
		return NULL;
	}

    close(fd);
    return (char *)map + offset;
}

void
mbox_unmap(void *ptr, unsigned int size)
{
    intptr_t offset = (intptr_t) ptr % PAGE_SIZE;
    ptr -= offset; // <- ?
    size += offset;

    if (munmap(ptr, size) == -1) {
        perror_inf();
		perror("Failed to munmap");
	}
}

uint32_t
mbox_vc_execute(int fd, uint32_t func_ptr, uint32_t r0, uint32_t r1,
        uint32_t r2, uint32_t r3, uint32_t r4, uint32_t r5)
{
    struct request_execute {
        mbox_buffer_t buffer;
        uint32_t function;
        uint32_t r0;
        uint32_t r1;
        uint32_t r2;
        uint32_t r3;
        uint32_t r4;
        uint32_t r5;
        uint32_t end_tag;
    };

    struct request_execute request;
    request.buffer.size = sizeof(struct request_execute);
    request.buffer.req_code = 0;
    request.buffer.tag.id = 0x00030010;
    request.buffer.tag.data_size = 7 * sizeof(uint32_t);
    request.buffer.tag.req_code = 0;

    request.function = func_ptr; // bus address!
    request.r0 = r0;
    request.r1 = r1;
    request.r2 = r2;
    request.r3 = r3;
    request.r4 = r4;
    request.r5 = r5;

    request.end_tag = 0;

    ioctl(fd, IOCTL_MBOX_PROPERTY, &request);
    return request.function; // request returns r0, but in the place of function
}

uint32_t
mbox_qpu_enable(int fd, uint32_t state)
{
    struct request_qpu_enable {
        mbox_buffer_t buffer;
        uint32_t state;
        uint32_t end_tag;
    };

    struct request_qpu_enable request;
    request.buffer.size = sizeof(struct request_qpu_enable);
    request.buffer.req_code = 0;
    request.buffer.tag.id = 0x00030012;
    request.buffer.tag.data_size = sizeof(uint32_t);
    request.buffer.tag.req_code = 0;

    request.state = state;

    request.end_tag = 0;

    ioctl(fd, IOCTL_MBOX_PROPERTY, &request);
    return request.state;
}

uint32_t
mbox_qpu_execute(int fd, uint32_t num_qpus, uint32_t control,
    uint32_t noflush, uint32_t timeout)
{
    struct request_qpu_execute {
        mbox_buffer_t buffer;
        uint32_t num_qpus;
        uint32_t control;
        uint32_t noflush;
        uint32_t timeout;
        uint32_t end_tag;
    };

    struct request_qpu_execute request;
    request.buffer.size = sizeof(struct request_qpu_execute);
    request.buffer.req_code = 0;
    request.buffer.tag.id = 0x00030011;
    request.buffer.tag.data_size = 4 * sizeof(uint32_t);
    request.buffer.tag.req_code = 0;

    request.num_qpus = num_qpus;
    request.control = control;
    request.noflush = noflush;
    request.timeout = timeout;

    request.end_tag = 0;

    ioctl(fd, IOCTL_MBOX_PROPERTY, &request);
    return request.num_qpus;
}
