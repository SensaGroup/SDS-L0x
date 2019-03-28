#include "sensor.h"
#include "lidar_info.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
//servo 10
bool sensor_init() {
    if (!lox.begin()) {
        return 0;
    } else {
        return 1;
    }      
}

bool sensor_detect() {

    VL53L0X_RangingMeasurementData_t measure;
    
    lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

    if (measure.RangeStatus != 4) {  // phase failures have incorrect data
        if(measure.RangeMilliMeter <= sensor_upper_range && measure.RangeMilliMeter >= sensor_lower_range) {
            Serial.print("sensor - detected at: "); Serial.println(measure.RangeMilliMeter);
            lidar_set_detected(1);
            return true;
        } else {
            lidar_set_detected(0);
            return false;
        }
    } else {
        Serial.println("sensor - out of range");
        lidar_set_detected(0);
        return false;
    }
    
}