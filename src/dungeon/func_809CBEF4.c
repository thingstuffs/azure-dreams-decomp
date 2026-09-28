#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_801736F4_arg0.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/entity.h"
#include "records/Rec_D_800814A8.h"



typedef struct S_801736F4_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801736F4_2;   /* base in func_801736F4 */


typedef struct S_801736F4_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_801736F4_4;   /* global in func_801736F4 */




extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80173A30(void *, void *, void *, void *);

extern u8 D_80170E54;
extern u8 D_80173CD4[];
extern u8 D_80173CDC[];

/* Advances the entity's animation state and processes pending actions. */
void func_801736F4(void *controller, void *context, void *sprite, void *entity)
{
    s32 state;

    state = ((Rec_func_801736F4_arg0 *)controller)->unk_9B;
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

        if (!(((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000)) {
            goto done;
        }

        dungeonStatus.unk_0A--;
        direction_anims = D_80173CDC;
        (*(void * *)((u8 *)sprite + 0x2C)) = direction_anims;
        func_80047784(sprite,
            direction_anims[((gameWork.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
            0);
        goto increment_state;
    }

state_one:
    {
        u32 entity_flags;

        if (((EntityRec *)entity)->tileY != 0) {

            (*(void * *)((u8 *)sprite + 0x2C)) = D_80173CD4;
            func_80047784(sprite,
                D_80173CD4[((gameWork.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
                0);
            (*(u32 *)((u8 *)entity + 0x1C)) |= 0x40000;
            dungeonStatus.unk_0A++;
            goto increment_state;
        }

        if (dungeonStatus.flags & 0x1000) {
            goto done;
        }

        if (((EntityRec *)entity)->unk_64 != 0) {
            if (func_800AA6B4(controller, context, sprite, 0) != 0) {
                goto done;
            }
        }

        if ((func_800A2C34(entity) << 16) != 0) {
            goto done;
        }

        entity_flags = ((u32)((EntityRec *)entity)->flags1C);
        if (entity_flags & 0x100) {
            func_800AA258(controller, context, sprite, entity);
            goto done;
        }

        if (entity_flags & 0x80000) {
            func_800AA888(controller, context, sprite, entity);
            func_80173A30(controller, context, sprite, entity);
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

        (*(void * *)((u8 *)sprite + 0x2C)) = D_80173CD4;
        func_80047784(sprite,
            D_80173CD4[((gameWork.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
            0);
        ((EntityRec *)entity)->flags1C |= 0x40000;
        dungeonStatus.unk_0A++;
    }

increment_state:
    ((Rec_func_801736F4_arg0 *)controller)->unk_9B++;
    goto done;

state_two:
    if (((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000) {

        dungeonStatus.unk_0A--;
        ((EntityRec *)entity)->flags1C &= ~0x208;
        ((Rec_func_801736F4_arg0 *)controller)->unk_8C = &D_80170E54;
    }

done:
    return;
}
