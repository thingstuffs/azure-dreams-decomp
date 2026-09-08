#include "common.h"

typedef struct {
    u8 pad_00[0x10];
    s32 field_10;
    u8 pad_14[0x08];
    s32 field_1C;
    u8 pad_20[0x68];
    u8 field_88;
} Func80039EF4State;

/* Decrements the script loop counter and rewinds the script while it remains nonnegative. */
void func_80039EF4(Func80039EF4State *vm) {
    u8 loop_count = vm->field_88;

    loop_count--;
    vm->field_88 = loop_count;
    if ((s8)loop_count >= 0) {
        vm->field_10 = 0;
        vm->field_1C--;
    }
}
