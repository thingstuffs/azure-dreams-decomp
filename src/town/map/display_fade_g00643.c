/* Display fade (G00643). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800BEA7C, PD:town/engine:80111FB0. */
#include "shared/object_node.h"
#include "town/map/display_fade_g00643.h"
#include "shared/object_flags.h"

/* Advances a timed color fade and sets completion flags when it finishes. */
void advance_color_fade_and_set_completion(void *fade_state, s32 unused, void *visual)
{
    s32 ticks_left;

    ticks_left = ((S_800BC290_0 *)fade_state)->unk_02.u - 1;
    ((S_800BC290_0 *)fade_state)->unk_02.u = ticks_left;

    switch (((S_800BC290_0 *)fade_state)->unk_00.s) {
    case 0:
        if ((ticks_left << 16) <= 0) {
            ((S_800BC290_1 *)visual)->unk_14 = 12;
            ((S_800BC290_1 *)visual)->unk_0C.s32 = 0xC0C0C0;
            ((S_800BC290_0 *)fade_state)->unk_02.u = 12;
            ((S_800BC290_0 *)fade_state)->unk_00.u++;
        }
        break;

    case 1:
    {
        s32 color;
        s32 color_step;

        if (((S_800BC290_1 *)visual)->unk_0C.u8 >= 0x10U) {
            color = ((S_800BC290_1 *)visual)->unk_0C.s32;
            color_step = 0xFFEFEFF0;
            color = color + color_step;
            ((S_800BC290_1 *)visual)->unk_0C.s32 = color;
        }
        if (((S_800BC290_0 *)fade_state)->unk_02.s <= 0) {
            noop_release_notification(D_80111FB0);
            ((S_800BC290_0 *)fade_state)->unk_00.u++;
        }
        break;
    }

    case 2:
        (*(u16 *)((u8 *)fade_state + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        break;
    }
}

/* Advance a timed state sequence, decrease its value, and set completion flags. */
void advance_timed_state_and_set_completion(void *object)
{
    s32 state;
    s32 timer;
    s32 decay_value;
    u16 prior_state;

    state = S16_AT(object, 0);
    timer = U16_AT(object, 2) - 1;
    U16_AT(object, 2) = timer;
    switch (state) {
    case 0:
        if ((timer << 16) > 0) {
            return;
        }
        U16_AT(object, 2) = 12;
        S16_AT(object, 0x14) = 3;
        U16_AT(object, 0)++;
        return;

    case 1:
        decay_value = S32_AT(object, 8);
        if (decay_value > 0) {
            S32_AT(object, 8) = decay_value + (s32)0xFFF7FBFC;
        }
        if (S16_AT(object, 2) > 0) {
            return;
        }
        prior_state = U16_AT(object, 0);
        U16_AT(object, 0) = prior_state + 1;
        return;

    case 2:
        U16_AT(object, -2) = U16_AT(object, -2) | NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
}

/* Builds two display entries and initializes a display object. */
void build_two_display_entries(s32 data_id, s32 position_offset)
{
    Copy8 layout;
    ObjectNodeHeader *display_obj;
    u8 *display_data;

    layout = D_8008961C;
    noop_display_setup_hook();
    *(u16 *)&layout.word0 += (s32)(position_offset << 16) >> 14;
    create_positioned_callback_object(&layout, D_800BC290,
                  decode_fullwidth_text(D_80111FB0, (void *)data_id, 0));
    create_positioned_callback_object((u8 *)&layout + 4, D_800BC290, D_800782EC);

    display_obj = allocate_flagged_object_node(1);
    if (display_obj != 0) {
        display_obj->update_callback = D_800BC390;
        display_data = (u8 *)display_obj + 0x20;
        register_node(display_obj, &display_registration_tag);
        *(s16 *)(display_data + 0xC) = 0x64;
        *(s16 *)(display_data + 0xE) = 0x34;
        *(s16 *)(display_data + 0x10) = 0x7C;
        *(s16 *)(display_data + 0x12) = 0x18;
        *(s16 *)(display_data + 0x16) = 1;
        *(s32 *)(display_data + 8) = 0x402020;
        *(s16 *)(display_data + 2) = 0x1E;
    }
}
