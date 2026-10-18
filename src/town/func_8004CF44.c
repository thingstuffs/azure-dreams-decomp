/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void func_800C2E84();          
extern s8 D_800826B8;
extern s32 D_800CA0D4;
extern s32 D_800D64DC;



void initialize_mother_event_countdown_variant_4cf44(Rec_func_80094268_arg0 *object, s32 unused, s32 init_data) {
    func_800C2E84(object, init_data, &D_800D64DC);
    D_800826B8 = 0;
    object->unk_54 = &D_800CA0D4;
    object->unk_6C.as_s16 = 0xA;
    object->unk_72.as_s16 = 0x400;
}
