/**
 * @file       bsp.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-01-23
 * @author     Thuan Le
 * @brief      Board Support Package (BSP)
 * @note       None
 * @example    None
 */

#ifndef BSP_PORTING_H
#define BSP_PORTING_H

#include "bsp/bsp.h"

bool bsp_porting_read_pin(uint8_t pin);
void bsp_porting_write_pin(uint8_t pin, bool enable);
void bsp_porting_delay(uint32_t ms);
uint8_t bsp_porting_spi_transfer(uint8_t data);

#endif
