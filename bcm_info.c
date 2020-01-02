#include <stdio.h>
#include <bcm_host.h>

int main(void) {
        printf("0x%X\n0x%X\n0x%X\n",
                bcm_host_get_peripheral_address(),
                bcm_host_get_model_type(),
                bcm_host_get_processor_id()
        );
        return 0;
}
