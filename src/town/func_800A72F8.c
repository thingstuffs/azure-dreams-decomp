#include "common.h"

extern u32 D_80100D94[];
extern u8 D_80083160[];
extern void *D_80089110[];

extern s32 func_80094AA0(s32, s32, s32);
extern void func_800A4AF4(void);
extern void func_800A4B20(void) __attribute__((noreturn));
extern void func_800A4B24(void) __attribute__((noreturn));

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
    base[0xAA] = 0x80;
    func_800A4B20();

case_1:
    {
        u32 *clear = (u32 *)0x80100000;
        OLD_GCC_KEEP(clear);
        base[0xA8] = 0;
        base[0xA9] = 0;
        base[0xAA] = 0;
        func_800A4B24();
    }

case_2:
    base[0xA8] = 0x40;
    base[0xA9] = 0x40;
    base[0xAA] = 0x40;
    func_800A4B20();

case_3:
    target = 0x80;
    func_800A4AF4();
    OLD_GCC_KEEP(target);
    return;

case_4:
    func_800A4AF4();
    target = 0;
    OLD_GCC_KEEP(target);
    return;

case_5:
    target = 0x40;
    OLD_GCC_KEEP(target);
    target &= 0xFF;
    value = func_80094AA0(base[0xA8], target, 8);
    base[0xA8] = value;
    base[0xA9] = value;
    base[0xAA] = value;
    if ((value & 0xFF) == target) {
        __asm__ __volatile__("" ::: "memory");
        D_80100D94[0] = 0;
    }

done:
    return;
}
