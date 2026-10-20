/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/object_index_slots.h"
#include "shared/town_handler.h"

typedef struct {
     s8 unk0[4];
     void *unk4;
     s8 unk8[2];
     s16 unkA;
} Struct_func_8009BDDC_arg0;

extern u8 D_80098078[];
extern u8 D_800D01D8[];

extern void clear_entity_record_fields(void *record);

void func_80099614(Struct_func_8009BDDC_arg0 *object, void *context, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) D_800D01D8, (Rec_func_80094268_arg0 *) object, ptr2);
    object_index_slots[1].unk_00 = 0;
    object_index_slots[1].unk_01 = 0;
    object->unk4 = D_80098078;
    object->unkA = 0x15;
    clear_entity_record_fields(context);
}
