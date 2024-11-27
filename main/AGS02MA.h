#include "esp_err.h"

#define ADDRESS_W 0x34
#define ADDRESS_R 0x35

#define ACK_CHECK_EN 0x1            /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS 0x0           /*!< I2C master will not check ack from slave */

#define ACK_VAL 0x0                 /*!< I2C ack value */
#define NACK_VAL 0x1                /*!< I2C nack value */

#define AGS02MA_VERSION_REG 0x11 

esp_err_t AGi2cinit(void);

uint32_t getTVOCdata(void);

uint32_t getFirmwareVersion(void);

uint32_t getGasResistance(void);