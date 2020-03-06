#include "mbed.h"
#include "SHT21.h"

extern I2C sht;
Serial pc_class(USBTX, USBRX);

SHT21::SHT21(PinName sda, PinName scl) : sht(sda, scl)
{
    _address  = ADDRESS << 1;
}

int SHT21::catchTemp()
{
    char data_temp[2];
    data_temp[0] = T_TRIGGER_HOLD_MASTER;

    sht.write((_address), &data_temp[0], 1, true);
    wait_us(85);
    sht.read((_address), data_temp, 2, false);

    int _temp = data_temp[0] << 8 | data_temp[1];
    pc_class.printf("%d", _temp);
    return _temp;
}


int SHT21::catchHumid()
{
    char data_rh[2];
    data_rh[0] = RH_TRIGGER_HOLD_MASTER;

    sht.write((_address), &data_rh[0], 1, true);
    wait_us(85);
    sht.read((_address), data_rh, 2, false);

    int _rh = data_rh[0] << 8 | data_rh[1];
    
    return _rh;
}

void SHT21::arithmetics(char command)
{
    switch(command) {
        case RH_TRIGGER_HOLD_MASTER: {
            int rh_ = catchHumid() & ~0x0003;
            rh = -6.0 + 125.0/65536 * (double)rh_;
        }

        case T_TRIGGER_HOLD_MASTER: {
            int temp_ = catchTemp() & ~0x0003;
            temp = -46.85 + 175.72/65536 * (double)temp_;
        }

        default:
            break;
    }
}

double SHT21::getTemp()
{
    arithmetics(T_TRIGGER_HOLD_MASTER);
    return temp;
}

double SHT21::getHumid()
{
    arithmetics(RH_TRIGGER_HOLD_MASTER);
    return rh;
}