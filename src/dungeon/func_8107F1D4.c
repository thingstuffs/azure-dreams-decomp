#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
extern int abs(int);

extern s32 D_8014CF68;
extern u8 D_8014FFB8[8];

s32 get_cd_command_queue_depth(void);
#include "engine/graphics/select_sprite_entry_api.h"
extern void *scan_monster_along_heading();
#include "dungeon/player/object/set_record_integer_tile_center_api.h"
#include "dungeon/actor/state/advance_status_timers_api.h"
extern void play_sound_if_enabled();
extern s32 create_actor_spell_effect();
void create_two_row_object_group(void *, s16);

typedef struct AnimationActionWork {
    u8 pad_00[0x8C];
    void * handler;
    u8 pad_90[0x6];
    u16 phaseTicks;
    u16 actionFlags;
    u8 pad_9A[0x1];
    u8 phase;
} AnimationActionWork;

/* Three adjacent action records are selected by action kind. */
typedef struct ActorActionSlots {
    u8 pad_00[8];
    u8 first[3];
    u8 second[3];
    u8 third[3];
} ActorActionSlots;

typedef struct ActorCounterView {
    u8 pad_00[0xA6];
    u16 pendingCount;
} ActorCounterView;

typedef struct TargetLinkHeader {
    void * positionRecord;
    u8 pad_04[0x10];
} TargetLinkHeader;   /* The position-record link is 0x14 bytes before the actor. */

typedef struct TargetPositionView {
    u8 pad_00[0x24];
    u8 tileX;
    u8 tileY;
} TargetPositionView;

typedef struct ActorSpriteView {
    u8 pad_00[4];
    s8 animationKind;
    u8 animationEnabled;
    u8 pad_06[0xE];
    u16 animationFlags;
    u8 pad_16[0xE];
    union {
        struct { u8 x, y; } tile;
        u16 packed;
    } position;
    union { s8 signedValue; u8 value; } roomId;
    u8 pad_27[5];
    u8 *directionFrames;
} ActorSpriteView;

/* Advance the actor animation state and reset movement when it finishes. */
void advance_actor_animation_and_reset_movement(AnimationActionWork *action, EntityRec *motion, ActorSpriteView *sprite, EntityRec *actor)
{
    u16 position[3];
    u8 *animation;
    s16 reuse_target;
    s32 reuse_test;
    s32 state;
    s32 anim_kind;
    void *target_root;
    void *target_source;
    void *new_target;
    s32 abs_x;
    s32 abs_y;

    state = action->phase;
    reuse_target = 0;
    switch (state) {
    case 0:
        if (actor->flags1C & 0x2000) {
            anim_kind = (actor->unk_46 & 0x3FFF) - 1;
            switch (anim_kind) {
            case 6:
                reuse_target = 1;
                /* fall through */
            case 2:
                animation = ((ActorActionSlots *)actor)->third;
                break;
            case 5:
                reuse_target = 1;
                /* fall through */
            case 1:
                animation = ((ActorActionSlots *)actor)->second;
                break;
            case 4:
                reuse_target = 1;
                /* fall through */
            case 0:
                animation = ((ActorActionSlots *)actor)->first;
                break;
            case 3:
            default:
                animation = 0;
                break;
            }
        } else {
            anim_kind = actor->unk_46 & 0x3FFF;
            switch (anim_kind) {
            case 3:
                animation = ((ActorActionSlots *)actor)->third;
                break;
            case 2:
                animation = ((ActorActionSlots *)actor)->second;
                break;
            case 1:
                animation = ((ActorActionSlots *)actor)->first;
                break;
            default:
                animation = 0;
                break;
            }
        }

        if (*animation != 0) {
            action->actionFlags &= 0xFF7F;
            reuse_test = reuse_target;
            if (reuse_test != 0) {
                target_root = D_800814A8;
                actor->target = target_root;
                target_source = ((TargetLinkHeader *)target_root)[-1].positionRecord;
                actor->unk_72 = ((TargetPositionView *)target_source)->tileX;
                actor->unk_73 = ((TargetPositionView *)target_source)->tileY;
            } else {
                new_target = scan_monster_along_heading(
                    actor, sprite->position.tile.x, sprite->position.tile.y,
                    actor->facing, 0x10);
                actor->target = new_target;
                abs_x = abs(actor->unk_72);
                abs_y = abs(actor->unk_73);
                actor->unk_72 = abs_x;
                actor->unk_73 = abs_y;
            }
            position[0] = ((u16)motion->x.w.i);
            position[1] = ((u16)motion->y.w.i);
            position[2] = ((u16)motion->z.w.i);
            if (create_actor_spell_effect(actor, animation, reuse_target, &action->actionFlags) != 0) {
                sprite->animationFlags &= 0xF7FF;
                play_sound_if_enabled(0x703);
                create_two_row_object_group(position, (s16)((*animation - 1) % 3));
                action->phase++;
                return;
            }
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, sprite->position.tile.x, sprite->position.tile.y);
        g_dungeon_status.unk_0C = 0;
        ((ActorCounterView *)D_800814A8)->pendingCount--;
        advance_status_timers(actor);
        actor->unk_6D--;
        action->handler = &D_8014CF68;
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            sprite->animationFlags |= 0x800;
            return;
        }
        sprite->animationFlags &= 0xF7FF;
        action->phase++;

        /* fall through */
    case 2:
        if ((sprite->animationKind == 8 &&
             (sprite->animationFlags & 0x1000)) ||
            (sprite->animationFlags & 0xE000)) {
            sprite->animationFlags |= 0x800;
            action->phaseTicks = 3;
            action->actionFlags |= 0x80;
        }
        action->phaseTicks--;
        if ((s16)action->phaseTicks <= 0) {
            action->phaseTicks = 0;
            sprite->animationFlags &= 0xF7FF;
        }
        if (sprite->animationFlags & 0xE000) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            set_record_integer_tile_center(motion, sprite->position.tile.x, sprite->position.tile.y);
            if (sprite->directionFrames != D_8014FFB8) {
                sprite->directionFrames = D_8014FFB8;
                select_sprite_entry(
                    (struct S_80047784 *)(sprite),
                    D_8014FFB8[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
            if (((s32)g_dungeon_status.unk_0C) == 0) {
                g_dungeon_status.unk_0A--;
                sprite->animationFlags &= 0xF7FF;
                action->handler = &D_8014CF68;
                advance_status_timers(actor);
                if (actor->unk_6D > 0) {
                    actor->unk_6D--;
                }
                actor->unk_73 = 0;
                actor->unk_72 = 0;
                actor->unk_46 &= 0x7FFF;
                play_sound_if_enabled(0xB4);
            }
        }

        return;
    }
}
