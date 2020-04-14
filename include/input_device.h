#include <device.h>

class InputDevice: public Device {
    protected:
        uint16_t value;
        uint16_t threshold;
        long read_timer;
        long sample_rate;
        virtual uint16_t read();
    public:
        InputDevice(uint16_t device_id, uint16_t threshold, long sample_rate):Device(device_id, INPUT_DEVICE_TYPE){
            this->sample_rate = sample_rate;
            this->threshold = threshold;
        }
        virtual bool hasChange();
        uint16_t getValue();
        DataPack run(DataPack input);
};

bool InputDevice::hasChange(){
    if(millis()-this->read_timer >= this->sample_rate){
        this->read_timer = millis();
        uint16_t temp_value = this->read();
        if(abs(temp_value - value) >= threshold){
            this->value = temp_value;
            return true;
        }
    }
    return false;
}

uint16_t InputDevice::getValue(){
    return this->value;
}

DataPack InputDevice::run(DataPack input){
    if(this->hasChange()){
        input.addData(DEVICE_ID_KEY, this->device_id);
        input.addData(DEVICE_TYPE_KEY, this->type);
        input.addData(VALUE_KEY, this->getValue());
    }
    return input;
}

