#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_801710EC_0 {
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
    u8 pad_A4[0xE];
    s16 unk_B2;
} S_801710EC_0;   /* arg0 in func_801710EC */


typedef struct S_801710EC_2 {
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
} S_801710EC_2;   /* arg2 in func_801710EC */


extern s32 func_80042900(void *, s32);
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
extern void func_8017169C(void *);
extern void func_80171854(void *, void *, void *, void *);
extern s32 func_80171F9C(void *, void *, void *, void *);
extern void func_80172234(void *, void *, void *, void *);
extern void func_80172358(void *, void *, void *, void *);
extern s32 func_8017266C(void *, void *, void *, s32);
extern void func_80174574(void *, void *, void *, void *);

extern u8 D_80175E40[];
extern u8 D_80175E48[];
extern u8 D_80175E98[];
extern u8 D_80175EA0[];
extern u8 D_80175EB0[];
extern u8 D_80175EB8[];

/* Updates actor animation and dispatches dungeon behavior based on status and position. */
void func_801710EC(void *actor, void *context, void *sprite, EntityRec *entity)
{
    s32 distance;
    s8 room_id;
    u16 action_flags;

    if (dungeonStatus.flags & 0x1000) {
        ((S_801710EC_0 *)actor)->unk_9A = 0xE;
        func_8017169C(actor);
        return;
    }

    if (entity->tileY == 0) {
        u8 *anim_table;

        func_800AA79C(actor, context, sprite, entity);
        if (((S_801710EC_2 *)sprite)->unk_2C == D_80175EA0) {
            return;
        }
        anim_table = D_80175EB0;
        (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
        func_80047784(sprite,
            anim_table[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)entity->flags1C) & 0x200) {
        if (((S_801710EC_2 *)sprite)->unk_2C == D_80175EA0) {
            ((S_801710EC_0 *)actor)->unk_9A = 0xD;
            ((S_801710EC_0 *)actor)->unk_9B = 1;
            ((S_801710EC_0 *)actor)->unk_8C = 0;
            entity->flags1C &= ~0x40000;
            return;
        }
        if (func_800AA924(actor, context, sprite, D_80175EB0) != 0) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((u32)entity->flags1C) & 0x100) {
            func_800AA258(actor, context, sprite, entity);
            return;
        }

        {
            void *current_anim;
            u8 *anim_table;

            if (((S_801710EC_0 *)actor)->unk_9A != 0xE) {
                ((S_801710EC_0 *)actor)->unk_9A = 0xE;
                ((S_801710EC_0 *)actor)->unk_B2 = 0;
            }

            current_anim = ((S_801710EC_2 *)sprite)->unk_2C;
            if (current_anim == D_80175EB8) {
                if (((S_801710EC_2 *)sprite)->unk_14 & 0xE000) {
                    u8 *reset_anim = D_80175E40;

                    (*(void * *)((u8 *)sprite + 0x2C)) = reset_anim;
                    func_80047784(sprite,
                        reset_anim[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                    ((S_801710EC_2 *)sprite)->unk_05 = 1;
                    ((S_801710EC_0 *)actor)->unk_A2.s = 0;
                    ((S_801710EC_0 *)actor)->unk_9E = 0;
                }
            } else {
                anim_table = D_80175E40;
                if (current_anim != anim_table) {
                    (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
                    func_80047784(sprite,
                        anim_table[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                    ((S_801710EC_2 *)sprite)->unk_05 = 1;
                    ((S_801710EC_0 *)actor)->unk_A2.s = 0;
                    ((S_801710EC_0 *)actor)->unk_9E = 0;
                }
            }
        }

        entity->flags1C |= 0x40000;
        ((S_801710EC_0 *)actor)->unk_98 &= 0xFFF7;

        if (entity->unk_64 != 0) {
            if (func_800AA6B4(actor, context, sprite, D_80175E48) != 0) {
                return;
            }
        }

        if (((u32)entity->flags1C) & 0x80000) {
            s16 adjusted_offset;

            func_800AA888(actor, context, sprite, entity);
            adjusted_offset = ((S_801710EC_0 *)actor)->unk_92.u - ((S_801710EC_0 *)actor)->unk_A2.u;
            ((S_801710EC_0 *)actor)->unk_A2.s = 0;
            ((S_801710EC_0 *)actor)->unk_9E = 0;
            ((S_801710EC_0 *)actor)->unk_92.s = adjusted_offset;
            func_80174574(actor, context, sprite, entity);
            return;
        }

        if ((func_800A1C58(entity) << 16) != 0) {
            func_800AAB10(actor, context, sprite, entity);
        }
    }

    room_id = func_8009FB34(((S_801710EC_2 *)sprite)->unk_24.at00.v, ((S_801710EC_2 *)sprite)->unk_24.at01.v);
    ((S_801710EC_2 *)sprite)->unk_26 = room_id;

    if (entity->unk_6D > 0) {
        if (((u32)entity->flags1C) & 0x20) {
            goto case_12;
        }
        if (((S_801710EC_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            goto generic;
        }
        if (!(entity->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((func_8009A180(entity,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_8017266C(actor, context, sprite, 0) << 16) == 0) {
                return;
            }
            action_flags = entity->unk_46 | 0x4000;
            entity->unk_46 = action_flags;
            if (!(action_flags & 0x8000)) {
                goto generic;
            }
        }

        {
            u32 action_index = (u32)((entity->unk_46 & 0x3FFF) - 1);

            switch (action_index) {
            case 7:
            case 8:
                if ((func_80171F9C(actor, context, sprite, entity) << 16) != 0) {
                    return;
                }
                func_80172234(actor, context, sprite, entity);
                return;

            case 4:
            case 5:
            case 6:
            {
                EntityRec *player;
                s16 facing_angle;

                facing_angle = func_800A0818(
                    ((S_801710EC_2 *)sprite)->unk_24.at00.v, ((S_801710EC_2 *)sprite)->unk_24.at01.v,
                    D_80082E80.tileX, D_80082E80.tileY,
                    &distance);
                player = D_800814A8;
                entity->facing = facing_angle;
                if (player->unk_9A == 0x11) {
                    goto case_123;
                }
            }
                            /* fallthrough */

            case 11:
case_12:
                func_800A9A0C(entity);
                return;

            case 0:
            case 1:
            case 2:
case_123:
                func_800AAF00(actor, context, sprite, D_80175E98, func_801710EC);
                return;

            case 3:
            case 9:
            case 10:
            default:
generic:
                func_80171854(actor, context, sprite, entity);
                return;
            }
        }
    }

    if (!(((u32)entity->flags1C) & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)entity->flags1C) & 0x430)) {

                if ((func_8009FD7C(
                        ((S_801710EC_2 *)sprite)->unk_24.at00.v, ((S_801710EC_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY) << 16) != 0) {
                    entity->facing = func_800A0818(
                        ((S_801710EC_2 *)sprite)->unk_24.at00.v, ((S_801710EC_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &distance);
                    return;
                }
            }
        }
    } else if ((func_80042900(entity, 4) << 16) == 0) {
        if (D_800814A8->unk_9A == 0x17) {
            func_80172358(actor, context, sprite, entity);
        }
    }
}
