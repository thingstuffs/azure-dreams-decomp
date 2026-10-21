#include "common.h"
#include "shared/game_work.h"

extern s32 D_800A5A98;
extern s16 D_800D01F8[];
extern u8 town_position_reference_state[];

extern void texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags(void *, u8, s8, s32);
extern void step_actor_animation(void *, s32);
extern s16 step_angle_12_toward(s32, s32, s32);
extern s32 view_relative_angle_sector(s16);
extern void clear_motion_along_blocked_directions_update_affected_axes(void *);
extern void copy_entity_record_fields(void *, void *);

/* Turn the entity toward its target angle and update its directional sprite. */
void turn_entity_toward_target(void *entity, void *transform, void *sprite) {
    GameWork *input_state;
    void *transform_arg;
    s32 direction;
    s32 current_angle;
    s32 target_angle;

    transform_arg = transform;
    input_state = &g_game_work;
    clear_motion_along_blocked_directions_update_affected_axes(transform_arg);
    {
        void *entity_type;

        entity_type = *(void **)entity;
        if (entity_type == (u8 *)&D_800A5A98 && (input_state->buttons & 0x2000)) {
            target_angle = *(s16 *)((u8 *)entity + 0x10);
            current_angle = *(s16 *)((u8 *)entity + 0x18);
            target_angle -= 0x200;
            *(s16 *)((u8 *)entity + 0x18) = step_angle_12_toward(current_angle, target_angle, 0x200);
        } else if (entity_type == (u8 *)&D_800A5A98 && (input_state->buttons & 0x8000)) {
            target_angle = *(s16 *)((u8 *)entity + 0x10);
            current_angle = *(s16 *)((u8 *)entity + 0x18);
            target_angle += 0x200;
            *(s16 *)((u8 *)entity + 0x18) = step_angle_12_toward(current_angle, target_angle, 0x200);
        } else {
            current_angle = *(s16 *)((u8 *)entity + 0x18);
            target_angle = *(s16 *)((u8 *)entity + 0x10);
            *(s16 *)((u8 *)entity + 0x18) = step_angle_12_toward(current_angle, target_angle, 0x200);
        }
    }
    direction = view_relative_angle_sector(*(s16 *)((u8 *)entity + 0x18));
    if (*(s16 *)((u8 *)entity + 0x12) != direction) {
        texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags(sprite,
                      *(u8 *)(*(u8 **)((u8 *)entity + 0x1C) + direction),
                      *(s8 *)((u8 *)sprite + 4), 0);
        *(s16 *)((u8 *)entity + 0x12) = direction;
    }
    {
        s16 *flip_table = D_800D01F8;
        u16 sprite_flags;

        if (flip_table[direction] != 0) {
            *(u16 *)((u8 *)sprite + 0x14) |= 1;
        } else {
            *(u16 *)((u8 *)sprite + 0x14) &= 0xFFFE;
        }
    }
    step_actor_animation(sprite, 0);
    {
        u8 *render_state = town_position_reference_state;

        copy_entity_record_fields(render_state, transform);
        *(s32 *)(render_state + 8) = 0;
    }
}
