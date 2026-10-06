#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef struct GroupLimit_8001D048 {
    s16 limit;
    u8 pad_02[0x6];
} GroupLimit_8001D048;


extern s32 func_8001D280(s32, s32, s32);
extern s32 func_8001E7E4(s32);
extern GroupLimit_8001D048 D_8001902C[][3];

/* Invoke the callback for nonzero row entries using the selected mode and bounds. */
void func_8001D048(void) {
    TownStateRecord *state;
    s32 mode;
    s32 i;
    s32 j;
    u8 entry;

    state = D_80016000->unk_38;
    if (func_8001E7E4(1) != 0) {
        mode = 0;
    } else if (func_8001E7E4(2) != 0) {
        mode = 1;
    } else {
        mode = 2;
    }
    for (i = 0; i < 16; i++) {
        for (j = 0; j < D_8001902C[i][mode].limit; j++) {
            entry = state->history[i][j];
            if (entry == 0) {
                break;
            }
            D_80016000->unk_20->callback_2D0(func_8001D280(i, j, mode), entry, mode);
        }
    }
}
