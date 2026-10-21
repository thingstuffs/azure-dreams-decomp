#include "common.h"
#include "engine/runtime.h"
#include "sdk/libcd.h"

typedef struct S_80083958 {
    /* 0x0 */ u32 unk0;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 unk5;
    /* 0x6 */ u16 counter1;
    /* 0x8 */ u16 counter2;
    /* 0xA */ u16 flags;
} S_80083958;

extern S_80083958 cd_driver_prefix;

/* Increment both retry counters, resetting counter1 and initializing the CD when counter1 reaches 0x401. */
void cd_inc_retry_counters(void)
{
    cd_driver_prefix.counter2++;
    cd_driver_prefix.counter1++;
    if (cd_driver_prefix.counter1 >= 0x401) {
        cd_driver_prefix.counter1 = 0;
        CdInit();
    }
}
