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
extern s16 func_800A0818(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void func_8016BCD4(void *, void *, void *, void *);
extern void func_8016BF40(void *, void *, void *, void *);
extern s32 func_8016C710(void *, void *, void *, void *);
extern void func_8016C8D4(void *, void *, void *, void *);
extern s32 func_8016C9EC(void *, void *, void *, s32);
extern void func_8016E3E8(void *, void *, void *, void *);
extern void func_8016E928(void *, void *, void *, void *);

extern s32 D_8016B728;
extern u8 D_8016EDEC[];
extern u8 D_8016EDFC[];
extern u8 D_8016EE2C[];
extern u8 D_8016EE44[];
extern u8 D_8016EE4C[];


typedef struct S_80171728_2 {
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
} S_80171728_2;   /* arg2 in func_8016B728 */


/* Updates creature behavior, facing, and animation from dungeon and action state. */
void func_8016B728(void *actor_in, void *context_in, void *sprite, EntityRec *creature_in)
{
    u8 *anim_table;
    s32 distance;
    s8 room_id;
    u16 action_flags;
    u32 initial_flags = dungeonStatus.flags;

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor_in)->unk_9A.as_u8 = 0xE;
        func_8016BCD4(actor_in, context_in, sprite, creature_in);
        return;
    }

    if (creature_in->tileY == 0) {
        func_800AA79C(actor_in, context_in, sprite, creature_in);
        if (((S_80171728_2 *)sprite)->unk_2C == D_8016EE4C) {
            return;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = D_8016EE44;
        func_80047784(sprite,
            D_8016EE44[((gameWork.view.viewAngle + creature_in->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)creature_in->flags1C) & 0x200) {
        if (((S_80171728_2 *)sprite)->unk_2C == D_8016EE4C) {
            ((Rec_func_800A9E70_arg0 *)actor_in)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)actor_in)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)actor_in)->unk_8C = 0;
            creature_in->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (func_800AA924(actor_in, context_in, sprite, D_8016EE44) != 0) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((u32)creature_in->flags1C) & 0x100) {
            func_800AA258(actor_in, context_in, sprite, creature_in);
            return;
        }

        {
            u32 current_state = ((Rec_func_800A9E70_arg0 *)actor_in)->unk_9A.as_u8;
            u32 next_state;

            next_state = 0xE;
            if (current_state != next_state) {
                anim_table = D_8016EDEC;
                if (((S_80171728_2 *)sprite)->unk_2C != anim_table) {
                    (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
                    func_80047784(sprite,
                        anim_table[((gameWork.view.viewAngle + creature_in->facing + 0x100) >> 9) & 7],
                        0);
                }
                ((Rec_func_800A9E70_arg0 *)actor_in)->unk_9E.as_s16 = 0;
                ((Rec_func_800A9E70_arg0 *)actor_in)->unk_A0.at00_s16.v = 0x14;
                ((Rec_func_800A9E70_arg0 *)actor_in)->unk_9A.as_u8 = next_state;
            }
        }

        ((Rec_func_800A9E70_arg0 *)actor_in)->unk_98 &= 0xFFF3;
        if (creature_in->unk_64 != 0) {
            if (func_800AA6B4(actor_in, context_in, sprite, D_8016EDFC) != 0) {
                return;
            }
        }

        if (((u32)creature_in->flags1C) & 0x80000) {
            func_800AA888(actor_in, context_in, sprite, creature_in);
            func_8016E3E8(actor_in, context_in, sprite, creature_in);
            (*(void * *)((u8 *)sprite + 0x2C)) = D_8016EDEC;
            func_80047784(sprite,
                D_8016EDEC[((gameWork.view.viewAngle + creature_in->facing + 0x100) >> 9) & 7],
                0);
            ((Rec_func_800A9E70_arg0 *)actor_in)->unk_90.at00_s32.v = 0;
            return;
        }

        if ((func_800A1C58(creature_in) << 16) != 0) {
            func_800AAB10(actor_in, context_in, sprite, creature_in);
        }
    }

    room_id = func_8009FB34(((S_80171728_2 *)sprite)->unk_24.at00.v, ((S_80171728_2 *)sprite)->unk_24.at01.v);
    ((S_80171728_2 *)sprite)->unk_26 = room_id;

    if (creature_in->unk_6D > 0) {
        if (((u32)creature_in->flags1C) & 0x20) {
            func_800A9A0C(creature_in);
            return;
        }
        if (((S_80171728_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            func_8016BF40(actor_in, context_in, sprite, creature_in);
            return;
        }
        if (!(creature_in->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((func_8009A180(creature_in,
                    (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_8016C9EC(actor_in, context_in, sprite, 0) << 16) == 0) {
                return;
            }
            action_flags = creature_in->unk_46 | 0x4000;
            creature_in->unk_46 = action_flags;
            if (!(action_flags & 0x8000)) {
                func_8016BF40(actor_in, context_in, sprite, creature_in);
                return;
            }
        }

        action_flags = creature_in->unk_46 & 0x3FFF;
        switch (action_flags) {
        case 8:
            if ((func_8016C710(actor_in, context_in, sprite, creature_in) << 16) != 0) {
                return;
            }
            func_8016C8D4(actor_in, context_in, sprite, creature_in);
            return;

        case 9:
            func_8016E928(actor_in, context_in, sprite, creature_in);
            return;

        case 5:
        case 6:
        case 7:
            {
                EntityRec *player;
                s16 heading;

                heading = func_800A0818(
                    ((S_80171728_2 *)sprite)->unk_24.at00.v, ((S_80171728_2 *)sprite)->unk_24.at01.v,
                    D_80082E80.tileX, D_80082E80.tileY,
                    &distance);
                player = D_800814A8;
                creature_in->facing = heading;
                if (player->unk_9A == 0x11) {
                    func_800AAF00(actor_in, context_in, sprite, D_8016EE2C, &D_8016B728);
                    return;
                }
            }

        case 12:
            func_800A9A0C(creature_in);
            return;

        case 1:
        case 2:
        case 3:
            func_800AAF00(actor_in, context_in, sprite, D_8016EE2C, &D_8016B728);
            return;

        case 10:
        default:
            func_8016BF40(actor_in, context_in, sprite, creature_in);
            return;
        }
    }

    if (!(((u32)creature_in->flags1C) & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)creature_in->flags1C) & 0x430)) {

                if ((func_8009FD7C(
                    ((S_80171728_2 *)sprite)->unk_24.at00.v, ((S_80171728_2 *)sprite)->unk_24.at01.v,
                    D_80082E80.tileX, D_80082E80.tileY) << 16) != 0) {
                    creature_in->facing = func_800A0818(
                        ((S_80171728_2 *)sprite)->unk_24.at00.v, ((S_80171728_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &distance);
                }
            }
        }
    }

    if (dungeonStatus.flags & 0x2000) {
        return;
    }
    if (((S_80171728_2 *)sprite)->unk_14 & 0x40) {
        return;
    }
    anim_table = D_8016EDEC;
    if (((S_80171728_2 *)sprite)->unk_2C == anim_table) {
        return;
    }
    (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
    func_80047784(sprite,
        *(u8 *)(((((gameWork.view.viewAngle + creature_in->facing + 0x100) >> 9) & 7)) + (u32)anim_table),
        0);
}
