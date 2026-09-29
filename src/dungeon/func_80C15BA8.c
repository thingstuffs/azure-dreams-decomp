#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"



typedef struct S_801713A8_2 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    u8 * unk_2C;
} S_801713A8_2;   /* arg2 in func_801713A8 */





extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(u8, u8);
extern s32 func_8009FD7C(u8, u8, u8, u8);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_801718D0(void *);
extern void func_80171A98(void *, void *, void *, void *);
extern s32 func_801721E0(void *, void *, void *, void *);
extern void func_801723A4(void *, void *, void *, void *);
extern s32 func_801724C4(void *, void *, void *, s32);
extern void func_80174250(void *, void *, void *, void *);

extern void *D_80170808[];
extern u8 D_80174494[];
extern u8 D_8017449C[];
extern u8 D_801744A4[];
extern u8 D_801744D4[];
extern u8 D_801744EC[];
extern u8 D_801744FC[];

/* Update actor animation and dispatch actions based on status and target position. */
void func_801713A8(void *actor, void *context, void *sprite, EntityRec *status)
{
    static void *const action_labels[] = {
        &&case_1, &&case_2, &&case_3, &&case_4,
        &&case_5, &&case_6, &&case_7, &&case_8,
        &&case_9, &&case_10, &&case_11, &&case_12,
    };
    s32 distance;
    u32 flags;
    s32 action_index;
    s8 tile_index;
    u16 action_flags;
    void *resume_handler;

    if (dungeonStatus.flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 14;
        func_801718D0(actor);
        return;
    }

    if (status->tileY == 0) {
        func_800AA79C(actor, context, sprite, status);
        if (((S_801713A8_2 *)sprite)->unk_2C == D_801744FC) {
            return;
        }
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801744EC;
        func_80047784(
            sprite,
            D_801744EC[((gameWork.view.viewAngle + status->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)status->flags1C) & 0x200) {
        if (((S_801713A8_2 *)sprite)->unk_2C == D_801744FC) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 13;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_u8 = 2;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
            status->flags1C &= ~0x40000;
            return;
        }
        if (func_800AA924(actor, context, sprite, D_801744EC) != 0) {
            return;
        }
    }

    if ((dungeonStatus.flags & 0x2000) == 0) {
        if (((u32)status->flags1C) & 0x100) {
            func_800AA258(actor, context, sprite, status);
            return;
        }

        if (((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 != 14) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 14;
        }

        if ((((S_801713A8_2 *)sprite)->unk_2C != D_80174494) &&
            (((S_801713A8_2 *)sprite)->unk_2C != D_8017449C)) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_A8 = 0;
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_8017449C;
            func_80047784(
                sprite,
                D_8017449C[((gameWork.view.viewAngle + status->facing + 0x100) >> 9) & 7],
                ((Rec_func_800A9E70_arg0 *)actor)->unk_A8);
        }

        status->flags1C |= 0x40000;
        ((Rec_func_800A9E70_arg0 *)actor)->unk_98 &= 0xFFF7;

        if (status->unk_64 != 0) {
            if (func_800AA6B4(actor, context, sprite, D_801744A4) != 0) {
                return;
            }
        }

        if (((u32)status->flags1C) & 0x80000) {
            func_800AA888(actor, context, sprite, status);
            ((Rec_func_800A9E70_arg0 *)actor)->unk_A8 = 0;
            func_80174250(actor, context, sprite, status);
            return;
        }

        if ((s16)func_800A1C58(status) != 0) {
            func_800AAB10(actor, context, sprite, status);
        }
    }

    tile_index = func_8009FB34(((S_801713A8_2 *)sprite)->unk_24.at00.v, ((S_801713A8_2 *)sprite)->unk_24.at01.v);
    ((S_801713A8_2 *)sprite)->unk_26 = tile_index;

    if (status->unk_6D > 0) {
        if (((u32)status->flags1C) & 0x20) {
            goto case_12;
        }
        if (((S_801713A8_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            goto case_default;
        }
        action_flags = status->unk_46;
        if ((action_flags & 0x8000) == 0) {
            if (dungeonStatus.flags & 0x2000) {
                if ((s16)func_8009A180(
                        status, (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_801724C4(actor, context, sprite, 0) == 0) {
                return;
            }
            action_flags = status->unk_46 | 0x4000;
            status->unk_46 = action_flags;
            if ((action_flags & 0x8000) == 0) {
                goto case_default;
            }
        }

        action_index = (status->unk_46 & 0x3FFF) - 1;
        if ((u32)action_index >= 12U) {
            goto case_default;
        }
        (void)action_labels;
        goto *D_80170808[action_index];

case_8:
case_9:
        if ((s16)func_801721E0(actor, context, sprite, status) != 0) {
            return;
        }
        func_801723A4(actor, context, sprite, status);
        return;

case_5:
case_6:
case_7:
        {
            s16 target_angle;
            EntityRec *active_actor;

            target_angle = func_800A0818(
                ((S_801713A8_2 *)sprite)->unk_24.at00.v, ((S_801713A8_2 *)sprite)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY, &distance);
            active_actor = D_800814A8;
            status->facing = target_angle;
            if (active_actor->unk_9A != 0x11) {
                goto case_12;
            }
        }
        resume_handler = (void *)func_801713A8;
        goto case_call;

case_12:
        func_800A9A0C(status);
        return;

case_1:
case_2:
case_3:
        resume_handler = (void *)func_801713A8;

case_call:
        func_800AAF00(actor, context, sprite, D_801744D4, resume_handler);
        return;

case_4:
case_10:
case_11:
case_default:
        func_80171A98(actor, context, sprite, status);
        return;
    }

    flags = ((u32)status->flags1C);
    if (flags & 0x2000) {
        return;
    }
    if (tile_index >= 0) {
        if (D_800E2970[tile_index].flags & 2) {
            return;
        }
    }
    if (flags & 0x430) {
        return;
    }

    if ((s16)func_8009FD7C(
            ((S_801713A8_2 *)sprite)->unk_24.at00.v, ((S_801713A8_2 *)sprite)->unk_24.at01.v,
            D_80082E80.tileX, D_80082E80.tileY) == 0) {
        return;
    }
    status->facing = func_800A0818(
        ((S_801713A8_2 *)sprite)->unk_24.at00.v, ((S_801713A8_2 *)sprite)->unk_24.at01.v,
        D_80082E80.tileX, D_80082E80.tileY, &distance);
}
