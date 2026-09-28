#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/entity.h"
#include "records/Rec_func_8017360C_arg0.h"



typedef struct S_80173AAC_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173AAC_2;   /* base in func_80173AAC */


typedef struct S_80173AAC_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_80173AAC_4;   /* global in func_80173AAC */




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
void func_80173AAC(void *actor, void *context, void *animation, void *entity)
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
    goto done;

at_least_two:
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    {
        u8 *direction_anims;

        if (!(((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000)) {
            goto done;
        }

        dungeonStatus.unk_0A--;
        direction_anims = D_80174158;
        (*(void * *)((u8 *)animation + 0x2C)) = direction_anims;
        func_80047784(animation,
            direction_anims[((gameWork.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
            0);
        goto increment_state;
    }

state_one:
    {
        u32 entity_flags;

        if (((EntityRec *)entity)->tileY != 0) {

            (*(void * *)((u8 *)animation + 0x2C)) = D_80174160;
            func_80047784(animation,
                D_80174160[((gameWork.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
                0);
            ((EntityRec *)entity)->flags1C |= 0x40000;
            dungeonStatus.unk_0A++;
            goto increment_state;
        }

        if (dungeonStatus.flags & 0x1000) {
            goto done;
        }

        if (((EntityRec *)entity)->unk_64 != 0) {
            if (func_800AA6B4(actor, context, animation, 0) != 0) {
                goto done;
            }
        }

        if ((func_800A2C34(entity) << 16) != 0) {
            goto done;
        }

        entity_flags = ((u32)((EntityRec *)entity)->flags1C);
        if (entity_flags & 0x100) {
            func_800AA258(actor, context, animation, entity);
            goto done;
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
            goto done;
        }

        if (((EntityRec *)entity)->unk_6D == 0) {
            goto done;
        }
        if ((func_800A2C34(entity) << 16) != 0) {
            if ((func_8009A180(entity,
                    (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                goto done;
            }
        }

        func_800A9A0C(entity);
        func_800A9A04(entity);
        if (((EntityRec *)entity)->tileY == 0) {
            goto done;
        }

        (*(void * *)((u8 *)animation + 0x2C)) = D_80174160;
        func_80047784(animation,
            D_80174160[((gameWork.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
            0);
        ((EntityRec *)entity)->flags1C |= 0x40000;
        dungeonStatus.unk_0A++;
    }

increment_state:
    ((Rec_func_8017360C_arg0 *)actor)->unk_9B++;
    goto done;

state_two:
    if (((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000) {

        dungeonStatus.unk_0A--;
        ((EntityRec *)entity)->flags1C &= ~8;
        ((Rec_func_8017360C_arg0 *)actor)->unk_8C.as_pv = &D_801714D4;
    }

done:
    return;
}
