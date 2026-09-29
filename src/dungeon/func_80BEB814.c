#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
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
extern s32 func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_80171574(void *, void *);
extern void func_80171784(void *, void *, void *, void *);
extern s32 func_80171ECC(void *, void *, void *, void *);
extern void func_80172090(void *, void *, void *, void *);
extern s32 func_801721B4(void *, void *, void *, void *);
extern void func_80173468(void *, void *, void *, void *);
extern void func_80173AE8(void *, void *, void *, void *);

extern u8 D_80171014[];
extern u8 D_8017420C[];
extern u8 D_8017421C[];
extern u8 D_8017424C[];
extern u8 D_80174254[];
extern u8 D_8017425C[];


typedef struct S_80171014_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    union { u16 u; s16 s; } unk_92;   /* accessed as both */
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    union { s16 s; u16 u; } unk_A2;   /* accessed as both */
} S_80171014_0;   /* arg0 in func_80171014 */


typedef struct S_80171014_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0x1E];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80171014_2;   /* arg2 in func_80171014 */


/* Updates a dungeon actor's state, animation, and behavior. */
void func_80171014(void *actor, void *actor_context, void *map_object, EntityRec *creature)
{
    s32 distance;
    s8 room_id;
    u16 action_state;

    if (dungeonStatus.flags & 0x1000) {
        ((S_80171014_0 *)actor)->unk_9A = 0xE;
        func_80171574(actor, actor_context);
        return;
    }
    if (creature->tileY == 0) {
        void *animation_table;

        func_800AA79C(actor, actor_context, map_object, creature);
        if (((S_80171014_2 *)map_object)->unk_2C == D_8017425C) {
            return;
        }
        animation_table = D_80174254;
        (*(void * *)((u8 *)map_object + (0x2C))) = animation_table;
        func_80047784(map_object,
            ((u8 *)animation_table)[((gameWork.view.viewAngle + creature->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)creature->flags1C) & 0x200) {
        if (((S_80171014_2 *)map_object)->unk_2C == D_8017425C) {
            ((S_80171014_0 *)actor)->unk_9A = 0xD;
            ((S_80171014_0 *)actor)->unk_9B = 1;
            ((S_80171014_0 *)actor)->unk_8C = 0;
            creature->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (func_800AA924(actor, actor_context, map_object, D_80174254) != 0) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((u32)creature->flags1C) & 0x100) {
            func_800AA258(actor, actor_context, map_object, creature);
            return;
        }

        {
            u8 current_state = ((S_80171014_0 *)actor)->unk_9A;
            u32 next_state = 0xE;
            void *current_animation;
            void *animation_table;

            if (current_state != next_state) {
                ((S_80171014_0 *)actor)->unk_9A = next_state;
            }
            current_animation = ((S_80171014_2 *)map_object)->unk_2C;
            animation_table = D_8017420C;
            if (current_animation != animation_table) {
                (*(void * *)((u8 *)map_object + (0x2C))) = animation_table;
                func_80047784(map_object,
                    ((u8 *)animation_table)[((gameWork.view.viewAngle + creature->facing + 0x100) >> 9) & 7],
                    0);
                ((S_80171014_2 *)map_object)->unk_05 = 1;
                ((S_80171014_0 *)actor)->unk_A2.s = 0;
                ((S_80171014_0 *)actor)->unk_9E = 0;
            }
        }

        creature->flags1C |= 0x40000;
        ((S_80171014_0 *)actor)->unk_98 &= 0xFFF7;

        if (creature->unk_64 != 0) {
            if (func_800AA6B4(actor, actor_context, map_object, D_8017421C) != 0) {
                return;
            }
        }

        if (((u32)creature->flags1C) & 0x80000) {
            s16 offset_delta;

            func_800AA888(actor, actor_context, map_object, creature);
            offset_delta = ((S_80171014_0 *)actor)->unk_92.u - ((S_80171014_0 *)actor)->unk_A2.u;
            ((S_80171014_0 *)actor)->unk_A2.s = 0;
            ((S_80171014_0 *)actor)->unk_9E = 0;
            ((S_80171014_0 *)actor)->unk_92.s = offset_delta;
            func_80173468(actor, actor_context, map_object, creature);
            return;
        }

        if ((func_800A1C58(creature) << 16) != 0) {
            if ((func_800AAB10(actor, actor_context, map_object, creature) << 16) != 0) {
                func_80173AE8(actor, actor_context, map_object, creature);
                return;
            }
        }
    }

    room_id = func_8009FB34(((S_80171014_2 *)map_object)->unk_24.at00.v, ((S_80171014_2 *)map_object)->unk_24.at01.v);
    ((S_80171014_2 *)map_object)->unk_26 = room_id;

    if (creature->unk_6D > 0) {
        if (((u32)creature->flags1C) & 0x20) {
            goto case_12;
        }
        if (((S_80171014_2 *)map_object)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            goto generic;
        }
        if (!(creature->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((func_8009A180(creature,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_801721B4(actor, actor_context, map_object, 0) << 16) == 0) {
                return;
            }
            action_state = creature->unk_46 | 0x4000;
            creature->unk_46 = action_state;
            if (!(action_state & 0x8000)) {
                goto generic;
            }
        }

        action_state = creature->unk_46 & 0x3FFF;
        switch (action_state - 1) {

    case 7:
    case 8:
        if ((func_80171ECC(actor, actor_context, map_object, creature) << 16) != 0) {
            return;
        }
        func_80172090(actor, actor_context, map_object, creature);
        return;

    case 4:
    case 5:
    case 6:
        {
            EntityRec *player;
            s16 facing_angle;

            facing_angle = func_800A0818(
                ((S_80171014_2 *)map_object)->unk_24.at00.v, ((S_80171014_2 *)map_object)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY,
                &distance);
            player = D_800814A8;
            creature->facing = facing_angle;
            if (player->unk_9A == 0x11) {
                goto case_123;
            }
        }

    case 11:
case_12:
        func_800A9A0C(creature);
        return;

    case 0:
    case 1:
    case 2:
case_123:
        func_800AAF00(actor, actor_context, map_object, D_8017424C, D_80171014);
        return;

    case 3:
    case 9:
    case 10:
    default:
generic:
        func_80171784(actor, actor_context, map_object, creature);
        return;
        }
    }

    if (!(((u32)creature->flags1C) & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)creature->flags1C) & 0x430)) {

                if ((func_8009FD7C(
                        ((S_80171014_2 *)map_object)->unk_24.at00.v, ((S_80171014_2 *)map_object)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY) << 16) != 0) {
                    creature->facing = func_800A0818(
                        ((S_80171014_2 *)map_object)->unk_24.at00.v, ((S_80171014_2 *)map_object)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &distance);
                }
            }
        }
    }
}
