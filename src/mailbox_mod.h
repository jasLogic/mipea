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
* https://github.com/raspberrypi/userland/blob/master/host_applications/linux/apps/hello_pi/hello_fft/mailbox.h *
********************************************************************************/

#ifndef _MAILBOX_MOD_H_
#define _MAILBOX_MOD_H_

#include <stdint.h>

#ifdef  __cplusplus
extern "C" {
#endif//__cplusplus

// the macros are for backward compatibility
#define mbox_alloc  mem_alloc
#define mbox_free   mem_free
#define mbox_lock   mem_lock
#define mbox_unlock mem_unlock
#define mbox_map    mapmem
#define mbox_unmap  unmapmem
#define mbox_vc_execute     execute_code
#define mbox_qpu_enable     qpu_enable
#define mbox_qpu_execute    execute_qpu


#define MAJOR_NUM 100
#define IOCTL_MBOX_PROPERTY _IOWR(MAJOR_NUM, 0, uint8_t *)
#define DEVICE_FILE_NAME    "/dev/vcio"

#define PAGE_SIZE       4096
#define BUS_TO_PHYS(x)  ((x) & ~0xC0000000)

// From: https://github.com/raspberrypi/firmware/wiki/Mailbox-property-interface#allocate-memory
#define MEM_FLAG_DISCARDABLE        0x01 // can be resized to 0 at any time. Use for cached data
#define MEM_FLAG_NORMAL             0x00 // normal allocating alias. Don't use from ARM
#define MEM_FLAG_DIRECT             0x04 // 0xC alias uncached
#define MEM_FLAG_COHERENT           0x08 // 0x8 alias. Non-allocating in L2 but coherent
#define MEM_FLAG_L1_NONALLOCATING   (MEM_FLAG_DIRECT | MEM_FLAG_COHERENT) // Allocating in L2
#define MEM_FLAG_ZERO               0x10 // initialise buffer to all zeros
#define MEM_FLAG_NO_INIT            0x20 // don't initialise (default is initialise to all ones
#define MEM_FLAG_HINT_PERMALOCK     0x40 // Likely to be locked for long periods of time

typedef struct {
    uint32_t id;
    uint32_t data_size;
    uint32_t req_code; // 31st bit cleared for requests
} mbox_tag_t;

typedef struct {
    uint32_t size;
    uint32_t req_code; // 0x00000000 for requests
    mbox_tag_t tag;
} mbox_buffer_t;

int     mbox_open(void);
void    mbox_close(int fd);

uint32_t mbox_alloc(int fd, unsigned int size, unsigned int align, unsigned int flags);
uint32_t mbox_free(int fd, uint32_t handle);

uint32_t mbox_lock(int fd, uint32_t handle);
uint32_t mbox_unlock(int fd, uint32_t handle);

void *  mbox_map(uint32_t addr, unsigned int size);
void    mbox_unmap(void *ptr, unsigned int size);

uint32_t mbox_vc_execute(int fd, uint32_t func_ptr, uint32_t r0, uint32_t r1,
    uint32_t r2, uint32_t r3, uint32_t r4, uint32_t r5);
uint32_t mbox_qpu_enable(int fd, uint32_t state);
uint32_t mbox_qpu_execute(int fd, uint32_t num_qpus, uint32_t control,
    uint32_t noflush, uint32_t timeout);

#ifdef  __cplusplus
}
#endif//__cplusplus

#endif//_MAILBOX_MOD_H_
