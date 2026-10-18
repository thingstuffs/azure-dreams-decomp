#include "modules/town_player_init.h"

void process_scene_record_update(void *context, void *input, void *record) {
    GameWork *work = &g_game_work;
    void *callback;
    s32 initial_flags;
    s32 flags;
    s32 movement;
    s32 index;

    clear_motion_along_blocked_directions_update_affected_axes(input);

    if (D_80100DB0[0] == 0) {
        if (((u16)work->view.viewAngle) >= 0x800) {
            work->view.viewAngle |= 0xF000;
        }

        callback = *(void **)context;
                /* garbage-passthru: a1/a2/a3 are caller-saved residue after clear_motion_along_blocked_directions_update_affected_axes. */
        if (callback == (void *)D_80097D2C || callback == (void *)&func_80090A64 ||
            func_800352FC() != 0) {
            if (D_8006ADD4[0] == 12) {
                func_800909A0();
            } else if (*(s16 *)((u8 *)input + 6) < 0x400) {
                clear_record_state_or_update(input);
            }
        } else if (D_8006ADD4[0] == 12) {
            initial_flags = work->buttons;
            if (initial_flags & 8) {
                work->view.viewAngle -= 0x20;
                if (work->view.viewAngle < -0x1E0) {
                    work->view.viewAngle = -0x1E0;
                }
            } else if (initial_flags & 4) {
                work->view.viewAngle += 0x20;
                if (work->view.viewAngle > 0x1E0) {
                    work->view.viewAngle = 0x1E0;
                }
            } else {
                func_800909A0();
            }
        } else if (*(s16 *)((u8 *)input + 6) < 0x400) {
            clear_record_state_or_update(input);
        } else {
            movement = runtime_estimate_vector_length(*(s32 *)((u8 *)input + 0xC),
                                     *(s32 *)((u8 *)input + 0x10));
            if (movement == 0) {
                work->view.viewAngle =
                    (((u16)work->view.viewAngle) + 8) & 0xFFF0;
            }
            movement /= 0x10000;
            flags = work->buttons;
            if (flags & 8) {
                work->view.viewAngle -= 0x10 + movement;
            }
            if (flags & 4) {
                work->view.viewAngle += 0x10 + movement;
            }
        }
    }

    callback = *(void **)context;
    if ((callback == (void *)&D_80091260) ||
        (callback == (void *)&D_80091528)) {
        *(s16 *)((u8 *)context + 0x18) =
            step_angle_12_toward(*(s16 *)((u8 *)context + 0x18),
                          *(s16 *)((u8 *)context + 0x10), 0x200);
    } else {
        *(s16 *)((u8 *)context + 0x18) = *(u16 *)((u8 *)context + 0x10);
    }
    index = view_relative_angle_sector(*(s16 *)((u8 *)context + 0x18));
    if (*(s16 *)((u8 *)context + 0x12) != index) {
        texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags(record,
                      *(u8 *)(*(u8 **)((u8 *)context + 0x1C) + index),
                      *(s8 *)((u8 *)record + 4), 0);
        *(s16 *)((u8 *)context + 0x12) = index;
    }

    {

        if (D_800D01F8[index] != 0) {
            *(u16 *)((u8 *)record + 0x14) |= 1;
        } else {
            *(u16 *)((u8 *)record + 0x14) &= 0xFFFE;
        }
    }
    dispatch_to_matching_fallback_handler_using_sentinel_terminated_key_lists(context, input, record);
    func_80048AC8(record, 0);

    {
        u8 *state = D_80100D98;

        copy_entity_record_fields(state, input);
        if (D_80100E18[0] == 0) {
            *(s32 *)(state + 8) = 0;
            return;
        }
        if (D_80100E18[0] == 2) {
            *(s32 *)(state + 8) /= 2;
        }
    }
}

/* MECHANISM: The three arguments stay in s1/s2/s3 and D_80083160 in s0, yielding the retail 0x28 frame.
   A one-sided schedule barrier preserves both clamp tails; ASM_TAILSLOT_PIN sinks the dead OR into its j slot.
   Memory fences retain the clear/store call sequence and force the post-store signed-halfword reload. */
