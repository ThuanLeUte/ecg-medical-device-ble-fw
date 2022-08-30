/**
 * @file       ads1292.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-07-31
 * @author     Thuan Le
 * @brief      Driver support ADS1292 (Analog Front-End for Biopotential Measurements)
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "ads1292.h"
#include "ads1292_def.h"

/* Private defines ---------------------------------------------------- */
// ADS1292 COMMANDS
#define ADS1292_CMD_WAKEUP                  (0x02) // Wake-up from standby mode
#define ADS1292_CMD_STANDBY                 (0x04) // Enter Standby mode
#define ADS1292_CMD_RESET                   (0x06) // Reset the device
#define ADS1292_CMD_START                   (0x08) // Start and restart (synchronize) conversions
#define ADS1292_CMD_STOP                    (0x0A) // Stop conversion
#define ADS1292_CMD_RDATAC                  (0x10) // Enable Read Data Continuous mode (default mode at power-up)
#define ADS1292_CMD_SDATAC                  (0x11) // Stop Read Data Continuous mode
#define ADS1292_CMD_RDATA                   (0x12) // Read data by command; Supports multiple read back
#define ADS1292_CMD_RREG                    (0x20) // (also = 00100000) is the first opcode that the address must be added to for RREG communication
#define ADS1292_CMD_WREG                    (0x40) // 01000000 in binary (Datasheet, pg. 35)

#define ADS1292_ID_ADS1292R                 (0x73)

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
static base_status_t m_ads1292_read_reg(ads1292_t *me, uint8_t reg, uint8_t *p_data, uint32_t len);
static base_status_t m_ads1292_write_reg(ads1292_t *me, uint8_t reg, uint8_t data);
static base_status_t m_ads1292_send_cmd(ads1292_t *me, uint8_t cmd);

