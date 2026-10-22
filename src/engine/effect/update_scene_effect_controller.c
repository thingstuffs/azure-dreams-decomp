#include "slus/jtbl_80052144.h"

#include "common.h"

/* Rodata owner: the row's switch emits its jump table(s) into this object's .rodata,
 * placed at the retail address by config/slus_modules.json (assets/800.bin carve). */

#include "slus/jtbl_80052144.h"

/* Times child effects, cancels them on a skip flag, and requests the next scene after all children finish. */
void update_scene_effect_controller(Controller *controller)
{
    s32 notify_id;
    s32 zero;
    s32 third_zero;
    Shared83160 *events = &D_80083160;
    s32 state;

    controller->timer++;

    if (controller->state < 4 && (events->flags10 & 0x40)) {
        if (controller->child0 != 0) {
            controller->child0->flags |= 0x8000;
            controller->child0 = 0;
            D_800814A0 |= 0x8000;
            controller->finished++;
        }
        if (controller->child1 != 0) {
            controller->child1->flags |= 0x8000;
            controller->child1 = 0;
            D_800814A0 |= 0x8000;
            controller->finished++;
        }
        if (controller->child2 != 0) {
            controller->child2->flags |= 0x8000;
            controller->child2 = 0;
            D_800814A0 |= 0x8000;
            controller->finished++;
        }
        if (controller->child3 != 0) {
            controller->child3->flags |= 0x8000;
            controller->child3 = 0;
            D_800814A0 |= 0x8000;
            controller->finished++;
        }
        if (controller->group != 0) {
            reset_group_and_flag_children(controller->group);
        }
        SD_Call(0xB4);
        controller->timer = 0;
        controller->state = 4;
    }

    state = controller->state;
    switch (state) {
    case 0:
        if (read_sound_mode_blocking_status(4) != 1) {
            return;
        }
        mark_staged_motion_effect_complete(controller->child0);
        mark_sine_motion_effect_complete(controller->child1);
        mark_timed_animation_sequence_complete(controller->group);
        controller->timer = 0;
        controller->state++;
        return;
    case 1:
        if (controller->child2 != 0) {
            if (controller->script[0] != controller->timer) {
                return;
            }
            mark_fade_in_out_effect_complete(controller->child2);
            controller->script = (s16 *)((u8 *)controller->script + 0x10);
            if (controller->script[0] != 0) {
                return;
            }
            controller->state++;
            return;
        }
        controller->state++;
        return;
    case 2:
        if (controller->timer != 0x1C09) {
            return;
        }
        mark_staged_motion_effect_complete(controller->child0);
        mark_sine_motion_effect_complete(controller->child1);
        controller->state++;
        return;
    case 3:
        if (controller->timer != 0x1CCF) {
            return;
        }
        mark_color_fade_effect_complete(controller->child3);
        controller->timer = 0;
        controller->state++;
        return;
    case 4:
        if (controller->attached != controller->finished) {
            return;
        }
        notify_id = 6;
        zero = 0;
        third_zero = zero;
        runtime_dispatch_state.flags16 |= 0x8000;
        request_scene_state_with_parameters(notify_id, zero, third_zero, zero, runtime_dispatch_state.flags16 ^ 1);
        *((u16 *)controller - 1) |= 0x8000;
        D_800814A0 |= 0x8000;
        return;
    default:
        if (controller->child0 != 0) {
            controller->child0->flags |= 0x8000;
            controller->child0 = 0;
            D_800814A0 |= 0x8000;
            controller->finished++;
        }
        if (controller->child1 != 0) {
            controller->child1->flags |= 0x8000;
            controller->child1 = 0;
            D_800814A0 |= 0x8000;
            controller->finished++;
        }
        if (controller->child2 != 0) {
            controller->child2->flags |= 0x8000;
            controller->child2 = 0;
            D_800814A0 |= 0x8000;
            controller->finished++;
        }
        if (controller->child3 != 0) {
            controller->child3->flags |= 0x8000;
            controller->child3 = 0;
            D_800814A0 |= 0x8000;
            controller->finished++;
        }
        if (controller->group != 0) {
            reset_group_and_flag_children(controller->group);
        }
        if (controller->attached != controller->finished) {
            return;
        }
        SD_Call(0xB4);
        notify_id = 6;
        zero = 0;
        third_zero = zero;
    }
    runtime_dispatch_state.flags16 |= 0x8000;
    request_scene_state_with_parameters(notify_id, zero, third_zero, zero, runtime_dispatch_state.flags16 ^ 1);
    *((u16 *)controller - 1) |= 0x8000;
    D_800814A0 |= 0x8000;
}
