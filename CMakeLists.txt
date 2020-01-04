cmake_minimum_required(VERSION 3.0.2)

project(mipea
        LANGUAGES C
        VERSION 2.1.4
        DESCRIPTION "minimalistic peripheral access library for the Raspberry Pi"
        HOMEPAGE_URL "https://github.com/jasLogic/mipea"
)
set(CMAKE_BUILD_TYPE Release)

# platform checks

# check for needed headers
include(CheckIncludeFile)
set(headers
        errno.h
        fcntl.h
        stddef.h
        stdint.h
        stdio.h
        stdlib.h
        sys/ioctl.h
        sys/mman.h
        sys/stat.h
        unistd.h
)
foreach(header ${headers})
        check_include_file(${header} HAVE_${header})
        if(NOT HAVE_${header})
                message(FATAL_ERROR "C header file \"${header}\" not found")
        endif()
endforeach()

# check for functions
include(CheckSymbolExists)
check_symbol_exists(mmap "sys/mman.h" HAVE_MMAP)
if(NOT HAVE_MMAP)
        message(FATAL_ERROR "C function \"mmap\" not found")
endif()
check_symbol_exists(munmap "sys/mman.h" HAVE_MUNMAP)
if(NOT HAVE_MUNMAP)
        message(FATAL_ERROR "C function \"munmap\" not found")
endif()

# TODO: cant get them running
# check for header symbols
#check_symbol_exists(size_t "inttypes.h" HAVE_SIZE_T)
#if (NOT HAVE_SIZE_T)
#        message(FATAL_ERROR "C symbol \"size_t\" not found")
#endif()

#foreach(TYPE int8_t uint8_t uint16_t uint32_t uint64_t)
#        check_symbol_exists(${TYPE} "stdint.h" HAVE_${TYPE})
#        if (NOT HAVE_${TYPE})
#                message(FATAL_ERROR "C symbol \"${TYPE}\" not found")
#        endif()
#endforeach()

execute_process(
        COMMAND "./bcm_info.sh"
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
        ERROR_VARIABLE error
)
if(result EQUAL 0)
        string(STRIP ${output} output)
        string(REPLACE "\n" ";" output ${output})

        set(MIPEA_PERIPHERAL_BASE -1)
        list(GET output 0 var)
        set(MIPEA_RASPBERRYPI_MODEL ${var})
        list(GET output 1 var)
        set(MIPEA_BCM_HOST_PROCESSOR ${var})
else()
        message(WARNING
                "could not gather info from /proc/cpuinfo with bcm_info.sh\n"
                "IMPORTANT: For the program to compile correctly go into the "
                "generated config.h and define RASPBERRYPI_MODEL and BCM_PROCESSOR.\n"
                "The correct values for these are defined here "
                "(https://github.com/raspberrypi/firmware/blob/master/opt/vc/include/bcm_host.h) "
                "and here "
                "(https://www.raspberrypi.org/documentation/hardware/raspberrypi/revision-codes/README.md)"
        )
endif()

configure_file(config.h.in mipeaconfig.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(sources
        src/clock_manager.c
        src/dma.c
        src/gpio.c
        src/i2c.c
        src/mailbox_mod.c
        src/mipea.c
        src/peripherals.c
        src/pwm.c
        src/spi.c
        src/timer.c
)
set(headers
        src/clock_manager.h
        src/gpio.h
        src/mailbox_mod.h
        src/peripherals.h
        src/spi.h
        src/dma.h
        src/i2c.h
        src/mipea.h
        src/pwm.h
        src/timer.h
        ${CMAKE_CURRENT_BINARY_DIR}/mipeaconfig.h
)

add_library(mipea SHARED "${sources}")
set_target_properties(mipea PROPERTIES PUBLIC_HEADER "${headers}")

include(GNUInstallDirs)
install(
        TARGETS mipea
        PUBLIC_HEADER
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/mipea"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)
