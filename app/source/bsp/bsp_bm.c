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

base_status_t bsp_bm_temperature(float *temp)
{
  CHECK_STATUS(ds2728_get_temperature(&m_ds2728, temp));

  return BS_OK;
}

/* Private function definitions ---------------------------------------- */
/* End of file -------------------------------------------------------- */
