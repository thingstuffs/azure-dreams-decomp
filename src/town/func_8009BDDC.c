#include "common.h"
#include "shared/object_index_slots.h"
#include "shared/town_handler.h"

typedef struct {
    /* 0x00 */ s8 unk0[4];
    /* 0x04 */ void *unk4;
    /* 0x08 */ s8 unk8[2];
    /* 0x0A */ s16 unkA;
} Struct_func_8009BDDC_arg0;

extern u8 D_80098078[];
extern u8 D_800D01C8[];

extern void townClearEntityRecordFields(void *record);

/* Initializes object state and resets global state before processing the supplied context. */
void townInitializeIndexedObjectState(Struct_func_8009BDDC_arg0 *object, void *context, void *ptr2) {
    townCallTheHandlerSelectsNonzeroEntry((s32 *) D_800D01C8, (Rec_func_80094268_arg0 *) object, ptr2);
    D_80082660[1].unk_00 = 0;
    D_80082660[1].unk_01 = 0;
    object->unk4 = D_80098078;
    object->unkA = 4;
    townClearEntityRecordFields(context);
}
