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
#define ADS1292_READ_BIT                    (0x20)
#define ADS1292_WRITE_BIT                   (0x40)
#define ADS1292_REVID_VALUE                 (0x01)

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
static base_status_t m_ads1292_write_reg(ads1292_t *me, uint8_t reg, uint8_t data);
base_status_t m_ads1292_send_cmd(ads1292_t *me, uint8_t cmd);

/* Function definitions ----------------------------------------------- */
base_status_t ads1292_init(ads1292_t *me)
{
  uint8_t revision_id;

  bsp_gpio_write(IO_AFE_RST, 0);
  bsp_delay_ms(100);
  bsp_gpio_write(IO_AFE_RST, 1);
  bsp_delay_ms(100);
  bsp_gpio_write(IO_AFE_START, 1);

  if ((me == NULL) || (me->spi_transmit_receive == NULL))
    return BS_ERROR;

  m_ads1292_read_reg(me, ADS1292_REG_ID, &revision_id, 1);
	
	m_ads1292_read_reg(me, ADS1292_REG_ID, &revision_id, 1);
	
	m_ads1292_read_reg(me, ADS1292_REG_ID, &revision_id, 1);

  NRF_LOG_ERROR("Revision ID: %d", revision_id);
  if (ADS1292_REVID_VALUE != revision_id)
    return BS_ERROR;

//  // Write init setting
//  for (uint8_t i = 0; i < (sizeof(ADS1292_SETTING_LIST) / sizeof(ADS1292_SETTING_LIST[0])); i++)
//  {
//    m_ads1292_write_reg(me, ADS1292_SETTING_LIST[i].reg, ADS1292_SETTING_LIST[i].value);
//  }

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
base_status_t m_ads1292_read_reg(ads1292_t *me, uint8_t reg, uint8_t *p_data, uint32_t len)
{
  uint8_t trx[3];

  trx[0] = (0x1F & reg) | ADS1292_READ_BIT; // 001r rrrr
  trx[1] = 0;                               // 000n nnnn
  trx[2] = 0;

  m_ads1292_send_cmd(me, 0x11);

  bsp_gpio_write(IO_AFE_CS, 0);

  CHECK(0 == me->spi_transmit_receive(trx, trx, 3), BS_ERROR);

  bsp_delay_ms(2);
  bsp_gpio_write(IO_AFE_CS, 1);

  *p_data = trx[2];

  return BS_OK;
}

base_status_t m_ads1292_send_cmd(ads1292_t *me, uint8_t cmd)
{
  bsp_gpio_write(IO_AFE_CS, 0);

  CHECK(0 == me->spi_transmit_receive(&cmd, NULL, 1), BS_ERROR);

  bsp_delay_ms(2);
  bsp_gpio_write(IO_AFE_CS, 1);

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

  tx[0] = (0x1F & reg) | ADS1292_WRITE_BIT; // 001r rrrr
  tx[1] = 0;                                // 000n nnnn
  tx[2] = data;

  bsp_gpio_write(IO_AFE_CS, 0);
  
  CHECK(0 == me->spi_transmit_receive(tx, NULL, 3), BS_ERROR);

  bsp_delay_ms(2);
  bsp_gpio_write(IO_AFE_CS, 1);

  return BS_OK;
}

/* End of file -------------------------------------------------------- */
