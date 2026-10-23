#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef s32 (*ActorCallback)(void *, void *, void *, void *);
extern void select_indirect_table_entry(void *, s32, s32);
extern void advance_sprite_animation_and_textures(void *);
extern s32 rsin(s32);
extern void apply_monster_koyaw_data(s32, void *);
extern s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);
extern s32 sample_terrain_surface_height(s32, s32, s16);
extern u8 D_801710EC[12];
extern u8 D_80175E40[12];
extern ActorCallback kewne_callbacks[16];
/* Update actor callbacks, movement, facing, animation, and ground height. */
void update_actor_callbacks_and_ground(void *actor, void *motion, SpriteFrameState *sprite)
{
    void *entry_actor = actor;
    s16 direction_index;
    s32 view_direction;
    s16 old_state;
    s16 height_offset;
    s32 ground_height;
    u16 sprite_flags;
    u16 anim_flags;
    u32 clear_mask;
    s32 actor_flags;
    s32 bob_step;
    s32 ground_offset;
    s32 bob_offset;
    s32 height_adjust;
    s32 physics_flags;
    void *actor_base = actor;
    ActorCallback callback;
    u32 initial_flags = g_dungeon_status.flags;
    if (initial_flags & 0x2000) {
        callback = *((ActorCallback *) (((u8 *) actor) + 0x8C));
        if (callback == ((ActorCallback) D_801710EC)) {
            callback(entry_actor, motion, sprite, entry_actor);
            return;
        }
        else {
            *((u8 *) (((u8 *) actor) + 0x71)) &= 0x7F;
            return;
        }
    }
    old_state = (s8) (*((u8 *) (((u8 *) actor) + 0x6D)));
    if (refresh_actor_facing_and_lifecycle(actor, motion, sprite, actor) != 0) {
        return;
    }
    if ((*((ActorCallback *) (((u8 *) actor) + 0x8C))) != 0) {
        (*((ActorCallback *) (((u8 *) actor) + 0x8C)))(actor, motion, sprite, actor);
    }
    kewne_callbacks[*((u8 *) (((u8 *) actor) + 0x9A))](actor, motion, sprite, actor);
    if (((s16) old_state) != (*((s8 *) (((u8 *) actor) + 0x6D)))) {
        try_move_actor_to_valid_position(actor, motion, sprite, actor);
    }
    *((s32 *) (((u8 *) motion) + 0)) += *((s32 *) (((u8 *) motion) + 0xC));
    *((s32 *) (((u8 *) motion) + 4)) += *((s32 *) (((u8 *) motion) + 0x10));
    if ((!((*((u32 *) (((u8 *) actor) + 0x1C))) & 0x40000)) && (!((*((u16 *) (((u8 *) actor) + 0x98))) & 8))) {
        *((s32 *) (((u8 *) motion) + 0x14)) += (*((s8 *) (((u8 *) actor) + 0x9D))) * 0x14000;
        (*((u8 *) (((u8 *) actor) + 0x9D)))++;
    }
    else {
        *((u8 *) (((u8 *) actor) + 0x9D)) = 0;
    }
    *((s32 *) (((u8 *) actor) + 0x90)) += *((s32 *) (((u8 *) motion) + 0x14));
    view_direction = ((g_game_work.view.camera_rotation.parts.viewAngle + (*((s16 *) (((u8 *) actor_base) + 0x2A)))) + 0x100) >> 9;
    bob_step = view_direction & 7;
    direction_index = bob_step;
    if ((*((s16 *) (((u8 *) actor) + 0x94))) != direction_index) {
        select_indirect_table_entry(sprite, *((u8 *) ((sprite->frameTable) + direction_index)),
            sprite->unk_04);
        *((s16 *) (((u8 *) actor) + 0x94)) = bob_step;
    }
    if (dir_sprite_flag[direction_index] != 0) {
        sprite_flags = (sprite->flags) | 1;
        sprite->flags = sprite_flags;
    }
    else {
        sprite_flags = (sprite->flags) & 0xFFFE;
        sprite->flags = sprite_flags;
    }
    anim_flags = sprite->flags;
    /* Select the animation path; afterwards physics_flags carries the flight bit. */
    physics_flags = anim_flags & 0x8000;
    switch (physics_flags) {
    case 0:
        apply_monster_koyaw_data(*((s32 *) (((u8 *) actor_base) + 0x1C)), ((u8 *) sprite) + 0xC);
        if (!((*((u32 *) (((u8 *) actor_base) + 0x1C))) & 0x20)) {
            if (!((sprite->flags) & 0x40)) {
                advance_sprite_animation_and_textures(sprite);
            }
        }
        else {
            sprite->flags |= 0x7000;
            *((u32 *) (((u8 *) actor_base) + 0x1C)) &= 0xFFFBFFFF;
        }
        *((u32 *) (((u8 *) actor_base) + 0x1C)) &= 0xF7FFFFFF;
        physics_flags = (*((u32 *) (((u8 *) actor_base) + 0x1C))) & 0x40000;
        if (physics_flags) {
            if ((!((sprite->flags) & 0x40))
                && ((sprite->frameTable) == D_80175E40)) {
                if ((*(u16 *)&sprite->unk_04) == 0x100) {
                    *((u16 *) (((u8 *) actor) + 0x9E)) = 0;
                    *((s32 *) (((u8 *) actor) + 0xA0)) = 0;
                }
                if (((u32) ((*(u8 *)&sprite->unk_04) - 1)) < 4) {
                    s16 bob_tick = *((u16 *) (((u8 *) actor) + 0x9E));
                    (*((u16 *) (((u8 *) actor) + 0x9E)))++;
                    *((s32 *) (((u8 *) actor) + 0xA0)) += rsin(bob_tick * 0xAA) << 5;
                }
                else {
                    s16 bob_tick = *((u16 *) (((u8 *) actor) + 0x9E));
                    (*((u16 *) (((u8 *) actor) + 0x9E)))++;
                    *((s32 *) (((u8 *) actor) + 0xA0)) += rsin(bob_tick * 0xAA) << 6;
                }
            }
            if (!((*((u16 *) (((u8 *) actor) + 0x98))) & 8)) {
                height_offset = *((s16 *) (((u8 *) actor) + 0x92));
                if (height_offset >= (-0x1F)) {
                    *((u16 *) (((u8 *) actor) + 0x92)) = ((u16) height_offset) - 8;
                }
                else if (height_offset < (-0x28)) {
                    *((u16 *) (((u8 *) actor) + 0x92)) = ((u16) height_offset) + 8;
                }
            }
            break;
        }
        /* Fall through with zero flags to share the ground-physics path. */
    default:
        if (physics_flags) {
            sprite->flags = (anim_flags & 0x800) ? (anim_flags & 0x8FFF) : (anim_flags | 0x7000);
            clear_mask = 0xF7FFFFFF;
            actor_flags = (*((u32 *) (((u8 *) actor_base) + 0x1C)));
            actor_flags &= clear_mask;
            *((u32 *) (((u8 *) actor_base) + 0x1C)) = actor_flags;
            actor_flags &= 0x40000;
            physics_flags = actor_flags;
        }
        if (!physics_flags) {
            bob_offset = *((s32 *) (((u8 *) actor) + 0xA0));

            *((u16 *) (((u8 *) actor) + 0x9E)) = 0;
            *((s32 *) (((u8 *) actor) + 0xA0)) = 0;
            *((s32 *) (((u8 *) actor) + 0x90)) -= bob_offset;
            if (!((*((u16 *) (((u8 *) actor) + 0x98))) & 8)) {
                ground_height = sample_terrain_surface_height(*((u16 *) (((u8 *) motion) + 2)), *((u16 *) (((u8 *) motion) + 6)),
                    (s16) ((*((u16 *) (((u8 *) actor_base) + 0x88))) - 0x20));
                ground_offset = ground_height - (*((u16 *) (((u8 *) actor_base) + 0x88)));
                if (((s16) ground_offset) < (*((s16 *) (((u8 *) actor) + 0x92)))) {
                    *((s16 *) (((u8 *) actor) + 0x92)) = ground_offset;
                    *((u8 *) (((u8 *) actor) + 0x9D)) = 0;
                    *((s32 *) (((u8 *) motion) + 0x14)) = 0;
                    *((u32 *) (((u8 *) actor_base) + 0x1C)) |= 0x08000000;
                }
            }
        }
        else {
            if ((!((sprite->flags) & 0x40)) && ((sprite->frameTable) == D_80175E40)) {
                if ((*(u16 *)&sprite->unk_04) == 0x100) {
                    *((u16 *) (((u8 *) actor) + 0x9E)) = 0;
                    *((s32 *) (((u8 *) actor) + 0xA0)) = 0;
                }
                if (((u32) ((*(u8 *)&sprite->unk_04) - 1)) < 4) {
                    s16 bob_tick = *((u16 *) (((u8 *) actor) + 0x9E));
                    (*((u16 *) (((u8 *) actor) + 0x9E)))++;
                    *((s32 *) (((u8 *) actor) + 0xA0)) += rsin(bob_tick * 0xAA) << 5;
                }
                else {
                    s16 bob_tick = *((u16 *) (((u8 *) actor) + 0x9E));
                    (*((u16 *) (((u8 *) actor) + 0x9E)))++;
                    *((s32 *) (((u8 *) actor) + 0xA0)) += rsin(bob_tick * 0xAA) << 6;
                }
            }
            if (!((*((u16 *) (((u8 *) actor) + 0x98))) & 8)) {
                height_offset = *((s16 *) (((u8 *) actor) + 0x92));
                if (height_offset >= (-0x1F)) {
                    *((u16 *) (((u8 *) actor) + 0x92)) = ((u16) height_offset) - 8;
                }
                else if (height_offset < (-0x28)) {
                    *((u16 *) (((u8 *) actor) + 0x92)) = ((u16) height_offset) + 8;
                }
            }
        }
    }
    actor_flags = *((u32 *) (((u8 *) actor_base) + 0x1C));

    if (actor_flags & 0x40000000) {
        *((u32 *) (((u8 *) actor_base) + 0x1C)) = actor_flags & 0xBFFFFFFF;
        ground_height = sample_terrain_surface_height(((sprite->unk_24) << 6) | 0x20, ((sprite->unk_25) << 6) | 0x20, (s16) ((*((u16 *) (((u8 *) actor_base) + 0x88))) - 0x20));
        if (((s16) ground_height) < 0x200) {
            height_adjust = (*((u16 *) (((u8 *) actor_base) + 0x88))) - ground_height;
            *((u16 *) (((u8 *) actor) + 0x92)) += height_adjust;
            *((u16 *) (((u8 *) actor_base) + 0x88)) = ground_height;
        }
    }
    *((s16 *) (((u8 *) motion) + 0xA)) = ((*((u16 *) (((u8 *) actor_base) + 0x88))) + (*((u16 *) (((u8 *) actor)
        + 0x92)))) - (*((u16 *) (((u8 *) actor) + 0xA2)));
    sprite->flags |= 0x40;
}
