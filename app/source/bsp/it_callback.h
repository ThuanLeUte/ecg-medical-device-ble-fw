/**
 * @file       it_callback.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-01-23
 * @author     Thuan Le
 * @brief      Interrupt callback
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __IT_CALLBACK_H
#define __IT_CALLBACK_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief         AFE data ready interrup
 *
 * @param[in]     pin       Interrupt pin
 * @param[in]     action    Interrupt action
 *
 * @attention     None
 *
 * @return        None
 */
void exint_afe_drdy_event_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __IT_CALLBACK_H

/* End of file -------------------------------------------------------- */
