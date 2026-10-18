#include "common.h"
#include "shared/object_node.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef union TilePairView {
    struct { u8 x; u8 y; } tile;
    u16 packed;
} TilePairView;

typedef struct ActorSpriteView {
    u8 pad_00[4];
    s8 frame;
    u8 pad_05[3];
    s32 animationKey;
    u8 pad_0C[8];
    u16 flags;
    u8 pad_16[0xE];
    TilePairView position;
    union { s8 signedIndex; u8 unsignedIndex; } tileIndex;
    u8 pad_27[5];
    u8 *directionFrames;
} ActorSpriteView;

/* Partial action view: timer loads keep their observed signedness. */
typedef struct ActorActionView {
    u8 pad_00[0x8C];
    union { s32 code; void *record; u8 *frames; s32 *word; } nextAction;
    Fixed1616 motionOffset;
    u8 pad_94[2];
    union { u16 unsignedTicks; s16 signedTicks; } timer;
    u16 flags;
    u8 behavior;
    u8 phase;
    u8 pad_9C[4];
    s16 frameParameter;
    u8 pad_A2[4];
    u16 effectTicks;
    union { s16 signedPhase; u16 phase; u16 startX; } effectState;
    union { u16 facing; u16 startY; } saved;
    u16 effectX;
    u16 effectY;
    u16 effectZ;
} ActorActionView;

typedef struct JumpEffectView {
    u8 pad_00[0x4];
    s32 baseColor;
    u16 endX;
    u16 endY;
    u16 endZ;
    u8 pad_0E[0x2];
    u16 startX;
    u16 startY;
    u16 startZ;
    u8 pad_16[0x2];
    s32 lightColor;
    s32 fadeColor;
    u8 pad_20[0xC];
    u16 facing;
    s16 scaleX;
    s16 scaleY;
    s16 angleX;
    s16 angleY;
    s16 scaleZ;
} JumpEffectView;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

typedef struct JumpEffectObjectView {
    ObjectNodeHeader header;
    JumpEffectView payload;
} JumpEffectObjectView;

/* The vector copies in retail use the two-byte aligned Vec3s view. */
typedef struct JumpEffectVectorsView {
    u8 pad_00[0x40];
    Vec3s first;
    Vec3s second;
} JumpEffectVectorsView;

typedef struct {
    Vec3s item[3];
} Vec3sTable;

extern Vec3sTable D_8015E838;
extern Vec3sTable D_8015E84C;
extern u8 D_80162AA4[];
extern u8 D_80162AAC[];
extern u8 D_8015EE94[];
extern void *D_800E3DE8[];
s32 resolve_record_orientation_or_fallback();
void *func_8003FD64(s32, void *);
s32 func_8004491C();
s16 func_80066460();
s16 func_8006649C();
void *resolve_attack_damage_and_effects();
void set_record_integer_tile_center();
s32 advance_status_timers();
s32 play_sound_if_enabled();
extern s32 D_800DB618;
extern s32 D_800DB660;
extern u8 D_80162A8C;
extern u8 D_80162A94;

