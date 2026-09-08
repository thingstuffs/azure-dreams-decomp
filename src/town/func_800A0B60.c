#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCC4.h"



M2C_UNK func_80041E28();           /* extern */
s32 func_8004B8DC(); /* extern */
extern u8 D_80010A80[];
extern Rec_D_800CFCC4 *D_800CFCC4;
extern M2C_UNK D_80100A10;
extern s32 D_80100AF4;

s32 func_8009E2C0(void) {
    u8 *table = (u8 *)0x80010A80;
    u32 index = D_800CFCC4->unk_4F & 0x3F;
    M2C_UNK *state = &D_80100A10;

    func_80041E28(state, table + (index * 0x54));
    D_80100AF4 = func_8004B8DC(state, 1, 0x5C, -0x68, 0x200);
    return 0;
}

/* MECHANISM: The state address remains live in s0 across both calls, yielding
   the retail 0x20 frame and sole s0 save. Removing ASM_KEEP(table), then
   declaring index before state, gives the exact prologue load interleave. */
