#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct ActionState {
    u8 pad_00[0x8C];
    s32 handler;
    u8 pad_90[2];
    union { s16 signedValue; u16 unsignedValue; } heightOffset;
    u8 pad_94[4];
    u16 flags;
    u8 action;
    u8 phase;
    u8 pad_9C[0xA];
    union { s16 signedValue; u16 unsignedValue; } motionOffset;
    void *target;
    u8 pad_AC[6];
    s16 motionTicks;
} ActionState;

typedef struct ActorSprite {
    u8 pad_00[5];
    u8 frameTick;
    u8 pad_06[0xE];
    u16 flags;
    u8 pad_16[0xE];
    union {
        struct { u8 x, y; } tile;
        u16 packed;
    } position;
    u8 room;
    u8 pad_27[5];
    void *directionFrames;
} ActorSprite;

typedef struct CreatureState {
    u8 pad_00[0x1C];
    u32 flags;
    u8 pad_20[5];
    u8 tileY;
    u8 pad_26[4];
    s16 facing;
    u8 pad_2C[0x1A];
    u16 action;
    u8 pad_48[0x1C];
    s16 reaction;
    u8 pad_66[7];
    s8 actionsLeft;
} CreatureState;

typedef struct TargetKind {
    u8 pad_00[0x13];
    u8 kind;
} TargetKind;

extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s16 func_800A0818(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 func_800A1C58(void *);
extern void *func_800A04F0(void *, s32, s32, s32);
extern s32 func_800C7F68(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void func_8014D5F0(void *, void *, void *, void *);
extern void func_8014D848(void *, void *, void *, void *);
extern s32 func_8014DFF4(void *, void *, void *, void *);
extern void func_8014E1B8(void *, void *, void *, void *);
extern void func_8014E2E0(void *, void *, void *, void *);
extern s32 func_8014E414(void *, void *, void *, s32);
extern void func_8014F834(void *, void *, void *, void *);
extern u8 D_80150880[];
extern u8 D_80150890[];
extern u8 D_801508C8;
extern u8 D_801508D8[];
extern u8 D_801508E0[];
void func_8014D058(ActionState *, void *, ActorSprite *, CreatureState *);
/* Update creature animation and dispatch its dungeon action. */
void func_8014D058(ActionState *actor, void *context, ActorSprite *sprite_arg, CreatureState *creature)
{
    s32 direction_aux;
    s8 room_id;
    u16 action;
    ActorSprite *sprite;
    u32 dungeon_flags = dungeonStatus.flags;
    if (dungeon_flags & 0x1000) {
        actor->action = 0xE;
        func_8014D5F0(actor, context, sprite_arg, creature);
        return;
    }
    if ((creature->tileY) == 0) {
        void *anim_table;
        func_800AA79C(actor, context, sprite_arg, creature);
        if ((sprite_arg->directionFrames) == D_801508E0) {
            return;
        }
        anim_table = D_801508D8;
        sprite_arg->directionFrames = anim_table;
        func_80047784(sprite_arg, ((u8 *) anim_table)[(((gameWork.view.viewAngle + (creature->facing)) + 0x100) >> 9) & 7], 0);
        return;
    }
    sprite = sprite_arg;
    if ((creature->flags) & 0x200) {
        if ((sprite->directionFrames) == D_801508E0) {
            actor->action = 0xD;
            actor->phase = 1;
            actor->handler = 0;
            creature->flags &= 0xFFFBFFFF;
            return;
        }
        if (func_800AA924(actor, context, sprite, D_801508D8) != 0) {
            return;
        }
    }
    if (!(dungeonStatus.flags & 0x2000)) {
        if ((creature->flags) & 0x100) {
            func_800AA258(actor, context, sprite, creature);
            return;
        }
        {
            void *current_anim;
            void *anim_table;
            if (actor->action != 0xE) {
                actor->action = 0xE;
            }

            current_anim = sprite->directionFrames;
            anim_table = D_80150880;
            if (current_anim != anim_table) {
                sprite->directionFrames = anim_table;
                func_80047784(sprite, ((u8 *) anim_table)[(((gameWork.view.viewAngle + (creature->facing)) + 0x100) >> 9) & 7], 0);
                sprite->frameTick = 1;
                actor->motionOffset.signedValue = 0;
                actor->motionTicks = 0;
            }
        }
        creature->flags |= 0x40000;
        actor->flags &= 0xFFF7;
        if ((creature->reaction) != 0) {
            if (func_800AA6B4(actor, context, sprite, D_80150890) != 0) {
                return;
            }
        }
        if ((creature->flags) & 0x80000) {
            s16 adjusted_offset;
            func_800AA888(actor, context, sprite, creature);
            adjusted_offset = (actor->heightOffset.unsignedValue) - (actor->motionOffset.unsignedValue);
            actor->motionOffset.signedValue = 0;
            actor->motionTicks = 0;
            actor->heightOffset.signedValue = adjusted_offset;
            func_8014F834(actor, context, sprite, creature);
            return;
        }
        if ((func_800A1C58(creature) << 16) != 0) {
            func_800AAB10(actor, context, sprite, creature);
        }
    }
    room_id = func_8009FB34(sprite->position.tile.x, sprite->position.tile.y);
    sprite->room = room_id;
    if ((creature->actionsLeft) > 0) {
        if ((creature->flags) & 0x20) {
            func_800A9A0C(creature);
            return;
        }
        if ((sprite->position.packed) == *(u16 *)&D_80082E80.tileX) {
            func_8014D848(actor, context, sprite, creature);
            return;
        }
        if (!((creature->action) & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((func_8009A180(creature, ((u8 *) D_800814A8->unk_58) + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_8014E414(actor, context, sprite, 0) << 16) == 0) {
                return;
            }
            action = (creature->action) | 0x4000;
            creature->action = action;
            if (!(action & 0x8000)) {
                func_8014D848(actor, context, sprite, creature);
                return;
            }
        }
        action = (creature->action) & 0x3FFF;
        if (((u32) (action - 1)) >= 12) {
            func_8014D848(actor, context, sprite, creature);
            return;
        }
        switch (action - 1) {
        case 8:
        {
            void *target = func_800A04F0(creature, sprite->position.tile.x, sprite->position.tile.y, creature->facing);
            actor->target = target;
            if (target == 0) {
                func_8014D848(actor, context, sprite, creature);
                return;
            }
            if (func_800C7F68(target) != 0) {
                func_8014D848(actor, context, sprite, creature);
                return;
            }
            if (((TargetKind *)actor->target)->kind < 0x33) {
                func_8014E2E0(actor, context, sprite, creature);
                return;
            }
            func_8014D848(actor, context, sprite, creature);
            return;
        }
        case 7:
            if ((func_8014DFF4(actor, context, sprite, creature) << 16) != 0) {
                return;
            }
            func_8014E1B8(actor, context, sprite, creature);
            return;
        case 4:
        case 5:
        case 6:
        {
            TileObject *player_pos = &D_80082E80;
            void *player;
            s16 facing_angle;
            facing_angle = func_800A0818(sprite->position.tile.x, sprite->position.tile.y,
                player_pos->tileX, player_pos->tileY, &direction_aux);
            player = D_800814A8;
            creature->facing = facing_angle;
            if ((((EntityRec *)player)->unk_9A) == 0x11) {
                func_800AAF00(actor, context, sprite, &D_801508C8, func_8014D058);
                return;
            }
        }
        case 11:
            func_800A9A0C(creature);
            return;
        case 0:
        case 1:
        case 2:
            func_800AAF00(actor, context, sprite, &D_801508C8, func_8014D058);
            return;
        case 3:
        case 9:
        case 10:
        default:
            func_8014D848(actor, context, sprite, creature);
            return;
        }
    }
    if (!((creature->flags) & 0x2000)) {
        s32 room_index = room_id;
        if ((room_index < 0) || (!(D_800E2970[room_index].flags & 2))) {
            if (!((creature->flags) & 0x430)) {
                TileObject *player_pos = &D_80082E80;
                if ((func_8009FD7C(sprite->position.tile.x, sprite->position.tile.y,
                    player_pos->tileX, player_pos->tileY) << 16) != 0) {
                    creature->facing = func_800A0818(sprite->position.tile.x,
                        sprite->position.tile.y, player_pos->tileX,
                        player_pos->tileY, &direction_aux);
                }
            }
        }
    }
    return;

}
