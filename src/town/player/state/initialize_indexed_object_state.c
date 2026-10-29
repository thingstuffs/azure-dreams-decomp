#include "common.h"
#include "town/player/object_initialization_g00546.h"
#include "shared/object_index_slots.h"
#include "shared/town_handler.h"
#include "town/player/object.h"

typedef struct {
    /* 0x00 */ s8 unk0[4];
    /* 0x04 */ void *unk4;
    /* 0x08 */ s8 unk8[2];
    /* 0x0A */ s16 unkA;
} Struct_func_8009BDDC_arg0;

extern u8 D_800D01C8[];


/* Initializes object state and resets global state before processing the supplied context. */
void initialize_indexed_object_state(Struct_func_8009BDDC_arg0 *object, void *context, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) D_800D01C8, (Rec_func_80094268_arg0 *) object, ptr2);
    object_index_slots[1].unk_00 = 0;
    object_index_slots[1].unk_01 = 0;
    object->unk4 = target_action_update_address;
    object->unkA = 4;
    clear_entity_record_fields(context);
}
