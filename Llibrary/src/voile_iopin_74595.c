#include "voile_iopin_74595.h"

voile_const_ioPin_Operate_t voile_const_ioPin_Operate_74595 = {
    .Init = (voile_status_t (*)(const void *, voile_io_mode_t, ...))voile_ioPin_Operate_Init_74595,
    .Write = (voile_status_t (*)(const void *, bool))voile_ioPin_Operate_Write_74595,
    .Read = (voile_status_t (*)(const void *, bool *))voile_ioPin_Operate_Read_74595,
    .Toggle = (voile_status_t (*)(const void *))voile_ioPin_Operate_Taggle_74595,
    .ReadRegister = (voile_status_t (*)(const void *, bool *))voile_ioPin_Operate_ReadRegister_74595
};

voile_const_ioPin_Get_t voile_const_ioPin_Get_74595 = {
    .Read = (bool (*)(const void *))voile_ioPin_Get_Read_74595,
    .ReadRegister = (bool (*)(const void *))voile_ioPin_Get_ReadRegister_74595
};


voile_status_t voile_ioPin_Operate_Init_74595(voile_const_internal_ioPin_74595_t *this, voile_io_mode_t mode, bool value) {
    this->chip->SER->Operate->Init(this->chip->SER, IOmodePushPull, 0);
    this->chip->SRCLK->Operate->Init(this->chip->SRCLK, IOmodePushPull, 1);
    this->chip->RCLK->Operate->Init(this->chip->RCLK, IOmodePushPull, 0);
    if (this->chip->_SRCLR != NULL) {
        this->chip->_SRCLR->Operate->Init(this->chip->_SRCLR, IOmodePushPull, 0);
    }
    if (this->chip->_OE != NULL) {
        this->chip->_OE->Operate->Init(this->chip->_OE, IOmodePushPull, 1);
    }
    if (this->chip->QH_ != NULL) {
        this->chip->QH_->Operate->Init(this->chip->QH_, IOmodeInput);
    }
    return success;
}

voile_status_t voile_ioPin_Operate_Write_74595(voile_const_internal_ioPin_74595_t *ioPin_p, bool value) {
    return success;
}

voile_status_t voile_ioPin_Operate_Taggle_74595(voile_const_internal_ioPin_74595_t *ioPin_p) {
    return success;
}

voile_status_t voile_ioPin_Operate_ReadRegister_74595(voile_const_internal_ioPin_74595_t *ioPin_p, bool *value) {
    return success;
}

bool voile_ioPin_Get_ReadRegister_74595(voile_const_internal_ioPin_74595_t *ioPin_p) {
    return 0;
}
