#include "common.h"

typedef struct S_func_804061C4_0 {
    u8 pad_00[4];
    s32 unk_04;
    u8 pad_08[0x20];
    s32 unk_28;
    u8 pad_2C[8];
    void (*unk_34)(void);
    s32 unk_38;
} S_func_804061C4_0;

typedef struct S_func_804061C4_1 {
    void (*unk_00)(void);
} S_func_804061C4_1;

extern s32 func_804022C8(s32 arg0);
extern void func_804033C4(void *arg0);
extern void func_80404688(s32 arg0);
extern void func_80406368(void);
extern void func_80405A64(void);

/* Updates state callbacks and processes five entries if the state check succeeds. */
void func_804061C4(S_func_804061C4_0 *state)
{
    s32 entry;
    s32 entry_count;

    if (state->unk_38 != 0) {
        ((S_func_804061C4_1 *)((u8 *)state - 0x10))->unk_00 = func_80406368;
        goto end;
    }

    if (func_804022C8(state->unk_28) != 0) {
        entry_count = 0;
        ((S_func_804061C4_1 *)((u8 *)state - 0x10))->unk_00 = func_80406368;
        do {
            entry = state->unk_04;
            state = (S_func_804061C4_0 *)((u8 *)state + 4);
            entry_count++;
            func_80404688(entry);
        } while (entry_count < 5);
    } else {
        state->unk_34 = func_80406368;
        func_804033C4((u8 *)state - 0x20);
        ((S_func_804061C4_1 *)((u8 *)state - 0x10))->unk_00 = func_80405A64;
    }

end:
    return;
}
