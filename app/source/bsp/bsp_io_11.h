/**
 * @file       bsp_io_11.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-01-23
 * @author     Thuan Le
 * @brief      Pin description for hardware version 1.1
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BSP_IO_11_H
#define __BSP_IO_11_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include <stdint.h>
#include <stdbool.h>

/* Public defines ----------------------------------------------------- */
                                    // Schematic
// PIN NAME PORT 0 ``````````````````````````````
#define IO_I2C0_SCL             (11)    // SCL signal pin
#define IO_I2C0_SDA             (12)    // SDA signal pin

#define IO_AFE_ALARM            (08)    // AFE ALARM
#define IO_AFE_RST              (10)    // AFE RST
#define IO_AFE_DRDY             (13)    // AFE DRDY
#define IO_AFE_MISO             (14)    // AFE MISO
#define IO_AFE_MOSI             (15)    // AFE MOSI
#define IO_AFE_SCLK             (16)    // AFE SCLK
#define IO_AFE_CS               (17)    // AFE CS

#define IO_CHARGE_FAST          (06)    // CHARGE FAST
#define IO_RGB_RED              (29)    // RGB RED
#define IO_RGB_GREEN            (28)    // RGB GREEN
#define IO_RGB_BLUE             (30)    // RGB BLUE

/* Public enumerate/structure ----------------------------------------- */
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/* -------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __BSP_IO_11_H

/* End of file -------------------------------------------------------- */
