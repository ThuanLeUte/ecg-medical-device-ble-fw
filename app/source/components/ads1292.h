/**
 * @file       ads1292.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-07-31
 * @author     Thuan Le
 * @brief      Driver support ADS1292 (Analog Front-End for Biopotential Measurements)
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __ADS1292_H
#define __ADS1292_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "bsp/bsp.h"

/* Public defines ----------------------------------------------------- */
#define ADS_NUM_CHANNEL   (2)

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief ADS1292 sensor struct
 */
typedef struct 
{
  void (*gpio_write)(uint8_t pin, uint8_t state);

  int (*spi_transmit_receive)(uint8_t *tx_data, uint8_t *rx_data, uint16_t len);
}
ads1292_t;

/* Public function prototypes ----------------------------------------- */
/**
 * @brief         ADS1292 init
 *
 * @param[in]     me      Pointer to handle of ADS1292 module.
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t ads1292_init(ads1292_t *me);

/**
 * @brief         ADS1292 start convert
 *
 * @param[in]     me        Pointer to handle of ADS1292 module.
 * @param[in]     enable    Enable
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t ads1292_start_convert(ads1292_t *me, bool enable);

/**
 * @brief         ADS1292 read ECG
 *
 * @param[in]     me        Pointer to handle of ADS1292 module.
 * @param[in]     data      Pointer to ECG data
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t ads1292_read_ecg(ads1292_t *me, uint8_t *data);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __ADS1292_H

/* End of file -------------------------------------------------------- */