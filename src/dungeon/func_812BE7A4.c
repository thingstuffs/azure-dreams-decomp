#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_80159FA4_0 {
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
    u8 pad_A4[0x12];
    s16 unk_B6;
} S_80159FA4_0;   /* arg0 in func_80159FA4 */


typedef struct S_80159FA4_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0xE];
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
} S_80159FA4_2;   /* arg2 in func_80159FA4 */


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
extern void func_8015A510(void *, void *, void *, void *);
extern void func_8015A6C8(void *, void *, void *, void *);
extern s32 func_8015AE10(void *, void *, void *, void *);
extern void func_8015B0A8(void *, void *, void *, void *);
extern s32 func_8015B1CC(void *, void *, void *, void *);
extern void func_8015D078(void *, void *, void *, void *);

extern u8 D_80159FA4[];
extern u8 D_8015DC30[];
extern u8 D_8015DC38[];
extern u8 D_8015DC88[];
extern u8 D_8015DC90[];
extern u8 D_8015DCA0[];
extern u8 D_8015DCA8[];

/* Updates an actor's animation and dispatches its dungeon behavior. */
void func_80159FA4(void *actor, void *context, void *sprite, EntityRec *entity)
{
    s32 distance;
    s8 room_id;
    u16 behavior;

    if (dungeonStatus.flags & 0x1000) {
        ((S_80159FA4_0 *)actor)->unk_9A = 0xE;
        func_8015A510(actor, context, sprite, entity);
        return;
    }
    if (entity->tileY == 0) {
        void *anim_table;

        func_800AA79C(actor, context, sprite, entity);
        if (((S_80159FA4_2 *)sprite)->unk_2C == D_8015DC90) {
            return;
        }
        anim_table = D_8015DCA0;
        (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
        func_80047784(sprite,
            ((u8 *)anim_table)[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)entity->flags1C) & 0x200) {
        if (((S_80159FA4_2 *)sprite)->unk_2C == D_8015DC90) {
            ((S_80159FA4_0 *)actor)->unk_9A = 0xD;
            ((S_80159FA4_0 *)actor)->unk_9B = 1;
            ((S_80159FA4_0 *)actor)->unk_8C = 0;
            entity->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (func_800AA924(actor, context, sprite, D_8015DCA0) != 0) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((u32)entity->flags1C) & 0x100) {
            func_800AA258(actor, context, sprite, entity);
            return;
        }

        {
            u8 current_state = ((S_80159FA4_0 *)actor)->unk_9A;
            u32 next_state = 0xE;
            void *current_anim;

            if (current_state != next_state) {
                ((S_80159FA4_0 *)actor)->unk_9A = next_state;
                ((S_80159FA4_0 *)actor)->unk_B6 = 0;
            }
            current_anim = ((S_80159FA4_2 *)sprite)->unk_2C;
            if (current_anim == D_8015DCA8) {
                if (((S_80159FA4_2 *)sprite)->unk_14 & 0xE000) {
                    (*(void * *)((u8 *)sprite + 0x2C)) = D_8015DC30;
                    func_80047784(sprite,
                        D_8015DC30[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                    ((S_80159FA4_2 *)sprite)->unk_05 = 1;
                    ((S_80159FA4_0 *)actor)->unk_A2.s = 0;
                    ((S_80159FA4_0 *)actor)->unk_9E = 0;
                }
            } else {
                void *idle_anim = D_8015DC30;
                if (current_anim != idle_anim) {
                    (*(void * *)((u8 *)sprite + 0x2C)) = idle_anim;
                    func_80047784(sprite,
                        *(u8 *)((((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7) + (u32)idle_anim),
                        0);
                    ((S_80159FA4_2 *)sprite)->unk_05 = 1;
                    ((S_80159FA4_0 *)actor)->unk_A2.s = 0;
                    ((S_80159FA4_0 *)actor)->unk_9E = 0;
                }
            }
        }

        (*(u32 *)&entity->flags1C) |= 0x40000;
        ((S_80159FA4_0 *)actor)->unk_98 &= 0xFFF7;

        if (entity->unk_64 != 0) {
            if (func_800AA6B4(actor, context, sprite, D_8015DC38) != 0) {
                return;
            }
        }

        if (((u32)entity->flags1C) & 0x80000) {
            s16 movement_delta;

            func_800AA888(actor, context, sprite, entity);
            movement_delta = ((S_80159FA4_0 *)actor)->unk_92.u - ((S_80159FA4_0 *)actor)->unk_A2.u;
            ((S_80159FA4_0 *)actor)->unk_A2.s = 0;
            ((S_80159FA4_0 *)actor)->unk_9E = 0;
            ((S_80159FA4_0 *)actor)->unk_92.s = movement_delta;
            func_8015D078(actor, context, sprite, entity);
            return;
        }

        if ((func_800A1C58(entity) << 16) != 0) {
            func_800AAB10(actor, context, sprite, entity);
        }
    }

    room_id = func_8009FB34(((S_80159FA4_2 *)sprite)->unk_24.at00.v, ((S_80159FA4_2 *)sprite)->unk_24.at01.v);
    ((S_80159FA4_2 *)sprite)->unk_26 = room_id;

    if (entity->unk_6D > 0) {
        if (((u32)entity->flags1C) & 0x20) {
            func_800A9A0C(entity);
            return;
        }
        if (((S_80159FA4_2 *)sprite)->unk_24.at00u.v != *(u16 *)(&D_80082E80.tileX)) {
            if (!(entity->unk_46 & 0x8000)) {
                if (dungeonStatus.flags & 0x2000) {
                    if ((func_8009A180(entity,
                            (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                        return;
                    }
                }
                if ((func_8015B1CC(actor, context, sprite, 0) << 16) == 0) {
                    return;
                }
                behavior = entity->unk_46 | 0x4000;
                entity->unk_46 = behavior;
            }

            if (entity->unk_46 & 0x8000) {
                behavior = entity->unk_46 & 0x3FFF;
                switch (behavior) {
                case 8:
                case 9:
                    if ((func_8015AE10(actor, context, sprite, entity) << 16) != 0) {
                        return;
                    }
                    func_8015B0A8(actor, context, sprite, entity);
                    return;

                case 5:
                case 6:
                case 7:
                {
                    EntityRec *player;
                    s16 facing_angle;

                    facing_angle = func_800A0818(
                        ((S_80159FA4_2 *)sprite)->unk_24.at00.v, ((S_80159FA4_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &distance);
                    player = D_800814A8;
                    entity->facing = facing_angle;
                    if (player->unk_9A == 0x11) {
                        func_800AAF00(actor, context, sprite, D_8015DC88, D_80159FA4);
                        return;
                    }
                }

                case 12:
                    func_800A9A0C(entity);
                    return;

                case 1:
                case 2:
                case 3:
                    func_800AAF00(actor, context, sprite, D_8015DC88, D_80159FA4);
                    return;

                case 11:
                default:
                    break;
                }
            }
        }

        func_8015A6C8(actor, context, sprite, entity);
        return;
    }

    if (!(((u32)entity->flags1C) & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)entity->flags1C) & 0x430)) {

                if ((func_8009FD7C(
                        ((S_80159FA4_2 *)sprite)->unk_24.at00.v, ((S_80159FA4_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY) << 16) != 0) {
                    entity->facing = func_800A0818(
                        ((S_80159FA4_2 *)sprite)->unk_24.at00.v, ((S_80159FA4_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &distance);
                }
            }
        }
    }
}
