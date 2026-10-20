#include "modules/dungeon_ovl_e0365c.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x2C];
    u8 *field_2C;
} SpriteFieldView_80DE48EC;


s32 check_actor_ahead_height(void *action_state, void *source_pos, void *sprite, void *actor)
{
    void *output;
    s16 next_x;   /* never assigned: read only in the decision-46 dead arm below */
    s16 next_y;
    u16 result = 0;
    u16 flags;
    s32 direction;
    u16 base_x;
    u16 base_y;
    s32 delta_offset;
    s16 x;
    s16 y;
    u16 *y_delta;
    u16 *x_delta;
    u8 *x_steps;
    s16 height;
    s32 step_y;

    ((E_801720EC_S_801720EC_0 *)actor)->unk_71 &= 0x7f;
    flags = g_dungeon_status.flags;
    if (flags & 0x2000) {
        return -1;
    }

    if (!(((E_801720EC_S_801720EC_0 *)actor)->unk_46 & 0x8000)) {
        if (flags & 8) {
            return -1;
        }
    }

    if ((s16)try_claim_dungeon_action_slot(actor) != 0) {
        return -1;
    }

    output = (u8 *)actor - 0x20;
    apply_camera_offset_and_select_target((s32)output, source_pos, 8, 0x300);
    if ((s16)try_claim_dungeon_action_slot(actor) != 0) {
        return -1;
    }

    base_x = ((E_801720EC_S_801720EC_1 *)sprite)->unk_24;
    base_y = ((E_801720EC_S_801720EC_1 *)sprite)->unk_25;
    x = base_x;
    y = base_y;
    direction = (((E_801720EC_S_801720EC_0 *)actor)->unk_2A.s >> 9) & 7;
    if ((s16)check_layer_offset_height(x << 6, y << 6, ((E_801720EC_S_801720EC_0 *)actor)->unk_88.s, direction << 9) != 0) {
return_tail:
        return result;
    }

    x_steps = (u8 *)dir_step_x;
    x_delta = (u16 *)(x_steps + (direction << 1));
    delta_offset = direction << 1;
    y_delta = (u16 *)((u8 *)dir_step_y + delta_offset);
    {
        s32 step_x;
        step_x = *x_delta;
        step_y = *y_delta;
        if (find_eligible_entry_at_coordinates(actor, (base_x + step_x) & 0xffff,
                          (base_y + step_y) & 0xffff) != 0) {
            goto return_tail;
        }
    }

    if ((s16)increment_bounded_event_counter() == 0) {
        return result;
    }

    height = sample_terrain_surface_height((((x + (s16)*x_delta) << 6) + 0x20) & 0xffe0,
                           (((y + (s16)*y_delta) << 6) + 0x20) & 0xffe0,
                           (s16)(((E_801720EC_S_801720EC_0 *)actor)->unk_88.u - 0x20));
    if (height >= 0x201) {
        return result;
    }
    if ((s16)(height - ((E_801720EC_S_801720EC_0 *)actor)->unk_88.u) < -0x3f) {
        return result;
    }
    ((E_801720EC_S_801720EC_2 *)action_state)->unk_9B = 0;
    ((E_801720EC_S_801720EC_2 *)action_state)->unk_8C = 0;
    ((E_801720EC_S_801720EC_2 *)action_state)->unk_9A = 0x17;
    (((SpriteFieldView_80DE48EC *)sprite)->field_2C) = D_80174558;
    select_sprite_entry(sprite,
                  D_80174558[((g_game_work.view.camera_rotation.parts.viewAngle + ((E_801720EC_S_801720EC_0 *)actor)->unk_2A.u + 0x100) >> 9) & 7],
                  0);
    advance_status_timers(actor);
    /* Decision 46 (owner 2026-10-13): post-combine dead arm. result is never reassigned, so combine folds this test
     * only after flow has counted the arm; scheduling, allocation and reload see it (x_delta's second set, the spilled
     * next_x/next_y slots retail's frame reserves) and jump2 deletes it - no code. The arm's BODY is a reconstruction:
     * the bytes fix its shape, not its content. */
    if (result != 0) {
        x_delta += next_x;
        try_claim_dungeon_action_slot(next_y + *x_delta);
    }
    {
        s32 update_flags = 0x300;
        step_y = 8;
        ((E_801720EC_S_801720EC_0 *)actor)->unk_6D--;
        select_nearby_target_and_initialize_slot((s32)output, source_pos, step_y, update_flags);
    }
    return 1;
}
