#include "common.h"

extern s32 func_80042900(void *, s32);
extern s32 func_800A6508(void);
extern s32 func_800A6D30(void);
extern s32 func_800CDCF0(void);

typedef struct {
    u8 pad[0xA];
    u16 value;
} CounterState;

extern CounterState D_80083460;
extern u8 D_800E3D40;
extern u8 *D_800E3D7C[];

s32 func_800CDC18(void *arg0)
{
    register s32 temp_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 divisor ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 remainder ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 var_s0;
    u8 temp_v1;

    if (*(u8 *)((u8 *)arg0 + 0x13) == 0) {
        var_s0 = 0;
        if (D_800E3D40 == 0) {
            temp_a0 = func_800A6D30() & 0xFFFF;
            temp_v1 = *(u8 *)((u8 *)arg0 + 3);
            if (temp_v1 != 0) {
                divisor = (s32)temp_v1;
                ASM_USE(divisor);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                remainder = temp_a0 % divisor;
                var_s0 = remainder;
            }
        }

        if (func_80042900(arg0, 10) << 16) {
            var_s0 = 0xFF;
        }

        if (var_s0 < 0x30) {
            *(u16 *)(D_800E3D7C[0] + 0xA2) |= 0x100;
            D_80083460.value += 1;
            return func_800CDCF0();
        }

        if (*(u8 *)((u8 *)arg0 + 0x13) == 0) {
            func_800A6508();
        }
    }
    return 1;
}
