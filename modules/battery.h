//
// Created by xiaoxianghui on 2023/3/9.
//

#ifndef TEST_BATTERY_H
#define TEST_BATTERY_H

#include "global_config.h"
#include "global_function.h"

/**
 * @defgroup Battery
 * @{
 */

typedef enum {
    batteryState_Discharge,
    batteryState_Charge,
    batteryState_TrickleCharge,
    batteryState_ChargeFull,
} batteryState;

bool batteryIsPlugIn(void);

uint16_t batteryGetVoltage(void);

uint16_t batteryGetCurrent(void);

batteryState batteryGetChargeStatus(void);

uint8_t batteryGetDirectPercent(void);

__attribute__((unused)) uint8_t batteryGetPercent(void);

/**
 * @brief 电池充满计数
 * @attention 此函数充电时调用，频率 1 Hz
 */
__attribute__((unused)) void batteryFullCount(void);

/** @} */

#endif //TEST_BATTERY_H
