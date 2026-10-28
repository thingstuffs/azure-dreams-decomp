#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "engine/node.h"
#include "dungeon/player/object.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(void **)((u8 *)(p) + (o)))

typedef struct {
    u8 bytes[32];
} __attribute__((packed)) Copy32;

extern Copy32 weadog_slot_g_direction_steps;
extern u8 D_80077C50[];
extern u8 weadog_object_callback[];
extern s32 weadog_action_resume_address;
extern u8 weadog_frame_set_3[];
extern u8 D_80174F18[];

extern void select_sprite_entry(void *, s32, s32);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);

/* Spawns a moving actor and advances the action through animation and recovery. */
void spawn_moving_actor(void *action_work, void *position, SpriteFrameState *sprite, void *actor) {
    Copy32 direction_vectors = weadog_slot_g_direction_steps;
    s32 state;
    u16 timer;
    u16 flags;
    u8 *animations;
    s32 direction_index;
    ObjectNodeHeader * spawned_actor;
    SpriteFrameState *spawned_sprite;
    void *spawned_work;
    void *spawned_pos;
    void *direction_ptr;
    s16 direction_y;
    s32 tile_coord;

    state = U8_AT(action_work, 0x9B);
    switch (state) {
    case 0:
        S32_AT(position, 0x14) = 0;
        S32_AT(position, 0x10) = 0;
        S32_AT(position, 0x0C) = 0;
        timer = U16_AT(action_work, 0x96) + 1;
        U16_AT(action_work, 0x96) = timer;
        if (((s16)timer < 0x14) && !(sprite->flags & 0x8000)) {
            return;
        }
        animations = D_80174F18;
        PTR_AT(sprite, 0x2C) = animations;
        select_sprite_entry(sprite,
            animations[((g_game_work.view.camera_rotation.parts.viewAngle + S16_AT(actor, 0x2A) + 0x100) >> 9) & 7], 0);
        U16_AT(action_work, 0x96) = 0x14;
        U8_AT(action_work, 0x9B) = U8_AT(action_work, 0x9B) + 1;
    case 1:
        if ((S16_AT(action_work, 0x96) == 0x13) || (sprite->flags & 0x8000)) {
            if (!(sprite->flags & 0x8000)) {
                play_sound_if_enabled(0x707);
            }
            spawned_actor = allocate_flagged_object_node(0x12);
            if (spawned_actor != 0) {
                spawned_actor->update_callback = weadog_object_callback;
                spawned_work = (u8 *)spawned_actor + 0x20;
                register_node(spawned_actor, project_sprite_chain);
                spawned_sprite = spawned_actor->sprite;
                spawned_sprite->flags &= 0xFFF3;
                PTR_AT(spawned_work, 0x40) = action_work;
                spawned_pos = spawned_actor->position;
                S16_AT(spawned_pos, 2) = U16_AT(position, 2);
                S16_AT(spawned_pos, 6) = U16_AT(position, 6);
                S16_AT(spawned_pos, 0x0A) = U16_AT(position, 0x0A) - 0x20;
                direction_ptr = &direction_vectors;
                direction_index = ((u16)S16_AT(actor, 0x2A) >> 7) & 0x1C;
                S32_AT(spawned_work, 0x6C) = S16_AT(direction_ptr, direction_index) << 0x13;
                direction_index = ((u16)S16_AT(actor, 0x2A) >> 7) & 0x1C;
                S32_AT(spawned_work, 0x70) =
                    (*(u16 *)(direction_index + (u8 *)direction_ptr + 2)) << 0x13;
                S32_AT(spawned_work, 0x74) = 0xFFF20000;
                S32_AT(spawned_work, 0x80) = 0x14900;
                S16_AT(spawned_work, 0x34) = ((u16)S16_AT(actor, 0x2A) >> 9) & 7;
                spawned_sprite = spawned_actor->sprite;
                spawned_sprite->scale_y = 0x1000;
                spawned_sprite->scale_x = 0x1000;
                direction_index = ((u16)S16_AT(actor, 0x2A) >> 7) & 0x1C;
                direction_ptr = direction_index + (u8 *)direction_ptr;
                direction_y = *(volatile u16 *)((u8 *)direction_ptr + 2);
                spawned_sprite->depth_bias = direction_y * 6;
                S16_AT(action_work, 0xA4) = 0x4D;
                tile_coord = S16_AT(position, 2);
                if (tile_coord < 0) {
                    tile_coord += 0x3F;
                }
                S8_AT(spawned_work, 0x5C) = tile_coord >> 6;
                tile_coord = S16_AT(position, 6);
                S8_AT(spawned_work, 0x5D) = (tile_coord / 64);
                spawned_sprite->color.c.b = 0x80;
                spawned_sprite->color.c.g = 0x80;
                spawned_sprite->color.c.r = 0x80;
                spawned_sprite->source = D_80077C50;
            }
        }
        if ((S16_AT(action_work, 0x96) == 0x12) || (sprite->flags & 0x8000)) {
            sprite->flags |= 0x800;
        }
        timer = U16_AT(action_work, 0x96) - 1;
        U16_AT(action_work, 0x96) = timer;
        if (((s32)(timer << 16) <= 0) || (sprite->flags & 0x8000)) {
            U8_AT(action_work, 0x9B) = U8_AT(action_work, 0x9B) + 1;
            sprite->flags &= 0xF7FF;
            return;
        }
        return;
    case 2:
        if (((sprite->unk_04 == state) && (sprite->flags & 0x1000)) ||
            (sprite->flags & 0x8000)) {
            sprite->flags |= 0x800;
            U16_AT(action_work, 0x96) = 0x23;
        }
        timer = U16_AT(action_work, 0x96) - 1;
        U16_AT(action_work, 0x96) = timer;
        if (((s32)(timer << 16) <= 0) || (sprite->flags & 0x8000)) {
            U16_AT(action_work, 0x96) = 0;
            sprite->flags &= 0xF7FF;
        }
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        S32_AT(position, 0x14) = 0;
        S32_AT(position, 0x10) = 0;
        S32_AT(position, 0x0C) = 0;
        set_record_integer_tile_center(position, sprite->tile_x, sprite->tile_y);
        if (PTR_AT(sprite, 0x2C) == weadog_frame_set_3) {
            return;
        }
        PTR_AT(sprite, 0x2C) = weadog_frame_set_3;
        sprite->flags &= 0xF7FF;
        direction_index = ((g_game_work.view.camera_rotation.parts.viewAngle + S16_AT(actor, 0x2A) + 0x100) >> 9) & 7;
        select_sprite_entry(sprite, U8_AT(PTR_AT(sprite, 0x2C), direction_index), 0);
        U8_AT(action_work, 0x9B) = U8_AT(action_work, 0x9B) + 1;
        return;
    case 3:
        if (S16_AT(action_work, 0xA4) != 0x4D) {
            spend_actor_mp(actor, 0x2000);
            PTR_AT(action_work, 0x8C) = &weadog_action_resume_address;
            g_dungeon_status.active_actor = 0;
            U16_AT(actor, 0x46) &= 0x7FFF;
        }
    }
}
