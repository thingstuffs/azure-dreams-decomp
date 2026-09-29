#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/entity.h"
#include "records/Rec_func_8017360C_arg0.h"







extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80173E00(void *, void *, void *, void *);

extern s32 D_801714D4;
extern u8 D_80174158[];
extern u8 D_80174160[];

/* Advance actor states, select directional animations, and process entity actions. */
void func_80173AAC(void *actor, void *context, void *animation, EntityRec *entity)
{
    s32 state;

    state = ((Rec_func_8017360C_arg0 *)actor)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state >= 2) {
        goto at_least_two;
    }
    if (state == 0) {
        goto state_zero;
    }
    return;

at_least_two:
    if (state == 2) {
        goto state_two;
    }
    return;

state_zero:
    {
        u8 *direction_anims;

        if (!(((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000)) {
            return;
        }

        dungeonStatus.unk_0A--;
        direction_anims = D_80174158;
        (*(void * *)((u8 *)animation + 0x2C)) = direction_anims;
        func_80047784(animation,
            direction_anims[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        goto increment_state;
    }

state_one:
    {
        u32 entity_flags;

        if (entity->tileY != 0) {

            (*(void * *)((u8 *)animation + 0x2C)) = D_80174160;
            func_80047784(animation,
                D_80174160[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            entity->flags1C |= 0x40000;
            dungeonStatus.unk_0A++;
            goto increment_state;
        }

        if (dungeonStatus.flags & 0x1000) {
            return;
        }

        if (entity->unk_64 != 0) {
            if (func_800AA6B4(actor, context, animation, 0) != 0) {
                return;
            }
        }

        if ((func_800A2C34(entity) << 16) != 0) {
            return;
        }

        entity_flags = ((u32)entity->flags1C);
        if (entity_flags & 0x100) {
            func_800AA258(actor, context, animation, entity);
            return;
        }

        if (entity_flags & 0x80000) {
            u16 stored_value;
            u16 pending_decrement;

            func_800AA888(actor, context, animation, entity);
            stored_value = ((Rec_func_8017360C_arg0 *)actor)->unk_92;
            pending_decrement = ((Rec_func_8017360C_arg0 *)actor)->unk_A2;
            ((Rec_func_8017360C_arg0 *)actor)->unk_A2 = 0;
            ((Rec_func_8017360C_arg0 *)actor)->unk_9E = 0;
            ((Rec_func_8017360C_arg0 *)actor)->unk_92 = stored_value - pending_decrement;
            func_80173E00(actor, context, animation, entity);
            return;
        }

        if (entity->unk_6D == 0) {
            return;
        }
        if ((func_800A2C34(entity) << 16) != 0) {
            if ((func_8009A180(entity,
                    (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }

        func_800A9A0C(entity);
        func_800A9A04(entity);
        if (entity->tileY == 0) {
            return;
        }

        (*(void * *)((u8 *)animation + 0x2C)) = D_80174160;
        func_80047784(animation,
            D_80174160[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        entity->flags1C |= 0x40000;
        dungeonStatus.unk_0A++;
    }

increment_state:
    ((Rec_func_8017360C_arg0 *)actor)->unk_9B++;
    return;

state_two:
    if (((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000) {

        dungeonStatus.unk_0A--;
        entity->flags1C &= ~8;
        ((Rec_func_8017360C_arg0 *)actor)->unk_8C.as_pv = &D_801714D4;
    }

    return;
}
