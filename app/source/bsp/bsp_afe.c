/**
 * @file       bsp_afe.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-09-05
 * @author     Thuan Le
 * @brief      Board Support Package for AFE (ADS1293)
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_afe.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static ads1293_t m_ads1293;

/* Private function prototypes ---------------------------------------- */
static base_status_t m_bsp_afe_read_channels(int16_t value[ADS_NUM_CHANNEL]);

/* Function definitions ----------------------------------------------- */
base_status_t bsp_afe_init(void)
{
  m_ads1293.spi_transmit_receive = bsp_spi_transmit_receive;

  CHECK_STATUS(ads1293_init(&m_ads1293));

  CHECK_STATUS(ads1293_start_convert(&m_ads1293, BS_TRUE));

  return BS_OK;
}

base_status_t bsp_afe_get_ecg(int16_t value[ADS_NUM_CHANNEL])
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
static base_status_t m_bsp_afe_read_channels(int16_t value[ADS_NUM_CHANNEL])
{
  uint8_t r[ADS_NUM_CHANNEL * 3];
  int32_t i[ADS_NUM_CHANNEL];

  CHECK_STATUS(ads1293_read_ecg(&m_ads1293, r));

  for (int k = 0; k < ADS_NUM_CHANNEL; k++)
  {
    // Compose int32_t value
    i[k] = (int32_t)((r[3 * k] << 16) | (r[3 * k + 1] << 8) | r[3 * k + 2]);

    // Convert int32_t to float
    value[k] = (int16_t)i[k];
  }

  return BS_OK;
}

/* End of file -------------------------------------------------------- */
