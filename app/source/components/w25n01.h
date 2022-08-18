/**
 * @file       w25n01.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-04-09
 * @author     Thuan Le
 * @brief      SERIAL SLC NAND FLASH MEMORY
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __W25N01_H
#define __W25N01_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "bsp/bsp.h"

/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief DS2728 sensor struct
 */
typedef struct 
{
  void (*bsp_gpio_write)(uint8_t pin , uint8_t state);
  base_status_t  (*spi_transfer)(uint8_t *tx_data, uint8_t *rx_data, uint16_t len);
}
w25n01_t;

/* Public function prototypes ----------------------------------------- */
/**
 * @brief         W25N01 init
 *
 * @param[in]     me    Pointer to handle of W25N01 module
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t w25n01_init(w25n01_t *me);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __W25N01_H

/* End of file -------------------------------------------------------- */