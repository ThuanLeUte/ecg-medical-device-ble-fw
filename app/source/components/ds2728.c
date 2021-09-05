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
#include "ds2728.h"

/* Private defines ---------------------------------------------------- */
#define DS2782_REG_STATUS             (0x01)
#define DS2782_REG_RAAC_MSB           (0x02)
#define DS2782_REG_RAAC_LSB           (0x03)
#define DS2782_REG_RSAC_MSB           (0x04)
#define DS2782_REG_RSAC_LSB           (0x05)
#define DS2782_REG_RARC               (0x06)
#define DS2782_REG_RSRC               (0x07)
#define DS2782_REG_IAVG_MSB           (0x08)
#define DS2782_REG_IAVG_LSB           (0x09)
#define DS2782_REG_TEMP_MSB           (0x0A)
#define DS2782_REG_TEMP_LSB           (0x0B)
#define DS2782_REG_VOLT_MSB           (0x0C)
#define DS2782_REG_VOLT_LSB           (0x0D)
#define DS2782_REG_CURR_MSB           (0x0E)
#define DS2782_REG_CURR_LSB           (0x0F)
#define DS2782_REG_ACR_MSB            (0x10)
#define DS2782_REG_ACR_LSB            (0x11)
#define DS2782_REG_ACRL_MSB           (0x12)
#define DS2782_REG_ACRL_LSB           (0x13)
#define DS2782_REG_AS                 (0x14)
#define DS2782_REG_SRF                (0x15)
#define DS2782_REG_FULL_MSB           (0x16)
#define DS2782_REG_FULL_LSB           (0x17)
#define DS2782_REG_AE_MSB             (0x18)
#define DS2782_REG_AE_LSB             (0x19)
#define DS2782_REG_SE_MSB             (0x1A)
#define DS2782_REG_SE_LSB             (0x1B)

#define DS2728_REG_CONTROL            (0x60)
#define DS2728_REG_AB                 (0x61)
#define DS2728_REG_AC_MSB             (0x62)
#define DS2728_REG_AC_LSB             (0x63)
#define DS2728_REG_VCHG               (0x64)
#define DS2728_REG_IMIN               (0x65)
#define DS2728_REG_VAE                (0x66)
#define DS2728_REG_IAE                (0x67)
#define DS2728_REG_ACTIVE_EMPTY_40    (0x68)
#define DS2728_REG_RSNSP              (0x69)
#define DS2728_REG_FULL_40_MSB        (0x6A)
#define DS2728_REG_FULL_40_LSB        (0x6B)
#define DS2728_REG_FULL_3040_SLOPE    (0x6C)
#define DS2728_REG_FULL_2030_SLOPE    (0x6D)
#define DS2728_REG_FULL_1020_SLOPE    (0x6E)
#define DS2728_REG_FULL_0010_SLOPE    (0x6F)
#define DS2728_REG_AE_3040_SLOPE      (0x70)
#define DS2728_REG_AE_2030_SLOPE      (0x71)
#define DS2728_REG_AE_1020_SLOPE      (0x72)
#define DS2728_REG_AE_0010_SLOPE      (0x73)
#define DS2728_REG_SE_3040_SLOPE      (0x74)
#define DS2728_REG_SE_2030_SLOPE      (0x75)
#define DS2728_REG_SE_1020_SLOPE      (0x76)
#define DS2728_REG_SE_0010_SLOPE      (0x77)
#define DS2728_REG_RSGAIN_MSB         (0x78)
#define DS2728_REG_RSGAIN_LSB         (0x78)
#define DS2728_REG_RSTC               (0x7A)
#define DS2728_REG_FRSGAIN_MSB        (0x7B)
#define DS2728_REG_FRSGAIN_LSB        (0x7C)

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
static base_status_t m_ds2728_read_reg(ds2728_t *me, uint8_t reg, uint8_t *p_data, uint32_t len);
static base_status_t m_ds2728_write_reg(ds2728_t *me, uint8_t reg, uint8_t *p_data, uint32_t len);

/* Function definitions ----------------------------------------------- */
base_status_t ds2728_init(ds2728_t *me)
{
  if ((me == NULL) || (me->i2c_read == NULL) || (me->i2c_write == NULL))
    return BS_ERROR;

  return BS_OK;
}

base_status_t ds2728_get_temperature(ds2728_t *me, float *temp)
{
  uint8_t buf[2];
  uint16_t raw_temp;

  CHECK_STATUS(m_ds2728_read_reg(me, DS2782_REG_TEMP_MSB, buf, 2));

  raw_temp = (((buf[0] & ~(1 << 7)) << 3) | ((buf[1] >> 5) & 0xF));

  *temp = (float)(raw_temp * 0.125);

  return BS_OK;
}

base_status_t ds2728_get_current(ds2728_t *me, float *current)
{
  uint8_t buf[2];
  uint16_t raw_current;

  CHECK_STATUS(m_ds2728_read_reg(me, DS2782_REG_CURR_MSB, buf, 2));

  raw_current = (buf[0] << 8) | (buf[1]);

  if (raw_current & 0x8000)
  {
    *current = (float)(raw_current - 65536 * 0.07813);
  }
  else
  {
    *current = (float)(raw_current * 0.07813);
  }

  return BS_OK;
}

base_status_t ds2728_get_voltage(ds2728_t *me, float *voltage)
{
  uint8_t buf[2];
  uint16_t raw_voltage;

  CHECK_STATUS(m_ds2728_read_reg(me, DS2782_REG_VOLT_MSB, buf, 2));

  raw_voltage = (((buf[0] & ~(1 << 7)) << 3) | ((buf[1] >> 5) & 0xF));

  *voltage = (float)(raw_voltage * 4.88);

  return BS_OK;
}

base_status_t ds2728_get_capacity(ds2728_t *me, uint8_t *capacity)
{
  CHECK_STATUS(m_ds2728_read_reg(me, DS2782_REG_RARC, capacity, 1));

  return BS_OK;
}

/* Private function definitions ---------------------------------------- */
/**
 * @brief         DS2728 read register
 *
 * @param[in]     me      Pointer to handle of DS2728 module.
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
static base_status_t m_ds2728_read_reg(ds2728_t *me, uint8_t reg, uint8_t *p_data, uint32_t len)
{
  CHECK(0 == me->i2c_read(me->device_address, reg, p_data, len), BS_ERROR);

  return BS_OK;
}

/**
 * @brief         DS2728 read register
 *
 * @param[in]     me      Pointer to handle of DS2728 module.
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
static base_status_t m_ds2728_write_reg(ds2728_t *me, uint8_t reg, uint8_t *p_data, uint32_t len)
{
  CHECK(0 == me->i2c_write(me->device_address, reg, p_data, len), BS_ERROR);

  return BS_OK;
}

/* End of file -------------------------------------------------------- */
