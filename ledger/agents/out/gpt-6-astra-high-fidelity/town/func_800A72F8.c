#include "common.h"

extern u32 D_80100D94[];
extern u8 D_80083160[];
extern void *D_80089110[];

extern s32 func_80094AA0(s32, s32, s32);

#ifdef NON_MATCHING
#define OLD_GCC_KEEP(var) ((void)0)
#else
#define OLD_GCC_KEEP(var) __asm__ __volatile__("" : "=r"(var) : "0"(var))
#endif

void func_800A4A58(void)
{
    s32 target;
    u8 *base;
    u32 state;
    s32 value;
    u32 *clear;
    static void *const keepalive[] = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4, &&case_5
    };

    base = D_80083160;
    if (D_80100D94[0] == 0) {
        goto done;
    }
    state = D_80100D94[0];
    if (state >= 6) {
        goto done;
    }
    goto *D_80089110[state];

case_0:
    base[0xA8] = 0x80;
    base[0xA9] = 0x80;
    /* MATCH: Keep the case stores separate, with the last store in the jump delay slot. */
    __asm__ __volatile__("" ::: "memory");
    base[0xAA] = 0x80;
    goto clear_state;

case_1:
    {
        clear = (u32 *)0x80100000;
        OLD_GCC_KEEP(clear);
        base[0xA8] = 0;
        base[0xA9] = 0;
        base[0xAA] = 0;
        goto clear_store;
    }

case_2:
    base[0xA8] = 0x40;
    base[0xA9] = 0x40;
    /* MATCH: Keep the case stores separate, with the last store in the jump delay slot. */
    __asm__ __volatile__("" ::: "memory");
    base[0xAA] = 0x40;
    goto clear_state;

case_3:
    target = 0x80;
    goto update;

case_4:
    target = 0;
    goto update;

case_5:
    target = 0x40;
    OLD_GCC_KEEP(target);
update:
    target &= 0xFF;
    value = func_80094AA0(base[0xA8], target, 8);
    base[0xA8] = value;
    base[0xA9] = value;
    base[0xAA] = value;
    if ((value & 0xFF) == target) {
clear_state:
        __asm__ __volatile__("" ::: "memory");
        clear = (u32 *)0x80100000;
clear_store:
        clear[0xD94 / 4] = 0;
    }

done:
    return;
}
