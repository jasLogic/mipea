project('mipea', 'c',
        version: '2.1.4',
        license: 'BSD-3-Clause',
        meson_version : '>= 0.50.0',
)

cc = meson.get_compiler('c')

# check for needed headers
headers = [
        'fcntl.h',
        'stddef.h',
        'stdint.h',
        'stdlib.h',
        'sys/ioctl.h',
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

bcm_host_header_dir = include_directories('/opt/vc/include')
bcm_host_header = cc.has_header(
        'bcm_host.h',
        include_directories: bcm_host_header_dir,
        required: false
)
mipea_conf.set10('HAVE_BCM_HOST_HEADER', bcm_host_header)

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
                include_directories: bcm_host_header_dir
        )
        if result.compiled() and result.returncode() == 0
                vals = result.stdout().strip().split('\n')
                mipea_conf.set('PERIPHERAL_BASE', vals[0])
                mipea_conf.set('RASPBERRYPI_MODEL', vals[1])
                mipea_conf.set('BCM_PROCESSOR', vals[2])
        else
                warning('error reading info from bcm_host with bcm_info.c, info is manually gathered from /proc/cpuinfo')
                info_manually = true
        endif
else
        warning('bcm_host library not found, info is manually gathered /proc/cpuinfo')
        info_manually = true
endif

if info_manually
        message('running bcm_info.sh')
        result = run_command('bcm_info.sh')
        if result.returncode() == 0
                vals = result.stdout().strip().split('\n')
                mipea_conf.set('PERIPHERAL_BASE', vals[0])
                mipea_conf.set('RASPBERRYPI_MODEL', vals[1])
                mipea_conf.set('BCM_PROCESSOR', vals[2])
        else
                # TODO: long error text and explanation
                error('could not gather info from /proc/cpuinfo with bcm_info.sh')
        endif
endif

configure_file(input: 'config.h.in', output: 'config.h', configuration: mipea_conf)
config_inc = include_directories('.')
# TODO: config.h in build ordner :(

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
        #include_directories: config_inc,
        version: meson.project_version(),
        install: true
)
install_headers(headers, subdir: 'mipea')

# TODO: unit tests: https://mesonbuild.com/Unit-tests.html