/* Function definitions ----------------------------------------------- */
base_status_t ads1292_init(ads1292_t *me)
{
  uint8_t revision_id, value_0, value_1, value_2;

  value_0 = 0xFF;
  value_1 = 0xFF;
  value_2 = 0xFF;

  if ((me == NULL) || (me->spi_transmit_receive == NULL))
    return BS_ERROR;
  
  bsp_delay_ms(2000);

  bsp_gpio_write(IO_AFE_RST, 1);
  bsp_delay_ms(100);
  bsp_gpio_write(IO_AFE_RST, 0);
  bsp_delay_ms(100);
  bsp_gpio_write(IO_AFE_RST, 1);
  bsp_delay_ms(1000);

  bsp_delay_ms(100);

  bsp_gpio_write(IO_AFE_START, 0);
  bsp_delay_ms(20);

  bsp_gpio_write(IO_AFE_START, 1);
  bsp_delay_ms(20);

  bsp_gpio_write(IO_AFE_START, 0);
  bsp_delay_ms(20);

  m_ads1292_send_cmd(me, ADS1292_CMD_START);
  m_ads1292_send_cmd(me, ADS1292_CMD_STOP);
  bsp_delay_ms(50);
  m_ads1292_send_cmd(me, ADS1292_CMD_SDATAC);

  CHECK_STATUS(m_ads1292_read_reg(me, ADS1292_REG_ID, &revision_id, 1));

  NRF_LOG_ERROR("Revision ID: %d", revision_id);
  if (ADS1292_ID_ADS1292R != revision_id)
    return BS_ERROR;

  // Write init setting
  // for (uint8_t i = 0; i < (sizeof(ADS1292_SETTING_LIST) / sizeof(ADS1292_SETTING_LIST[0])); i++)
  // {
  //   CHECK_STATUS(m_ads1292_write_reg(me, ADS1292_SETTING_LIST[i].reg, ADS1292_SETTING_LIST[i].value));

  //   CHECK_STATUS(m_ads1292_read_reg(me, ADS1292_SETTING_LIST[i].reg, &value_0, 1));
  //   bsp_delay_ms(10);

  //   if (value_0 != ADS1292_SETTING_LIST[i].value)
  //     return BS_ERROR;
  // }

  CHECK_STATUS(m_ads1292_read_reg(me, ADS1292_REG_CONFIG1, &value_0, 1));
  CHECK_STATUS(m_ads1292_write_reg(me, ADS1292_REG_CONFIG1, 0x00));
  CHECK_STATUS(m_ads1292_read_reg(me, ADS1292_REG_CONFIG1, &value_0, 1));
  bsp_delay_ms(200);
  if (value_0 != 0x00)
    return BS_ERROR;

  CHECK_STATUS(m_ads1292_read_reg(me, ADS1292_REG_CONFIG2, &value_0, 1));
  CHECK_STATUS(m_ads1292_write_reg(me, ADS1292_REG_CONFIG2, 0xA0));
  CHECK_STATUS(m_ads1292_read_reg(me, ADS1292_REG_CONFIG2, &value_0, 1));
  bsp_delay_ms(200);

  if (value_0 != 0xA0)
    return BS_ERROR;

  CHECK_STATUS(m_ads1292_read_reg(me, ADS1292_REG_LOFF, &value_0, 1));
  CHECK_STATUS(m_ads1292_write_reg(me, ADS1292_REG_LOFF, 0x10));
  CHECK_STATUS(m_ads1292_read_reg(me, ADS1292_REG_LOFF, &value_0, 1));
  bsp_delay_ms(200);

  if (value_0 != 0x10)
    return BS_ERROR;

  CHECK_STATUS(m_ads1292_read_reg(me, ADS1292_REG_CH1SET, &value_0, 1));
  CHECK_STATUS(m_ads1292_write_reg(me, ADS1292_REG_CH1SET, 0x40));
  CHECK_STATUS(m_ads1292_read_reg(me, ADS1292_REG_CH1SET, &value_0, 1));
  bsp_delay_ms(200);

  if (value_0 != 0x40)
    return BS_ERROR;

  CHECK_STATUS(m_ads1292_read_reg(me, ADS1292_REG_CH2SET, &value_0, 1));
  CHECK_STATUS(m_ads1292_write_reg(me, ADS1292_REG_CH2SET, 0x60));
  CHECK_STATUS(m_ads1292_read_reg(me, ADS1292_REG_CH2SET, &value_0, 1));
  bsp_delay_ms(200);

  if (value_0 != 0x60)
    return BS_ERROR;

  CHECK_STATUS(m_ads1292_read_reg(me, ADS1292_REG_RLDSENS, &value_0, 1));
  CHECK_STATUS(m_ads1292_write_reg(me, ADS1292_REG_RLDSENS, 0x2C));
  CHECK_STATUS(m_ads1292_read_reg(me, ADS1292_REG_RLDSENS, &value_0, 1));
  bsp_delay_ms(200);

  if (value_0 != 0x2C)
    return BS_ERROR;

  CHECK_STATUS(m_ads1292_read_reg(me, ADS1292_REG_LOFFSENS, &value_0, 1));
  CHECK_STATUS(m_ads1292_write_reg(me, ADS1292_REG_LOFFSENS, 0x00));
  CHECK_STATUS(m_ads1292_read_reg(me, ADS1292_REG_LOFFSENS, &value_0, 1));
  bsp_delay_ms(200);

  if (value_0 != 0x00)
    return BS_ERROR;

  CHECK_STATUS(m_ads1292_read_reg(me, ADS1292_REG_RESP1, &value_0, 1));
  CHECK_STATUS(m_ads1292_write_reg(me, ADS1292_REG_RESP1, 0xF2));
  CHECK_STATUS(m_ads1292_read_reg(me, ADS1292_REG_RESP1, &value_0, 1));
  bsp_delay_ms(200);

  if (value_0 != 0xF2)
    return BS_ERROR;

  CHECK_STATUS(m_ads1292_read_reg(me, ADS1292_REG_RESP2, &value_0, 1));
  CHECK_STATUS(m_ads1292_write_reg(me, ADS1292_REG_RESP2, 0x03));
  CHECK_STATUS(m_ads1292_read_reg(me, ADS1292_REG_RESP2, &value_0, 1));
  bsp_delay_ms(200);

  if (value_0 != 0x03)
    return BS_ERROR;

  CHECK_STATUS(m_ads1292_read_reg(me, 0x0B, &value_0, 1));
  CHECK_STATUS(m_ads1292_write_reg(me, 0x0B, 0x0C));
  CHECK_STATUS(m_ads1292_read_reg(me, 0x0B, &value_0, 1));
  bsp_delay_ms(200);

  if (value_0 != 0x0C)
    return BS_ERROR;

  bsp_gpio_write(IO_AFE_START, 1);
  bsp_delay_ms(200);
  CHECK_STATUS(m_ads1292_send_cmd(me, ADS1292_CMD_RDATAC));
//  m_ads1292_send_cmd(me, ADS1292_CMD_START);

  return BS_OK;
}

