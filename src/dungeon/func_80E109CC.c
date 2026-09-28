#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/entity.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_801741CC_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0xA];
    u16 unk_A6;
    u8 pad_A8[0x4];
    u16 unk_AC;
} S_801741CC_0;   /* arg0 in func_801741CC */


typedef struct S_801741CC_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801741CC_2;   /* base in func_801741CC */


typedef struct S_801741CC_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_801741CC_4;   /* global in func_801741CC */




extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80174520(void *, void *, void *, void *);

extern s32 D_80171094;
extern u8 D_80176470[];
extern u8 D_80176478[];

/* Update the actor action state, directional animation, and entity flags. */
void func_801741CC(void *actor, void *action_ctx, void *anim, void *entity)
{
    s32 action_state;

    action_state = ((S_801741CC_0 *)actor)->unk_9B;
    if (action_state == 1) {
        goto state_one;
    }
    if (action_state >= 2) {
        goto at_least_two;
    }
    if (action_state == 0) {
        goto state_zero;
    }
    goto done;

at_least_two:
    if (action_state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    {
        u8 *direction_anims;

        if (!(((Rec_func_800AA258_arg2 *)anim)->unk_14 & 0xE000)) {
            goto done;
        }

        dungeonStatus.unk_0A--;
        direction_anims = D_80176470;
        (*(void * *)((u8 *)anim + 0x2C)) = direction_anims;
        func_80047784(anim,
            direction_anims[((gameWork.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
            0);
        goto increment_state;
    }

state_one:
    {
        u32 entity_flags;

        if (((EntityRec *)entity)->tileY != 0) {

            (*(void * *)((u8 *)anim + 0x2C)) = D_80176478;
            func_80047784(anim,
                D_80176478[((gameWork.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
                0);
            ((EntityRec *)entity)->flags1C |= 0x40000;
            dungeonStatus.unk_0A++;
            goto increment_state;
        }

        if (dungeonStatus.flags & 0x1000) {
            goto done;
        }

        if (((EntityRec *)entity)->unk_64 != 0) {
            if (func_800AA6B4(actor, action_ctx, anim, 0) != 0) {
                goto done;
            }
        }

        if ((func_800A2C34(entity) << 16) != 0) {
            goto done;
        }

        entity_flags = ((u32)((EntityRec *)entity)->flags1C);
        if (entity_flags & 0x100) {
            func_800AA258(actor, action_ctx, anim, entity);
            goto done;
        }

        if (entity_flags & 0x80000) {
            u16 stat_value;
            u16 stat_delta;

            func_800AA888(actor, action_ctx, anim, entity);
            stat_value = ((S_801741CC_0 *)actor)->unk_92;
            stat_delta = ((S_801741CC_0 *)actor)->unk_A6;
            ((S_801741CC_0 *)actor)->unk_A6 = 0;
            ((S_801741CC_0 *)actor)->unk_AC = 0;
            ((S_801741CC_0 *)actor)->unk_92 = stat_value - stat_delta;
            func_80174520(actor, action_ctx, anim, entity);
            goto done;
        }

        if (((EntityRec *)entity)->unk_6D == 0) {
            goto done;
        }
        if ((func_800A2C34(entity) << 16) != 0) {
            if ((func_8009A180(entity,
                    (u8 *)((EntityRec *)D_800814A8)->unk_58 + 0x20) << 16) != 0) {
                goto done;
            }
        }

        func_800A9A0C(entity);
        func_800A9A04(entity);
        if (((EntityRec *)entity)->tileY == 0) {
            goto done;
        }

        (*(void * *)((u8 *)anim + 0x2C)) = D_80176478;
        func_80047784(anim,
            D_80176478[((gameWork.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
            0);
        ((EntityRec *)entity)->flags1C |= 0x40000;
        dungeonStatus.unk_0A++;
    }

increment_state:
    ((S_801741CC_0 *)actor)->unk_9B++;
    goto done;

state_two:
    if (((Rec_func_800AA258_arg2 *)anim)->unk_14 & 0xE000) {

        dungeonStatus.unk_0A--;
        ((EntityRec *)entity)->flags1C &= ~8;
        ((S_801741CC_0 *)actor)->unk_8C = &D_80171094;
    }

done:
    return;
}
