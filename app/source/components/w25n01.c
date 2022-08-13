/**
 * @file       ds2728.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-04-09
 * @author     Thuan Le
 * @brief      Driver support DS2728 (Stand-Alone Fuel Gauge IC)
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "w25n01.h"
#include "bsp.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */
#define W25N_JEDEC_ID             0x9F
#define WINBOND_MAN_ID            0xEF
#define W25N01GV_DEV_ID           0xAA21

base_status_t w25n01_init(void)
{
  uint8_t jedec[5] = {W25N_JEDEC_ID, 0x00, 0x00, 0x00, 0x00};
  uint8_t jedec_receive[5];

  bsp_gpio_write(IO_AFE_CS, 0);
  bsp_delay_ms(100);
  bsp_gpio_write(IO_AFE_CS, 1);


  bsp_gpio_write(IO_AFE_CS, 0);
  bsp_spi_transmit_receive(jedec, jedec_receive, sizeof(jedec));
  bsp_gpio_write(IO_AFE_CS, 1);

  if (jedec_receive[2] == WINBOND_MAN_ID)
  {
    if ((uint16_t)(jedec_receive[3] << 8 | jedec_receive[4]) == W25N01GV_DEV_ID)
    {
      return BS_OK;
    }
  }

    return BS_ERROR;
}
/* End of file -------------------------------------------------------- */
