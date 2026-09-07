#include "common.h"

typedef struct {
    u8 pad[8];
    s32 value;
} TownRecord;

extern TownRecord D_8001791C[];
extern s32 D_80018054[];
extern u8 *D_8001E950;
extern void func_8001E578(s32);

s32 func_8001B5A0(void) {
    u8 **player_ptr = &D_8001E950;
    u8 *player = *player_ptr;
    u8 index = player[4];

    if (D_8001791C[index].value == 0) {
        func_8001E578(0x401);
    }

    {
        u8 *return_player = *player_ptr;
        u8 return_index = return_player[4];

        return D_80018054[return_index];
    }
}

/* MECHANISM: Hold &D_8001E950 across the conditional call so its page lives
   in s0. A 12-byte record type keeps value as lw 8(base), while the return
   table remains 4-byte-scaled; cdk-G0 supplies retail's post-merge schedule. */
