/* Relink of matched town/func_800CA8A0; every changed retail word is a paired relocation. */
#define D_80082680 D_800826B8
#define D_800C7E70 D_800CA094
#define D_800D5FE8 D_800D64DC
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void townInitializeObjectEntries();          /* extern */
extern s8 D_800826B8;
extern s32 D_800CA094;
extern s32 D_800D64DC;


/* Initialize the object state, callback, countdown, and starting value. */
void func_800CA64C(Rec_func_80094268_arg0 *object, s32 unused, s32 init_data) {
    townInitializeObjectEntries(object, init_data, &D_800D64DC);
    D_800826B8 = 0;
    object->unk_54 = &D_800CA094;
    object->unk_6C.as_s16 = 0xA;
    object->unk_72.as_s16 = 0xC00;
}
