project('mipea', 'c',
        version: '2.1.4',
        license: 'BSD-3-Clause',
        meson_version : '>= 0.50.0',
)

cc = meson.get_compiler('c')

# check for needed headers
headers = [
        'errno.h',
        'fcntl.h',
        'stddef.h',
        'stdint.h',
        'stdio.h',
        'stdlib.h',
        'sys/ioctl.h',
        'sys/mman.h',
        'sys/stat.h',
        'unistd.h',
]
foreach header: headers
        cc.has_header(header, required: true)
endforeach

# check for library functions
functions = [
        'mmap',
        'munmap',
]
foreach function: functions
        if not cc.has_function(function)
                error('C function \'' + function + '\' not found')
        endif
endforeach

# check for header symbols
header_symbols = {
        'stddef.h': ['size_t'],
        'stdint.h': [
                'int8_t',
                'uint8_t',
                'uint16_t',
                'uint32_t',
                'uint64_t',
        ],
}
foreach header, symbols: header_symbols
        foreach symbol: symbols
                cc.has_header_symbol(header, symbol, required: true)
        endforeach
endforeach

# TODO: check and set inline -> spi.c, timer.c

# create config.h file
mipea_conf = configuration_data()

# check which board we are on
message('trying to get info from bcm_host library')

bcm_host_header = cc.has_header(
        'bcm_host.h',
        args: '-I/opt/vc/include',
        required: false
)

bcm_host_dep = cc.find_library(
        'bcm_host',
        dirs: '/opt/vc/lib',
        required: false
)

info_manually = false
if bcm_host_header and bcm_host_dep.found()
        # with bcm_host.h
        result = cc.run(
                files('bcm_info.c'),
                dependencies: bcm_host_dep,
                args: '-I/opt/vc/include'
        )
        if result.compiled() and result.returncode() == 0
                vals = result.stdout().strip().split('\n')
                mipea_conf.set('MIPEA_PERIPHERAL_BASE', vals[0])
                mipea_conf.set('MIPEA_RASPBERRYPI_MODEL', vals[1])
                mipea_conf.set('MIPEA_BCM_HOST_PROCESSOR', vals[2])
        else
                warning('error reading info from bcm_host with bcm_info.c, info is manually gathered from /proc/cpuinfo and hard coded')
                info_manually = true
        endif
else
        warning('bcm_host library not found, info is manually gathered from /proc/cpuinfo and hard coded')
        info_manually = true
endif

if info_manually
        message('running bcm_info.sh')
        result = run_command('./bcm_info.sh')
        if result.returncode() == 0
                vals = result.stdout().strip().split('\n')
                mipea_conf.set('MIPEA_PERIPHERAL_BASE', -1)
                mipea_conf.set('MIPEA_RASPBERRYPI_MODEL', vals[0])
                mipea_conf.set('MIPEA_BCM_HOST_PROCESSOR', vals[1])
        else
                warning('''
could not gather info from /proc/cpuinfo with bcm_info.sh
IMPORTANT: For the program to compile correctly go into the generated config.h
and define RASPBERRYPI_MODEL and BCM_PROCESSOR.
The correct values for these are defined here
(https://github.com/raspberrypi/firmware/blob/master/opt/vc/include/bcm_host.h)
and here
(https://www.raspberrypi.org/documentation/hardware/raspberrypi/revision-codes/README.md)
''')
                mipea_conf.set('MIPEA_PERIPHERAL_BASE', -1)
                mipea_conf.set('MIPEA_RASPBERRYPI_MODEL', -1)
                mipea_conf.set('MIPEA_BCM_HOST_PROCESSOR', -1)
        endif
endif

configure_file(
        configuration: mipea_conf,
        input: 'config.h.in',
        output: 'mipeaconfig.h',
        install: true,
        install_dir: 'include/mipea'
)
config_inc = include_directories('.')

srcs = [
        'src/clock_manager.c',
        'src/gpio.c',
        'src/mailbox_mod.c',
        'src/peripherals.c',
        'src/spi.c',
        'src/dma.c',
        'src/i2c.c',
        'src/mipea.c',
        'src/pwm.c',
        'src/timer.c'
]
headers = [
        'src/clock_manager.h',
        'src/dma.h',
        'src/gpio.h',
        'src/i2c.h',
        'src/mailbox_mod.h',
        'src/mipea.h',
        'src/peripherals.h',
        'src/pwm.h',
        'src/spi.h',
        'src/timer.h'
]

shared_library('mipea', srcs,
        include_directories: config_inc,
        version: meson.project_version(),
        install: true
)
install_headers(headers, subdir: 'mipea')

# TODO: unit tests: https://mesonbuild.com/Unit-tests.html
