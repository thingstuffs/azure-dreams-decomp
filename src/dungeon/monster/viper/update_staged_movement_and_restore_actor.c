#include "dungeon/actor.h"
#include "engine/graphics.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "sdk/libgpu.h"
#include "dungeon/player/object.h"
#include "dungeon/system.h"
#include "engine/scene.h"
#include "dungeon/actor/status.h"
#include "engine/node/allocation.h"
#include "dungeon/effect/screen.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;
typedef struct {
    Vec3s item[3];
} Vec3sTable;

extern Vec3sTable D_80170838;
extern Vec3sTable D_8017084C;
extern u8 viper_frame_set_4[];
extern u8 viper_frame_set_3[];
extern u8 viper_action_continuation_address[];
extern void *actor_update_node_cursor[];
s32 register_node(ObjectNodeHeader *entry, void *registration_id);
extern void D_800DB618();
extern s32 D_800DB660();
extern u8 D_80174A8C;
extern u8 D_80174A94;

typedef struct S_801727B4_4 {
    u8 pad_00[0x4];
    s32 unk_04;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u8 pad_0E[0x2];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x2];
    s32 unk_18;
    s32 unk_1C;
    u8 pad_20[0xC];
    u16 unk_2C;
    s16 unk_2E;
    s16 unk_30;
    s16 unk_32;
    s16 unk_34;
    s16 unk_36;
} S_801727B4_4;

/* Updates a staged movement animation, emits effects, and restores the actor at its starting position. */
/* Animates Viper's backward leap and forward strike, draws its attack trail, then returns, spends MP, and
 * rolls a split. */
