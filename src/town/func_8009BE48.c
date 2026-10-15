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
extern u8 D_800D01D0[];

extern void func_80099754(void *record);

void func_800995A8(Struct_func_8009BDDC_arg0 *object, void *context, void *ptr2) {
    func_80094984((s32 *) D_800D01D0, (Rec_func_80094268_arg0 *) object, ptr2);
    D_80082660[1].unk_00 = 0;
    D_80082660[1].unk_01 = 0;
    object->unk4 = D_80098078;
    object->unkA = 4;
    func_80099754(context);
}
