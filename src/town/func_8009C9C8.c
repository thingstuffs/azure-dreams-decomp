/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"
#include "shared/runtime_dispatch.h"


extern s32 D_80099AC4;

/*
 * Selects the linked handler table, clears the indexed object slot, and installs D_80099AC4 with
 * count 0x20.
 */
void init_player_countdown_action(Rec_func_80094268_arg0 *object, void *unused, void *handler_context) {
    call_the_handler_selects_nonzero_entry((s32 *) ((HandlerTableWordView *)(object->unk_44))->unk_08, object, handler_context);
    object_index_slots[object->unk_40].unk_00 = 0;
    object->unk_04.as_pm = &D_80099AC4;
    object->unk_0A.as_s16 = 0x20;
}
