#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_8006A3A4();
extern s32 func_8052B158() __attribute__((noreturn));
extern s32 func_8052B1D8() __attribute__((noreturn));
extern s32 D_80084D5C;

s32 func_80810454(void *arg0, void *arg1) {
    s16 state;

    if (FIELD(FIELD(arg0, void *, 4), s16, 0x18) == 2) {
        FIELD(arg0, s16, 0) = 3;
    }
    state = FIELD(arg0, s16, 0);
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

        position = FIELD(arg1, s32, 8);
        position += 0x100000;
        FIELD(arg1, s32, 8) = position;
        if (position >= (s32)0xFF900000) {
            FIELD(arg0, u16, 2) = 0;
            FIELD(arg1, s32, 0x14) = -0x40000;
            return func_8052B158();
        }
        return -0x40000;
    }

state_1: {
        s32 old_speed;
        s32 position;
        s32 speed;

        position = FIELD(arg1, volatile s32, 8);
        old_speed = FIELD(arg1, volatile s32, 0x14);
        speed = FIELD(arg1, volatile s32, 0x14);
        position += old_speed;
        speed += 0x4000;
        FIELD(arg1, s32, 8) = position;
        FIELD(arg1, s32, 0x14) = speed;
        if (speed == 0x40000) {
            FIELD(arg0, s16, 0) = 2;
            return func_8052B1D8(old_speed);
        }
        return 0x40000;
    }

state_2: {
        s32 position;
        register s32 result ASM_REG("$2");
        s32 speed;

        position = FIELD(arg1, s32, 8);
        speed = FIELD(arg1, s32, 0x14);
        position += speed;
        FIELD(arg1, s32, 8) = position;
        result = FIELD(arg1, s32, 0x14);
        result -= 0x8000;
        FIELD(arg1, s32, 0x14) = result;
        if (result == -0x40000) {
            FIELD(arg0, s16, 0) = 1;
            return func_8052B1D8();
        }
        return result;
    }

state_f0: {
        s32 result;
        u16 phase;

        phase = (FIELD(arg0, u16, 2) + 1) & 0x7F;
        FIELD(arg0, u16, 2) = phase;
        result = func_8006A3A4(phase << 6);
        FIELD(arg1, s32, 8) = (result << 7) + (s32)0xFF900000;
        return func_8052B1D8();
    }

state_3: {
        register s32 result ASM_REG("$2");

        result = FIELD(arg1, s32, 8);
        result -= 0x100000;
        FIELD(arg1, s32, 8) = result;
        if (result <= (s32)0xFE000000) {
            FIELD(arg0, u16, -2) |= 0x8000;
            result = D_80084D5C;
            result |= 0x8000;
            D_80084D5C = result;
        }
        return result;
    }
}
