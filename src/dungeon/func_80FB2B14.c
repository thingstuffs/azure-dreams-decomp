#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"



typedef struct S_80172314_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_80172314_2;   /* arg0 in func_80172314 */



extern s32 func_80047784();
extern s32 func_8009C93C();
extern s32 func_800A0134();
extern s32 func_800A04F0();
extern s32 func_800A2B5C();
extern s32 func_800A2CB8();
extern s32 func_800C7930();
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80175258[];

/* Validate an actor transition and update its state and directional animation on success. */
s32 func_80172314(void *state, s32 transition_id, void *sprite, void *actor)
{
    s16 transitioned;
    s32 target_heading;
    u16 *global_flags;

    ((Rec_D_800E3D7C *)actor)->unk_71.as_u8 &= 0x7F;
    global_flags = (u16 *)&D_80083460;
    transitioned = 0;
    if (global_flags[1] & 0x2000) {
        goto abort_transition;
    }
    target_heading = func_800A04F0(actor, ((Rec_D_80082E80 *)sprite)->unk_24,
                           ((Rec_D_80082E80 *)sprite)->unk_25, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16);
    if ((func_800A2CB8(actor, target_heading) << 16) == 0) {
        return 0;
    }
    if (global_flags[1] & 0x2000) {
        return -1;
    }
    if (!(((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x8000) && (global_flags[1] & 8)) {
        return -1;
    }
    if ((u16)(-func_800A0134(target_heading, actor) + 0x40) >= 0x81U) {
        return transitioned;
    }

    transitioned = 1;
    if ((func_800A2B5C(actor) << 16) != 0) {
        return -1;
    }
    func_800C7930((u8 *)actor - 0x20, transition_id, 8, 0x300);
    if ((func_800A2B5C(actor) << 16) == 0) {
        goto transition_ok;
    }

abort_transition:
    return -1;

transition_ok:
    {
        u16 state_flags;

        state_flags = ((S_80172314_2 *)state)->unk_98;
        ((S_80172314_2 *)state)->unk_9B = 0;
        ((S_80172314_2 *)state)->unk_8C = 0;
        if (state_flags & 0x8000) {
            ((S_80172314_2 *)state)->unk_9A = 0x17;
            ((Rec_D_800E3D7C *)actor)->unk_84.as_u8 = 0x28;
            ((Rec_D_800E3D7C *)actor)->unk_85.as_u8 = 0x10;
        } else {
            ((S_80172314_2 *)state)->unk_9A = 0x11;
            ((Rec_D_800E3D7C *)actor)->unk_84.as_u8 = 0x7C;
            ((Rec_D_800E3D7C *)actor)->unk_85.as_u8 = 0;
        }
    }

    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80175258;
    func_80047784(sprite,
                  D_80175258[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                  0);
    ((Rec_D_800E3D7C *)actor)->unk_6D.as_u8--;
    func_8009C93C(actor, sprite, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1, 0);
    return transitioned;
}

/* MECHANISM: True-rowbase 0x80172484/0x801724E8 are local joins; placing the abort label before
   the success body reproduces the branch polarity and exact 0x38-frame CFG. The guarded $s3 transitioned
   hold preserves the eight-register save set, and -call()+0x40 emits retail's v0 negu/addiu pair. */
