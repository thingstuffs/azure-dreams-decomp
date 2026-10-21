/* Dispatch context callbacks and initialize entry tables (G00713). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8047E130. */
#include "town/scene/context_callback_g00713.h"

void dispatch_town_callback_or_default(s32 value0, s32 value1)
{
    SceneCallType2 callback;

    callback = ((Runtime *)D_80016000)->callbacks[((Runtime *)D_80016000)->callbackIndex].callback;
    if (callback == 0) {
        initialize_context_entry_tables_variant_1(value0, value1);
    } else {
        callback();
    }
}

void initialize_context_entry_tables_variant_1(s32 unused_a, s32 unused_b) {
    D_8001794C.record._0 = &D_80017720[0];
    {
        Rec_D_80016000 *context = D_80016000;
        ((TownPositionState *)context->unk_1C)->unk_40 = &D_80017B88[0];
        ((S_8047E130_2 *)(context->unk_08 * 8 +
                  (s8 *)context->unk_40))->unk_00 = (EntryWords *)&D_80016178[0];
    }
}
