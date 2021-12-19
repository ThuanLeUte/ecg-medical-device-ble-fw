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
#define SHIFT_BIT_ADS1293  (3)

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static ads1293_t m_ads1293;

/* Private function prototypes ---------------------------------------- */
static base_status_t m_bsp_afe_read_channels(int32_t value[ADS_NUM_CHANNEL]);

/* Function definitions ----------------------------------------------- */
base_status_t bsp_afe_init(void)
{
  m_ads1293.spi_transmit_receive = bsp_spi_transmit_receive;
  m_ads1293.gpio_write           = bsp_gpio_write;

  CHECK_STATUS(ads1293_init(&m_ads1293));

  CHECK_STATUS(ads1293_start_convert(&m_ads1293, BS_TRUE));

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
  uint8_t r[ADS_NUM_CHANNEL * 3];
  int32_t i[ADS_NUM_CHANNEL];

  // CHECK_STATUS(ads1293_read_ecg(&m_ads1293, r));

  int32_t ecgTmp = 0;
  int32_t ecgTmp2 = 0;
  int32_t ecgVal;

  uint8_t x1, x2, x3;

  // for (int k = 0; k < ADS_NUM_CHANNEL; k++)
  {
    // Compose int32_t value
    // i[k] = (int32_t)((r[3 * k] << 16) | (r[3 * k + 1] << 8) | r[3 * k + 2]);

    m_ads1293_read_reg(&m_ads1293, 0x37, &x1, 1);
    m_ads1293_read_reg(&m_ads1293, 0x38, &x2, 1);
    m_ads1293_read_reg(&m_ads1293, 0x39, &x3, 1);

    uint32_t tempData = (uint32_t)x1 << 16;
    tempData = (uint32_t)x2 << 8;
    tempData |= x3;
    tempData = tempData << 8;

    value[0] = tempData;
  }

  return BS_OK;
}

/* End of file -------------------------------------------------------- */
