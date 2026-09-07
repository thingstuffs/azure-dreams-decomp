#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_8009822C(void);
extern s32 func_80098DC0(void);

s32 func_800981D4(s32 arg0, void *arg1)
{
    s16 current;
    u16 raw;
    s32 result;

    current = FIELD(arg1, s16, 6);
    raw = FIELD(arg1, u16, 6);
    if (current < 0x300) {
        current = raw + 4;
        FIELD(arg1, s16, 6) = current;
        if (current < 0x300) {
            result = 0x300;
        } else {
            return func_8009822C();
        }
    } else {
        current = raw - 4;
        FIELD(arg1, s16, 6) = current;
        if (current < 0x301) {
            result = 0x300;
            FIELD(arg1, s16, 6) = result;
            result = func_80098DC0();
        } else {
            result = 0x300;
        }
    }
    return result;
}
