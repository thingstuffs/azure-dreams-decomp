#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"

extern void func_80047784(void *, s32, s32);
extern s32 dungeonCheckEntityRelation(void *, void *);
extern s8 func_8009FB34(s32, s32);
extern s32 dungeonCompareMonsterNeighborValues(s32, s32, s32, s32);
extern s16 dungeonGetRoundedFacingAndRoundingFlag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void dungeonBeginPushedActorMove(void *, void *, void *, void *);
extern s32 dungeonBeginReadyActorDirectionalAction(void *, void *, void *, void *);
extern void dungeonAdvanceActorPendingAction(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 dungeonResetActorActionState(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void dungeonProcessSelectedActorRecord(void *, void *, void *, void *);
extern void dungeonBeginActorSpellAction(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void func_8014DCD4(void *, void *, void *, void *);
extern void func_8014DF40(void *, void *, void *, void *);
extern s32 func_8014E710(void *, void *, void *, void *);
extern void func_8014E8D4(void *, void *, void *, void *);
extern s32 func_8014E9EC(void *, void *, void *, s32);
extern void func_801503E8(void *, void *, void *, void *);
extern void func_80150928(void *, void *, void *, void *);

extern s32 D_8014D728;
extern u8 D_80150DEC[];
extern u8 D_80150DFC[];
extern u8 D_80150E2C[];
extern u8 D_80150E44[];
extern u8 D_80150E4C[];

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

void dungeonUpdateCreatureActionBehaviorVariant(void *controller, void *context, void *sprite, EntityRec *creature)
{
    u8 *anim_table;
    s32 direction_flags;
    s8 room_id;
    u16 action_flags;
    u32 initial_flags = dungeonStatus.flags;

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = 0xE;
        func_8014DCD4(controller, context, sprite, creature);
        return;
    }

    if (creature->tileY == 0) {
        dungeonAdvanceActorPendingAction(controller, context, sprite, creature);
        if (((ActorSpriteView *)sprite)->animationTable == D_80150E4C) {
            return;
        }
        ((ActorSpriteView *)sprite)->animationTable = D_80150E44;
        func_80047784(sprite,
            D_80150E44[((gameWork.view.viewAngle + creature->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)creature->flags1C) & 0x200) {
        if (((ActorSpriteView *)sprite)->animationTable == D_80150E4C) {
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)controller)->unk_8C = 0;
            creature->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (dungeonResetActorActionState(controller, context, sprite, D_80150E44) != 0) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((u32)creature->flags1C) & 0x100) {
            dungeonBeginPushedActorMove(controller, context, sprite, creature);
            return;
        }

        {
            u32 current_state = ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8;
            u32 next_state;

            next_state = 0xE;
            if (current_state != next_state) {
                anim_table = D_80150DEC;
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
            if (dungeonBeginReadyActorDirectionalAction(controller, context, sprite, D_80150DFC) != 0) {
                return;
            }
        }

        if (((u32)creature->flags1C) & 0x80000) {
            func_800AA888(controller, context, sprite, creature);
            func_801503E8(controller, context, sprite, creature);
            ((ActorSpriteView *)sprite)->animationTable = D_80150DEC;
            func_80047784(sprite,
                D_80150DEC[((gameWork.view.viewAngle + creature->facing + 0x100) >> 9) & 7],
                0);
            ((Rec_func_800A9E70_arg0 *)controller)->unk_90.at00_s32.v = 0;
            return;
        }

        if ((func_800A1C58(creature) << 16) != 0) {
            dungeonProcessSelectedActorRecord(controller, context, sprite, creature);
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
            func_8014DF40(controller, context, sprite, creature);
            return;
        }
        if (!(creature->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((dungeonCheckEntityRelation(creature,
                    (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_8014E9EC(controller, context, sprite, 0) << 16) == 0) {
                return;
            }
            action_flags = creature->unk_46 | 0x4000;
            creature->unk_46 = action_flags;
            if (!(action_flags & 0x8000)) {
                func_8014DF40(controller, context, sprite, creature);
                return;
            }
        }

        action_flags = creature->unk_46 & 0x3FFF;
        switch (action_flags) {
        case 8:
            if ((func_8014E710(controller, context, sprite, creature) << 16) != 0) {
                return;
            }
            func_8014E8D4(controller, context, sprite, creature);
            return;

        case 9:
            func_80150928(controller, context, sprite, creature);
            return;

        case 5:
        case 6:
        case 7:
            {
                EntityRec *player;
                s16 heading;

                heading = dungeonGetRoundedFacingAndRoundingFlag(
                    ((ActorSpriteView *)sprite)->tile.bytes.x, ((ActorSpriteView *)sprite)->tile.bytes.y,
                    D_80082E80.tileX, D_80082E80.tileY,
                    &direction_flags);
                player = D_800814A8;
                creature->facing = heading;
                if (player->unk_9A == 0x11) {
                    dungeonBeginActorSpellAction(controller, context, sprite, D_80150E2C, &D_8014D728);
                    return;
                }
            }

        case 12:
            func_800A9A0C(creature);
            return;

        case 1:
        case 2:
        case 3:
            dungeonBeginActorSpellAction(controller, context, sprite, D_80150E2C, &D_8014D728);
            return;

        case 10:
        default:
            func_8014DF40(controller, context, sprite, creature);
            return;
        }
    }

    if (!(((u32)creature->flags1C) & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)creature->flags1C) & 0x430)) {

                if ((dungeonCompareMonsterNeighborValues(
                    ((ActorSpriteView *)sprite)->tile.bytes.x, ((ActorSpriteView *)sprite)->tile.bytes.y,
                    D_80082E80.tileX, D_80082E80.tileY) << 16) != 0) {
                    creature->facing = dungeonGetRoundedFacingAndRoundingFlag(
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
    anim_table = D_80150DEC;
    if (((ActorSpriteView *)sprite)->animationTable == anim_table) {
        return;
    }
    ((ActorSpriteView *)sprite)->animationTable = anim_table;
    func_80047784(sprite,
        anim_table[((gameWork.view.viewAngle + creature->facing + 0x100) >> 9) & 7],
        0);
}
