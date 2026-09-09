#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8002589C();        /* extern */
M2C_UNK func_80026548();                 /* extern */
M2C_UNK func_8002660C();    /* extern */
M2C_UNK func_800266D0();                  /* extern */
s32 func_8003DE58(); /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_8009B4B0();                /* extern */
M2C_UNK func_8009CE1C(); /* extern */
s32 func_800A44E0();              /* extern */
extern u16 D_800281F8;
extern s16 D_8002966C[6];
extern u8 D_8002966E;
extern s32 D_80029670;
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s32 D_800814A0;
extern M2C_UNK D_80082E80;
extern u16 D_80082E94;
extern u16 D_80083780[];
extern M2C_UNK D_800C9034;
extern void *D_800E3D7C;


typedef struct S_80025C80_0_pre {
    u16 unk_00;
} S_80025C80_0_pre;   /* the 0x2 bytes before arg0 in func_80025C80, addressed as arg0[-1] */

typedef struct S_80025C80_0 {
    u8 pad_00[0x20];
    void * unk_20;
    u16 unk_24;
    u16 unk_26;
    u16 unk_28;
    u8 pad_2A[0x2];
    s16 unk_2C;
    s16 unk_2E;
    union { s16 n; volatile u16 v; } unk_30;   /* accessed as both */
    s16 unk_32;
    u8 pad_34[0x2];
    s16 unk_36;
    s16 unk_38;
    u16 unk_3A;
    s16 unk_3C;
    union { s16 n; volatile s16 v; } unk_3E;   /* accessed as both */
    union { u16 u; s16 s; } unk_40;   /* accessed as both */
    u16 unk_42;
} S_80025C80_0;   /* arg0 in func_80025C80 */

typedef struct S_80025C80_1 {
    s32 unk_00;
    u8 unk_04;
    u8 pad_05[0x3];
    s32 unk_08;
    union { struct { u8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_80025C80_1;   /* arg2 in func_80025C80 */

typedef struct S_80025C80_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_0C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_10;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_14;   /* overlapping accesses */
} S_80025C80_2;   /* arg1 in func_80025C80 */

typedef struct S_80025C80_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x1E];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80025C80_3;   /* temp_v1_6 in func_80025C80 */

typedef struct S_80025C80_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80025C80_4;   /* case0_base in func_80025C80 */

typedef struct S_80025C80_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80025C80_5;   /* var_a0 in func_80025C80 */

typedef struct S_80025C80_6 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x12];
    u16 unk_1E;
} S_80025C80_6;   /* temp_a0 in func_80025C80 */

typedef struct S_80025C80_7 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x7];
    s32 unk_0C;
    u8 pad_10[0x6];
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_80025C80_7;   /* temp_s0 in func_80025C80 */

typedef struct S_80025C80_8 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_80025C80_8;   /* ((S_80025C80_0 *)arg0)->unk_20 in func_80025C80 */

