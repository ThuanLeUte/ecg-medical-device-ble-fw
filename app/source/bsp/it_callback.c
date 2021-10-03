
/**
 * @file       it_callback.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-01-23
 * @author     Thuan Le
 * @brief      Interrupt callback
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "it_callback.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */
void exint_afe_drdy_event_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
  bsp_afe_get_ecg();
}

/* Private function definitions ---------------------------------------- */
/* End of file -------------------------------------------------------- */
