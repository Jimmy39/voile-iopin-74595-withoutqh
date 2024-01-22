#ifndef __VOILE_IOPIN_74595_WITHOUTQH_H__
#define __VOILE_IOPIN_74595_WITHOUTQH_H__

#include "voile_interface_iopin.h"
#include "voile_74595.h"

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
 * @brief Initialise or reinitialise a IO and set IO mode and default output value
 * 
 * @param[in] this :[voile_const_internal_ioPin_74595_withoutQH_t *]This ioPin object.
 * @param[in] mode :[voile_io_mode_t]Which mode select to use @ref voile_io_mode_t.
 * @param[in] value :[bool](option when input mode)If 0 clear the IO, 1 set it. Input mode will ignore this param.
 * @return voile_status_t.
 *
 * @par Sample
 * @code {.C}
 * voile_ioPin_Operate_Init_74595_withoutQH(&myIO, IOmodePushPull, 1);
 * @endcode
 * 
 * @details 
 * 74595 only support the push-pull mode.
 * 
 */
voile_status_t voile_ioPin_Operate_Init_74595_withoutQH(voile_const_internal_ioPin_74595_withoutQH_t *);

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
 * @return voile_status_t.
 *
 * @par Sample
 * @code {.C}
 * voile_ioPin_Operate_Write_74595_withoutQH(&myIO, 1);
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
 * @return voile_status_t.
 *
 * @par Sample
 * @code {.C}
 * voile_ioPin_Operate_Taggle_74595_withoutQH(&myIo);
 * @endcode
 *  
 */
voile_status_t voile_ioPin_Operate_Taggle_74595_withoutQH(voile_const_internal_ioPin_74595_withoutQH_t *);

/**
 * @brief Get state of a single specified IO output
 * 
 * @param[in] this :[voile_const_internal_ioPin_74595_withoutQH_t *]This ioPin object.
 * @param[out] value :[bool *]Current state of the GPIO output. 0 for low, 1 for high.
 * @return voile_status_t.
 *
 * @par Sample
 * @code {.C}
 * bool value;
 * voile_ioPin_Operate_ReadRegister_74595_withoutQH(&myIO, &value);
 * @endcode
 *  
 */
voile_status_t voile_ioPin_Operate_ReadRegister_74595_withoutQH(voile_const_internal_ioPin_74595_withoutQH_t *, bool *);


/**
 * @brief Get state of a single io output
 * 
 * @param[in] this :[voile_const_internal_ioPin_74595_withoutQH_t *]This ioPin object.
 * @return [bool]Current state of the IO init. 0 for not init, 1 for init.
 *
 * @par Sample
 * @code {.C}
 * value = voile_ioPin_Get_Mode_74595_withoutQH(&myIO);
 * @endcode
 *  
 */
bool voile_ioPin_Get_Mode_74595_withoutQH(voile_const_internal_ioPin_74595_withoutQH_t *);

// 74595 can't read io
#define voile_ioPin_Get_Read_74595_withoutQH ((bool (*)(voile_const_internal_ioPin_74595_withoutQH_t *))voile_ReturnHardwareUnsupportedError)

/**
 * @brief Get state of a single specified IO output
 * 
 * @param[in] this :[voile_const_internal_ioPin_74595_withoutQH_t *]This ioPin object.
 * @return [bool]Current state of the GPIO output. 0 for low, 1 for high.
 *
 * @par Sample
 * @code {.C}
 * value = voile_ioPin_Get_ReadRegister_74595_withoutQH(&myIO);
 * @endcode
 *  
 */
bool voile_ioPin_Get_ReadRegister_74595_withoutQH(voile_const_internal_ioPin_74595_withoutQH_t *);

#endif // !__VOILE_IOPIN_74595_WITHOUTQH_H__

#ifdef __DEVICELIST_C__

#ifdef AUTOFUNCINIT
#undef AUTOFUNCINIT
#endif // AUTOFUNCINIT

// This micro use to init all function 
#define AUTOFUNCINIT VOILE_IOPIN_74595_WITHOUTQH_FUNCINIT

#endif // __DEVICELIST_C__
