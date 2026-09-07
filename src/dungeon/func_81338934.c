#include "common.h"

typedef struct DungeonState {
    s8 pad00[0x12];
    u16 field12;
    u8 pad14[4];
    u16 field18;
} DungeonState;

extern DungeonState *D_80175D58[];
extern DungeonState *D_80175D5C[];

void func_8016F934(s32 arg0) {
    if (arg0 == 0) {
        DungeonState *state_zero;

        state_zero = (DungeonState *)((u8 *)D_80175D58[0] + 0x20);
        state_zero->field18 = 0;
        state_zero->field12++;
        return;
    }

    {
        DungeonState *state_nonzero;

        state_nonzero = (DungeonState *)((u8 *)D_80175D5C[0] + 0x20);
        state_nonzero->field18 = 0;
        state_nonzero->field12++;
    }
}
