#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_80082E80.h"

M2C_UNK func_8003DB94();        /* extern */
M2C_UNK func_80047784();        /* extern */
extern s32 D_80081458[];
extern M2C_UNK D_800D07A4[];
extern s16 D_800D07AC;

/* Sets the object state for the selected mode and flags. */
void func_8009DC8C(void *owner, void *object, s32 mode, s32 flags) {
    if (mode == 2) {
        ((Rec_func_80094268_arg0 *)owner)->unk_93 = 1;
        (*(s32 *)((u8 *)object + (0x28))) = D_80081458[0];
        func_80047784(object, D_800D07AC, 0);
        return;
    }
    func_8003DB94(object, D_800D07A4[mode], 0);
    if (flags & 2) {
        ((Rec_D_80082E80 *)object)->unk_12.at00_s16.v = 0x100;
        return;
    }
    if (flags & 4) {
        ((Rec_D_80082E80 *)object)->unk_12.at00_s16.v = 0x200;
        return;
    }
    ((Rec_D_80082E80 *)object)->unk_12.at00_s16.v = 0;
}
