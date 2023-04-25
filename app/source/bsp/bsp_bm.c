/**
 * @file       bsp_bm.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-05-09
 * @author     Thuan Le
 * @brief      Board Support Package Battery Monitor
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_bm.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static ds2728_t m_ds2728;

/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */
base_status_t bsp_bm_init(void)
{
  m_ds2728.device_address = DS2728_I2C_ADDR;
  m_ds2728.i2c_read       = bsp_i2c_read;
  m_ds2728.i2c_write      = bsp_i2c_write;

  CHECK_STATUS(ds2728_init(&m_ds2728));

  return BS_OK;
}

base_status_t bsp_bm_get_info(bsp_bm_info_t *bm)
{
  // CHECK_STATUS(ds2728_get_temperature(&m_ds2728, &bm->temp));
  // CHECK_STATUS(ds2728_get_current(&m_ds2728, &bm->current));
  // CHECK_STATUS(ds2728_get_voltage(&m_ds2728, &bm->voltage));
  // CHECK_STATUS(ds2728_get_capacity(&m_ds2728, &bm->capacity));

  return BS_OK;
}

uint16_t battery_level;

base_status_t bsp_bm_get_soc(uint8_t *soc)
{
  #define BATTERY_VOLTAGE_MIN           (3400)          // mV Voltage at 0%
  #define BATTERY_VOLTAGE_MAX           (4190)          // mV Voltage at 100%

  bsp_bm_info_t bm;

  // CHECK_STATUS(bsp_bm_get_info(&bm));

  if (bm.voltage <= BATTERY_VOLTAGE_MIN)
  {
    battery_level = 0;
  }
  else
  {
    battery_level = (bm.voltage - BATTERY_VOLTAGE_MIN) / (float)((BATTERY_VOLTAGE_MAX - BATTERY_VOLTAGE_MIN) / 100);

    if (battery_level >= 100)
      battery_level = 100;
  }

  *soc = (uint8_t)battery_level;

  return BS_OK;
}

/* Private function definitions ---------------------------------------- */
/* End of file -------------------------------------------------------- */
