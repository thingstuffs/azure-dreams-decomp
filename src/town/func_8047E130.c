#include "modules/town_ovl_3fe0d0_p00.h"

void initialize_context_entry_tables_variant_1(s32 unused_a, s32 unused_b) {
    D_8001794C.record._0 = &D_80017720[0];
    {
        Rec_D_80016000 *context = D_80016000;
        ((TownPositionState *)context->unk_1C)->unk_40 = &D_80017B88[0];
        ((S_8047E130_2 *)(context->unk_08 * 8 +
                  (s8 *)context->unk_40))->unk_00 = (EntryWords *)&D_80016178[0];
    }
}
