#include <input_device.h>

class ThSensor: public InputDevice {
private:
    uint8_t pin;
public:
    ThSensor(uint16_t device_id, uint16_t threshold, long sample_time): InputDevice(device_id, threshold, sample_rate) {};
    bool init(uint8_t pin);
    uint16_t read();
};

bool ThSensor::init(uint8_t pin){
    this->pin = pin;
    this->read_timer = millis();
}

uint16_t ThSensor::read(){
    return digitalRead(this->pin);
}
