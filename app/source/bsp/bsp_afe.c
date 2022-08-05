/**
 * @file       bsp_afe.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-09-05
 * @author     Thuan Le
 * @brief      Board Support Package for AFE (ADS1292)
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_afe.h"

/* Private defines ---------------------------------------------------- */
#define SHIFT_BIT_ADS1292  (3)

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static ads1292_t m_ads1292;

/* Private function prototypes ---------------------------------------- */
static base_status_t m_bsp_afe_read_channels(int32_t value[ADS_NUM_CHANNEL]);

/* Function definitions ----------------------------------------------- */
base_status_t bsp_afe_init(void)
{
  m_ads1292.spi_transmit_receive = bsp_spi_transmit_receive;
  m_ads1292.gpio_write           = bsp_gpio_write;

  CHECK_STATUS(ads1292_init(&m_ads1292));

  CHECK_STATUS(ads1292_start_convert(&m_ads1292, BS_TRUE));

  return BS_OK;
}

base_status_t bsp_afe_get_ecg(int32_t value[ADS_NUM_CHANNEL])
{
  m_bsp_afe_read_channels(value);

  return BS_OK;
}

/* Private function definitions ---------------------------------------- */
/**
 * @brief         AFE read channel data
 *
 * @param[in]     value   AEF data
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
static base_status_t m_bsp_afe_read_channels(int32_t value[ADS_NUM_CHANNEL])
{
  uint8_t rx[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  // m_ads1292_read_reg(&m_ads1292, 0x50, &rx[0], sizeof(rx));

  uint32_t tempData = (uint32_t)rx[0] << 16;
  tempData |= (uint32_t)rx[1] << 8;
  tempData |= rx[2];

  value[0] = tempData;
  
  tempData = (uint32_t)rx[3] << 16;
  tempData |= (uint32_t)rx[4] << 8;
  tempData |= rx[5];  

  value[1] = tempData;

  return BS_OK;
}

/* End of file -------------------------------------------------------- */
