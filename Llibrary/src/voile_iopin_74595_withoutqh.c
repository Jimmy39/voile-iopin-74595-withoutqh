/**
 * @file voile_iopin_74595_withoutqh.c
 * @author JimmyWang
 * @brief Define class ioPin for 54595
 * @version alpha-240123
 * 
 */
#include "voile_iopin_74595_withoutqh.h"

voile_const_ioPin_Operate_t voile_const_ioPin_Operate_74595_withoutQH = {
    .Init = (voile_status_t (*)(voile_const_ioPin_t *))voile_ioPin_Operate_Init_74595_withoutQH,
    .SetMode = (voile_status_t (*)(voile_const_ioPin_t *, voile_io_mode_t))voile_ioPin_Operate_SetMode_74595_withoutQH,
    .Write = (voile_status_t (*)(voile_const_ioPin_t *, bool))voile_ioPin_Operate_Write_74595_withoutQH,
    .Read = (voile_status_t (*)(voile_const_ioPin_t *, bool *))voile_ioPin_Operate_Read_74595_withoutQH,
    .Toggle = (voile_status_t (*)(voile_const_ioPin_t *))voile_ioPin_Operate_Taggle_74595_withoutQH,
    .ReadRegister = (voile_status_t (*)(voile_const_ioPin_t *, bool *))voile_ioPin_Operate_ReadRegister_74595_withoutQH
};

voile_const_ioPin_Get_t voile_const_ioPin_Get_74595_withoutQH = {
    .Mode = (voile_io_mode_t (*)(voile_const_ioPin_t *))voile_ioPin_Get_Mode_74595_withoutQH,
    .Read = (bool (*)(voile_const_ioPin_t *))voile_ioPin_Get_Read_74595_withoutQH,
    .ReadRegister = (bool (*)(voile_const_ioPin_t *))voile_ioPin_Get_ReadRegister_74595_withoutQH
};


voile_status_t voile_ioPin_Operate_Init_74595_withoutQH(voile_const_internal_ioPin_74595_withoutQH_t *this) {
    voile_status_t status;

    // Defination cheak
    if ((this->cascade == 0)|| \
        (this->chip == NULL)|| \
        (this->pinNumber >= 8*this->cascade)|| \
        (this->shiftRegisterMirror == NULL)) {
            return failure;
    }


    if (voile_ioPin_Get_Mode_74595_withoutQH(this) == IOuninit) {
        status = voile_74595_Operate_Init(this->chip);
        if (status != success) {
            return status;
        }
        voile_74595_Operate_ShiftBytes(this->chip, this->shiftRegisterMirror, this->cascade);
        voile_74595_Operate_Load(this->chip);
        voile_74595_Operate_Enable(this->chip);
    }
    return success;
}

voile_status_t voile_ioPin_Operate_Write_74595_withoutQH(voile_const_internal_ioPin_74595_withoutQH_t *this, bool value) {

    // Defination cheak
    if (this->shiftRegisterMirror == NULL) {
        return failure;
    }

    if (value) {
    *(this->shiftRegisterMirror+this->pinNumber/8) |= 1ul << (this->pinNumber%8);
    }
    else {
        *(this->shiftRegisterMirror+this->pinNumber/8) &= ~(1ul << (this->pinNumber%8));
    }
    if (voile_ioPin_Get_Mode_74595_withoutQH(this) == IOuninit) {
        return success;
    }
    else {
        voile_74595_Operate_ShiftBytes(this->chip, this->shiftRegisterMirror, this->cascade);
        voile_74595_Operate_Load(this->chip);
        return success;
    }
}

voile_status_t voile_ioPin_Operate_Taggle_74595_withoutQH(voile_const_internal_ioPin_74595_withoutQH_t *this) {

    // Defination cheak
    if (this->shiftRegisterMirror == NULL) {
        return failure;
    }

    *(this->shiftRegisterMirror+this->pinNumber/8) ^= 1ul << (this->pinNumber%8);
    if (voile_ioPin_Get_Mode_74595_withoutQH(this) == IOuninit) {
        return failure;
    }
    voile_74595_Operate_ShiftBytes(this->chip, this->shiftRegisterMirror, this->cascade);
    voile_74595_Operate_Load(this->chip);
    return success;
}

voile_status_t voile_ioPin_Operate_ReadRegister_74595_withoutQH(voile_const_internal_ioPin_74595_withoutQH_t *this, bool *value) {
    *value = !!(*(this->shiftRegisterMirror+this->pinNumber/8) & (1ul << (this->pinNumber%8)));
    return success;
}

bool voile_ioPin_Get_Mode_74595_withoutQH(voile_const_internal_ioPin_74595_withoutQH_t *this) {
    voile_io_mode_t ioMode;
    ioMode = this->chip->SER->Get->Mode(this->chip->SER);
    if ((ioMode != IOmodePushPull)&&(ioMode != IOmodeQuasiBidirectional)&&(ioMode != IOmodeOpenDrain)) {
        return IOuninit;
    }
    ioMode = this->chip->SRCLK->Get->Mode(this->chip->SRCLK);
    if ((ioMode != IOmodePushPull)&&(ioMode != IOmodeQuasiBidirectional)&&(ioMode != IOmodeOpenDrain)) {
        return IOuninit;
    }
    ioMode = this->chip->RCLK->Get->Mode(this->chip->RCLK);
    if ((ioMode != IOmodePushPull)&&(ioMode != IOmodeQuasiBidirectional)&&(ioMode != IOmodeOpenDrain)) {
        return IOuninit;
    }
    if (this->chip->_SRCLR != NULL) {
        ioMode = this->chip->_SRCLR->Get->Mode(this->chip->_SRCLR);
        if ((ioMode != IOmodePushPull)&&(ioMode != IOmodeQuasiBidirectional)&&(ioMode != IOmodeOpenDrain)) {
            return IOuninit;
        }
        if (this->chip->_SRCLR->Get->ReadRegister(this->chip->_SRCLR) == 0) {
            return IOuninit;
        }
    }
    if (this->chip->_OE != NULL) {
        ioMode = this->chip->_OE->Get->Mode(this->chip->_OE);
        if ((ioMode != IOmodePushPull)&&(ioMode != IOmodeQuasiBidirectional)&&(ioMode != IOmodeOpenDrain)) {
            return IOuninit;
        }
        if(this->chip->_OE->Get->ReadRegister(this->chip->_OE) == 1) {
            return IOuninit;
        }
    }
    return IOmodePushPull;
}

bool voile_ioPin_Get_ReadRegister_74595_withoutQH(voile_const_internal_ioPin_74595_withoutQH_t *this) {
    return !!(*(this->shiftRegisterMirror+this->pinNumber/8) & (1ul << (this->pinNumber%8)));
}
