#include "common.h"
#include "m2c_compat.h"

extern void *D_80088CB8[];
void func_8009DF0C();
s32 func_800A2C34();
M2C_UNK func_800A634C();
M2C_UNK func_800A67F4();
extern s16 D_80013630[4];
extern M2C_UNK D_8001363C;
extern M2C_UNK D_80082E80;
extern M2C_UNK D_80083160;
extern M2C_UNK D_800E296C;
extern void *D_800E3D7C;

typedef struct S_func_8009E038_0 {
    u8 pad_00[4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
    u8 pad_18[2];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    u16 unk_2C;
} S_func_8009E038_0;

typedef struct S_func_8009E038_1 {
    u8 pad_00[2];
    s16 unk_02;
    u8 pad_04[2];
    s16 unk_06;
} S_func_8009E038_1;

typedef struct S_func_8009E038_2 {
    u8 pad_00[0xC];
    union {
        s32 s32;
        struct {
            u8 unk_0C;
            u8 unk_0D;
            u8 unk_0E;
        } bytes;
    } unk_0C;
    u8 pad_10[0xC];
    u16 unk_1C;
    u16 unk_1E;
    union {
        s16 s16;
        u16 u16;
    } unk_20;
    union {
        s16 s16;
        u16 u16;
    } unk_22;
} S_func_8009E038_2;

typedef struct S_func_8009E038_3 {
    s32 unk_00;
} S_func_8009E038_3;

typedef struct S_func_8009E038_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_func_8009E038_4;

typedef struct S_func_8009E038_5 {
    u8 pad_00[8];
    s32 unk_08;
    u8 pad_0C[4];
    s32 unk_10;
} S_func_8009E038_5;

typedef struct S_func_8009E038_6 {
    u8 pad_00[0x296C];
    s32 unk_296C;
} S_func_8009E038_6;

typedef struct S_func_8009E038_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_func_8009E038_7;

typedef struct S_func_8009E038_8 {
    u8 pad_00[0x3630];
    s16 unk_3630;
    s16 unk_3632;
    s16 unk_3634;
    s16 unk_3636;
} S_func_8009E038_8;

/* Update the viewport transition, blending its bounds, center, scale, and brightness. */
void func_8009E038(S_func_8009E038_0 *transition, S_func_8009E038_1 *center, S_func_8009E038_2 *render_params, M2C_UNK *context) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c16, &&jt_c32, &&jt_c48 };
    s32 top_step;
    S_func_8009E038_7 *target_offsets;
    S_func_8009E038_5 *input;
    s16 reset_frames;
    s16 move_frames;
    s16 next_scale;
    s16 reset_remaining;
    s16 hold_remaining;
    s32 state;
    register s16 move_remaining ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 current_scale;
    s32 height_step;
    s32 flags;
    s32 cleared_flags;
    s32 previous_state;
    s32 flags_mask;
    u16 offset_x;
    u16 idle_frames;
    u16 shrink_scale;
    u16 reduced_scale;
    u16 offset_y;
    u16 target_scale;
    u16 target_left;
    u16 target_top;
    u16 target_width;
    u16 target_height;
    u16 reset_scale;
    u16 blended_scale;
    u16 moving_scale;
    u8 brightness;
    u8 next_brightness;
    S_func_8009E038_2 *render;
    S_func_8009E038_8 *viewport_page;
    S_func_8009E038_6 *flags_page;
    S_func_8009E038_7 *idle_offsets;
    s32 left_step;
    register s32 shared_flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 reset_flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

    render = render_params;
    input = (S_func_8009E038_5 *)&D_80083160;
    if (!(((S_func_8009E038_3 *)&D_800E296C)->unk_00 & 0x2000)) {
        goto check_reset;
    }
    if (transition->unk_1A >= 0x20) {
        goto check_reset;
    }
    transition->unk_1A = 0x20;
check_reset:
    flags = ((S_func_8009E038_3 *)&D_800E296C)->unk_00;
    if (!(flags & 0x800000)) {
        goto check_shrink_end;
    }
    previous_state = transition->unk_1A;
    cleared_flags = flags & ~0x2000;
    (*(s32 *)&D_800E296C) = cleared_flags;
    if (previous_state < 2) {
        goto clear_idle;
    }
    transition->unk_1A = 0;
    transition->unk_1C = 8;
clear_idle:
    reset_flags = ((S_func_8009E038_3 *)&D_800E296C)->unk_00;
    transition->unk_2C = 0U;
    (*(s32 *)&D_800E296C) = reset_flags & 0xFEFFFFFF;
    goto check_idle;
check_shrink_end:
    if ((u32) ((u16) transition->unk_1A - 0x20) >= 0x10U) {
        goto check_idle;
    }
    if (((S_func_8009E038_3 *)&D_800E296C)->unk_00 & 0x2000) {
        goto check_idle;
    }
    transition->unk_1A = 0x30;
check_idle:
    if (transition->unk_1A != 0) {
        goto reset_idle;
    }
    if (!(((S_func_8009E038_4 *)D_800E3D7C)->unk_1C & 0x10)) {
        goto dispatch_state;
    }
