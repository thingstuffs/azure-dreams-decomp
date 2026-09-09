#include "common.h"

typedef struct S_80017EF0_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80017EF0_0;

typedef struct S_80017EF0_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80017EF0_1;

extern s32 func_80017EA0();
extern s32 D_80019BB0;
extern s32 D_80019BB4;

/* Update the indexed entry unless the current state is 3; return whether updated. */
s32 func_80017EF0(S_80017EF0_0 *entry_table, s32 entry_index) {
    if (D_80019BB0 != 3) {
        ((S_80017EF0_1 *)((entry_index * 0x10) + entry_table->unk_10))->unk_08 =
            func_80017EA0(D_80019BB4);
        return 1;
    }
    return 0;
}
