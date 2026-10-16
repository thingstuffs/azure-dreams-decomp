#include "modules/town_ovl_3fe0d0_p00.h"

void func_80016178(void) {
    D_8001794C.record._0 = &D_80017774[0];
    {
        Rec_D_80016000 *context = D_80016000;
        ((TownPositionState *)context->unk_1C)->unk_40 = &D_80017E66[0];
        ((S_8047E178_2 *)(context->unk_08 * 8 +
                  (s8 *)context->unk_40))->unk_00 = (EntryWords *)&D_800161C0[0];
    }
}
