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
extern void func_8016BCD8(void *, void *, void *, void *);
extern void func_8016BF1C(void *, void *, void *, void *);
extern s32 func_8016C6D0(void *, void *, void *, void *);
extern void func_8016C894(void *, void *, void *, void *);
extern s32 func_8016C9AC(void *, void *, void *, s32);
extern void func_8016E598(void *, void *, void *, void *);
extern void func_8016E76C(void *, void *, void *, void *);

extern u8 D_8016B760[];
extern u8 D_8016EE88[];
extern u8 D_8016EE98[];
extern u8 D_8016EEE0[];
extern u8 D_8016EEE8[];
extern u8 D_8016EEF0[];

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

void func_8016B760(void *controller, void *context, void *sprite, EntityRec *actor)
{
    u8 *anim_table;
    s32 room_id;
    s32 direction_flags;
    u32 initial_flags = dungeonStatus.flags;

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = 0xE;
        func_8016BCD8(controller, context, sprite, actor);
        return;
    }

    if (actor->tileY == 0) {
        func_800AA79C(controller, context, sprite, actor);
        if (((ActorSpriteView *)sprite)->animationTable != D_8016EEF0) {
            ((ActorSpriteView *)sprite)->animationTable = D_8016EEE8;
            func_80047784(sprite,
                D_8016EEE8[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            return;
        }
        return;
    }

    if (((u32)actor->flags1C) & 0x200) {
        if (((ActorSpriteView *)sprite)->animationTable == D_8016EEF0) {
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)controller)->unk_8C = 0;
            actor->flags1C &= ~0x40000;
            return;
        }
        if (func_800AA924(controller, context, sprite, D_8016EEE8)) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((u32)actor->flags1C) & 0x100) {
            func_800AA258(controller, context, sprite, actor);
            return;
        }

        {
            u8 current_state;
            u8 idle_state;

            current_state = ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8;
            idle_state = 0xE;
            if (current_state != idle_state) {
                anim_table = D_8016EE88;
                if (((ActorSpriteView *)sprite)->animationTable != anim_table) {
                    ((ActorSpriteView *)sprite)->animationTable = anim_table;
                    func_80047784(sprite,
                        anim_table[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                        0);
                }
                ((Rec_func_800A9E70_arg0 *)controller)->unk_9E.as_s16 = 0;
                ((Rec_func_800A9E70_arg0 *)controller)->unk_A0.at00_s16.v = (rand() & 0x1F) + 0xF;
                ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = idle_state;
            }
        }

        ((Rec_func_800A9E70_arg0 *)controller)->unk_98 &= 0xFFF3;
        if (actor->unk_64 != 0) {
            if (func_800AA6B4(controller, context, sprite, D_8016EE98)) {
                return;
            }
        }

        if (((u32)actor->flags1C) & 0x80000) {
            func_800AA888(controller, context, sprite, actor);
            func_8016E598(controller, context, sprite, actor);
            return;
        }

        if ((func_800A1C58(actor) << 16) != 0) {
            func_800AAB10(controller, context, sprite, actor);
        }
    }

    room_id = func_8009FB34(((ActorSpriteView *)sprite)->tile.bytes.x, ((ActorSpriteView *)sprite)->tile.bytes.y);
    ((ActorSpriteView *)sprite)->room = room_id;

    if (actor->unk_6D > 0) {
        u16 action_state;

        if (((u32)actor->flags1C) & 0x20) {
            func_800A9A0C(actor);
            return;
        }
        if (!(((ActorSpriteView *)sprite)->tile.packed == *(u16 *)(&D_80082E80.tileX))) {
            if (!(actor->unk_46 & 0x8000)) {
                if (dungeonStatus.flags & 0x2000) {
                    if ((func_8009A180(actor,
                            (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                        return;
                    }
                }
                if ((func_8016C9AC(controller, context, sprite, 0) << 16) == 0) {
                    return;
                }
                action_state = actor->unk_46 | 0x4000;
                actor->unk_46 = action_state;
            }

            if (actor->unk_46 & 0x8000) {
                action_state = actor->unk_46 & 0x3FFF;
                switch (action_state) {
                case 8:
                    if ((func_8016C6D0(controller, context, sprite, actor) << 16) != 0) {
                        return;
                    }
                    func_8016C894(controller, context, sprite, actor);
                    return;

                case 9:
                    func_8016E76C(controller, context, sprite, actor);
                    return;

                case 5:
                case 6:
                case 7:
                {
                    EntityRec *player;
                    s16 facing_angle;

                    facing_angle = func_800A0818(
                        ((ActorSpriteView *)sprite)->tile.bytes.x, ((ActorSpriteView *)sprite)->tile.bytes.y,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &direction_flags);
                    player = D_800814A8;
                    actor->facing = facing_angle;
                    if (player->unk_9A == 0x11) {
                        func_800AAF00(controller, context, sprite, D_8016EEE0, D_8016B760);
                        return;
                    }
                }

                case 12:
                    func_800A9A0C(actor);
                    return;

                case 1:
                case 2:
                case 3:
                    func_800AAF00(controller, context, sprite, D_8016EEE0, D_8016B760);
                    return;

                case 11:
                default:
                    break;
                }
            }
        }
        func_8016BF1C(controller, context, sprite, actor);
        return;
    } else if (!(((u32)actor->flags1C) & 0x2000)) {
        s32 room_index = (s8)room_id;

        if ((room_index < 0) ||
            !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)actor->flags1C) & 0x430)) {

                if ((func_8009FD7C(
                        ((ActorSpriteView *)sprite)->tile.bytes.x, ((ActorSpriteView *)sprite)->tile.bytes.y,
                        D_80082E80.tileX, D_80082E80.tileY) << 16) != 0) {
                    actor->facing = func_800A0818(
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
    anim_table = D_8016EE88;
    if (((ActorSpriteView *)sprite)->animationTable == anim_table) {
        return;
    }
    ((ActorSpriteView *)sprite)->animationTable = anim_table;
    func_80047784(sprite,
        anim_table[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
        0);
}
