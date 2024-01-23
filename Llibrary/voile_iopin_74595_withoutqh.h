/**
 * @file voile_iopin_74595_withoutqh.h
 * @author JimmyWang
 * @brief Define class ioPin for 54595
 * @version alpha-240123
 * 
 */
#ifndef __VOILE_IOPIN_74595_WITHOUTQH_H__
#define __VOILE_IOPIN_74595_WITHOUTQH_H__

#include "voile_interface_iopin.h"
#include "voile_74595.h"

// This micro use to init all function 
#define VOILE_IOPIN_74595_WITHOUTQH_FUNCINIT \
    .Operate = &voile_const_ioPin_Operate_74595_withoutQH,    \
    .Get = &voile_const_ioPin_Get_74595_withoutQH

/**
 * @brief Operate 74595 as same as gpio for init
 * 
 */
typedef const struct{

    // Operate ioPin
    voile_const_ioPin_Operate_t *Operate;

    // Get something from io
    voile_const_ioPin_Get_t *Get;
    
    // Number of cascades
    uint8_t cascade;

    // 595 config
    voile_const_internal_74595_t *chip;

    // The number of pin, begin 0. For example, QC in 1st cascade is 2, QA in 2st cascade is 8
    uint8_t pinNumber;

    // The mirror of shift register
    uint8_t *shiftRegisterMirror;

} voile_const_internal_ioPin_74595_withoutQH_t;

// The functions operate the pin
extern voile_const_ioPin_Operate_t voile_const_ioPin_Operate_74595_withoutQH;

// The functions get date or status from pin
extern voile_const_ioPin_Get_t voile_const_ioPin_Get_74595_withoutQH;



/**
 * @brief Initialise or reinitialise a IO and enable it
 * @param[in] this :[voile_const_internal_ioPin_74595_withoutQH_t *]This ioPin object.
 * @return [voile_status_t] The status of function.
 *
 * @par Sample
 * @code {.C}
 * myIo.Operate->Init(&myIo);
 * @endcode
 * 
 * @note 
 * - You should set mode and write value for output befor init. 
 * 
 */
voile_status_t voile_ioPin_Operate_Init_74595_withoutQH(voile_const_internal_ioPin_74595_withoutQH_t *);

/**
 * @brief Set mode for sigle io
 * 
 * @param[in] this :[voile_const_internal_ioPin_74595_withoutQH_t *]This ioPin object.
 * @param[in] mode :[voile_io_mode_t]Which mode select to use.
 * @return [voile_status_t] The status of function.
 *
 * @par Sample
 * @code {.C}
 * myIo.Operate->SetMode(&myIo, IOmodePushPull);
 * @endcode
 * 
 * @details 
 * 74595 can't change mode, this function do nothing. It will return success when you set quasi-bidirectional mode, open-drain mode or push-pull mode. Otherwize it will return hardwareUnsupportedError.
 * 
 */
static inline voile_status_t voile_ioPin_Operate_SetMode_74595_withoutQH(voile_const_ioPin_t *this, voile_io_mode_t mode) {
    if ((mode == IOmodeQuasiBidirectional)||(mode == IOmodePushPull)||(mode == IOmodeOpenDrain)) {
        return success;
    }
    else {
        return hardwareUnsupportedError;
    }
}

/**
 * @brief Drive a single IO high/low
 * 
 * @param[in] this :[voile_const_internal_ioPin_74595_withoutQH_t *]This ioPin object.
 * @param[in] value :[bool]If 0 clear the IO, 1 set it.
 * @return [voile_status_t] The status of function.
 *
 * @par Sample
 * @code {.C}
 * myIo.Operate->Write(&myIo, 0);
 * @endcode
 *  
 */
voile_status_t voile_ioPin_Operate_Write_74595_withoutQH(voile_const_internal_ioPin_74595_withoutQH_t *, bool);

// 74595 can't read io
#define voile_ioPin_Operate_Read_74595_withoutQH ((voile_status_t (*)(voile_const_internal_ioPin_74595_withoutQH_t *, bool *))voile_ReturnHardwareUnsupportedError)

/**
 * @brief Toggle a single io
 * 
 * @param[in] this :[voile_const_internal_ioPin_74595_withoutQH_t *]This ioPin object.
 * @return [voile_status_t] The status of function.
 *
 * @par Sample
 * @code {.C}
 * myIo.Operate->Toggle(&myIo);
 * @endcode
 *  
 */
voile_status_t voile_ioPin_Operate_Taggle_74595_withoutQH(voile_const_internal_ioPin_74595_withoutQH_t *);

/**
 * @brief Get state of a single specified IO output
 * 
 * @param[in] this :[voile_const_internal_ioPin_74595_withoutQH_t *]This ioPin object.
 * @param[out] value :[bool *]Current state of the GPIO output. 0 for low, 1 for high.
 * @return [voile_status_t] The status of function.
 *
 * @par Sample
 * @code {.C}
 * bool value;
 * myIo.Operate->ReadRegister(&myIo, &i);
 * @endcode
 *  
 */
voile_status_t voile_ioPin_Operate_ReadRegister_74595_withoutQH(voile_const_internal_ioPin_74595_withoutQH_t *, bool *);


/***************Get*********************/

/**
 * @brief Get mode of a single
 * 
 * @param[in] this :[ voile_const_internal_ioPin_74595_withoutQH_t *] This ioPin object.
 * @return [voile_io_mode_t] The mode of the single io.
 *
 * @par Sample
 * @code {.C}
 * if (myIo.Get->Mode(&myIo) == IOuninit) {
 *  ;
 * }
 * @endcode
 * 
 * @details 
 * If the io controled 74595 have not initialized, this function will return IOuninit, other return IOmodePushPull.
 *  
 */
bool voile_ioPin_Get_Mode_74595_withoutQH(voile_const_internal_ioPin_74595_withoutQH_t *);

// 74595 can't read io
#define voile_ioPin_Get_Read_74595_withoutQH ((bool (*)(voile_const_internal_ioPin_74595_withoutQH_t *))voile_ReturnHardwareUnsupportedError)

/**
 * @brief Get state of a single specified IO output
 * 
 * @param[in] this :[voile_const_internal_ioPin_74595_withoutQH_t *]This ioPin object.
 * @return [bool]Current state of the IO output. 0 for low, 1 for high.
 *
 * @par Sample
 * @code {.C}
 * bool i = myIo.Get->ReadRegister(&myIo);
 * @endcode
 *  
 */
bool voile_ioPin_Get_ReadRegister_74595_withoutQH(voile_const_internal_ioPin_74595_withoutQH_t *);

#endif // !__VOILE_IOPIN_74595_WITHOUTQH_H__

#ifdef __DEVICELIST_C__

#ifdef AUTOFUNCINIT
#undef AUTOFUNCINIT
#endif // AUTOFUNCINIT

#define AUTOFUNCINIT VOILE_IOPIN_74595_WITHOUTQH_FUNCINIT

#endif // __DEVICELIST_C__
