#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80098928();     /* extern */
s16 func_800C2AE8();                          


/* extern */

/* Move toward the target position and advance the motion state when the countdown ends. */
void func_80099790(Rec_func_80094268_arg0 *motion, Rec_D_800E3D7C *position, M2C_UNK context) {
    u16 steps_left;

    position->unk_08.at02_s16.v = func_800C2AE8(position);
    steps_left = motion->unk_0A.as_u16 - 1;
    motion->unk_0A.as_u16 = steps_left;
    if ((s16) steps_left <= 0) {
        position->unk_00.at02_u16.v = (u16) motion->unk_30;
        position->unk_04.at02_u16.v = (u16) motion->unk_32;
        motion->unk_10.as_u16 = (u16) motion->unk_0E;
        func_80098928(motion, position, context);
        return;
    }
    position->unk_00.at02_u16.v = (u16) (position->unk_00.at02_u16.v + ((s32) ((s16) motion->unk_30 - (s16) position->unk_00.at02_u16.v) / (s16) steps_left));
    position->unk_04.at02_u16.v = (u16) (position->unk_04.at02_u16.v + ((s32) ((s16) motion->unk_32 - (s16) position->unk_04.at02_u16.v) / (s16) motion->unk_0A.as_u16));
}
