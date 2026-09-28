#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"


typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s32 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_8017139C(void *, void *, void *, void *);
extern void func_801715F4(void *, void *, void *, void *);
extern s32 func_80171DA0(void *, void *, void *, void *);
extern void func_80171F64(void *, void *, void *, void *);
extern s32 func_8017207C(void *, void *, void *, s32);
extern void func_80173A30(void *, void *, void *, void *);

extern void *D_80170808[];
extern u8 D_80170E54;
extern u8 D_80173C7C[];
extern u8 D_80173C84[];
extern u8 D_80173CCC[];
extern u8 D_80173CD4[];
extern u8 D_80173CDC[];




typedef struct S_80170E54_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80170E54_2;   /* arg2 in func_80170E54 */


typedef struct S_80170E54_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80170E54_4;   /* origin in func_80170E54 */

typedef struct S_80170E54_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80170E54_5;   /* global in func_80170E54 */

/* Updates entity behavior, facing, and animation from dungeon and actor state. */
void func_80170E54(void *input_controller, void *input_context, void *input_entity, void *input_actor_state)
{
    void *controller;
    void *context;
    void *entity;
    void *actor_state;
    u8 *anim_table;
    register u8 *next_table ASM_REG("$5"); /* MATCH: both paths supply the shared tail anim_table in a1. */
    s32 room_id;
    s32 direction_flags;
    u32 initial_flags = dungeonStatus.flags;

    controller = input_controller;
    context = input_context;
    entity = input_entity;
    actor_state = input_actor_state;

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = 0xE;
        func_8017139C(controller, context, entity, actor_state);
        return;
    }


    if (((EntityRec *)actor_state)->tileY == 0) {
        func_800AA79C(controller, context, entity, actor_state);
        if (((S_80170E54_2 *)entity)->unk_2C != D_80173CDC) {
            next_table = D_80173CD4;
            goto update_table;
        }
        return;
    }

    if (((u32)((EntityRec *)actor_state)->flags1C) & 0x200) {
        if (((S_80170E54_2 *)entity)->unk_2C == D_80173CDC) {
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)controller)->unk_8C = 0;
            ((EntityRec *)actor_state)->flags1C &= ~0x40000;
            return;
        }
        if (func_800AA924(controller, context, entity, D_80173CD4)) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((u32)((EntityRec *)actor_state)->flags1C) & 0x100) {
            func_800AA258(controller, context, entity, actor_state);
            return;
        }

        if (((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 != 0xE) {
            u8 control_state = 0xE;

            anim_table = D_80173C7C;
            if (((S_80170E54_2 *)entity)->unk_2C != anim_table) {
                (*(void * *)((u8 *)entity + (0x2C))) = anim_table;
                func_80047784(entity,
                    anim_table[((gameWork.viewAngle + ((EntityRec *)actor_state)->facing + 0x100) >> 9) & 7],
                    0);
            }
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = control_state;
        }

        ((Rec_func_800A9E70_arg0 *)controller)->unk_98 &= 0xFFF3;
        if (((EntityRec *)actor_state)->unk_64 != 0) {
            if (func_800AA6B4(controller, context, entity, D_80173C84)) {
                return;
            }
        }

        if (((u32)((EntityRec *)actor_state)->flags1C) & 0x80000) {
            func_800AA888(controller, context, entity, actor_state);
            func_80173A30(controller, context, entity, actor_state);
            return;
        }

        if ((s16)func_800A1C58(actor_state) != 0) {
            func_800AAB10(controller, context, entity, actor_state);
        }
    }

    room_id = func_8009FB34(((S_80170E54_2 *)entity)->unk_24.at00.v, ((S_80170E54_2 *)entity)->unk_24.at01.v);
    ((S_80170E54_2 *)entity)->unk_26 = room_id;

    if (((EntityRec *)actor_state)->unk_6D > 0) {
        if (((u32)((EntityRec *)actor_state)->flags1C) & 0x20) {
            goto special_cleanup;
        }
        if (((S_80170E54_2 *)entity)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            goto ordinary_cleanup;
        }
        if (!(((EntityRec *)actor_state)->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((s16)func_8009A180(actor_state,
                        (u8 *)((EntityRec *)D_800814A8)->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_8017207C(controller, context, entity, 0) == 0) {
                return;
            }
            ((EntityRec *)actor_state)->unk_46 |= 0x4000;
            if (!(((EntityRec *)actor_state)->unk_46 & 0x8000)) {
                goto ordinary_cleanup;
            }
        }

#ifdef __mips__
        {
            static void *volatile dispatch_labels[] = {
                &&aaf_cleanup, &&aaf_cleanup, &&aaf_cleanup,
                &&ordinary_cleanup,
                &&coords_case, &&coords_case, &&coords_case,
                &&handler_case, &&handler_case,
                &&ordinary_cleanup, &&ordinary_cleanup,
                &&special_cleanup,
            };
            s32 dispatch_index;

            dispatch_index = (((EntityRec *)actor_state)->unk_46 & 0x3FFF) - 1;
            if ((u32)dispatch_index >= 12) {
                goto ordinary_cleanup;
            }
            goto *D_80170808[dispatch_index];
        }
handler_case:
#else
        switch (((EntityRec *)actor_state)->unk_46 & 0x3FFF) {
        case 8:
        case 9:
#endif
            if ((s16)func_80171DA0(controller, context, entity, actor_state) == 0) {
                func_80171F64(controller, context, entity, actor_state);
                return;
            }
            return;

#ifdef __mips__
coords_case:
#else
        case 5:
        case 6:
        case 7:
#endif
        {
            void *player_controller;
            s32 direction;

            direction = func_800A0818(
                ((S_80170E54_2 *)entity)->unk_24.at00.v, ((S_80170E54_2 *)entity)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY,
                &direction_flags);
            player_controller = D_800814A8;
            ((EntityRec *)actor_state)->facing = direction;
            if (((S_80170E54_5 *)player_controller)->unk_9A == 0x11) {
                goto aaf_cleanup;
            }
            goto special_cleanup;
        }
#ifndef __mips__
        case 1:
        case 2:
        case 3:
            goto aaf_cleanup;

        case 12:
            goto special_cleanup;

        default:
            goto ordinary_cleanup;
        }
#endif

special_cleanup:
        func_800A9A0C(actor_state);
        return;

aaf_cleanup:
        func_800AAF00(controller, context, entity, D_80173CCC, &D_80170E54);
        return;

ordinary_cleanup:
        func_801715F4(controller, context, entity, actor_state);
        return;
    } else if (!(((u32)((EntityRec *)actor_state)->flags1C) & 0x2000)) {
        s32 room_index = (s8)room_id;

        if ((room_index < 0) || !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)((EntityRec *)actor_state)->flags1C) & 0x430)) {

                if ((s16)func_8009FD7C(((S_80170E54_2 *)entity)->unk_24.at00.v,
                        ((S_80170E54_2 *)entity)->unk_24.at01.v, D_80082E80.tileX,
                        D_80082E80.tileY) != 0) {
                    ((EntityRec *)actor_state)->facing = func_800A0818(
                        ((S_80170E54_2 *)entity)->unk_24.at00.v, ((S_80170E54_2 *)entity)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &direction_flags);
                }
            }
        }
    }

    if (dungeonStatus.flags & 0x2000) {
        return;
    }
    if (((S_80170E54_2 *)entity)->unk_14 & 0x40) {
        return;
    }
    anim_table = D_80173C7C;
    if (((S_80170E54_2 *)entity)->unk_2C == anim_table) {
        return;
    }
    next_table = anim_table;
update_table:
    anim_table = next_table;
    (*(void * *)((u8 *)entity + (0x2C))) = anim_table;
    func_80047784(entity,
        *(u8 *)((u32)(((gameWork.viewAngle + ((EntityRec *)actor_state)->facing + 0x100) >> 9) & 7) + (u32)anim_table),
        0);
}
