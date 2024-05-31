//
// Created by xiaoxianghui on 2023/3/9.
//

#include "battery.h"
#include <stdlib.h>

static uint16_t sgBatteryFullCount;
static uint16_t sgBatteryTrickleChargeCount;
static uint8_t sgBatteryPercent;

static uint16_t sgMaxVoltage;
static uint16_t sgMinCurrent;

typedef struct {
    uint16_t voltage;
    uint8_t percent;
} batteryVoltageSamplePoint;

typedef struct {
    uint16_t current;
    uint8_t percent;
} batteryCurrentSamplePoint;

static batteryState sgBatteryStatus;

static const batteryVoltageSamplePoint sgDischargeVoltageTable[] = BATTERY_DISCHARGE_VOLTAGE_TAB;

static const batteryVoltageSamplePoint sgChargeVoltageTable[] = BATTERY_CHARGE_VOLTAGE_TAB;

static const batteryCurrentSamplePoint sgTrickleChargeCurrentTable[] = BATTERY_TRICKLE_CHARGE_CURRENT_TAB;

#define BATTERY_FLUCTUATION_V       10 /**< unit:mV */

bool batteryIsPlugIn(void) {
    /// \todo 需要相应接口
    bool status = rand() % 2 ? true : false;
    return status;
}

uint16_t batteryGetVoltage(void) {
    /// \todo 需要相应接口
    return (uint16_t)(rand() % (BATTERY_FULL_V - 3000) + 3000 + 1);
}

uint16_t batteryGetCurrent(void) {
    /// \todo 需要相应接口
    return (uint16_t)(rand() % (BATTERY_CHARGE_CURRENT - BATTERY_FULL_A) + BATTERY_FULL_A + 1);
}

batteryState batteryGetChargeStatus(void) {
    if (!batteryIsPlugIn()) {
        sgBatteryStatus = batteryState_Discharge;
        sgBatteryTrickleChargeCount = 0;
        sgBatteryFullCount = 0;
        sgMaxVoltage = 0;
        sgMinCurrent = 0;
    } else if (sgBatteryFullCount >= BATTERY_FULL_COUNT) {
        sgBatteryStatus = batteryState_ChargeFull;
    } else if (sgBatteryFullCount) {
        sgBatteryStatus = batteryState_TrickleCharge;
    } else {
        sgBatteryStatus = batteryState_Charge;
    }
    return sgBatteryStatus;
}

static uint8_t sBatteryCalculatePercent(const batteryVoltageSamplePoint *voltageTable, const uint8_t index,
                                               uint16_t stepValue, const uint16_t stepTotalValue) {
    stepValue = MIN(stepValue, stepTotalValue);
    uint8_t percent = voltageTable[index - 1].percent +
                      stepValue * (voltageTable[index].percent - voltageTable[index - 1].percent) / stepTotalValue;
    return percent;
}

uint8_t batteryGetDirectPercent(void) {
    uint16_t voltage = batteryGetVoltage();
#if BATTERY_PIN_CHARGE_CURRENT_DET != NO_CONFIG_PIN
    uint16_t current = batteryGetCurrent();
#endif
    const batteryVoltageSamplePoint *voltageTable;
    size_t voltageTableSize;
    bool isPlugIn = batteryIsPlugIn();
    batteryState status = batteryGetChargeStatus();
    if (isPlugIn) {
        voltageTable = sgChargeVoltageTable;
        voltageTableSize = ARRAY_SIZE(sgChargeVoltageTable);
    } else {
        voltageTable = sgDischargeVoltageTable;
        voltageTableSize = ARRAY_SIZE(sgDischargeVoltageTable);
    }
    size_t i;
    for (i = 0; i < voltageTableSize; ++i) if (voltage <= voltageTable[i].voltage) break;
    uint8_t percent;
    if (i == 0) {
        percent = 0;
    } else if ((!isPlugIn && i == voltageTableSize) || status == batteryState_ChargeFull) {
        percent = 100;
    } else if (status == batteryState_TrickleCharge) {
#if BATTERY_PIN_CHARGE_CURRENT_DET != NO_CONFIG_PIN
        size_t currentTableSize = ARRAY_SIZE(sgTrickleChargeCurrentTable);
        for (i = 0; i < currentTableSize; ++i)
            if (current > sgTrickleChargeCurrentTable[i].current) break;
        if (i == currentTableSize) i--;
        percent = sgTrickleChargeCurrentTable[i].percent;
#else
        percent = sBatteryCalculatePercent(voltageTable, voltageTableSize - 1, sgBatteryFullCount, BATTERY_FULL_COUNT);
#endif
    } else {
        percent = sBatteryCalculatePercent(voltageTable, i, voltage - voltageTable[i - 1].voltage,
                                           voltageTable[i].voltage - voltageTable[i - 1].voltage);
    }
    return percent;
}

__attribute__((unused)) uint8_t batteryGetPercent(void) {
    uint8_t percent = batteryGetDirectPercent();
    bool isPlugIn = batteryIsPlugIn();
    if (isPlugIn && batteryGetChargeStatus() != batteryState_ChargeFull) {
        percent = (percent == 100) ? 99 : percent;
    }
    sgBatteryPercent = isPlugIn ? MAX(sgBatteryPercent, percent) : MIN(sgBatteryPercent, percent);
    return sgBatteryPercent;
}

__attribute__((unused)) void batteryFullCount(void) {
    if (!batteryIsPlugIn()) {
        sgBatteryTrickleChargeCount = 0;
        sgBatteryFullCount = 0;
        sgMaxVoltage = 0;
        sgMinCurrent = 0;
        return;
    }
    uint16_t voltage = batteryGetVoltage();
#if BATTERY_PIN_CHARGE_CURRENT_DET != NO_CONFIG_PIN
    uint16_t current = batteryGetCurrent();
#endif
    if (sgBatteryTrickleChargeCount < BATTERY_TRICKLE_CHARGE_COUNT &&
        voltage > BATTERY_TRICKLE_CHARGE_DET_V - BATTERY_FLUCTUATION_V) {
        sgBatteryTrickleChargeCount++;
    }
    if (sgMaxVoltage < voltage - BATTERY_FLUCTUATION_V) {
        sgMaxVoltage = voltage;
        sgBatteryTrickleChargeCount = 0;
    }
#if BATTERY_PIN_CHARGE_CURRENT_DET != NO_CONFIG_PIN
    if (sgMinCurrent == 0 || sgMinCurrent > current) {
        sgMinCurrent = current;
        sgBatteryTrickleChargeCount = 0;
    }
#endif
#ifdef BATTERY_MAX_POWER_LIMIT_DISABLED
    if (sgBatteryTrickleChargeCount >= BATTERY_TRICKLE_CHARGE_COUNT) {
#else
    if (sgBatteryTrickleChargeCount >= BATTERY_TRICKLE_CHARGE_COUNT ||
        voltage >= BATTERY_FULL_V - BATTERY_FLUCTUATION_V) {
#endif
        if (sgBatteryFullCount < BATTERY_FULL_COUNT) sgBatteryFullCount++;
    } else {
        sgBatteryFullCount = 0;
    }
}
