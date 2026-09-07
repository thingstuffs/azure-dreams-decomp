#include "common.h"

typedef struct {
    u8 pad_00[0x10];
    s32 field_10;
    u8 pad_14[0x08];
    s32 field_1C;
    u8 pad_20[0x68];
    u8 field_88;
} Func80039EF4State;

void func_80039EF4(Func80039EF4State *arg0) {
    u8 value = arg0->field_88;

    value--;
    arg0->field_88 = value;
    if ((s8)value >= 0) {
        arg0->field_10 = 0;
        arg0->field_1C--;
    }
}
