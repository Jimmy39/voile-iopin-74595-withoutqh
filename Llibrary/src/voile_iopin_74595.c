#include "voile_iopin_74595.h"

#include "voile_uart_rp2040.h"

extern voile_const_uart_t uart;


voile_const_ioPin_Operate_t voile_const_ioPin_Operate_74595 = {
    .Init = (voile_status_t (*)(const void *, voile_io_mode_t, ...))voile_ioPin_Operate_Init_74595,
    .Write = (voile_status_t (*)(const void *, bool))voile_ioPin_Operate_Write_74595,
    .Read = (voile_status_t (*)(const void *, bool *))voile_ioPin_Operate_Read_74595,
    .Toggle = (voile_status_t (*)(const void *))voile_ioPin_Operate_Taggle_74595,
    .ReadRegister = (voile_status_t (*)(const void *, bool *))voile_ioPin_Operate_ReadRegister_74595
};

voile_const_ioPin_Get_t voile_const_ioPin_Get_74595 = {
    .IfInit = (bool (*)(const void *))voile_ioPin_Get_IfInit_74595,
    .Read = (bool (*)(const void *))voile_ioPin_Get_Read_74595,
    .ReadRegister = (bool (*)(const void *))voile_ioPin_Get_ReadRegister_74595
};


voile_status_t voile_ioPin_Operate_Init_74595(voile_const_internal_ioPin_74595_t *this, voile_io_mode_t mode, bool value) {
    int8_t i;
    uint8_t date;
    if ((this->chip->state == NULL)&&(this->chip->QH_ == NULL)) {
        return failure;
    }
    if (!voile_ioPin_Get_IfInit_74595(this)) {
        voile_74595_Operate_Init(this->chip);
        for (i = this->cascade - 1; i >= 0; i--) {
            if ((!value)&&(this->pinNumber/8 == i)) {
                date = 0xff^(1ul << (this->pinNumber%8));
            }
            else {
                date = 0xff;
            }
            voile_74595_Operate_ShiftBytes(this->chip, &date, 1);
            if (this->chip->state != NULL) {
                *(this->chip->state+i) = date;
            }
    uart.Operate->Transmit(&uart, i);
        }
        voile_74595_Operate_Load(this->chip);
        if ((mode == IOmodeQuasiBidirectional)||(mode == IOmodePushPull)||(mode == IOmodeOpenDrain)) {
            voile_74595_Operate_Enable(this->chip);
        }
    }
    else {
        voile_ioPin_Operate_Write_74595(this, value);
    }
    return success;
}

voile_status_t voile_ioPin_Operate_Write_74595(voile_const_internal_ioPin_74595_t *this, bool value) {
    if (this->chip->state != NULL) {
        if (value) {
            *(this->chip->state+this->pinNumber/8) |= 1ul << (this->pinNumber%8);
        }
        else {
            *(this->chip->state+this->pinNumber/8) &= ~(1ul << (this->pinNumber%8));
        }
        voile_74595_Operate_ShiftBytes(this->chip, this->chip->state, this->cascade);
    uart.Operate->Transmit(&uart, *(this->chip->state));
        voile_74595_Operate_Load(this->chip);
        return success;
    }
    else if (this->chip->QH_ != NULL) {
        
        return success;
    }
    else {
        return failure;
    }
}

voile_status_t voile_ioPin_Operate_Taggle_74595(voile_const_internal_ioPin_74595_t *ioPin_p) {
    return success;
}

voile_status_t voile_ioPin_Operate_ReadRegister_74595(voile_const_internal_ioPin_74595_t *ioPin_p, bool *value) {
    return success;
}

bool voile_ioPin_Get_IfInit_74595(voile_const_internal_ioPin_74595_t *this) {
    return 0;
}

bool voile_ioPin_Get_ReadRegister_74595(voile_const_internal_ioPin_74595_t *ioPin_p) {
    return 0;
}
