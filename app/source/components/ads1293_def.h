/**
 * @file       ads1293.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-07-31
 * @author     Thuan Le
 * @brief      Driver support ADS1293 (Analog Front-End for Biopotential Measurements)
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __ADS1293_DEF_H
#define __ADS1293_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "bsp/bsp.h"

/* Public defines ----------------------------------------------------- */
#define ADS1293_REG_CONFIG                (0x00)    // Main Configuration
#define ADS1293_REG_FLEX_CH1_CN           (0x01)    // Flex Routing Swich Control for Channel 1
#define ADS1293_REG_FLEX_CH2_CN           (0x02)    // Flex Routing Swich Control for Channel 2
#define ADS1293_REG_FLEX_CH3_CN           (0x03)    // Flex Routing Swich Control for Channel 3
#define ADS1293_REG_FLEX_PACE_CN          (0x04)    // Flex Routing Swich Control for Pace Channel
#define ADS1293_REG_FLEX_VBAT_CN          (0x05)    // Flex Routing Swich Control for Battery Monitoriing
#define ADS1293_REG_LOD_CN                (0x06)    // Lead Off Detect Control
#define ADS1293_REG_LOD_EN                (0x07)    // Lead Off Detect Enable
#define ADS1293_REG_LOD_CURRENT           (0x08)    // Lead Off Detect Current
#define ADS1293_REG_LOD_AC_CN             (0x09)    // AC Lead Off Detect Current
#define ADS1293_REG_CMDET_EN              (0x0A)    // Common Mode Detect Enable
#define ADS1293_REG_CMDET_CN              (0x0B)    // Commond Mode Detect Control
#define ADS1293_REG_RLD_CN                (0x0C)    // Right Leg Drive Control
#define ADS1293_REG_WILSON_EN1            (0x0D)    // Wilson Reference Input one Selection
#define ADS1293_REG_WILSON_EN2            (0x0E)    // Wilson Reference Input two Selection
#define ADS1293_REG_WILSON_EN3            (0x0F)    // Wilson Reference Input three Selection
#define ADS1293_REG_WILSON_CN             (0x10)    // Wilson Reference Input Control
#define ADS1293_REG_REF_CN                (0x11)    // Internal Reference Voltage Control
#define ADS1293_REG_OSC_CN                (0x12)    // Clock Source and Output Clock Control
#define ADS1293_REG_AFE_RES               (0x13)    // Analog Front-End Frequency and Resolution
#define ADS1293_REG_AFE_SHDN_CN           (0x14)    // Analog Front-End Shutdown Control
#define ADS1293_REG_AFE_FAULT_CN          (0x15)    // Analog Front-End Fault Detection Control
#define ADS1293_REG_AFE_DITHER_EN         (0x16)    // Enable Dithering in Signma-Delta
#define ADS1293_REG_AFE_PACE_CN           (0x17)    // Analog Pace Channel Output Routing Control
#define ADS1293_REG_ERROR_LOD             (0x18)    // Lead Off Detect Error Status
#define ADS1293_REG_ERROR_STATUS          (0x19)    // Other Error Status
#define ADS1293_REG_ERROR_RANGE1          (0x1A)    // Channel 1 Amplifier Out of Range Status
#define ADS1293_REG_ERROR_RANGE2          (0x1B)    // Channel 1 Amplifier Out of Range Status
#define ADS1293_REG_ERROR_RANGE3          (0x1C)    // Channel 1 Amplifier Out of Range Status
#define ADS1293_REG_ERROR_SYNC            (0x1D)    // Synchronization Error
#define ADS1293_REG_R2_RATE               (0x21)    // R2 Decimation Rate
#define ADS1293_REG_R3_RATE1              (0x22)    // R3 Decimation Rate for Channel 1
#define ADS1293_REG_R3_RATE2              (0x23)    // R3 Decimation Rate for Channel 2
#define ADS1293_REG_R3_RATE3              (0x24)    // R3 Decimation Rate for Channel 3
#define ADS1293_REG_R1_P_DRATE            (0x25)    // R1 2x Pace Data Rate
#define ADS1293_REG_DIS_EFILTER           (0x26)    // ECG Filter Disable
#define ADS1293_REG_DRDYB_SRC             (0x27)    // Data Ready Pin Source
#define ADS1293_REG_SYNCOUTB_SRC          (0x28)    // Sync Out Pin Source
#define ADS1293_REG_MASK_DRDYB            (0x29)    // Optional Mask Control for DRDYB Output
#define ADS1293_REG_MASK_ERR              (0x2A)    // Mask Error on ALARMB Pin
#define ADS1293_REG_ALARM_FILTER          (0x2E)    // Digital Filter for Analog Alarm Signals
#define ADS1293_REG_CH_CNFG               (0x2F)    // Configure Channel for Loop Read Back Mode
#define ADS1293_REG_DATA_STATUS           (0x30)    // ECG and Pace Data Ready Status
#define ADS1293_REG_DATA_CH1_PACE_H       (0x31)    // Channel1 Pace Data High [15:8]
#define ADS1293_REG_DATA_CH1_PACE_L       (0x32)    // Channel1 Pace Data Low [7:0]
#define ADS1293_REG_DATA_CH2_PACE_H       (0x33)    // Channel2 Pace Data High [15:8]
#define ADS1293_REG_DATA_CH2_PACE_L       (0x34)    // Channel2 Pace Data Low [7:0]
#define ADS1293_REG_DATA_CH3_PACE_H       (0x35)    // Channel3 Pace Data High [15:8]
#define ADS1293_REG_DATA_CH3_PACE_L       (0x36)    // Channel3 Pace Data Low [7:0]
#define ADS1293_REG_DATA_CH1_ECG_H        (0x37)    // Channel1 ECG Data High [23:16]
#define ADS1293_REG_DATA_CH1_ECG_M        (0x38)    // Channel1 ECG Data Medium [15:8]
#define ADS1293_REG_DATA_CH1_ECG_L        (0x39)    // Channel1 ECG Data Low [7:0]
#define ADS1293_REG_DATA_CH2_ECG_H        (0x3A)    // Channel2 ECG Data High [23:16]
#define ADS1293_REG_DATA_CH2_ECG_M        (0x3B)    // Channel2 ECG Data Medium [15:8]
#define ADS1293_REG_DATA_CH2_ECG_L        (0x3C)    // Channel2 ECG Data Low [7:0]
#define ADS1293_REG_DATA_CH3_ECG_H        (0x3D)    // Channel3 ECG Data High [23:16]
#define ADS1293_REG_DATA_CH3_ECG_M        (0x3E)    // Channel3 ECG Data Medium [15:8]
#define ADS1293_REG_DATA_CH3_ECG_L        (0x3F)    // Channel3 ECG Data Low [7:0]
#define ADS1293_REG_REVID                 (0x40)    // Revision ID
#define ADS1293_REG_DATA_LOOP             (0x50)    // Loop Read Back Address

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief ADS1293 setting struct
 */