void update_actor_behavior_variant(ActorActionView *action, EntityRec *motion, ActorSpriteView *animation, EntityRec *actor)
{
    Vec3sTable effect_vectors_a;
    Vec3sTable effect_vectors_b;
    s32 reverse_facing;
    s32 actor_handle;
    s32 facing;
    s32 has_offset;
    s32 direction_index;
    s32 vertical_speed;
    u32 fade_steps;
    s32 wrapped_facing;
    s32 axis_distance;
    s32 start_coord;
    u16 effect_coord;
    u16 ticks_left;
    u8 state;
    u8 previous_state;
    JumpEffectView *effect_data;
    void *effect;

    effect_vectors_a = D_8015E838;
    effect_vectors_b = D_8015E84C;
    state = action->phase;
    switch (state) {
    default:
        return;
    case 0:
        action->effectState.startX = (u16) ((u16)motion->x.w.i);
        action->saved.startY = (u16) ((u16)motion->y.w.i);
        if (animation->flags & 0x8000) {
            action->phase = 5U;
            animation->flags = (u16) (animation->flags | 0x6000);
            resolve_attack_damage_and_effects(actor, animation, actor->facing, 1);
            return;
        }
        facing = ((u16) actor->facing >> 9) & 7;
        reverse_facing = facing + 4;
        wrapped_facing = reverse_facing;
        if (reverse_facing < 0) {
            wrapped_facing = facing + 0xB;
        }
        direction_index = reverse_facing - (wrapped_facing & 0x18);
        motion->unk_0C = (s32) ((s16) dir_step_x[direction_index] * 0x30000);
        motion->unk_10 = (s32) ((s16) dir_step_y[direction_index] * 0x30000);
        animation->directionFrames = &D_80162A8C;
        func_80047784(animation, (&D_80162A8C)[((s32) (g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        previous_state = action->phase;
        action->phase = (u8) (previous_state + 1);
        return;
    case 1:
        if (!(animation->flags & 0xE000)) {
            return;
        }
        animation->directionFrames = &D_80162A94;
        func_80047784(animation, (&D_80162A94)[((s32) (g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        action->motionOffset.v = 0;
        action->flags = (u16) (action->flags | 8);
        motion->flags14 = 0xFFF40000;
        previous_state = action->phase;
        action->phase = (u8) (previous_state + 1);
        return;
    case 2:
        vertical_speed = motion->flags14 + 0x20000;
        motion->flags14 = vertical_speed;
        action->motionOffset.v = (s32) (action->motionOffset.v + vertical_speed);
        if (!(animation->flags & 0xE000)) {
            return;
        }
        motion->unk_0C = (s32) ((s32) (0 - motion->unk_0C) >> 1);
        motion->unk_10 = (s32) ((s32) (0 - motion->unk_10) >> 1);
        animation->directionFrames = D_80162AA4;
        func_80047784(animation, D_80162AA4[((s32) (g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        action->timer.unsignedTicks = 7;
        action->phase = (u8) (action->phase + 1);
        return;
    case 3:
        if (animation->frame < 3) {
            if (resolve_record_orientation_or_fallback(animation->animationKey, animation, &action->effectX, 0) == 0) {
                action->effectZ = 0U;
                action->effectY = 0U;
                action->effectX = 0U;
            }
            action->effectX = (u16) (action->effectX + ((u16)motion->x.w.i));
            action->effectY = (u16) (action->effectY + ((u16)motion->y.w.i));
            action->effectZ = (u16) (action->effectZ + ((u16)motion->z.w.i));
        } else {
            effect = func_8003FD64(1, ((u8 *)(&D_80083498)));
            if (effect != NULL) {
                ((ObjectNodeHeader *)effect)->unk_10 = &D_800DB618;
                func_8004491C(effect, &D_800DB660);
                effect_data = &((JumpEffectObjectView *)effect)->payload;
                effect_data->startX = (u16) action->effectX;
                effect_data->startY = (u16) action->effectY;
                effect_data->startZ = (u16) action->effectZ;
                has_offset = resolve_record_orientation_or_fallback(animation->animationKey, animation, &action->effectX, 0);
                if (has_offset == 0) {
                    action->effectZ = 0U;
                    action->effectY = 0U;
                    action->effectX = 0U;
                }
                {
                    s32 purple;
                    s32 light_gray;
                    s32 base_gray;

                    purple = 0x200020;
                    light_gray = 0xC0C0C0;
                    effect_coord = action->effectX + ((u16)motion->x.w.i);
                    action->effectX = effect_coord;
                    effect_data->endX = effect_coord;
                    effect_coord = action->effectY + ((u16)motion->y.w.i);
                    action->effectY = effect_coord;
                    effect_data->endY = effect_coord;
                    effect_coord = action->effectZ + ((u16)motion->z.w.i);
                    action->effectZ = effect_coord;
                    effect_data->endZ = effect_coord;
                    effect_data->facing = (u16) actor->facing;
                    effect_data->scaleX = 0x10;
                    effect_data->scaleY = 0x10;
                    effect_data->scaleZ = 0x10;
                    effect_data->baseColor = purple;
                    effect_data->lightColor = light_gray;
                    fade_steps = 6 - animation->frame;
                    base_gray = 0x141414;
                    effect_data->fadeColor = (s32) ((fade_steps * 0x30303) + base_gray);
                    ((JumpEffectVectorsView *)effect)->first = effect_vectors_a.item[animation->frame - 3];
                    ((JumpEffectVectorsView *)effect)->second = effect_vectors_b.item[animation->frame - 3];
                    effect_data->angleX = func_80066460(0, 1, 0x2C0, 0x100);
                    effect_data->angleY = func_8006649C(0, 0x1F8);
                }
            }
        }
        ticks_left = action->timer.unsignedTicks - 1;
        action->timer.unsignedTicks = ticks_left;
        if ((ticks_left << 16) == 0 || (animation->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, animation, actor->facing, 1);
            play_sound_if_enabled(0x808);
        }
        if (!(animation->flags & 0xE000)) {
            return;
        }
        animation->directionFrames = D_80162AAC;
        func_80047784(animation, D_80162AAC[((s32) (g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        action->flags = (u16) (action->flags & 0xFFF7);
        action->phase = (u8) (action->phase + 1);
        return;
    case 4:
        if (!(animation->flags & 0xE000)) {
            return;
        }
        animation->directionFrames = D_80162AAC;
        func_80047784(animation, D_80162AAC[((s32) (g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        if (animation->flags & 0x8000) {
            set_record_integer_tile_center(motion, animation->position.tile.x, animation->position.tile.y);
        }
        previous_state = action->phase;
        action->phase = (u8) (previous_state + 1);
        return;
    case 5:
        axis_distance = (s16) ((u16)motion->x.w.i);
        start_coord = (s16) action->effectState.startX;
        axis_distance = axis_distance - start_coord;
        if (axis_distance < 0) {
            axis_distance = 0 - axis_distance;
        }
        if (axis_distance < 0x41) {
            axis_distance = (s16) ((u16)motion->y.w.i);
            start_coord = (s16) action->saved.startY;
            axis_distance = axis_distance - start_coord;
            if (axis_distance < 0) {
                axis_distance = 0 - axis_distance;
            }
            if (axis_distance >= 0x41) {
                set_record_integer_tile_center(motion, animation->position.tile.x, animation->position.tile.y);
            }
        } else {
            set_record_integer_tile_center(motion, animation->position.tile.x, animation->position.tile.y);
        }
        if ((s16) ((u16)motion->x.w.i) != (s16) action->effectState.startX) {
            return;
        }
        if ((s16) ((u16)motion->y.w.i) != (s16) action->saved.startY) {
            return;
        }
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, animation->position.tile.x, animation->position.tile.y);
        reduce_actor_food_meter(actor, 0x100);
        action->nextAction.frames = D_8015EE94;
        g_dungeon_status.unk_0C = 0;
        advance_status_timers(actor);
        if (actor->unk_6D == 0) {
            actor->unk_46 = (u16) (actor->unk_46 & 0x7FFF);
        } else {
            *D_800E3DE8 = (u8 *)actor - 0x20;
        }
        actor_handle = ((s32)actor->target);
        if (actor_handle == 0) {
            return;
        }
        if (actor->flags14 & 0x20000) {
            return;
        }
        roll_actor_stack_split(actor_handle, 0x10);
        return;
    }
}
