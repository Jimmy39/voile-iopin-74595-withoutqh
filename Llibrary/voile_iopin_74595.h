#ifndef __VOILE_IOPIN_74595_H__
#define __VOILE_IOPIN_74595_H__

#include "voile_interface_iopin.h"

/**
 * @brief Operate 74595 as same as gpio
 * 
 */
typedef const struct{

    // Operate ioPin
    voile_const_ioPin_Operate_t *Operate;

    // Get something from io
    voile_const_ioPin_Get_t *Get;
    
    // Number of cascades
    const uint8_t cascade;

    // _SRCLR pin
    voile_const_ioPin_t *_SRCLR;

    // _OE pin
    voile_const_ioPin_t *_OE;
    
    // SRCLK pin
    voile_const_ioPin_t *SRCLK;
    
    // SER pin
    voile_const_ioPin_t *SER;
    
    // _RCLK pin
    voile_const_ioPin_t *RCLK;

    // How to read back io output state
    union {

        // Storige io state by memory
        struct {

            // Symbol
            uint8_t select  : 1;
            uint8_t         : 7;

            // Point to variable
            uint8_t *Memory;

        } byMemory;

        // Use QH' read shift register
        struct {
            // Symbol
            uint8_t         : 1;
            uint8_t select  : 1;
            uint8_t         : 6;

            // QH' pin
            voile_const_ioPin_t *QH_;

        } byQH;

    } readBackMode;

} voile_const_internal_ioPin_rp2040_t;

// The functions operate the pin
extern voile_const_ioPin_Operate_t voile_const_ioPin_Operate_74595;

// The functions get date or status from pin
extern voile_const_ioPin_Get_t voile_const_ioPin_Get_74595;



/**
 * @brief Initialise or reinitialise a IO and set IO mode and default output value
 * 
 * @param[in] this :[voile_const_internal_ioPin_rp2040_t *]This ioPin object.
 * @param[in] mode :[voile_io_mode_t]Which mode select to use @ref voile_io_mode_t.
 * @param[in] value :[bool](option when input mode)If 0 clear the IO, 1 set it. Input mode will ignore this param.
 * @return voile_status_t.
 *
 * @par Sample
 * @code {.C}
 * voile_ioPin_Operate_Init_74595(&myIO, IOmodePushPull, 1);
 * @endcode
 * 
 * @details 
 * 74595 only support the push-pull mode.
 * 
 */
voile_status_t voile_ioPin_Operate_Init_74595(voile_const_internal_ioPin_rp2040_t *, voile_io_mode_t, bool);

/**
 * @brief Drive a single IO high/low
 * 
 * @param[in] this :[voile_const_internal_ioPin_rp2040_t *]This ioPin object.
 * @param[in] value :[bool]If 0 clear the IO, 1 set it.
 * @return voile_status_t.
 *
 * @par Sample
 * @code {.C}
 * voile_ioPin_Operate_Write_74595(&myIO, 1);
 * @endcode
 *  
 */
voile_status_t voile_ioPin_Operate_Write_74595(voile_const_internal_ioPin_rp2040_t *, bool);

// 74595 can't read io
#define voile_ioPin_Operate_Read_74595 ((voile_status_t (*)(voile_const_internal_ioPin_rp2040_t *, bool *))voile_ReturnHardwareUnsupportedError)

/**
 * @brief Toggle a single io
 * 
 * @param[in] this :[voile_const_internal_ioPin_rp2040_t *]This ioPin object.
 * @return voile_status_t.
 *
 * @par Sample
 * @code {.C}
 * voile_ioPin_Operate_Taggle_74595(&myIo);
 * @endcode
 *  
 */
voile_status_t voile_ioPin_Operate_Taggle_74595(voile_const_internal_ioPin_rp2040_t *);

/**
 * @brief Get state of a single specified IO output
 * 
 * @param[in] this :[voile_const_internal_ioPin_rp2040_t *]This ioPin object.
 * @param[out] value :[bool *]Current state of the GPIO output. 0 for low, 1 for high.
 * @return voile_status_t.
 *
 * @par Sample
 * @code {.C}
 * bool value;
 * voile_ioPin_Operate_ReadRegister_74595(&myIO, &value);
 * @endcode
 *  
 */
voile_status_t voile_ioPin_Operate_ReadRegister_74595(voile_const_internal_ioPin_rp2040_t *, bool *);



// 74595 can't read io
#define voile_ioPin_Get_Read_74595 ((bool (*)(voile_const_internal_ioPin_rp2040_t *))voile_ReturnHardwareUnsupportedError)

/**
 * @brief Get state of a single specified IO output
 * 
 * @param[in] this :[voile_const_internal_ioPin_rp2040_t *]This ioPin object.
 * @return [bool]Current state of the GPIO output. 0 for low, 1 for high.
 *
 * @par Sample
 * @code {.C}
 * value = voile_ioPin_Get_ReadRegister_74595(&myIO);
 * @endcode
 *  
 */
bool voile_ioPin_Get_ReadRegister_74595(voile_const_internal_ioPin_rp2040_t *);

#endif // !__VOILE_IOPIN_74595_H__

#ifdef __DEVICELIST_C__

#ifdef FUNCINIT
#undef FUNCINIT
#endif // FUNCINIT

// This micro use to init all function 
#define FUNCINIT  \
    .Operate = &voile_const_ioPin_Operate_74595,    \
    .Get = &voile_const_ioPin_Get_74595

#endif // __DEVICELIST_C__