reset_idle:
    reset_flags = ((S_func_8009E038_3 *)&D_800E296C)->unk_00;
    transition->unk_2C = 0U;
    (*(s32 *)&D_800E296C) = reset_flags & 0xFEFFFFFF;
dispatch_state:
    state = transition->unk_1A;
    if ((u32) state >= 0x31U) {
        goto apply_transition;
    }
    (void)jt_keep; goto *D_80088CB8[(u32)(state)];
jt_c0:
    if ((*(s32 *)((u8 *)&D_800E296C + 0)) & 0x800000) {
        goto blend_reset;
    }
    idle_frames = transition->unk_2C + 1;
    transition->unk_2C = idle_frames;
    if ((s16) idle_frames != 0x1F) {
        goto clamp_idle;
    }
    (*(s32 *)&D_800E296C) = (s32) (((S_func_8009E038_3 *)&D_800E296C)->unk_00 | 0x01000000);
    func_800A634C(0);
    goto blend_reset;
clamp_idle:
    if ((s16) idle_frames < 0x20) {
        goto blend_reset;
    }
    transition->unk_2C = 0x20U;
blend_reset:
    reset_frames = transition->unk_1C;
    if (reset_frames <= 0) {
        goto tick_reset;
    }
    brightness = render->unk_0C.bytes.unk_0E;
    next_brightness = brightness + ((s32) (0x80 - brightness) / reset_frames);
    render->unk_0C.bytes.unk_0E = next_brightness;
    render->unk_0C.bytes.unk_0D = next_brightness;
    render->unk_0C.bytes.unk_0C = next_brightness;
    reset_scale = render->unk_1E;
    offset_x = render->unk_20.u16;
    blended_scale = reset_scale + ((s32) (0x3000 - reset_scale) / (s16) transition->unk_1C);
    render->unk_1E = blended_scale;
    render->unk_1C = blended_scale;
    offset_y = render->unk_22.u16;
    render->unk_20.u16 = (u16) (offset_x + ((s32) (0x20 - offset_x) / (s16) transition->unk_1C));
    render->unk_22.u16 = (u16) (offset_y + ((s32) (0x20 - offset_y) / (s16) transition->unk_1C));
    center->unk_02 = (s16) ((u16) center->unk_02 + ((s32) (0xA0 - center->unk_02) / (s16) transition->unk_1C));
    center->unk_06 = (s16) ((u16) center->unk_06 + ((s32) (0x78 - center->unk_06) / (s16) transition->unk_1C));
    transition->unk_04 = (s16) ((u16) transition->unk_04 + ((s32) (0 - transition->unk_04) / (s16) transition->unk_1C));
    transition->unk_06 = (s16) ((u16) transition->unk_06 + ((s32) (0 - transition->unk_06) / (s16) transition->unk_1C));
    transition->unk_08 = (s16) ((u16) transition->unk_08 + ((s32) (0x140 - transition->unk_08) / (s16) transition->unk_1C));
    transition->unk_0A = (s16) ((u16) transition->unk_0A + ((s32) (0xE0 - transition->unk_0A) / (s16) transition->unk_1C));
tick_reset:
    reset_remaining = (u16) transition->unk_1C - 1;
    transition->unk_1C = reset_remaining;
    if ((reset_remaining << 0x10) > 0) {
        goto apply_transition;
    }
    center->unk_02 = 0xA0;
    center->unk_06 = 0x78;
    render->unk_1E = 0x3000U;
    render->unk_1C = 0x3000U;
    render->unk_20.u16 = 0x20U;
    render->unk_22.u16 = 0x20U;
    render->unk_0C.s32 = 0x808080;
    transition->unk_08 = 0x140;
    transition->unk_0A = 0xE0;
    reset_flags = ((S_func_8009E038_3 *)&D_800E296C)->unk_00;
    transition->unk_04 = 0;
    transition->unk_06 = 0;
    transition->unk_1C = 0;
    if (!(reset_flags & 0x800000)) {
        goto check_move_start;
    }
    transition->unk_1C = 0x1E;
    transition->unk_1A = (s16) ((u16) transition->unk_1A + 1);
    goto apply_transition;
check_move_start:
    if (input->unk_08 & 0x100) {
        goto apply_transition;
    }
    transition->unk_1C = 4;
    transition->unk_1A = 0x10;
    goto apply_transition;
jt_c1:
    hold_remaining = (u16) transition->unk_1C - 1;
    transition->unk_1C = hold_remaining;
    if ((hold_remaining << 0x10) > 0) {
        goto apply_transition;
    }
    flags_mask = 0xFF7FFFFF;
    shared_flags = 8;
    flags_page = (S_func_8009E038_6 *)0x800E0000;
    transition->unk_1C = shared_flags;
    shared_flags = flags_page->unk_296C;
    transition->unk_1A = 0x10;
    goto store_flags;
