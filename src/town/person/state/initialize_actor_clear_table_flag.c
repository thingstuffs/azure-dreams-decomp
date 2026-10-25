#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
extern void D_800C5ADC();
extern s32 D_800D54BC[];


/* Initialize the actor, clear its table flag, and install its handler. */
void initialize_actor_clear_table_flag(Rec_func_80094268_arg0 *actor, s32 unused, void *init_param) {
    initialize_object_entries((Struct800C5724 *)(actor), init_param, D_800D54BC);
    object_index_slots[actor->unk_60].unk_00 = 0;
    actor->unk_54 = &D_800C5ADC;
}
