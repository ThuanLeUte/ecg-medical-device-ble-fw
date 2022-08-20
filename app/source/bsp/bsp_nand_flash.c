/**
 * @file       bsp_nand_flash.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-09-05
 * @author     Thuan Le
 * @brief      Board Support Package for Nand Flash
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_nand_flash.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static w25n01_t m_w25n01;

/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */
base_status_t bsp_nand_flash_init(void)
{
  m_w25n01.spi_transfer = bsp_spi_transmit_receive;
  m_w25n01.gpio_write   = bsp_gpio_write;

  CHECK_STATUS(w25n01_init(&m_w25n01));

  return BS_OK;
}

/* Private function definitions ---------------------------------------- */
/* End of file -------------------------------------------------------- */
