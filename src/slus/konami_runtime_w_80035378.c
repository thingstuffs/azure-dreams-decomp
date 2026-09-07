#include "common.h"

#include "common.h"

typedef struct {
    u8 pad_00[0x48];
    s32 slots[15];
} RuntimeState;

extern RuntimeState D_80082A38;
extern s32 D_80082AB8[];

void func_80035378(s32 arg0) {
    s32 index;

    for (index = 10; index < 15; index++) {
        if (D_80082A38.slots[index] == 0) {
            D_80082A38.slots[index] = arg0;
            if (index != 14) {
                D_80082A38.slots[index + 1] = 0;
            }
            return;
        }
    }

    for (index = 11; index < 14; index++) {
        D_80082A38.slots[index] = D_80082A38.slots[index + 1];
    }
    D_80082AB8[0] = arg0;
}
