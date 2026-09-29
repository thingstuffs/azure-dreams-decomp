#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef struct TownState {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} TownState;


/* Set the town state's unk4 and unk8 values to 0x6A0 and 0x4A0. */
void func_80017054(void) {
    ((TownState *)D_80016000->unk_1C)->unk4 = 0x6A0;
    ((TownState *)D_80016000->unk_1C)->unk8 = 0x4A0;
}
