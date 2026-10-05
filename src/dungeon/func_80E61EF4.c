#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"


extern void func_80047784(void *, s32, s32);
extern s32 rand(void);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s32 func_800A0818(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void func_80171CA8(void *, void *, void *);
extern void func_80171EEC(void *, void *, void *, void *);
extern s32 func_801726B0(void *, void *, void *, void *);
extern void func_80172874(void *, void *, void *, void *);
extern s32 func_8017298C(void *, void *, void *, s32);
extern void func_8017430C(void *, void *, void *, void *);
extern void func_80174FE4(void *, void *, void *, void *);

extern u8 D_801716F4[];
extern u8 D_80175554[];
extern u8 D_8017555C[];
extern u8 D_80175564[];
extern u8 D_80175594[];
extern u8 D_8017559C[];
extern u8 D_801755A4[];


typedef struct S_801716F4_2 {
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
} S_801716F4_2;   /* arg2 in func_801716F4 */


/* Updates a dungeon actor's behavior, facing, and directional animation. */
void func_801716F4(void *actor_arg, void *context_arg, void *sprite, EntityRec *entity_arg)
{
    u8 *anim_table;
    s32 room_id;
    s32 distance;
    u32 initial_flags = dungeonStatus.flags;


    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 = 0xE;
        func_80171CA8(actor_arg, context_arg, sprite);
        return;
    }


    if (entity_arg->tileY == 0) {
        func_800AA79C(actor_arg, context_arg, sprite, entity_arg);
        {
        void *current_anim = ((S_801716F4_2 *)sprite)->unk_2C;
        ((S_801716F4_2 *)sprite)->unk_2C = current_anim;
        if (current_anim != D_801755A4) {
            (*(void * *)((u8 *)sprite + (0x2C))) = D_8017559C;
            {
                s32 direction_index = ((gameWork.view.viewAngle + entity_arg->facing + 0x100) >> 9) & 7;
                func_80047784(sprite, D_8017559C[direction_index], 0);
            }
        }
        }
        return;
    }

    if (((u32)entity_arg->flags1C) & 0x200) {
        if (((S_801716F4_2 *)sprite)->unk_2C == D_801755A4) {
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_8C = 0;
            entity_arg->flags1C &= ~0x40000;
            return;
        }
        if (func_800AA924(actor_arg, context_arg, sprite, D_8017559C)) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((u32)entity_arg->flags1C) & 0x100) {
            func_800AA258(actor_arg, context_arg, sprite, entity_arg);
            return;
        }

        if (((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 != 0xE) {
            u8 idle_state = 0xE;

            anim_table = D_80175554;
            if (((S_801716F4_2 *)sprite)->unk_2C != anim_table) {
                (*(void * *)((u8 *)sprite + (0x2C))) = anim_table;
                func_80047784(sprite,
                    anim_table[((gameWork.view.viewAngle + entity_arg->facing + 0x100) >> 9) & 7],
                    0);
            }
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9E.as_s16 = 0;
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_A0.at00_s16.v = (rand() & 0x1F) + 0xF;
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 = idle_state;
        }

        ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_98 &= 0xFFF3;
        if (entity_arg->unk_64 != 0) {
            if (func_800AA6B4(actor_arg, context_arg, sprite, D_80175564)) {
                return;
            }
        }

        if (((u32)entity_arg->flags1C) & 0x80000) {
            u8 *event_table;
            u8 *anim_entry;
            void *anim_sprite;
            s32 direction_index;

            func_800AA888(actor_arg, context_arg, sprite, entity_arg);
            func_8017430C(actor_arg, context_arg, sprite, entity_arg);
            event_table = D_8017555C;
            (*(void * *)((u8 *)sprite + (0x2C))) = event_table;
            direction_index = ((gameWork.view.viewAngle + entity_arg->facing + 0x100) >> 9) & 7;
            anim_sprite = sprite;
            anim_entry = event_table + direction_index;
            func_80047784(anim_sprite, anim_entry[0], 0);
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_90.at00_s32.v = 0;
            return;
        }

        if ((func_800A1C58(entity_arg) << 16) != 0) {
            func_800AAB10(actor_arg, context_arg, sprite, entity_arg);
        }
    }

    room_id = func_8009FB34(((S_801716F4_2 *)sprite)->unk_24.at00.v, ((S_801716F4_2 *)sprite)->unk_24.at01.v);
    ((S_801716F4_2 *)sprite)->unk_26 = room_id;

    if (entity_arg->unk_6D > 0) {
        u16 action_flags;

        if (((u32)entity_arg->flags1C) & 0x20) {
            func_800A9A0C(entity_arg);
            return;
        }
        if (((S_801716F4_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            func_80171EEC(actor_arg, context_arg, sprite, entity_arg);
            return;
        }
        if (!(entity_arg->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((func_8009A180(entity_arg,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_8017298C(actor_arg, context_arg, sprite, 0) << 16) == 0) {
                return;
            }
            action_flags = entity_arg->unk_46 | 0x4000;
            entity_arg->unk_46 = action_flags;
            if (!(action_flags & 0x8000)) {
                func_80171EEC(actor_arg, context_arg, sprite, entity_arg);
                return;
            }
        }

        action_flags = entity_arg->unk_46 & 0x3FFF;
        switch (action_flags) {
        case 8:
            if ((func_801726B0(actor_arg, context_arg, sprite, entity_arg) << 16) != 0) {
                return;
            }
            func_80172874(actor_arg, context_arg, sprite, entity_arg);
            return;

        case 9:
            func_80174FE4(actor_arg, context_arg, sprite, entity_arg);
            return;

        case 5:
        case 6:
        case 7:
        {
            EntityRec *player;
            s16 heading;

            heading = func_800A0818(
                ((S_801716F4_2 *)sprite)->unk_24.at00.v, ((S_801716F4_2 *)sprite)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY,
                &distance);
            player = D_800814A8;
            entity_arg->facing = heading;
            if (player->unk_9A == 0x11) {
                func_800AAF00(actor_arg, context_arg, sprite, D_80175594, D_801716F4);
                return;
            }
        }

        case 12:
            func_800A9A0C(entity_arg);
            return;

        case 1:
        case 2:
        case 3:
            func_800AAF00(actor_arg, context_arg, sprite, D_80175594, D_801716F4);
            return;

        default:
            func_80171EEC(actor_arg, context_arg, sprite, entity_arg);
            return;
        }
    } else if (!(((u32)entity_arg->flags1C) & 0x2000)) {
        s32 room_index = (s8)room_id;

        if ((room_index < 0) ||
            !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)entity_arg->flags1C) & 0x430)) {

                if ((func_8009FD7C(
                        ((S_801716F4_2 *)sprite)->unk_24.at00.v, ((S_801716F4_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY) << 16) != 0) {
                    entity_arg->facing = func_800A0818(
                        ((S_801716F4_2 *)sprite)->unk_24.at00.v, ((S_801716F4_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &distance);
                }
            }
        }
    }

    if (dungeonStatus.flags & 0x2000) {
        return;
    }
    if (((S_801716F4_2 *)sprite)->unk_14 & 0x40) {
        return;
    }
    anim_table = D_80175554;
    if (((S_801716F4_2 *)sprite)->unk_2C == anim_table) {
        return;
    }
    (*(void * *)((u8 *)sprite + (0x2C))) = anim_table;
    {
        s32 direction_index = ((gameWork.view.viewAngle + entity_arg->facing + 0x100) >> 9) & 7;
        func_80047784(sprite, anim_table[direction_index], 0);
    }
}
