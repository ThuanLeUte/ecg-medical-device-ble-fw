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
#include "nrf_log.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
static base_status_t m_ads1293_read_reg(ads1293_t *me, uint8_t reg, uint8_t *p_data, uint32_t len);
static base_status_t m_ads1293_write_reg(ads1293_t *me, uint8_t reg, uint8_t data);

/* Function definitions ----------------------------------------------- */
base_status_t ads1293_init(ads1293_t *me)
{
  if ((me == NULL) || (me->spi_transmit_receive == NULL))
    return BS_ERROR;

  // Write init setting
  for (uint8_t i = 0; i < sizeof(ADS1293_SETTING_LIST), i++)
  {
    CHECK_STATUS(m_ads1293_write_reg(me, ADS1293_SETTING_LIST[i].register, ADS1293_SETTING_LIST[i].value));
  }

  return BS_OK;
}

base_status_t ads1293_start_convert(ads1293_t *me, bool enable)
{
  return m_ads1293_write_reg(me, ADS1293_REG_CONFIG, enable);
}

base_status_t ads1293_read_ecg(ads1293_t *me, uint8_t *data)
{
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
static base_status_t m_ads1293_read(ads1293_t *me, uint8_t reg, uint8_t *p_data, uint32_t len)
{
  CHECK(0 == me->spi_transmit_receive(&reg, NULL, 1), BS_ERROR);
  CHECK(0 == me->spi_transmit_receive(NULL, p_data, len), BS_ERROR);

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
static base_status_t m_ads1293_write(ads1293_t *me, uint8_t reg, uint8_t data)
{
  CHECK(0 == me->spi_transmit_receive(&reg, NULL, 1), BS_ERROR);
  CHECK(0 == me->spi_transmit_receive(&data, NULL, len), BS_ERROR);

  return BS_OK;
}

/* End of file -------------------------------------------------------- */
