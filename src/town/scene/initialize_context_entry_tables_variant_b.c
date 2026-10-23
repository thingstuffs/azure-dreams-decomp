#include "modules/town_ovl_3fe0d0_p00.h"

void initialize_context_entry_tables_variant_2(void) {
    D_8001794C.record._0 = &scene_mode_event_data[0];
    {
        Rec_D_80016000 *context = town_scene_root;
        ((TownPositionState *)context->position)->unk_40 = &D_80017E66[0];
        ((S_8047E178_2 *)(context->entry_index * 8 +
                  (s8 *)context->event_data))->unk_00 = (EntryWords *)&D_800161C0[0];
    }
}
