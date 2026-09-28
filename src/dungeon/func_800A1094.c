#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/dungeon_status.h"

extern s8 D_800DCF4F[];
extern s8 D_800E045C[];

extern s32 func_80035208(void *arg);
extern void func_80035348(void);

/* When unblocked, clears a set flag and decrements its counter before running updates. */
void func_800A67F4(void) {
    if (!(D_800E296C & 0x200000) && !(D_80013714 & 8)) {
        if (D_800DCF4F[0] != 0) {
            D_800DCF4F[0] = 0;
            dungeonStatus.unk_0A--;
        }
        func_80035208(&D_800E045C[0]);
        func_80035348();
    }
}
