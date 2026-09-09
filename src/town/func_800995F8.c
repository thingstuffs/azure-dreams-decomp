#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
} Input;

typedef struct {
    u8 pad[0x24];
    s32 unk24;
    u8 pad28[8];
    s32 unk30;
} State;

extern s16 D_8006ADD4[];
extern State D_800FE520;

/* Update the state limits from the input value unless mode 12 is active. */
void func_80096D58(Input *source) {
    register Input *input ASM_REG("$5");
    State *state_page;
    s32 input_value;

    if (D_8006ADD4[0] == 12) {
        return;
    }

    input = source;
    ASM_KEEP(input);
    input_value = input->unk4;
    if (input_value <= 0x03FFFFFF) {
        State *state = &D_800FE520;

        state_page = (State *)0x80100000;
        state->unk24 = 0x0F500000;
        state->unk30 = 0x10B00000;
    } else {
        state_page = (State *)0x80100000;
        ASM_KEEP(state_page);
        state_page = (State *)((u8 *)state_page - 0x1AE0);
        state_page->unk24 = 0x13500000 - input_value;
        state_page->unk30 = input->unk4 + 0x0CB00000;
    }
}
