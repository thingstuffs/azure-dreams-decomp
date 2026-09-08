#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_8008ACDC_arg0.h"

M2C_UNK func_80095DD0(); /* extern */
M2C_UNK func_800A2B04();              /* extern */
extern M2C_UNK D_80083460;
extern M2C_UNK D_80096384;

typedef struct S_8009704C_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    s16 unk_04;
} S_8009704C_0;   /* state in func_8009704C */

/* Move the actor toward the destination tile and finish movement when the timer expires. */
void func_8009704C(Rec_func_8008ACDC_arg0 *actor, Rec_D_800E3D7C *motion, Rec_D_80082E80 *destination, M2C_UNK context) {
    s16 frames_left;
    u16 actor_flags;
    register s8 *move_state = (s8 *)&D_80083460;
    M2C_UNK saved_context;
    saved_context = context;

    if (((S_8009704C_0 *)move_state)->unk_02 & 0x80) {
        ((S_8009704C_0 *)move_state)->unk_04 = 0;
    }
    if (((S_8009704C_0 *)move_state)->unk_04 != 0) {
        motion->unk_0C.as_s32 = (s32) ((s32) ((((destination->unk_24 << 6) + 0x20) << 0x10) - motion->unk_00.at00_s32.v) / (s16) ((S_8009704C_0 *)move_state)->unk_04);
        motion->unk_10.at00_s32.v = (s32) ((s32) ((((destination->unk_25 << 6) + 0x20) << 0x10) - motion->unk_04.at00_s32.v) / (s16) ((S_8009704C_0 *)move_state)->unk_04);
    }
    actor_flags = actor->unk_A2;
    if (!(actor_flags & 0x10)) {
        actor->unk_A2 = (u16) (actor_flags | 1);
    }
    frames_left = (u16) ((S_8009704C_0 *)move_state)->unk_04 - 1;
    ((S_8009704C_0 *)move_state)->unk_04 = frames_left;
    if ((frames_left << 0x10) <= 0) {
        ((S_8009704C_0 *)move_state)->unk_04 = 0;
        motion->unk_14.as_s32 = 0;
        motion->unk_10.at00_s32.v = 0;
        motion->unk_0C.as_s32 = 0;
        func_800A2B04(motion, destination->unk_24, destination->unk_25);
        destination->unk_14.at00_u16.v = (u16) (destination->unk_14.at00_u16.v | 0x4000);
        if (actor->unk_100 >= 0) {
            func_80095DD0(actor, motion, destination, saved_context);
            return;
        }
        actor->unk_8C.as_pm = &D_80096384;
    }
}