jt_c16:
    move_frames = transition->unk_1C;
    if (move_frames == 0) {
        goto sync_offsets;
    }
    moving_scale = ((s32) (transition->unk_1E - render->unk_1E) / move_frames) + render->unk_1E;
    render->unk_1E = moving_scale;
    render->unk_1C = moving_scale;
    center->unk_02 = (s16) ((u16) center->unk_02 + ((s32) (transition->unk_14 - center->unk_02) / (s16) transition->unk_1C));
    center->unk_06 = (s16) ((u16) center->unk_06 + ((s32) (transition->unk_16 - center->unk_06) / (s16) transition->unk_1C));
    target_offsets = (S_func_8009E038_7 *)&D_80082E80;
    render->unk_20.u16 = (u16) (((s32) (target_offsets->unk_24 - render->unk_20.u16) / (s16) transition->unk_1C) + render->unk_20.u16);
    render->unk_22.u16 = (u16) (((s32) (target_offsets->unk_25 - render->unk_22.u16) / (s16) transition->unk_1C) + render->unk_22.u16);
    left_step = (s32) (transition->unk_0C - transition->unk_04) / (s16) transition->unk_1C;
    transition->unk_04 = (s16) ((u16) transition->unk_04 + left_step);
    top_step = (s32) (transition->unk_0E - transition->unk_06) / (s16) transition->unk_1C;
    transition->unk_06 = (s16) ((u16) transition->unk_06 + top_step);
    transition->unk_08 = (s16) ((u16) transition->unk_08 + ((s32) (transition->unk_10 - transition->unk_08) / (s16) transition->unk_1C));
    height_step = (s32) (transition->unk_12 - transition->unk_0A) / (s16) transition->unk_1C;
    move_remaining = (u16) transition->unk_1C - 1;
    transition->unk_1C = move_remaining;
    transition->unk_0A = (s16) ((u16) transition->unk_0A + height_step);
    if ((move_remaining << 0x10) > 0) {
        goto check_scale_input;
    }
    center->unk_02 = (s16) (u16) transition->unk_14;
    center->unk_06 = (s16) (u16) transition->unk_16;
    target_scale = (u16) transition->unk_1E;
    render->unk_1E = target_scale;
    render->unk_1C = target_scale;
    render->unk_20.s16 = (s16) ((S_func_8009E038_7 *)&D_80082E80)->unk_24;
    render->unk_22.s16 = (s16) ((S_func_8009E038_7 *)&D_80082E80)->unk_25;
    target_left = (u16) transition->unk_0C;
    viewport_page = (S_func_8009E038_8 *)0x80010000;
    transition->unk_04 = (s16) target_left;
    viewport_page->unk_3630 = target_left;
    target_top = (u16) transition->unk_0E;
    transition->unk_06 = (s16) target_top;
    viewport_page->unk_3632 = target_top;
    target_width = (u16) transition->unk_10;
    transition->unk_08 = (s16) target_width;
    viewport_page->unk_3634 = target_width;
    target_height = (u16) transition->unk_12;
    transition->unk_0A = (s16) target_height;
    viewport_page->unk_3636 = target_height;
    goto check_scale_input;
sync_offsets:
    idle_offsets = (S_func_8009E038_7 *)&D_80082E80;
    render->unk_20.s16 = (s16) idle_offsets->unk_24;
    render->unk_22.s16 = (s16) idle_offsets->unk_25;
check_scale_input:
    if (!(input->unk_08 & 0x10)) {
        goto check_reset_input;
    }
    if (!(input->unk_10 & 8)) {
        goto check_reset_input;
    }
    current_scale = transition->unk_1E;
    if (current_scale >= 0x5000) {
        goto wrap_scale;
    }
    next_scale = (u16) transition->unk_1E + 0x1000;
    transition->unk_1E = next_scale;
    *(s32 *)0x8001363C = (s32) next_scale;
    goto start_scale_blend;
wrap_scale:
    transition->unk_1E = 0;
    *(s32 *)0x8001363C = 0;
start_scale_blend:
    transition->unk_1C = 4;
check_reset_input:
    if (!(input->unk_08 & 0x100)) {
        goto apply_transition;
    }
    if ((func_800A2C34(0) << 0x10) != 0) {
        goto apply_transition;
    }
    func_800A67F4();
    flags_mask = 0xFEFFFFFF;
    do {
        flags_page = (S_func_8009E038_6 *)0x800E0000;
    } while (0);
    shared_flags = flags_page->unk_296C;
    transition->unk_2C = 0U;
    transition->unk_1A = 0;
    transition->unk_1C = 1;
store_flags:
    flags_page->unk_296C = shared_flags & flags_mask;
    goto apply_transition;
jt_c32:
    shrink_scale = render->unk_1E;
    reduced_scale = shrink_scale - (shrink_scale >> 2);
    render->unk_1E = reduced_scale;
    if ((u32) (reduced_scale & 0xFFFF) >= 0x100U) {
        goto apply_transition;
    }
    render->unk_1E = 0U;
    goto apply_transition;
jt_c48:
    transition->unk_1A = 0x10;
    transition->unk_1C = 4;
apply_transition:
    func_8009DF0C(transition);
    return;
}