typedef struct 
{
  uint8_t reg;
  uint8_t value;
}
ads1293_seting_t;

/* Private variables -------------------------------------------------- */
#define INFO(_register, _value)[_register] = { .reg = _register, .value = _value }
const ads1293_seting_t ADS1293_SETTING_LIST[] =
{
  //  //  +===============================+=======+
  //  //  |REGISTER                       | VALUE
  //  //  +-------------------------------+-------+
  //  INFO(ADS1293_REG_CONFIG,                0x00)
  
  // /*
  // LEAD I    = LA - RA
  // LEAD II   = LL - RA
  // LEAD III  = Disconnect

  // CH1P - IN2 - LA   -->   LEAD I
  // CH1N - IN1 - RA
  // CH2P - IN3 - LL   -->   LEAD II
  // CH2N - IN1 - RA
  // */
  // ,INFO(ADS1293_REG_FLEX_CH1_CN,           0x11)
  // ,INFO(ADS1293_REG_FLEX_CH2_CN,           0x19)
  // ,INFO(ADS1293_REG_FLEX_CH3_CN,           0x00)
  // ,INFO(ADS1293_REG_FLEX_PACE_CN,          0x00)
  // ,INFO(ADS1293_REG_FLEX_VBAT_CN,          0x00)

  // /*
  // Lead-off detection circuitry is shut down
  // */
  // ,INFO(ADS1293_REG_LOD_CN,                0x08)
  // ,INFO(ADS1293_REG_LOD_EN,                0x00)
  // ,INFO(ADS1293_REG_LOD_CURRENT,           0x00)
  // ,INFO(ADS1293_REG_LOD_AC_CN,             0x00)

  // /*
  // Common-Mode Detect Enable for: IN1, IN2, IN3
  // Right-leg drive output connected to IN4
  // */
  // ,INFO(ADS1293_REG_CMDET_EN,              0x07)
  // ,INFO(ADS1293_REG_CMDET_CN,              0x00)
  // ,INFO(ADS1293_REG_RLD_CN,                0x04)

  // /*
  // Internal reference voltage is on (2.4V)
  // */
  // ,INFO(ADS1293_REG_REF_CN,                0x00)

  // /*
  // Use internal clock with external
  // */
  // ,INFO(ADS1293_REG_OSC_CN,                0x05)

  // /*
  // 2560 SPS / 512 HZ
  // Analog Front-End Frequency and Resolution
  // */
  // ,INFO(ADS1293_REG_AFE_RES,               0x38)

  // /*
  // Connect the analog pace channel ourput to the RLDIN pin
  // */
  // ,INFO(ADS1293_REG_AFE_PACE_CN,           0x0A)

  // /*
  // 2560 SPS / 512 HZ
  // R1 = 4
  // R2 = 5
  // R3 = 4
  // */
  // ,INFO(ADS1293_REG_R2_RATE,               0x02)
  // ,INFO(ADS1293_REG_R3_RATE1,              0x01)
  // ,INFO(ADS1293_REG_R3_RATE2,              0x01)
  // ,INFO(ADS1293_REG_R3_RATE3,              0x01)
  // ,INFO(ADS1293_REG_R1_P_DRATE,            0x00)

  // /*
  // CH1 ECG as DRDYB source
  // */
  // ,INFO(ADS1293_REG_DRDYB_SRC,             0x08)

  // /*
  // Enable loop back read on CH1, CH2, CH3
  // */
  // ,INFO(ADS1293_REG_ALARM_FILTER,          0x33)
  // ,INFO(ADS1293_REG_CH_CNFG,               0x30)
  // //  +===============================+=======+

   INFO(ADS1293_REG_FLEX_CH1_CN, 0x11)
  ,INFO(ADS1293_REG_FLEX_CH2_CN, 0x19)
  ,INFO(ADS1293_REG_CMDET_EN, 0x07)
  ,INFO(ADS1293_REG_RLD_CN, 0x04)
  ,INFO(ADS1293_REG_OSC_CN, 0x04)
  ,INFO(ADS1293_REG_AFE_SHDN_CN, 0x24)
  ,INFO(ADS1293_REG_R2_RATE, 0x02)
  ,INFO(ADS1293_REG_R3_RATE1, 0x02)
  ,INFO(ADS1293_REG_R3_RATE2, 0x02)
  ,INFO(ADS1293_REG_DRDYB_SRC, 0x08)
  ,INFO(ADS1293_REG_CH_CNFG, 0x30)
  ,INFO(ADS1293_REG_CONFIG, 0x01)
};
#undef INFO

/* Public function prototypes ----------------------------------------- */

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __ADS1293_DEF_H

/* End of file -------------------------------------------------------- */
