#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
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
extern u8 D_80175258[];

/* Validate an actor transition and update its state and directional animation on success. */
s32 func_80172314(void *state, s32 transition_id, void *sprite, EntityRec *actor)
{
    s16 transitioned;
    s32 target_heading;

    actor->unk_71 &= 0x7F;
    transitioned = 0;
    if (dungeonStatus.flags & 0x2000) {
        return -1;
    }
    target_heading = func_800A04F0(actor, ((Rec_D_80082E80 *)sprite)->unk_24,
                           ((Rec_D_80082E80 *)sprite)->unk_25, actor->facing);
    if ((func_800A2CB8(actor, target_heading) << 16) == 0) {
        return 0;
    }
    if (dungeonStatus.flags & 0x2000) {
        return -1;
    }
    if (!(actor->unk_46 & 0x8000) && (dungeonStatus.flags & 8)) {
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
    if ((func_800A2B5C(actor) << 16) != 0) {
        return -1;
    }
    {
        u16 state_flags;

        state_flags = ((S_80172314_2 *)state)->unk_98;
        ((S_80172314_2 *)state)->unk_9B = 0;
        ((S_80172314_2 *)state)->unk_8C = 0;
        if (state_flags & 0x8000) {
            ((S_80172314_2 *)state)->unk_9A = 0x17;
            actor->unk_84 = 0x28;
            actor->unk_85 = 0x10;
        } else {
            ((S_80172314_2 *)state)->unk_9A = 0x11;
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
        }
    }

    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80175258;
    func_80047784(sprite,
                  D_80175258[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                  0);
    actor->unk_6D--;
    func_8009C93C(actor, sprite, actor->facing, 1, 0);
    return transitioned;
}

/* MECHANISM: True-rowbase 0x80172484/0x801724E8 are local joins; placing the abort label before
   the success body reproduces the branch polarity and exact 0x38-frame CFG. The guarded $s3 transitioned
   hold preserves the eight-register save set, and -call()+0x40 emits retail's v0 negu/addiu pair. */
