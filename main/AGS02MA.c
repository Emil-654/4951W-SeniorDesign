/*
*  ESP32 Driver for AGS02MA sensor
*
*
*/


#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "AGS02MA.h"

esp_err_t AGi2cinit(void){
        i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = 21,         
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = 22,         
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 20000,  
        
    };

    esp_err_t err = i2c_param_config(I2C_NUM_0, &conf);
    if (err != ESP_OK) {
            return err;
        }

    return i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);
}


uint32_t getTVOCdata(void){


int len = 5;

  uint8_t data[5];
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, (0x1A << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
  i2c_master_write_byte(cmd, (0x00) , ACK_CHECK_EN);
  i2c_master_stop(cmd);
  esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 50 / portTICK_PERIOD_MS);

vTaskDelay(31/ portTICK_PERIOD_MS);

  cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, (0x1A << 1) | I2C_MASTER_READ, ACK_CHECK_EN);
  if (len > 1) {
        i2c_master_read(cmd, data, len - 1, ACK_VAL);
    }
  i2c_master_read_byte(cmd, data+len-1, NACK_VAL);
  i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 50 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    if (ret == ESP_OK) {
        for (int i = 0; i < len; i++) {
            printf("0x%02x ", data[i]);
            if ((i + 1) % 16 == 0) {
                printf("\r\n");
            }
        }
        if (len % 16) {
            printf("\r\n");
        }
    } else if (ret == ESP_ERR_TIMEOUT) {
        ESP_LOGW("test", "Bus is busy");
    } else {
        ESP_LOGW("test", "Read failed");
    }

    uint32_t temp = data[0];
  temp <<= 8;
  temp |= data[1];
  temp <<= 8;
  temp |= data[2];
  temp <<= 8;
  temp |= data[3];

  return temp & 0x00FFFFFF;

}

uint32_t getFirmwareVersion(void) {

int len = 5;

  uint8_t data[5];
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, (0x1A << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
  i2c_master_write_byte(cmd, (0x11) , ACK_CHECK_EN);
  i2c_master_stop(cmd);
  i2c_master_cmd_begin(I2C_NUM_0, cmd, 50 / portTICK_PERIOD_MS);

vTaskDelay(31/ portTICK_PERIOD_MS);

  cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, (0x1A << 1) | I2C_MASTER_READ, ACK_CHECK_EN);
  if (len > 1) {
        i2c_master_read(cmd, data, len - 1, ACK_VAL);
    }
  i2c_master_read_byte(cmd, data+len-1, NACK_VAL);
  i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM_0, cmd, 50 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    uint32_t temp = data[0];
  temp <<= 8;
  temp |= data[1];
  temp <<= 8;
  temp |= data[2];
  temp <<= 8;
  temp |= data[3];

  return temp;
}

uint32_t getGasResistance(void){

int len = 5;

  uint8_t data[5];
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, (0x1A << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
  i2c_master_write_byte(cmd, (0x20) , ACK_CHECK_EN);
  i2c_master_stop(cmd);
  esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 50 / portTICK_PERIOD_MS);

vTaskDelay(31/ portTICK_PERIOD_MS);

  cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, (0x1A << 1) | I2C_MASTER_READ, ACK_CHECK_EN);
  if (len > 1) {
        i2c_master_read(cmd, data, len - 1, ACK_VAL);
    }
  i2c_master_read_byte(cmd, data+len-1, NACK_VAL);
  i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 50 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    if (ret == ESP_OK) {
        for (int i = 0; i < len; i++) {
            printf("0x%02x ", data[i]);
            if ((i + 1) % 16 == 0) {
                printf("\r\n");
            }
        }
        if (len % 16) {
            printf("\r\n");
        }
    } else if (ret == ESP_ERR_TIMEOUT) {
        ESP_LOGW("test", "Bus is busy");
    } else {
        ESP_LOGW("test", "Read failed");
    }

    uint32_t temp = data[0];
  temp <<= 8;
  temp |= data[1];
  temp <<= 8;
  temp |= data[2];
  temp <<= 8;
  temp |= data[3];

  return temp *100;


}