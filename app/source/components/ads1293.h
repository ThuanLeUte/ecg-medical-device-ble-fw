/**
 * @file       ads1293.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-07-31
 * @author     Thuan Le
 * @brief      Driver support ADS1293 (Analog Front-End for Biopotential Measurements)
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __ADS1293_H
#define __ADS1293_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "bsp/bsp.h"

/* Public defines ----------------------------------------------------- */
#define ADS_NUM_CHANNEL   (2)

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief ADS1293 axis enable enum
 */
typedef enum
{
   MIS2DH_AXIS_X_ENABLE   = 0x01
  ,MIS2DH_AXIS_Y_ENABLE   = 0x02
  ,MIS2DH_AXIS_Z_ENABLE   = 0x04
  ,MIS2DH_AXIS_XYZ_ENABLE = 0x07
}
ads1293_axis_enable_t;

/**
 * @brief ADS1293 sensor struct
 */
typedef struct 
{
  void (*gpio_write)(uint8_t pin, uint8_t state);

  int (*spi_transmit_receive)(uint8_t *tx_data, uint16_t tx_len, uint8_t *rx_data, uint16_t rx_len);
}
ads1293_t;

/* Public function prototypes ----------------------------------------- */
/**
 * @brief         ADS1293 init
 *
 * @param[in]     me      Pointer to handle of ADS1293 module.
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t ads1293_init(ads1293_t *me);

/**
 * @brief         ADS1293 start convert
 *
 * @param[in]     me        Pointer to handle of ADS1293 module.
 * @param[in]     enable    Enable
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t ads1293_start_convert(ads1293_t *me, bool enable);

/**
 * @brief         ADS1293 read ECG
 *
 * @param[in]     me        Pointer to handle of ADS1293 module.
 * @param[in]     data      Pointer to ECG data
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t ads1293_read_ecg(ads1293_t *me, uint8_t *data);

/**
 * @brief         ADS1293 set sampling state
 *
 * @param[in]     me       Pointer to handle of ADS1293 module.
 * @param[in]     state    BS_TRUE:  Start sampling
 *                         BS_FALSE: Stop sampling
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t ads1293_set_sampling_state(ads1293_t *me, bool_t state);

/**
 * @brief         ADS1293 set sampling rate
 *
 * @param[in]     me        Pointer to handle of ADS1293 module.
 * @param[in]     rate      Sampling rate
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t ads1293_set_sampling_rate(ads1293_t *me, uint16_t rate);

base_status_t m_ads1293_read_reg(ads1293_t *me, uint8_t reg, uint8_t *p_data, uint32_t len);


/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __ADS1293_H

/* End of file -------------------------------------------------------- */
