/**
 * @file       ads1292_def.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-07-31
 * @author     Thuan Le
 * @brief      Driver support ADS1292 (Analog Front-End for Biopotential Measurements)
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __ADS1292_DEF_H
#define __ADS1292_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "bsp/bsp.h"

/* Public defines ----------------------------------------------------- */
#define ADS1292_REG_ID          (0x00)
#define ADS1292_REG_CONFIG1     (0x01)
#define ADS1292_REG_CONFIG2     (0x02)
#define ADS1292_REG_LOFF        (0x03)
#define ADS1292_REG_CH1SET      (0x04)
#define ADS1292_REG_CH2SET      (0x05)
#define ADS1292_REG_RLDSENS     (0x06)
#define ADS1292_REG_LOFFSENS    (0x07)
#define ADS1292_REG_LOFFSTAT    (0x08)
#define ADS1292_REG_RESP1       (0x09)
#define ADS1292_REG_RESP2       (0x0A)

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief ADS1292 setting struct
 */
typedef struct
{
  uint8_t reg;
  uint8_t value;
}
ads1292_seting_t;

/* Private variables -------------------------------------------------- */
#define INFO(_register, _value)[_register] = { .reg = _register, .value = _value }
const ads1292_seting_t ADS1292_SETTING_LIST[] =
{
   //  +===============================+=======+
   //  |REGISTER                       | VALUE
   //  +-------------------------------+-------+
   INFO(ADS1292_REG_CONFIG1,               0x00)    // Sampling rate to 125 SPS
  ,INFO(ADS1292_REG_CONFIG2,         0b10100000)    // Lead-off comp off, test signal disabled
  ,INFO(ADS1292_REG_LOFF,            0b00010000)    // Lead-off defaults
  ,INFO(ADS1292_REG_CH1SET,          0b01000000)    // Ch 1 enabled, gain 6, connected to electrode in
  ,INFO(ADS1292_REG_CH2SET,          0b01100000)    // Ch 2 enabled, gain 6, connected to electrode in
  ,INFO(ADS1292_REG_RLDSENS,         0b00101100)    // RLD settings: fmod/16, RLD enabled, RLD inputs from Ch2 only
  ,INFO(ADS1292_REG_LOFFSENS,              0x00)    // LOFF settings: all disabled
  ,INFO(ADS1292_REG_RESP1,           0b11110010)    // Respiration: MOD/DEMOD turned only, phase 0
  ,INFO(ADS1292_REG_RESP2,           0b00000011)    // Respiration: Calib OFF, respiration freq defaults
   //  +===============================+=======+
};
#undef INFO

/* Public function prototypes ----------------------------------------- */

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __ADS1292_DEF_H

/* End of file -------------------------------------------------------- */
