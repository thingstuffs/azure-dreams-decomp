#include "common.h"

extern void func_8004E5A0(s32 value, s32 width, u8 *dst);
extern u8 *func_8004E69C(u8 *text);
extern u8 D_80089304[];

typedef struct {
    u8 pad0[2];
    s8 value;
} Input;

/* Formats a nonzero signed value into text, using default text for zero. */
u8 *func_800B5918(Input *input, u8 *text) {
    s8 value;

    memcpy(text, D_80089304, 4);
    value = input->value;
    if (value != 0) {
        text[0] = value > 0 ? 0x6B : 0x6C;
        func_8004E5A0(input->value >= 0 ? input->value : -input->value,
                      2, text + 1);
        func_8004E69C(text);
    }
    return text;
}