/* Updates effect movement and fading, or copies a linked monster's position and appearance. */
void func_80025C80(void *effect_in, void *motion_in, void *sprite_in) {
    void *effect;
    void *motion;
    void *sprite;
    register s32 x_step ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 y_step ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 end_frame ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    void *resident_sprite;
    void *source_data;
    register s16 *update_base ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s16 *update_ptr;
    register s16 *update_y_page ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s16 *update_y_base;
    s16 *update_y_ptr;
    s32 update_y_offset;
    register s32 motion_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 motion_dx ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 motion_y ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 motion_dy;
    register s32 motion_z ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 motion_dz ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 motion_damp_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 motion_damp_y;
    u16 linked_flags;
    s32 *linked_global;
    u8 *resident_page;
    s16 frame_toggle;
    s16 fade_ticks;
    s16 next_z;
    s16 move_ticks;
    s16 phase;
    s16 rise_ticks;
    s16 follow_ticks;
    s32 delta_x;
    s32 delta_y;
    s32 target_x;
    s32 target_y;
    s32 transform_result;
    s32 tile_object;
    u16 steps_left;
    register u16 update_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u16 update_y;
    u8 frame;
    u8 brightness;
    u8 next_brightness;
    u8 start_tile_y;
    S_80025C80_6 *linked_monster;
    S_80025C80_7 *linked_sprite;
    S_80025C80_5 *base_position;

    effect = effect_in;
    motion = motion_in;
    sprite = sprite_in;
    linked_monster = ((S_80025C80_0 *)effect)->unk_20;
    D_800281F8 = D_800281F8 + 1;
    if (linked_monster != NULL) {
        goto copy_linked_monster;
    }
    func_8002660C(sprite, effect + 0x32, ((S_80025C80_0 *)effect)->unk_38, ((S_80025C80_0 *)effect)->unk_36);
    func_80026548(effect, ((S_80025C80_1 *)sprite)->unk_00);
    phase = ((S_80025C80_0 *)effect)->unk_2C;
    if (phase == 1) {
        goto follow;
    }
    if (phase < 2) {
        if (phase == 0) {
            goto rise;
        }
        goto finish_update;
    }
    if (phase == 2) {
        goto advance;
    }
    if (phase == 0x10) {
        goto fade;
    }
    goto finish_update;

rise:
    ((S_80025C80_2 *)motion)->unk_08.at00.v = (s32) (((S_80025C80_2 *)motion)->unk_08.at00.v + 0xFFFF0000);
    brightness = ((S_80025C80_1 *)sprite)->unk_0C.at00.v;
    next_brightness = brightness + ((s32) (0x80 - brightness) / (s16) ((S_80025C80_0 *)effect)->unk_30.n);
    ((S_80025C80_1 *)sprite)->unk_0C.at00.v = next_brightness;
    ((S_80025C80_1 *)sprite)->unk_0C.at02.v = next_brightness;
    ((S_80025C80_1 *)sprite)->unk_0C.at01.v = next_brightness;
    frame_toggle = ((u16) ((S_80025C80_0 *)effect)->unk_30.n ^ 1) & 1;
    rise_ticks = ((S_80025C80_0 *)effect)->unk_30.v - 1;
    ASM_KEEP(frame_toggle);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ((S_80025C80_0 *)effect)->unk_30.n = rise_ticks;
    ((S_80025C80_0 *)effect)->unk_32 = frame_toggle;
    if (((rise_ticks << 0x10) <= 0) && (((S_80025C80_1 *)sprite)->unk_14 & 0x4000)) {
        end_frame = 8;
        ASM_KEEP(end_frame);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        source_data = D_800E3D7C;
        ((S_80025C80_0 *)effect)->unk_38 = end_frame;
        ((S_80025C80_0 *)effect)->unk_36 = 0xF;
        ((S_80025C80_0 *)effect)->unk_32 = 1;
        ((S_80025C80_0 *)effect)->unk_3A = (u16) ((S_80025C80_3 *)source_data)->unk_88;
        ((S_80025C80_0 *)effect)->unk_40.u = (u16) (((u16) ((S_80025C80_3 *)source_data)->unk_2A >> 9) & 7);
        resident_sprite = &D_80082E80;
        ((S_80025C80_0 *)effect)->unk_3C = ((S_80025C80_4 *)resident_sprite)->unk_24;
        start_tile_y = ((S_80025C80_4 *)resident_sprite)->unk_25;
        ((S_80025C80_0 *)effect)->unk_42 = end_frame;
        ((S_80025C80_0 *)effect)->unk_30.n = 3;
        ((S_80025C80_0 *)effect)->unk_2C = (s16) ((u16) ((S_80025C80_0 *)effect)->unk_2C + 1);
        ((S_80025C80_0 *)effect)->unk_3E.n = start_tile_y;
        goto finish_update;
    }
    goto finish_update;

follow:
    resident_page = (u8 *) 0x80080000;
    ASM_KEEP_NV(resident_page);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    sprite = resident_page + 0x2E80;
    transform_result = func_8003DE58(((S_80025C80_1 *)sprite)->unk_08, sprite, effect + 0x24, 0);
    follow_ticks = (u16) ((S_80025C80_0 *)effect)->unk_30.n - 1;
    ((S_80025C80_0 *)effect)->unk_30.n = follow_ticks;
    if ((follow_ticks << 0x10) <= 0) {
        goto finish_follow;
    }
    if (transform_result == 0) {
        goto finish_follow;
    }
    if ((((S_80025C80_1 *)sprite)->unk_14 & 0x8000) == 0) {
        goto apply_base_position;
    }
finish_follow:
    if (D_80082E94 & 0x8000) {
        ((S_80025C80_2 *)motion)->unk_00.at02.v = D_80083780[1];
        ((S_80025C80_2 *)motion)->unk_04.at02.v = D_80083780[3];
        ((S_80025C80_2 *)motion)->unk_08.at02.v = D_80083780[5] - 0x10;
    }
    ((S_80025C80_0 *)effect)->unk_30.n = 0;
    ((S_80025C80_0 *)effect)->unk_2C = (u16) ((S_80025C80_0 *)effect)->unk_2C + 1;
    goto finish_update;

apply_base_position:
    base_position = &D_80083780;
    ((S_80025C80_2 *)motion)->unk_00.at02.v = (s16) (base_position->unk_02 + ((S_80025C80_0 *)effect)->unk_24);
    ((S_80025C80_2 *)motion)->unk_04.at02.v = (s16) (base_position->unk_06 + ((S_80025C80_0 *)effect)->unk_26);
    ((S_80025C80_2 *)motion)->unk_08.at02.v = (s16) (base_position->unk_0A + ((S_80025C80_0 *)effect)->unk_28);
    goto finish_update;

advance:
    if (((S_80025C80_0 *)effect)->unk_30.n != 0) {
        goto move_to_tile;
    }
    if ((func_800A44E0(((((S_80025C80_0 *)effect)->unk_3C << 6) + 0x20) & 0xFFE0, ((((S_80025C80_0 *)effect)->unk_3E.n << 6) + 0x20) & 0xFFE0, (s16) (((S_80025C80_0 *)effect)->unk_3A - 0x20), (s16) (((S_80025C80_0 *)effect)->unk_40.u << 9)) << 0x10) != 0) {
        goto start_fade;
    }
    steps_left = ((S_80025C80_0 *)effect)->unk_42 - 1;
    ((S_80025C80_0 *)effect)->unk_42 = steps_left;
    if ((steps_left << 0x10) > 0) {
        goto advance_tile;
    }
start_fade:
    ((S_80025C80_0 *)effect)->unk_2C = 0x10;
    ((S_80025C80_2 *)motion)->unk_0C.at02.v = D_8006CCD8[((S_80025C80_0 *)effect)->unk_40.s] * 8;
    ((S_80025C80_2 *)motion)->unk_10.at02.v = D_8006CCE8[((S_80025C80_0 *)effect)->unk_40.s] * 8;
    x_step = 8;
    ((S_80025C80_2 *)motion)->unk_14.at02.v = x_step;
    ((S_80025C80_0 *)effect)->unk_30.n = x_step;
    goto move_to_tile;

advance_tile:
    update_base = D_8006CCD8;
    update_ptr = &update_base[((S_80025C80_0 *)effect)->unk_40.s];
    update_x = (u16) ((S_80025C80_0 *)effect)->unk_3C;
    x_step = (u16) *update_ptr;
    update_x += x_step;
    update_y_page = (s16 *) 0x80070000;
    ASM_KEEP_NV(update_y_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ((S_80025C80_0 *)effect)->unk_3C = update_x;
    update_y_base = (s16 *) ((u8 *) update_y_page - 0x3318);
    update_y_offset = ((S_80025C80_0 *)effect)->unk_40.s << 1;
    update_y_ptr = (s16 *) ((unsigned long) update_y_offset + (unsigned long) update_y_base);
    update_y = (u16) ((S_80025C80_0 *)effect)->unk_3E.v;
    y_step = (u16) *(volatile u16 *) update_y_ptr;
    ((S_80025C80_0 *)effect)->unk_30.n = 3;
    update_y += y_step;
    ((S_80025C80_0 *)effect)->unk_3E.n = update_y;
move_to_tile:
    target_x = ((S_80025C80_0 *)effect)->unk_3C << 6;
    delta_x = ((S_80025C80_2 *)motion)->unk_00.at02.v - 0x20;
    x_step = (target_x - delta_x) / ((S_80025C80_0 *)effect)->unk_30.n;
    ((S_80025C80_2 *)motion)->unk_00.at02.v = (u16) ((S_80025C80_2 *)motion)->unk_00.at02.v + x_step;
    target_y = ((S_80025C80_0 *)effect)->unk_3E.n << 6;
    delta_y = ((S_80025C80_2 *)motion)->unk_04.at02.v - 0x20;
    y_step = (target_y - delta_y) / ((S_80025C80_0 *)effect)->unk_30.n;
    next_z = (u16) ((S_80025C80_2 *)motion)->unk_08.at02.v + 5;
    ((S_80025C80_2 *)motion)->unk_08.at02.v = next_z;
    ((S_80025C80_2 *)motion)->unk_04.at02.v = (u16) ((S_80025C80_2 *)motion)->unk_04.at02.v + y_step;
    if (((s16) ((S_80025C80_0 *)effect)->unk_3A - 0x10) < next_z) {
        ((S_80025C80_2 *)motion)->unk_08.at02.v = (s16) (((S_80025C80_0 *)effect)->unk_3A - 0x10);
    }
    move_ticks = (u16) ((S_80025C80_0 *)effect)->unk_30.n - 1;
    ((S_80025C80_0 *)effect)->unk_30.n = move_ticks;
    if (move_ticks == 2) {
        tile_object = func_8009B4B0(D_800E3D7C, (u16) ((S_80025C80_0 *)effect)->unk_3C, (u16) ((S_80025C80_0 *)effect)->unk_3E.n);
        if (tile_object != 0) {
            func_8009CE1C(tile_object, 0xC, D_8002966E, 9, (s32) (s16) (((S_80025C80_0 *)effect)->unk_40.u << 9), D_80029670, 5);
        }
        goto update_direction;
    }
    goto update_direction;

fade:
    motion_x = ((S_80025C80_2 *)motion)->unk_00.at00.v;
    motion_dx = ((S_80025C80_2 *)motion)->unk_0C.at00.v;
    motion_y = ((S_80025C80_2 *)motion)->unk_04.at00.v;
    motion_dy = ((S_80025C80_2 *)motion)->unk_10.at00.v;
    motion_x += motion_dx;
    motion_y += motion_dy;
    ((S_80025C80_2 *)motion)->unk_04.at00.v = motion_y;
    motion_z = ((S_80025C80_2 *)motion)->unk_08.at00.v;
    motion_dz = ((S_80025C80_2 *)motion)->unk_14.at00.v;
    ((S_80025C80_2 *)motion)->unk_00.at00.v = motion_x;
    motion_damp_x = ((S_80025C80_2 *)motion)->unk_0C.at00.v;
    motion_z += motion_dz;
    ((S_80025C80_2 *)motion)->unk_08.at00.v = motion_z;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    motion_damp_x -= motion_damp_x >> 2;
    motion_damp_y = motion_dy;
    ((S_80025C80_2 *)motion)->unk_0C.at00.v = motion_damp_x;
    ASM_KEEP(motion_damp_y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    motion_damp_y -= motion_damp_x >> 2;
    ((S_80025C80_2 *)motion)->unk_10.at00.v = motion_damp_y;
    if (((s16) ((S_80025C80_0 *)effect)->unk_3A - 0x10) < ((S_80025C80_2 *)motion)->unk_08.at02.v) {
        ((S_80025C80_2 *)motion)->unk_08.at02.v = (s16) (((S_80025C80_0 *)effect)->unk_3A - 0x10);
    }
    ((S_80025C80_1 *)sprite)->unk_0C.at00.v = ((S_80025C80_1 *)sprite)->unk_0C.at00.v - ((s32) ((S_80025C80_1 *)sprite)->unk_0C.at00.v / ((S_80025C80_0 *)effect)->unk_30.n);
    ((S_80025C80_1 *)sprite)->unk_0C.at01.v = ((S_80025C80_1 *)sprite)->unk_0C.at01.v - ((s32) ((S_80025C80_1 *)sprite)->unk_0C.at01.v / ((S_80025C80_0 *)effect)->unk_30.n);
    ((S_80025C80_1 *)sprite)->unk_0C.at02.v = ((S_80025C80_1 *)sprite)->unk_0C.at02.v - ((s32) ((S_80025C80_1 *)sprite)->unk_0C.at02.v / ((S_80025C80_0 *)effect)->unk_30.n);
    fade_ticks = (u16) ((S_80025C80_0 *)effect)->unk_30.n - 1;
    ((S_80025C80_0 *)effect)->unk_30.n = fade_ticks;
    if ((fade_ticks << 0x10) <= 0) {
        D_8002966C[0] = 0;
        goto linked_flag_update;
    }
    frame = ((S_80025C80_1 *)sprite)->unk_04;
    if ((s8) frame == ((S_80025C80_0 *)effect)->unk_36) {
        ((S_80025C80_0 *)effect)->unk_32 = -1;
        goto update_direction;
        return;
    }
    if ((s8) frame == ((S_80025C80_0 *)effect)->unk_38) {
        ((S_80025C80_0 *)effect)->unk_32 = 1;
        goto update_direction;
    }
update_direction:
    func_8002589C(effect - 0x20, (s16) ((S_80025C80_0 *)effect)->unk_40.u, 0xF0);
    goto finish_update;

copy_linked_monster:
    ASM_KEEP(effect);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(motion);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(sprite);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    if (linked_monster->unk_1E & 0x8000) {
linked_flag_update:
        linked_flags = ((S_80025C80_0_pre *)effect)[-1].unk_00;
        linked_global = &D_800814A0;
        linked_flags |= 0x8000;
        ((S_80025C80_0_pre *)effect)[-1].unk_00 = linked_flags;
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        *linked_global |= 0x8000;
        return;
    }
    source_data = linked_monster->unk_08;
    ((S_80025C80_2 *)motion)->unk_00.at02.v = (s16) ((S_80025C80_3 *)source_data)->unk_02;
    ((S_80025C80_2 *)motion)->unk_04.at02.v = (s16) ((S_80025C80_3 *)source_data)->unk_06;
    ((S_80025C80_2 *)motion)->unk_08.at02.v = (s16) ((S_80025C80_3 *)source_data)->unk_0A;
    linked_sprite = ((S_80025C80_8 *)(((S_80025C80_0 *)effect)->unk_20))->unk_0C;
    func_800266D0(sprite, linked_sprite->unk_04);
    func_80026548(effect, ((S_80025C80_1 *)sprite)->unk_00);
    ((S_80025C80_1 *)sprite)->unk_1C = (u16) linked_sprite->unk_1C;
    ((S_80025C80_1 *)sprite)->unk_1E = (u16) linked_sprite->unk_1E;
    ((S_80025C80_1 *)sprite)->unk_20 = (u16) linked_sprite->unk_20;
    ((S_80025C80_1 *)sprite)->unk_0C.at00u.v = linked_sprite->unk_0C;
    ((S_80025C80_1 *)sprite)->unk_16 = (u16) linked_sprite->unk_16;
    ((S_80025C80_1 *)sprite)->unk_18 = (u16) linked_sprite->unk_18;
    ((S_80025C80_1 *)sprite)->unk_1A = (u16) linked_sprite->unk_1A;
finish_update:
    if (((S_80025C80_0 *)effect)->unk_2E == 0) {
        func_8004491C(effect - 0x20, &D_800C9034);
        ((S_80025C80_0 *)effect)->unk_2E = (s16) ((u16) ((S_80025C80_0 *)effect)->unk_2E + 1);
    }
}
