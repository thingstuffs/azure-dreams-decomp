#include "common.h"

typedef struct {
    u16 field_00;
    u16 field_02;
    u8 pad_04[8];
    s32 field_0C;
    s32 field_10;
    u16 field_14;
    u16 field_16;
} DungeonState;

extern DungeonState D_80083460;
extern s32 func_800A2B5C(void *);
extern s32 func_800ADAE4(void *, void *);
extern void func_800AB510(void) __attribute__((noreturn));

s32 func_800AB464(void *arg0, s32 arg1, void *arg2, void *arg3) {
    DungeonState *state;
    s32 result;

    if (*((u8 *)arg0 + 0x9B) == 0) {
        *((u8 *)arg3 + 0x71) &= 0x7F;
        state = &D_80083460;
        if (state->field_02 & 0x2000) {
            return 0;
        }
        if ((func_800A2B5C(arg3) << 16) != 0) {
            return 0;
        }

        result = func_800ADAE4(arg2, arg3);
        if ((result << 16) != 0) {
            state->field_0C = 0;
            state->field_14 -= 1;
            *((u8 *)arg0 + 0x9B) = 1;
            func_800AB510();
        }
    } else {
        result = 1;
    }
    return (s16)result;
}
