#include "modules/town_town_windows.h"

/* Cleans up an object when its state check succeeds, or dispatches its callback and updates it. */
void func_8009DD40(void *object, s32 source, s32 context) {
    s8 *status_ptr;

    if (func_8009D20C(object, source) != 0) {
        func_8008F134(object);
        status_ptr = ((Rec_D_80082D58 *)object)->unk_98.as_ps8;
        if (status_ptr != NULL) {
            *status_ptr = 0;
        }
        func_80033D08(object);
        ((func_800A05E0_S_8009DD40_0_pre *)object)[-1].unk_00 = (u16) (((func_800A05E0_S_8009DD40_0_pre *)object)[-1].unk_00 | 0x8000);
        objectFlagBlock.flags = objectFlagBlock.flags | 0x8000;
        return;
    }
    ((Rec_D_80082D58 *)object)->unk_50.as_x151a23(object, object, source, context);
    if (!(((func_800A05E0_S_8009DD40_0_pre *)object)[-1].unk_00 & 0x8000)) {
        func_800970AC(func_80096FF4(source), object);
        if (((Rec_D_80082D58 *)object)->unk_4D == 0x13) {
            func_800478B8(context);
        }
    }
}
