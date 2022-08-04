/**
 * @file       ads1292.h
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
  } ads1292_seting_t;

/* Private variables -------------------------------------------------- */
#define INFO(_register, _value)[_register] = { .reg = _register, .value = _value }
// const ads1292_seting_t ADS1292_SETTING_LIST[] =
// {
//    //  +===============================+=======+
//    //  |REGISTER                       | VALUE
//    //  +-------------------------------+-------+
//    INFO(ADS1292_REG_CONFIG,                0x00)
  
//   /*
//   LEAD I    = LA - RA
//   LEAD II   = LL - RA
//   LEAD III  = Disconnect

//   CH1P - IN2 - LA   -->   LEAD I
//   CH1N - IN1 - RA
//   CH2P - IN3 - LL   -->   LEAD II
//   CH2N - IN1 - RA
//   */
//   ,INFO(ADS1292_REG_FLEX_CH1_CN,           0x11)
//   ,INFO(ADS1292_REG_FLEX_CH2_CN,           0x19)
//   ,INFO(ADS1292_REG_FLEX_CH3_CN,           0x00)
//   ,INFO(ADS1292_REG_FLEX_PACE_CN,          0x00)
//   ,INFO(ADS1292_REG_FLEX_VBAT_CN,          0x00)

//   /*
//   Lead-off detection circuitry is shut down
//   */
//   ,INFO(ADS1292_REG_LOD_CN,                0x08)
//   ,INFO(ADS1292_REG_LOD_EN,                0x00)
//   ,INFO(ADS1292_REG_LOD_CURRENT,           0x00)
//   ,INFO(ADS1292_REG_LOD_AC_CN,             0x00)

//   /*
//   Common-Mode Detect Enable for: IN1, IN2, IN3
//   Right-leg drive output connected to IN4
//   */
//   ,INFO(ADS1292_REG_CMDET_EN,              0x07)
//   ,INFO(ADS1292_REG_CMDET_CN,              0x00)
//   ,INFO(ADS1292_REG_RLD_CN,                0x04)

//   /*
//   Internal reference voltage is on (2.4V)
//   */
//   ,INFO(ADS1292_REG_REF_CN,                0x00)

//   /*
//   Use internal clock with external
//   */
//   ,INFO(ADS1292_REG_OSC_CN,                0x05)

//   /*
//   2560 SPS / 512 HZ
//   Analog Front-End Frequency and Resolution
//   */
//   ,INFO(ADS1292_REG_AFE_RES,               0x38)

//   /*
//   Connect the analog pace channel ourput to the RLDIN pin
//   */
//   ,INFO(ADS1292_REG_AFE_PACE_CN,           0x0A)

//   /*
//   2560 SPS / 512 HZ
//   R1 = 4
//   R2 = 5
//   R3 = 4
//   */
//   ,INFO(ADS1292_REG_R2_RATE,               0x02)
//   ,INFO(ADS1292_REG_R3_RATE1,              0x01)
//   ,INFO(ADS1292_REG_R3_RATE2,              0x01)
//   ,INFO(ADS1292_REG_R3_RATE3,              0x01)
//   ,INFO(ADS1292_REG_R1_P_DRATE,            0x00)

//   /*
//   CH1 ECG as DRDYB source
//   */
//   ,INFO(ADS1292_REG_DRDYB_SRC,             0x08)

//   /*
//   Enable loop back read on CH1, CH2, CH3
//   */
//   ,INFO(ADS1292_REG_ALARM_FILTER,          0x33)
//   ,INFO(ADS1292_REG_CH_CNFG,               0x30)
//   //  +===============================+=======+
// };
// #undef INFO

/* Public function prototypes ----------------------------------------- */

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __ADS1292_DEF_H

/* End of file -------------------------------------------------------- */