base_status_t ads1292_start_convert(ads1292_t *me, bool enable)
{
//  return m_ads1292_write_reg(me, ADS1292_REG_CONFIG, enable);
}

base_status_t ads1292_read_ecg(ads1292_t *me, uint8_t *data)
{
//  return m_ads1292_read_reg(me, ADS1292_REG_DATA_CH1_ECG_H, data, ADS_NUM_CHANNEL * 3);
}

/* Private function definitions ---------------------------------------- */
/**
 * @brief         ADS1292 read register
 *
 * @param[in]     me      Pointer to handle of ADS1292 module.
 * @param[in]     reg     Register
 * @param[in]     p_data  Pointer to handle of data
 * @param[in]     len     Data length
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
static base_status_t m_ads1292_read_reg(ads1292_t *me, uint8_t reg, uint8_t *p_data, uint32_t len)
{
  uint8_t trx[3];

  trx[0] = (0x1F & reg) | ADS1292_CMD_RREG; // 001r rrrr
  trx[1] = 0;                               // 000n nnnn
  trx[2] = 0;

  m_ads1292_send_cmd(me, ADS1292_CMD_SDATAC);

  bsp_gpio_write(IO_AFE_CS, 0);
  CHECK(0 == me->spi_transmit_receive(trx, trx, 3), BS_ERROR);
  bsp_delay_ms(2); // Decode delay
  bsp_gpio_write(IO_AFE_CS, 1);

  *p_data = trx[2];

  return BS_OK;
}

/**
 * @brief         ADS1292 read register
 *
 * @param[in]     me      Pointer to handle of ADS1292 module.
 * @param[in]     reg     Register
 * @param[in]     data    Data
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
static base_status_t m_ads1292_write_reg(ads1292_t *me, uint8_t reg, uint8_t data)
{
  uint8_t tx[3];

  switch (reg)
  {
  
    case 1: data = data & 0x87;
        break;
        
    case 2: data = data & 0xFB;
        data |= 0x80;
        break;
        
    case 3: data = data & 0xFD;
        data |= 0x10;
        break;
        
    case 7: data = data & 0x3F;
        break;
        
    case 8: data = data & 0x5F;
        break;
        
    case 9:data |= 0x02;
        break;
        
    case 10:data = data & 0x87;
        data |= 0x01;
        break;
        
    case 11:data = data & 0x0F;
        break;
        
    default:break;
  }

  tx[0] = (0x1F & reg) | ADS1292_CMD_WREG; // 001r rrrr
  tx[1] = 0;                               // 000n nnnn
  tx[2] = data;

  m_ads1292_send_cmd(me, ADS1292_CMD_SDATAC);
  
  bsp_gpio_write(IO_AFE_CS, 0);
  CHECK(0 == me->spi_transmit_receive(tx, NULL, 3), BS_ERROR);
  bsp_delay_ms(2); // Decode delay
  bsp_gpio_write(IO_AFE_CS, 1);

  return BS_OK;
}

/**
 * @brief         ADS1292 send command
 *
 * @param[in]     me      Pointer to handle of ADS1292 module.
 * @param[in]     cmd     Comamnd
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
static base_status_t m_ads1292_send_cmd(ads1292_t *me, uint8_t cmd)
{
  bsp_gpio_write(IO_AFE_CS, 0);
  CHECK(0 == me->spi_transmit_receive(&cmd, NULL, 1), BS_ERROR);
  bsp_delay_ms(2); // Decode delay
  bsp_gpio_write(IO_AFE_CS, 1);

  return BS_OK;
}

base_status_t m_ads1292_read_data(ads1292_t *me, uint8_t *p_data, uint16_t len)
{
  bsp_gpio_write(IO_AFE_CS, 0);
  CHECK(0 == me->spi_transmit_receive(p_data, p_data, len), BS_ERROR);
  bsp_delay_ms(2); // Decode delay
  bsp_gpio_write(IO_AFE_CS, 1);

  return BS_OK;
}

/* End of file -------------------------------------------------------- */
