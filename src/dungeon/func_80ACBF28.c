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

typedef struct ActorSpriteView {
    u8 pad_00[0x14];
    u16 flags;
    u8 pad_16[0xE];
    union {
        struct { u8 x; u8 y; } bytes;
        u16 packed;
    } tile;
    u8 room;
    u8 pad_27[0x5];
    void * animationTable;
} ActorSpriteView;

void func_8016B728(void *controller, void *context, void *sprite, EntityRec *creature)
{
    u8 *anim_table;
    s32 direction_flags;
    s8 room_id;
    u16 action_flags;
    u32 initial_flags = dungeonStatus.flags;

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = 0xE;
        func_8016BCD4(controller, context, sprite, creature);
        return;
    }

    if (creature->tileY == 0) {
        func_800AA79C(controller, context, sprite, creature);
        if (((ActorSpriteView *)sprite)->animationTable == D_8016EE4C) {
            return;
        }
        ((ActorSpriteView *)sprite)->animationTable = D_8016EE44;
        func_80047784(sprite,
            D_8016EE44[((gameWork.view.viewAngle + creature->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)creature->flags1C) & 0x200) {
        if (((ActorSpriteView *)sprite)->animationTable == D_8016EE4C) {
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)controller)->unk_8C = 0;
            creature->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (func_800AA924(controller, context, sprite, D_8016EE44) != 0) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((u32)creature->flags1C) & 0x100) {
            func_800AA258(controller, context, sprite, creature);
            return;
        }

        {
            u32 current_state = ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8;
            u32 next_state;

            next_state = 0xE;
            if (current_state != next_state) {
                anim_table = D_8016EDEC;
                if (((ActorSpriteView *)sprite)->animationTable != anim_table) {
                    ((ActorSpriteView *)sprite)->animationTable = anim_table;
                    func_80047784(sprite,
                        anim_table[((gameWork.view.viewAngle + creature->facing + 0x100) >> 9) & 7],
                        0);
                }
                ((Rec_func_800A9E70_arg0 *)controller)->unk_9E.as_s16 = 0;
                ((Rec_func_800A9E70_arg0 *)controller)->unk_A0.at00_s16.v = 0x14;
                ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = next_state;
            }
        }

        ((Rec_func_800A9E70_arg0 *)controller)->unk_98 &= 0xFFF3;
        if (creature->unk_64 != 0) {
            if (func_800AA6B4(controller, context, sprite, D_8016EDFC) != 0) {
                return;
            }
        }

        if (((u32)creature->flags1C) & 0x80000) {
            func_800AA888(controller, context, sprite, creature);
            func_8016E3E8(controller, context, sprite, creature);
            ((ActorSpriteView *)sprite)->animationTable = D_8016EDEC;
            func_80047784(sprite,
                D_8016EDEC[((gameWork.view.viewAngle + creature->facing + 0x100) >> 9) & 7],
                0);
            ((Rec_func_800A9E70_arg0 *)controller)->unk_90.at00_s32.v = 0;
            return;
        }

        if ((func_800A1C58(creature) << 16) != 0) {
            func_800AAB10(controller, context, sprite, creature);
        }
    }

    room_id = func_8009FB34(((ActorSpriteView *)sprite)->tile.bytes.x, ((ActorSpriteView *)sprite)->tile.bytes.y);
    ((ActorSpriteView *)sprite)->room = room_id;

    if (creature->unk_6D > 0) {
        if (((u32)creature->flags1C) & 0x20) {
            func_800A9A0C(creature);
            return;
        }
        if (((ActorSpriteView *)sprite)->tile.packed == *(u16 *)(&D_80082E80.tileX)) {
            func_8016BF40(controller, context, sprite, creature);
            return;
        }
        if (!(creature->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((func_8009A180(creature,
                    (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_8016C9EC(controller, context, sprite, 0) << 16) == 0) {
                return;
            }
            action_flags = creature->unk_46 | 0x4000;
            creature->unk_46 = action_flags;
            if (!(action_flags & 0x8000)) {
                func_8016BF40(controller, context, sprite, creature);
                return;
            }
        }

        action_flags = creature->unk_46 & 0x3FFF;
        switch (action_flags) {
        case 8:
            if ((func_8016C710(controller, context, sprite, creature) << 16) != 0) {
                return;
            }
            func_8016C8D4(controller, context, sprite, creature);
            return;

        case 9:
            func_8016E928(controller, context, sprite, creature);
            return;

        case 5:
        case 6:
        case 7:
            {
                EntityRec *player;
                s16 heading;

                heading = func_800A0818(
                    ((ActorSpriteView *)sprite)->tile.bytes.x, ((ActorSpriteView *)sprite)->tile.bytes.y,
                    D_80082E80.tileX, D_80082E80.tileY,
                    &direction_flags);
                player = D_800814A8;
                creature->facing = heading;
                if (player->unk_9A == 0x11) {
                    func_800AAF00(controller, context, sprite, D_8016EE2C, &D_8016B728);
                    return;
                }
            }

        case 12:
            func_800A9A0C(creature);
            return;

        case 1:
        case 2:
        case 3:
            func_800AAF00(controller, context, sprite, D_8016EE2C, &D_8016B728);
            return;

        case 10:
        default:
            func_8016BF40(controller, context, sprite, creature);
            return;
        }
    }

    if (!(((u32)creature->flags1C) & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)creature->flags1C) & 0x430)) {

                if ((func_8009FD7C(
                    ((ActorSpriteView *)sprite)->tile.bytes.x, ((ActorSpriteView *)sprite)->tile.bytes.y,
                    D_80082E80.tileX, D_80082E80.tileY) << 16) != 0) {
                    creature->facing = func_800A0818(
                        ((ActorSpriteView *)sprite)->tile.bytes.x, ((ActorSpriteView *)sprite)->tile.bytes.y,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &direction_flags);
                }
            }
        }
    }

    if (dungeonStatus.flags & 0x2000) {
        return;
    }
    if (((ActorSpriteView *)sprite)->flags & 0x40) {
        return;
    }
    anim_table = D_8016EDEC;
    if (((ActorSpriteView *)sprite)->animationTable == anim_table) {
        return;
    }
    ((ActorSpriteView *)sprite)->animationTable = anim_table;
    func_80047784(sprite,
        anim_table[((gameWork.view.viewAngle + creature->facing + 0x100) >> 9) & 7],
        0);
}
