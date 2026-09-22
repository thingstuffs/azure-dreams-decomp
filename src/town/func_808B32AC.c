#include "common.h"

typedef struct FlagPageState {
    u8 pad_00[0xE];
    u8 unk_0E;
} FlagPageState;   /* page_state in func_808B32AC */



extern s32 func_8070021C();
extern s32 func_807002A4();
extern s32 func_807002D4();
extern s32 func_80700B7C();

/* Devkit flag page 2: pass the value through when idle, else mark dirty and rescan. */
s32 func_808B32AC(s32 carry_value)
{
    FlagPageState *page_state;

    if (func_8070021C(2) == 0) {
        func_807002D4(2);
        return carry_value;
    }
    else {
        func_807002A4(2);
        page_state = *(void **)0xA0700F40;
        page_state->unk_0E = page_state->unk_0E;
        func_80700B7C();
    }
}
