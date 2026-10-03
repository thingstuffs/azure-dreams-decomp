#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"


extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
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
extern void func_80171684(void *, void *, void *, void *);
extern void func_801718DC(void *, void *, void *, void *);
extern s32 func_80172088(void *, void *, void *, void *);
extern void func_8017224C(void *, void *, void *, void *);
extern s32 func_80172364(void *, void *, void *, s32);
extern void func_80174060(void *, void *, void *, void *);
extern void func_80174234(void *, void *, void *, void *);
extern void func_80174B14(void *, void *, void *, void *);

extern u8 D_800DCF5B;
extern u8 D_80174F00[];
extern u8 D_80174F08[];
extern u8 D_80174F38;
extern u8 D_80174F40;
extern u8 D_80174F48;


typedef struct S_801710F4_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_801710F4_2;   /* arg2 in func_801710F4 */


/* Updates dungeon actor behavior, facing, and animation from its current state. */
void func_801710F4(void *actor, void *context, void *sprite, EntityRec *entity)
{
    u8 *anim_table;
    s32 distance;
    s8 room_id;
    u16 action_state;
    u16 initial_flags = dungeonStatus.flags;


    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xE;
        func_80171684(actor, context, sprite, entity);
        return;
    }


    if (entity->tileY == 0) {
        func_800AA79C(actor, context, sprite, entity);
        if (((S_801710F4_2 *)sprite)->unk_2C != &D_80174F48) {
            u8 *next_anim_table = &D_80174F40;

            (*(void * *)((u8 *)sprite + 0x2C)) = next_anim_table;
            func_80047784(sprite,
                *(u8 *)((u32)(((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7) +
                        (u32)next_anim_table),
                0);
        }
        return;
    }

    if (((u32)entity->flags1C) & 0x200) {
        if (((S_801710F4_2 *)sprite)->unk_2C == &D_80174F48) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
            entity->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (func_800AA924(actor, context, sprite, &D_80174F40) != 0) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((u32)entity->flags1C) & 0x100) {
            func_800AA258(actor, context, sprite, entity);
            return;
        }

        if (((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 != 0xE) {
            u8 actor_state = 0xE;

            anim_table = D_80174F00;
            if (((S_801710F4_2 *)sprite)->unk_2C != anim_table) {
                (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
                func_80047784(sprite,
                    anim_table[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                    0);
            }
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = actor_state;
        }

        ((Rec_func_800A9E70_arg0 *)actor)->unk_98 &= 0xFFF3;
        if (entity->unk_64 != 0) {
            if (func_800AA6B4(actor, context, sprite, D_80174F08) != 0) {
                return;
            }
        }

        if (((u32)entity->flags1C) & 0x80000) {
            func_800AA888(actor, context, sprite, entity);
            func_80174060(actor, context, sprite, entity);
            return;
        }

        if ((func_800A1C58(entity) << 16) != 0) {
            func_800AAB10(actor, context, sprite, entity);
        }
    }

    room_id = func_8009FB34(((S_801710F4_2 *)sprite)->unk_24.at00.v, ((S_801710F4_2 *)sprite)->unk_24.at01.v);
    ((S_801710F4_2 *)sprite)->unk_26 = room_id;

    if (entity->unk_6D > 0) {
        if (((u32)entity->flags1C) & 0x20) {
            func_800A9A0C(entity);
            return;
        }
        if (((S_801710F4_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            func_801718DC(actor, context, sprite, entity);
            return;
        }
        if (!(entity->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((func_8009A180(entity,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_80172364(actor, context, sprite, 0) << 16) == 0) {
                return;
            }
            action_state = entity->unk_46 | 0x4000;
            entity->unk_46 = action_state;
            if (!(action_state & 0x8000)) {
                func_801718DC(actor, context, sprite, entity);
                return;
            }
        }

        action_state = entity->unk_46 & 0x3FFF;
        switch (action_state) {
        case 8:
            if ((func_80172088(actor, context, sprite, entity) << 16) == 0) {
                func_8017224C(actor, context, sprite, entity);
            }
            return;

        case 10:
            func_80174B14(actor, context, sprite, entity);
            return;

        case 9:
            if (D_800DCF5B != 0) {
                break;
            }
            func_80174234(actor, context, sprite, entity);
            return;

        case 5:
        case 6:
        case 7:
        {
            EntityRec *player;
            s16 facing_angle;

            facing_angle = func_800A0818(
                ((S_801710F4_2 *)sprite)->unk_24.at00.v, ((S_801710F4_2 *)sprite)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY,
                &distance);
            player = D_800814A8;
            entity->facing = facing_angle;
            if (player->unk_9A == 0x11) {
                func_800AAF00(actor, context, sprite, &D_80174F38, func_801710F4);
                return;
            }
        }

        case 12:
            func_800A9A0C(entity);
            return;

        case 1:
        case 2:
        case 3:
            func_800AAF00(actor, context, sprite, &D_80174F38, func_801710F4);
            return;

        case 11:
        case 4:
        default:
            break;
        }
        func_801718DC(actor, context, sprite, entity);
        return;
    }

    if (!(((u32)entity->flags1C) & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)entity->flags1C) & 0x430)) {

                if ((func_8009FD7C(
                        ((S_801710F4_2 *)sprite)->unk_24.at00.v, ((S_801710F4_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY) << 16) != 0) {
                    entity->facing = func_800A0818(
                        ((S_801710F4_2 *)sprite)->unk_24.at00.v, ((S_801710F4_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &distance);
                }
            }
        }
    }

    if (dungeonStatus.flags & 0x2000) {
        return;
    }
    if (((S_801710F4_2 *)sprite)->unk_14 & 0x40) {
        return;
    }
    anim_table = D_80174F00;
    if (((S_801710F4_2 *)sprite)->unk_2C == anim_table) {
        return;
    }

    (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
    func_80047784(sprite,
        *(u8 *)((u32)(((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7) +
                (u32)anim_table),
        0);
}
