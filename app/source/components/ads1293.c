/**
 * @file       ads1293.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-07-31
 * @author     Thuan Le
 * @brief      Driver support ADS1293 (Analog Front-End for Biopotential Measurements)
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "ads1293.h"
#include "nrf_log.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
static base_status_t m_ads1293_read_reg(ads1293_t *me, uint8_t reg, uint8_t *p_data, uint32_t len);
static base_status_t m_ads1293_write_reg(ads1293_t *me, uint8_t reg, uint8_t *p_data, uint32_t len);

/* Function definitions ----------------------------------------------- */
base_status_t ads1293_init(ads1293_t *me)
{
  if ((me == NULL) || (me->spi_transmit_receive == NULL))
    return BS_ERROR;

  return BS_OK;
}

/* Private function definitions ---------------------------------------- */
/**
 * @brief         ADS1293 read register
 *
 * @param[in]     me      Pointer to handle of ADS1293 module.
 * @param[in]     reg     Register
 * @param[in]     p_data  Pointer to handle of data
 * @param[in]     len     Data length
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
static base_status_t m_ads1293_read(ads1293_t *me, uint8_t reg, uint8_t *p_data, uint32_t len)
{
 // CHECK(0 == me->i2c_read(me->device_address, reg, p_data, len), BS_ERROR);

  return BS_OK;
}

/**
 * @brief         ADS1293 read register
 *
 * @param[in]     me      Pointer to handle of ADS1293 module.
 * @param[in]     reg     Register
 * @param[in]     p_data  Pointer to handle of data
 * @param[in]     len     Data length
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
static base_status_t m_ads1293_write(ads1293_t *me, uint8_t reg, uint8_t *p_data, uint32_t len)
{
  //CHECK(0 == me->i2c_write(me->device_address, reg, p_data, len), BS_ERROR);

  return BS_OK;
}

/* End of file -------------------------------------------------------- */
