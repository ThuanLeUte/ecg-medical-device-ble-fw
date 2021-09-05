/**
 * @file       ds2728.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-04-09
 * @author     Thuan Le
 * @brief      Driver support DS2728 (Stand-Alone Fuel Gauge IC)
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __DS2728_H
#define __DS2728_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "bsp/bsp.h"

/* Public defines ----------------------------------------------------- */
#define DS2728_I2C_ADDR               (0x34) // 7 Bits

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief DS2728 sensor struct
 */
typedef struct 
{
  uint8_t  device_address;  // I2C device address

  // Read n-bytes from device's internal address <reg_addr> via I2C bus
  int (*i2c_read) (uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint32_t len);

  // Write n-bytes from device's internal address <reg_addr> via I2C bus
  int (*i2c_write) (uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint32_t len);
}
ds2728_t;

/* Public function prototypes ----------------------------------------- */
/**
 * @brief         DS2728 init
 *
 * @param[in]     me    Pointer to handle of DS2728 module
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t ds2728_init(ds2728_t *me);

/**
 * @brief         DS2728 init
 *
 * @param[in]     me    Pointer to handle of DS2728 module
 * @param[in]     temp  Temperature
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t ds2728_get_temperature(ds2728_t *me, float *temp);

/**
 * @brief         DS2728 init
 *
 * @param[in]     me       Pointer to handle of DS2728 module
 * @param[in]     current  Current
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t ds2728_get_current(ds2728_t *me, float *current);

/**
 * @brief         DS2728 init
 *
 * @param[in]     me      Pointer to handle of DS2728 module
 * @param[in]     voltage Voltage
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t ds2728_get_voltage(ds2728_t *me, float *voltage);

/**
 * @brief         DS2728 init
 *
 * @param[in]     me        Pointer to handle of DS2728 module
 * @param[in]     capacity  Capacity
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t ds2728_get_capacity(ds2728_t *me, uint8_t *capacity);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __DS2728_H

/* End of file -------------------------------------------------------- */
