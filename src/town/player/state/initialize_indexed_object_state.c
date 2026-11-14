#include "town/player/position_handlers.h"
#include "common.h"
#include "town/player/object_initialization_g00546.h"
#include "shared/object_index_slots.h"
#include "shared/town_handler.h"
#include "town/player/object.h"
#include "town/player/state.h"

typedef struct Struct_func_8009BDDC_arg0 {
    /* 0x00 */ s8 unk0[4];
    /* 0x04 */ void *unk4;
    /* 0x08 */ s8 unk8[2];
    /* 0x0A */ s16 unkA;
} Struct_func_8009BDDC_arg0;

extern u8 D_800D01C8[];


/* Initializes object state and resets global state before processing the supplied context. */
void initialize_indexed_object_state(Struct_func_8009BDDC_arg0 *object, ObjectPosition *context, void *ptr2) {
    dispatch_selected_entry_if_nonzero((s32 *) D_800D01C8, (TownObjectRecord *) object, ptr2);
    object_index_slots[1].unk_00 = 0;
    object_index_slots[1].unk_01 = 0;
    object->unk4 = target_action_update_address;
    object->unkA = 4;
    clear_object_velocity(context);
}
