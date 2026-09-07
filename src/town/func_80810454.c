#include "common.h"

typedef struct S_80810454_0_pre {
    u16 unk_00;
} S_80810454_0_pre;   /* the 0x2 bytes before arg0 in func_80810454, addressed as arg0[-1] */

typedef struct S_80810454_0 {
    s16 unk_00;
    u16 unk_02;
    void * unk_04;
} S_80810454_0;   /* arg0 in func_80810454 */

typedef struct S_80810454_1 {
    u8 pad_00[0x8];
    union { s32 s; volatile s32 u; } unk_08;   /* accessed as both */
    u8 pad_0C[0x8];
    union { s32 s; volatile s32 u; } unk_14;   /* accessed as both */
} S_80810454_1;   /* arg1 in func_80810454 */

typedef struct S_80810454_2 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_80810454_2;   /* ((S_80810454_0 *)arg0)->unk_04 in func_80810454 */



extern s32 func_8006A3A4();
extern s32 func_8052B158() __attribute__((noreturn));
extern s32 func_8052B1D8() __attribute__((noreturn));
extern s32 D_80084D5C;

s32 func_80810454(void *arg0, S_80810454_1 *arg1) {
    s16 state;

    if (((S_80810454_2 *)(((S_80810454_0 *)arg0)->unk_04))->unk_18 == 2) {
        ((S_80810454_0 *)arg0)->unk_00 = 3;
    }
    state = ((S_80810454_0 *)arg0)->unk_00;
    if (state != 2) {
        if (state < 3) {
            if (state != 0) {
                if (state == 1) {
                    goto state_1;
                }
                return func_8052B1D8();
            }
            goto state_0;
        }
        if (state == 3) {
            goto state_3;
        }
        if (state == 0xF0) {
            goto state_f0;
        }
        return func_8052B1D8();
    }
    goto state_2;

state_0: {
        s32 position;

        position = arg1->unk_08.s;
        position += 0x100000;
        arg1->unk_08.s = position;
        if (position >= (s32)0xFF900000) {
            ((S_80810454_0 *)arg0)->unk_02 = 0;
            arg1->unk_14.s = -0x40000;
            return func_8052B158();
        }
        return -0x40000;
    }

state_1: {
        s32 old_speed;
        s32 position;
        s32 speed;

        position = arg1->unk_08.u;
        old_speed = arg1->unk_14.u;
        speed = arg1->unk_14.u;
        position += old_speed;
        speed += 0x4000;
        arg1->unk_08.s = position;
        arg1->unk_14.s = speed;
        if (speed == 0x40000) {
            ((S_80810454_0 *)arg0)->unk_00 = 2;
            return func_8052B1D8(old_speed);
        }
        return 0x40000;
    }

state_2: {
        s32 position;
        register s32 result ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
        s32 speed;

        position = arg1->unk_08.s;
        speed = arg1->unk_14.s;
        position += speed;
        arg1->unk_08.s = position;
        result = arg1->unk_14.s;
        result -= 0x8000;
        arg1->unk_14.s = result;
        if (result == -0x40000) {
            ((S_80810454_0 *)arg0)->unk_00 = 1;
            return func_8052B1D8();
        }
        return result;
    }

state_f0: {
        s32 result;
        u16 phase;

        phase = (((S_80810454_0 *)arg0)->unk_02 + 1) & 0x7F;
        ((S_80810454_0 *)arg0)->unk_02 = phase;
        result = func_8006A3A4(phase << 6);
        arg1->unk_08.s = (result << 7) + (s32)0xFF900000;
        return func_8052B1D8();
    }

state_3: {
        register s32 result ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */

        result = arg1->unk_08.s;
        result -= 0x100000;
        arg1->unk_08.s = result;
        if (result <= (s32)0xFE000000) {
            ((S_80810454_0_pre *)arg0)[-1].unk_00 |= 0x8000;
            result = D_80084D5C;
            result |= 0x8000;
            D_80084D5C = result;
        }
        return result;
    }
}
