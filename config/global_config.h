//
// Created by xiaoxianghui on 2023/3/10.
//

#ifndef TEST_GLOBAL_CONFIG_H
#define TEST_GLOBAL_CONFIG_H

#include "hardware_config.h"

/**
 * @addtogroup Battery
 * @{
 */
#define BATTERY_FULL_V                          4200 /**< unit:mV */
#define BATTERY_FULL_A                          5 /**< unit:mA */
#define BATTERY_CHARGE_CURRENT                  100 /**< unit:mA */

#define BATTERY_TRICKLE_CHARGE_COUNT            600 /**< unit:Sec */
#define BATTERY_TRICKLE_CHARGE_DET_V            4160 /**< unit:mV */

#define BATTERY_FULL_COUNT                      (1800 - BATTERY_TRICKLE_CHARGE_COUNT) /**< unit:Sec */
#if BATTERY_PIN_CHARGE_CURRENT_DET != NO_CONFIG_PIN
#undef BATTERY_FULL_COUNT
#define BATTERY_FULL_COUNT                      5 /**< unit:Sec */
#endif

#define BATTERY_MAX_POWER_LIMIT_DISABLED

/// 电量表采样点电量需要单调递增，采样点至少要有 0% 100% 进入涓流充电 的三个采样点
#define BATTERY_DISCHARGE_VOLTAGE_TAB           { \
    {3000, 0}, \
    {3617, 5}, \
    {3661, 10}, \
    {3712, 20}, \
    {3739, 30}, \
    {3762, 40}, \
    {3796, 50}, \
    {3845, 60}, \
    {3911, 70}, \
    {3978, 80}, \
    {4066, 90}, \
    {4182, 100}, \
}
#define BATTERY_CHARGE_VOLTAGE_TAB              { \
    {3354, 0}, \
    {3749, 5}, \
    {3774, 10}, \
    {3836, 20}, \
    {3862, 30}, \
    {3890, 40}, \
    {3925, 50}, \
    {3973, 60}, \
    {4032, 70}, \
    {4102, 80}, \
    {4200, 90}, \
    {4200, 100}, \
}
#define BATTERY_TRICKLE_CHARGE_CURRENT_TAB      { \
    {92, 90}, \
    {81, 91}, \
    {72, 92}, \
    {62, 93}, \
    {53, 94}, \
    {44, 95}, \
    {35, 96}, \
    {27, 97}, \
    {19, 98}, \
    {11, 99}, \
    {5,  100}, \
}
/** @} */

#endif //TEST_GLOBAL_CONFIG_H
