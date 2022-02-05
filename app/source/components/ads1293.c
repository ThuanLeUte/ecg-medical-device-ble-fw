/**
 * @file       ads1293.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-07-31
 * @author     Thuan Le
 * @brief      Driver support ADS1293 (Analog Front-End for Biopotential Measurements)
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "ads1293.h"
#include "ads1293_def.h"
#include "nrf_delay.h"

/* Private defines ---------------------------------------------------- */
#define ADS1293_READ_BIT                    (0x80)
#define ADS1293_WRITE_BIT                   (0x7F)
#define ADS1293_REVID_VALUE                 (0x01)

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
// static base_status_t m_ads1293_read_reg(ads1293_t *me, uint8_t reg, uint8_t *p_data, uint32_t len);
static base_status_t m_ads1293_write_reg(ads1293_t *me, uint8_t reg, uint8_t data);

static bool m_init_success = false;

/* Function definitions ----------------------------------------------- */
base_status_t ads1293_init(ads1293_t *me)
{
  uint8_t revision_id;

  if ((me == NULL) || (me->spi_transmit_receive == NULL))
    return BS_ERROR;

  m_ads1293_read_reg(me, ADS1293_REG_REVID, &revision_id, 1);

  NRF_LOG_ERROR("Revision ID: %d", revision_id);
  if (ADS1293_REVID_VALUE != revision_id)
    return BS_ERROR;

  // Write init setting
  m_ads1293_write_reg(me, ADS1293_REG_CONFIG, 0);
  nrf_delay_ms(1);
  
  for (uint8_t i = 0; i < (sizeof(ADS1293_SETTING_LIST) / sizeof(ADS1293_SETTING_LIST[0])); i++)
  {
    if(ADS1293_SETTING_LIST[i].reg != ADS1293_REG_CONFIG)
    {
      m_ads1293_write_reg(me, ADS1293_SETTING_LIST[i].reg, ADS1293_SETTING_LIST[i].value);
      nrf_delay_ms(1);
    }
  }

  m_init_success = true;
  return BS_OK;
}

base_status_t ads1293_start_convert(ads1293_t *me, bool enable)
{
  if(m_init_success == false)
  {
    return BS_ERROR;
  }
  
  return m_ads1293_write_reg(me, ADS1293_REG_CONFIG, enable);
}

base_status_t ads1293_read_ecg(ads1293_t *me, uint8_t *data)
{
  if(m_init_success == false)
  {
    return BS_ERROR;
  }
  
  return m_ads1293_read_reg(me, ADS1293_REG_DATA_CH1_ECG_H, data, ADS_NUM_CHANNEL * 3);
}

/* Private function definitions ---------------------------------------- */
/**
 * @brief         ADS1293 read register
 *
 * @param[in]     me      Pointer to handle of ADS1293 module.
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
base_status_t m_ads1293_read_reg(ads1293_t *me, uint8_t reg, uint8_t *p_data, uint32_t len)
{
  if(m_init_success == false)
  {
    if(reg != ADS1293_REG_REVID)
    {
      return BS_ERROR;
    }
  }
  
  uint8_t rx_data[len + sizeof(reg)];
  
  bsp_gpio_write(IO_AFE_CS, 0);

  reg = reg | ADS1293_READ_BIT;

  CHECK(0 == me->spi_transmit_receive(&reg, sizeof(reg), &rx_data[0], sizeof(rx_data)), BS_ERROR);

  bsp_gpio_write(IO_AFE_CS, 1);
  
  memcpy(&p_data[0], &rx_data[1], len);

  return BS_OK;
}

/**
 * @brief         ADS1293 read register
 *
 * @param[in]     me      Pointer to handle of ADS1293 module.
 * @param[in]     reg     Register
 * @param[in]     data    Data
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
static base_status_t m_ads1293_write_reg(ads1293_t *me, uint8_t reg, uint8_t data)
{
  uint8_t tx_data[] = {reg, data};
  
  bsp_gpio_write(IO_AFE_CS, 0);
  
  reg = reg & ADS1293_WRITE_BIT;
  CHECK(0 == me->spi_transmit_receive(&tx_data[0], sizeof(tx_data), NULL, 0), BS_ERROR);

  bsp_gpio_write(IO_AFE_CS, 1);

  return BS_OK;
}

/* End of file -------------------------------------------------------- */