void update_staged_movement_and_restore_actor(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    Vec3sTable effect_vectors_a;
    Vec3sTable effect_vectors_b;
    s32 reverse_facing;
    u8 * actor_handle;
    s32 facing;
    void *has_offset;
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
    S_801727B4_4 *effect_data;
    void *effect;

    effect_vectors_a = D_80170838;
    effect_vectors_b = D_8017084C;
    state = body->action_phase.u;
    switch (state) {
    default:
        return;
    case 0:
        body->unk_A8.u = (u16) ((u16)motion->x.w.i);
        body->unk_AA = (u16) ((u16)motion->y.w.i);
        if (sprite->flags & 0x8000) {
            body->action_phase.u = 5U;
            sprite->flags = (u16) (sprite->flags | 0x6000);
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }
        facing = ((u16) actor->facing >> 9) & 7;
        reverse_facing = facing + 4;
        wrapped_facing = reverse_facing;
        if (reverse_facing < 0) {
            wrapped_facing = facing + 0xB;
        }
        direction_index = reverse_facing - (wrapped_facing & 0x18);
        motion->velocity_x = (s32) ((s16) dir_step_x[direction_index] * 0x30000);
        motion->velocity_y = (s32) ((s16) dir_step_y[direction_index] * 0x30000);
        sprite->frameTable = &D_80174A8C;
        select_sprite_entry(sprite, (&D_80174A8C)[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        previous_state = body->action_phase.u;
        body->action_phase.u = (u8) (previous_state + 1);
        return;
    case 1:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        sprite->frameTable = &D_80174A94;
        select_sprite_entry(sprite, (&D_80174A94)[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        body->unk_90.value = 0;
        body->action_state_flags = (u16) (body->action_state_flags | 8);
        motion->velocity_z = 0xFFF40000;
        previous_state = body->action_phase.u;
        body->action_phase.u = (u8) (previous_state + 1);
        return;
    case 2:
        vertical_speed = motion->velocity_z + 0x20000;
        motion->velocity_z = vertical_speed;
        body->unk_90.value = (s32) (body->unk_90.value + vertical_speed);
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        motion->velocity_x = (s32) ((s32) (0 - motion->velocity_x) >> 1);
        motion->velocity_y = (s32) ((s32) (0 - motion->velocity_y) >> 1);
        sprite->frameTable = viper_frame_set_4;
        select_sprite_entry(sprite, viper_frame_set_4[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        body->action_timer.u = 7;
        body->action_phase.u = (u8) (body->action_phase.u + 1);
        return;
    case 3:
        if (sprite->unk_04 < 3) {
            if (resolve_record_orientation_or_fallback(sprite->source, sprite, ((void *)body) + 0xAC, 0) == 0) {
                body->unk_B0.halves.low.u = 0U;
                body->unk_AC.halves.high.u = 0U;
                body->unk_AC.halves.low.u = 0U;
            }
            body->unk_AC.halves.low.u = (u16) (body->unk_AC.halves.low.u + ((u16)motion->x.w.i));
            body->unk_AC.halves.high.u = (u16) (body->unk_AC.halves.high.u + ((u16)motion->y.w.i));
            body->unk_B0.halves.low.u = (u16) (body->unk_B0.halves.low.u + ((u16)motion->z.w.i));
        } else {
            effect = allocate_list_node(1, &scene_object_list_anchor.next);
            if (effect != NULL) {
                (((ObjectNodeHeader *)effect)->update_callback) = &D_800DB618;
                register_node(effect, &D_800DB660);
                effect_data = effect + 0x20;
                effect_data->unk_10 = (u16) body->unk_AC.halves.low.u;
                effect_data->unk_12 = (u16) body->unk_AC.halves.high.u;
                effect_data->unk_14 = (u16) body->unk_B0.halves.low.u;
                has_offset = resolve_record_orientation_or_fallback(sprite->source, sprite, ((void *)body) + 0xAC, 0);
                if (has_offset == 0) {
                    body->unk_B0.halves.low.u = 0U;
                    body->unk_AC.halves.high.u = 0U;
                    body->unk_AC.halves.low.u = 0U;
                }
                {
                    s32 purple;
                    s32 light_gray;
                    s32 base_gray;

                    purple = 0x200020;
                    light_gray = 0xC0C0C0;
                    effect_coord = body->unk_AC.halves.low.u + ((u16)motion->x.w.i);
                    body->unk_AC.halves.low.u = effect_coord;
                    effect_data->unk_08 = effect_coord;
                    effect_coord = body->unk_AC.halves.high.u + ((u16)motion->y.w.i);
                    body->unk_AC.halves.high.u = effect_coord;
                    effect_data->unk_0A = effect_coord;
                    effect_coord = body->unk_B0.halves.low.u + ((u16)motion->z.w.i);
                    body->unk_B0.halves.low.u = effect_coord;
                    effect_data->unk_0C = effect_coord;
                    effect_data->unk_2C = (u16) actor->facing;
                    effect_data->unk_2E = 0x10;
                    effect_data->unk_30 = 0x10;
                    effect_data->unk_36 = 0x10;
                    effect_data->unk_04 = purple;
                    effect_data->unk_18 = light_gray;
                    fade_steps = 6 - sprite->unk_04;
                    base_gray = 0x141414;
                    effect_data->unk_1C = (s32) ((fade_steps * 0x30303) + base_gray);
                    (*(Vec3s *)((u8 *)effect + 0x40)) = effect_vectors_a.item[sprite->unk_04 - 3];
                    (*(Vec3s *)((u8 *)effect + 0x46)) = effect_vectors_b.item[sprite->unk_04 - 3];
                    effect_data->unk_32 = GetTPage(0, 1, 0x2C0, 0x100);
                    effect_data->unk_34 = GetClut(0, 0x1F8);
                }
            }
        }
        ticks_left = body->action_timer.u - 1;
        body->action_timer.u = ticks_left;
        if ((ticks_left << 0x10) == 0 || (sprite->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            play_sound_if_enabled(0x808);
        }
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        sprite->frameTable = viper_frame_set_3;
        select_sprite_entry(sprite, viper_frame_set_3[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        body->action_state_flags = (u16) (body->action_state_flags & 0xFFF7);
        body->action_phase.u = (u8) (body->action_phase.u + 1);
        return;
    case 4:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        sprite->frameTable = viper_frame_set_3;
        select_sprite_entry(sprite, viper_frame_set_3[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        if (sprite->flags & 0x8000) {
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        }
        previous_state = body->action_phase.u;
        body->action_phase.u = (u8) (previous_state + 1);
        return;
    case 5:
        axis_distance = (s16) ((u16)motion->x.w.i);
        start_coord = (s16) body->unk_A8.u;
        axis_distance = axis_distance - start_coord;
        if (axis_distance < 0) {
            axis_distance = 0 - axis_distance;
        }
        if (axis_distance < 0x41) {
            axis_distance = (s16) ((u16)motion->y.w.i);
            start_coord = (s16) body->unk_AA;
            axis_distance = axis_distance - start_coord;
            if (axis_distance < 0) {
                axis_distance = 0 - axis_distance;
            }
            if (axis_distance >= 0x41) {
                set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            }
        } else {
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        }
        if ((s16) ((u16)motion->x.w.i) != (s16) body->unk_A8.u) {
            return;
        }
        if ((s16) ((u16)motion->y.w.i) != (s16) body->unk_AA) {
            return;
        }
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        spend_actor_mp(actor, 0x100);
        body->unk_8C.byte_ptr = viper_action_continuation_address;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        if (actor->pending_turn_updates == 0) {
            actor->action_flags = (u16) (actor->action_flags & ACTOR_ACTION_CLEAR_PENDING_MASK);
        } else {
            *actor_update_node_cursor = (u8 *)actor - 0x20;
        }
        actor_handle = actor->target;
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
