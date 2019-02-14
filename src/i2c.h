#ifndef _I2C_H_
#define _I2C_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define I2C_BASE        0x20804000 /* BSC1 */
#define I2C_BLOCK_SIZE  0x20

volatile uint32_t *i2c_base_ptr;

struct i2c_register_map {
    uint32_t C;
    uint32_t S;
    uint32_t DLEN;
    uint32_t A;
    uint32_t FIFO;
    uint32_t DIV;
    uint32_t DEL;
    uint32_t CLKT;
};
#define I2C     ((struct i2c_register_map *)i2c_base_ptr)

typedef struct {
    uint8_t addr: 7;
    uint16_t div;
} i2c_config_t;

uint32_t *  i2c_map(void);
void        i2c_unmap(void);

void i2c_configure(i2c_config_t *config);

extern void     i2c_transfer_start(void);
extern void     i2c_transfer_stop(void);

extern void     i2c_transfer_byte(uint8_t byte);
extern uint8_t  i2c_receive_byte(void);

extern void     i2c_transfer_data(uint8_t *data, uint16_t dlen);
extern void     i2c_receive_data(uint8_t *buffer, uint16_t dlen);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _I2C_H_ */
