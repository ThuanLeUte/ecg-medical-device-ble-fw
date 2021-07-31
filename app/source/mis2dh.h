/**
 * @file       mis2dh.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-03-22
 * @author     Hiep Le
 * @brief      Driver support MIS2DH (Accelerometer)
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __MIS2DH_H
#define __MIS2DH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "bsp.h"

/* Public defines ----------------------------------------------------- */
#define MIS2DH_I2C_ADDR                       (0x19) // 7 Bits

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief MIS2DH axis enable enum
 */
typedef enum
{
   MIS2DH_AXIS_X_ENABLE   = 0x01
  ,MIS2DH_AXIS_Y_ENABLE   = 0x02
  ,MIS2DH_AXIS_Z_ENABLE   = 0x04
  ,MIS2DH_AXIS_XYZ_ENABLE = 0x07
}
mis2dh_axis_enable_t;

/**
 * @brief MIS2DH refresh rate enum
 */
typedef enum
{
   MIS2DH_RF_RATE_PW_DOWN = 0X00
  ,MIS2DH_RF_RATE_1HZ     = 0X01
  ,MIS2DH_RF_RATE_10HZ    = 0X02
  ,MIS2DH_RF_RATE_25HZ    = 0X03
  ,MIS2DH_RF_RATE_50HZ    = 0X04
  ,MIS2DH_RF_RATE_100HZ   = 0X05
  ,MIS2DH_RF_RATE_200HZ   = 0X06
  ,MIS2DH_RF_RATE_400HZ   = 0X07
  ,MIS2DH_RF_RATE_1_620HZ = 0X08
  ,MIS2DH_RF_RATE_1_344HZ = 0X09
}
mis2dh_refresh_rate_t;

/**
 * @brief MIS2DH resolution enum
 */
typedef enum
{
   MIS2DH_RES_VALUE_8_BIT  = 0X00
  ,MIS2DH_RES_VALUE_10_BIT = 0X01
  ,MIS2DH_RES_VALUE_12_BIT = 0X02
}
mis2dh_resolution_t;

/**
 * @brief MIS2DH scale enum
 */
typedef enum
{
   MIS2DH_SCALE_2G  = 0X00
  ,MIS2DH_SCALE_4G  = 0X01
  ,MIS2DH_SCALE_8G  = 0X02
  ,MIS2DH_SCALE_16G = 0X03
}
mis2dh_scale_t;

/**
 * @brief MIS2DH raw data
 */
typedef struct
{
  float x;
  float y;
  float z;
}
mis2dh_raw_data_t;

/**
 * @brief MIS2DH sensor struct
 */
typedef struct 
{
  uint8_t  device_address;  // I2C device address

  mis2dh_raw_data_t raw_data;

  // Read n-bytes from device's internal address <reg_addr> via I2C bus
  int (*i2c_read) (uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint32_t len);

  // Write n-bytes from device's internal address <reg_addr> via I2C bus
  int (*i2c_write) (uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint32_t len);
}
mis2dh_t;

/* Public function prototypes ----------------------------------------- */
/**
 * @brief         MIS2DH init
 *
 * @param[in]     me      Pointer to handle of MIS2DH module.
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t mis2dh_init(mis2dh_t *me);

/**
 * @brief         MIS2DH set resolution
 *
 * @param[in]     me            Pointer to handle of MIS2DH module.
 * @param[in]     resolution    Resolution

 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t mis2dh_set_resolution(mis2dh_t *me, mis2dh_resolution_t resolution);

/**
 * @brief         MIS2DH set scale
 *
 * @param[in]     me        Pointer to handle of MIS2DH module.
 * @param[in]     scale     Scale

 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t mis2dh_set_scale(mis2dh_t *me, mis2dh_scale_t scale);

/**
 * @brief         MIS2DH set refresh rate
 *
 * @param[in]     me      Pointer to handle of MIS2DH module.
 * @param[in]     rf_rate Refresh rate
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t mis2dh_set_refresh_rate(mis2dh_t *me, mis2dh_refresh_rate_t rf_rate);

/**
 * @brief         MIS2DH get accel raw data
 *
 * @param[in]     me        Pointer to handle of MIS2DH module
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t mis2dh_get_raw_data(mis2dh_t *me);

/**
 * @brief         MIS2DH enable axis
 *
 * @param[in]     me      Pointer to handle of MIS2DH module.
 * @param[in]     axis    Axis x, y, z
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t mis2dh_enable_axis(mis2dh_t *me, mis2dh_axis_enable_t axis);

/**
 * @brief         MIS2DH disble axis
 *
 * @param[in]     me      Pointer to handle of MIS2DH module.
 * @param[in]     axis    Axis x, y, z
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t mis2dh_disable_axis(mis2dh_t *me, mis2dh_axis_enable_t axis);

/**
 * @brief         MIS2DH reboot memory
 *
 * @param[in]     me      Pointer to handle of MIS2DH module.
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t mis2dh_reboot_memory(mis2dh_t *me);

/**
 * @brief         MIS2DH enter normal mode
 *
 * @param[in]     me      Pointer to handle of MIS2DH module.
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t mis2dh_enter_normal_mode(mis2dh_t *me);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __MIS2DH_H

/* End of file -------------------------------------------------------- */
