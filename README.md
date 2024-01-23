# voile-iopin-74595-withoutQH
Operate 74595 as same as gpio in voile library.

For atomic Register Access, this library ues memory to save a mirror of shift register. Change the mirror in memory and wirite to shift register.

For more informations about voile library, see [voile-library](https://github.com/Jimmy39/voile-library).

## Dependence
**[voile-interface-iopin](https://github.com/Jimmy39/voile-interface-iopin)** : Define interface to use io.

**[voile-74595](https://github.com/Jimmy39/voile-74595)** : 74595 operation.

**[voile-library](https://github.com/Jimmy39/voile-library)** : Some common defination.

## Class voile_const_internal_ioPin_74595_withoutQH_t

This library defines struct ```voile_const_internal_ioPin_74595_withoutQH_t```:
```C
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
```

### Define

You should define and init struct at *devicelist.c*.

This is a example for 2 cascades of 74595:
```C
#define __DEVICELIST_C__


// GPIO defination
#include "voile_iopin_xxx.h"

// Define the io you use to control 74595
voile_const_internal_ioPin_xxx_t my595_RCLK = {
    // ...
    // It depends
};

// ...
// And other pin

#include "voile_iopin_xxx_end.h"

// 74595 defination
#include "voile_74595.h"

voile_const_internal_74595_t my595 = {
    // A micro to init all const function pointer srtuct
    AUTOFUNCINIT,

    // The pin you use to control 74595
    .RCLK = (voile_const_ioPin_t *)&my595_RCLK,
    .SER = (voile_const_ioPin_t *)&my595_SER,
    .SRCLK = (voile_const_ioPin_t *)&my595_SRCLK,
    ._OE = (voile_const_ioPin_t *)&my595__OE,
    ._SRCLR = (voile_const_ioPin_t *)&my595__SRCLR,
    // This library don't need QH', you can define it or set null
    .QH_ = NULL
};

#include "voile_74595_end.h"

// Define 75595 as ioPin
#include "voile_iopin_74595_withoutqh.h"

uint8_t cache_SN74595[2]  = {0xff, 0xff};
voile_const_internal_ioPin_74595_withoutQH_t myIoPin0 = {
    AUTOFUNCINIT,
    .cascade = 2,
    .chip = &my595,
    .pinNumber = 0,     // QA of the 1st 595 
    .shiftRegisterMirror = cache_SN74595
};
// ...
// Other pin
voile_const_internal_ioPin_74595_withoutQH_t myIoPin15 = {
    AUTOFUNCINIT,
    .cascade = 2,
    .chip = &my595,
    .pinNumber = 15,     // QH of the 2ed 595 
    .shiftRegisterMirror = cache_SN74595
};

#include "voile_iopin_74595_withoutqh_end.h"

```

### Declare

And declare at *devicelist.h* as struct ```voile_const_ioPin_t```

```C
#include "voile_interface_iopin.h"

extern voile_const_ioPin_t myIoPin0;
// ...
// Other pin
extern voile_const_ioPin_t myIoPin15;
```

struct ```voile_const_ioPin_t``` is the public part of struct ```voile_const_internal_ioPin_74595_withoutQH_t```, defined in [voile-interface-iopin](https://github.com/Jimmy39/voile-interface-iopin).

### Usage

See [voile-interface-iopin](https://github.com/Jimmy39/voile-interface-iopin).