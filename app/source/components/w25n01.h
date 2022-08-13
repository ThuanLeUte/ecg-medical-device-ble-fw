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
/* Public enumerate/structure ----------------------------------------- */
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
base_status_t w25n01_init(void);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __DS2728_H

/* End of file -------------------------------------------------------- */
