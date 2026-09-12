#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C2824_0 {
    void * unk_00;
    s16 unk_04;
    s16 unk_06;
} S_800C2824_0;   /* arg0 in func_800C2824 */

typedef struct S_800C2824_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800C2824_1;   /* temp_s0 in func_800C2824 */

typedef struct S_800C2824_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800C2824_2;   /* temp_v1_2 in func_800C2824 */

typedef struct S_800C2824_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_800C2824_3;   /* arg1 in func_800C2824 */

typedef struct S_800C2824_4 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    union { struct { s32 v; } at00; struct { s8 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s8 v; } at02; } unk_0C;   /* overlapping accesses */
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800C2824_4;   /* arg2 in func_800C2824 */

typedef struct S_800C2824_5 {
    u8 pad_00[0xA93];
    s8 unk_A93;
} S_800C2824_5;   /* page_base + (var_a2 * 0x54) in func_800C2824 */

typedef struct S_800C2824_6_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800C2824_6_pre;   /* the 0x14 bytes before c2_object in func_800C2824, addressed as c2_object[-1] */

typedef struct S_800C2824_6 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800C2824_6;   /* c2_object in func_800C2824 */

typedef struct S_800C2824_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800C2824_7;   /* (void *)c2_coord in func_800C2824 */

typedef struct S_800C2824_8 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_800C2824_8;   /* temp_t0 in func_800C2824 */

typedef struct S_800C2824_9_pre {
    u16 unk_00;
} S_800C2824_9_pre;   /* the 0x2 bytes before c3_object in func_800C2824, addressed as c3_object[-1] */

typedef struct S_800C2824_10 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_800C2824_10;   /* c3_page in func_800C2824 */

typedef struct S_800C2824_11 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800C2824_11;   /* temp_a1_2 in func_800C2824 */

typedef struct S_800C2824_12_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800C2824_12_pre;   /* the 0x14 bytes before c17_object in func_800C2824, addressed as c17_object[-1] */

typedef struct S_800C2824_12 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800C2824_12;   /* c17_object in func_800C2824 */

typedef struct S_800C2824_13 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800C2824_13;   /* (void *)c17_coord in func_800C2824 */

typedef struct S_800C2824_14_pre {
    u16 unk_00;
} S_800C2824_14_pre;   /* the 0x2 bytes before temp_v1_8 in func_800C2824, addressed as temp_v1_8[-1] */

typedef struct S_800C2824_15 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_800C2824_15;   /* c17_final_ptr in func_800C2824 */

typedef struct S_800C2824_16 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800C2824_16;   /* ((S_800C2824_0 *)arg0)->unk_00 in func_800C2824 */

extern void *D_8008938C[];
extern u8 D_80010000[];
s32 func_80042900();
s32 func_8004491C();
void func_80044A50();
M2C_UNK func_80099844();
M2C_UNK func_8009A028();
M2C_UNK func_8009A3D0();
void *func_800A32A4();
M2C_UNK func_800A56E0();
s32 func_800A6620();
M2C_UNK func_800B8FC8();
s32 func_800BBA40(u8, u8, s16, void *, s32, s32, void *);
void func_800BC318();
extern M2C_UNK D_800814A0;
extern u8 D_80082E80[];
extern M2C_UNK D_800C0180;
extern M2C_UNK D_800C27F0;
extern M2C_UNK D_800CEF54;
extern M2C_UNK D_800DF45C;
extern M2C_UNK D_800DF4A4;
extern void *D_800DF55C;
extern void *D_800DF560;
extern M2C_UNK D_800E1640;
extern void *D_800E3D7C;

typedef struct {
    s32 sp20;
    s32 sp24;
    s16 sp28;
    s16 sp2A;
} StackArgs;

/* Advance the object effect through fading, tile cleanup, and completion. */
void func_800C2824(void *effect, void *vertices, void *sprite) {
    static void *const state_labels[] = { &&state_init, &&state_fade, &&state_release, &&state_finish, &&state_start_wait, &&state_wait };
    StackArgs effect_args;
    M2C_UNK object_slot;
    M2C_UNK release_flags;
    M2C_UNK tile_flags;
    s16 fade_ticks;
    s16 wait_ticks;
    s32 state;
    register u8 *flags_page ASM_REG("$4"); /* MATCH: retain the shared flag page in retail a0. */
    void *linked_object;
    s32 effect_param;
    register s32 effect_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 faded_shade;
    u16 vertex_x;
    u16 vertex_y;
    u16 vertex_z;
    u8 shade;
    void *object_coords;
    void *object_base;
    register void *source_object ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    void *object_vertices;
    void *finished_object;
    register u8 *player_coords ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    void *release_object;
    u32 release_coord;
    s32 release_status;
    s32 release_x;
    void *expired_object;
    u32 expired_coord;
    s32 expired_status;
    s32 expired_x;
    void *final_object;
    register s32 global_flags ASM_REG("$3"); /* MATCH: both flag paths feed the shared tail in v1. */
    u16 final_flags;
    void *effect_object;
    u8 *slots_page;

    state = ((S_800C2824_0 *)effect)->unk_04;
    if ((u32) state >= 0x12U) {
        goto done;
    }
    (void)state_labels; goto *D_8008938C[(u32)(state)];
state_init:
    if (((S_800C2824_16 *)(((S_800C2824_0 *)effect)->unk_00))->unk_14 & 0x4000) {
        goto init_fade;
    }
    ((S_800C2824_0 *)effect)->unk_04 = 0x10;
    return;
init_fade:
    effect_args.sp20 = 0x01800340;
    effect_args.sp24 = 0x400040;
    effect_args.sp28 = 0x360;
    effect_args.sp2A = 0x1B8;
    func_800B8FC8(((S_800C2824_0 *)effect)->unk_00, &effect_args.sp20, &effect_args.sp28, 1, 2);
    object_base = ((S_800C2824_0 *)effect)->unk_00 - 0x20;
    func_80044A50(object_base);
    func_800BC318(object_base);
    object_vertices = ((S_800C2824_1 *)object_base)->unk_08;
    vertex_x = ((S_800C2824_2 *)object_vertices)->unk_02;
    ((S_800C2824_3 *)vertices)->unk_02 = vertex_x;
    ((S_800C2824_3 *)vertices)->unk_0E = vertex_x;
    vertex_y = ((S_800C2824_2 *)object_vertices)->unk_06;
    ((S_800C2824_3 *)vertices)->unk_06 = vertex_y;
    ((S_800C2824_3 *)vertices)->unk_12 = vertex_y;
    vertex_z = ((S_800C2824_2 *)object_vertices)->unk_0A;
    ((S_800C2824_3 *)vertices)->unk_0A = vertex_z;
    ((S_800C2824_3 *)vertices)->unk_16 = vertex_z;
    func_8004491C(effect - 0x20, &D_800CEF54);
    ((S_800C2824_4 *)sprite)->unk_10 = 0x20;
    ((S_800C2824_4 *)sprite)->unk_08 = &D_800DF4A4;
    ((S_800C2824_4 *)sprite)->unk_0C.at00.v = 0x808080;
    ((S_800C2824_4 *)sprite)->unk_1E = 0x1000;
    ((S_800C2824_4 *)sprite)->unk_1C = 0x1000;
    ((S_800C2824_4 *)sprite)->unk_14 = (u16) (((S_800C2824_4 *)sprite)->unk_14 | 0xC);
    ((S_800C2824_0 *)effect)->unk_06 = 0x10;
    func_800A56E0(1);
    ((S_800C2824_0 *)effect)->unk_04 = (s16) ((u16) ((S_800C2824_0 *)effect)->unk_04 + 1);
state_fade:
    shade = (u8) ((S_800C2824_4 *)sprite)->unk_0C.at00.v;
    faded_shade = shade - ((s32) shade / (s16) ((S_800C2824_0 *)effect)->unk_06);
    ((S_800C2824_4 *)sprite)->unk_0C.at00u.v = faded_shade;
    ((S_800C2824_4 *)sprite)->unk_0C.at02.v = faded_shade;
    ((S_800C2824_4 *)sprite)->unk_0C.at01.v = faded_shade;
    fade_ticks = (u16) ((S_800C2824_0 *)effect)->unk_06 - 1;
    ((S_800C2824_0 *)effect)->unk_06 = fade_ticks;
    if ((fade_ticks << 0x10) > 0) {
        goto done;
    }
    ((S_800C2824_0 *)effect)->unk_04 = (u16) ((S_800C2824_0 *)effect)->unk_04 + 1;
    return;
state_release:
    linked_object = func_800A32A4(((S_800C2824_0 *)effect)->unk_00);
    if (linked_object == 0) {
        goto release_tile;
    }
    object_slot = func_800A6620(linked_object, 0);
    if (object_slot >= 0x40) {
        goto release_tile;
    }
    slots_page = (u8 *)0x80010000;
    ((S_800C2824_5 *)(slots_page + (object_slot * 0x54)))->unk_A93 = 0;
    ((s32 *)0x80010980)[object_slot] = 0;
release_tile:
    if ((func_80042900(((S_800C2824_0 *)effect)->unk_00, 0x1B) << 0x10) != 0) {
        goto finish_release;
    }
    release_object = ((S_800C2824_0 *)effect)->unk_00;
    release_status = ((S_800C2824_6 *)release_object)->unk_1C;
    release_coord = (u32)((S_800C2824_6_pre *)release_object)[-1].unk_00;
    release_status &= 0x2000;
    release_x = ((S_800C2824_7 *)((void *)release_coord))->unk_24;
    release_coord = ((S_800C2824_7 *)((void *)release_coord))->unk_25;
    release_flags = 0x3000;
    if (!release_status) {
        goto clear_release_tile;
    }
    release_flags = 0x300;
clear_release_tile:
    func_8009A3D0(release_x, release_coord, release_flags);
finish_release:
    func_8009A028(((S_800C2824_0 *)effect)->unk_00);
    func_80099844(((S_800C2824_0 *)effect)->unk_00, &D_800E1640);
    ((S_800C2824_0 *)effect)->unk_04 = (u16) ((S_800C2824_0 *)effect)->unk_04 + 1;
    return;
state_finish: {
    register u8 *coords_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register void *active_object ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    coords_page = (u8 *)0x80080000;
    ASM_KEEP(coords_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    player_coords = coords_page + 0x2E80;
    effect_object = D_800E3D7C;
    D_800DF55C = effect_object;
    effect_flags = 0x208020;
    if (func_800BBA40(player_coords[0x24], player_coords[0x25], ((S_800C2824_8 *)effect_object)->unk_88, &D_800DF45C, 0x2800, effect_flags, &D_800C0180) == 0) {
        goto done;
    }
    flags_page = (u8 *)0x80080000;
    active_object = ((S_800C2824_0 *)effect)->unk_00;
    ((S_800C2824_9_pre *)active_object)[-1].unk_00 = (u16) (((S_800C2824_9_pre *)active_object)[-1].unk_00 | 0x8000);
    global_flags = ((S_800C2824_10 *)flags_page)->unk_14A0 | 0x8000;
    ((S_800C2824_10 *)flags_page)->unk_14A0 = global_flags;
    goto mark_done;
}
state_start_wait:
    source_object = ((S_800C2824_0 *)effect)->unk_00;
    effect_object = source_object;
    object_coords = (*(void **)((u8 *)effect_object + -0x14));
    effect_param = ((S_800C2824_8 *)effect_object)->unk_88;
    D_800DF55C = effect_object;
    effect_flags = 0x208020;
    if (func_800BBA40(((S_800C2824_11 *)object_coords)->unk_24, ((S_800C2824_11 *)object_coords)->unk_25, effect_param, &D_800DF45C, 0x2800, effect_flags, &D_800C27F0) == 0) {
        goto done;
    }
    ((S_800C2824_0 *)effect)->unk_06 = 0x3C;
    ((S_800C2824_0 *)effect)->unk_04 = (u16) ((S_800C2824_0 *)effect)->unk_04 + 1;
    return;
state_wait:
    wait_ticks = (u16) ((S_800C2824_0 *)effect)->unk_06 - 1;
    ((S_800C2824_0 *)effect)->unk_06 = wait_ticks;
    if ((wait_ticks << 0x10) > 0) {
        goto done;
    }
    func_800A32A4(((S_800C2824_0 *)effect)->unk_00);
    if ((func_80042900(((S_800C2824_0 *)effect)->unk_00, 0x1B) << 0x10) != 0) {
        goto finish_expired;
    }
    expired_object = ((S_800C2824_0 *)effect)->unk_00;
    expired_status = ((S_800C2824_12 *)expired_object)->unk_1C;
    expired_coord = (u32)((S_800C2824_12_pre *)expired_object)[-1].unk_00;
    expired_status &= 0x2000;
    expired_x = ((S_800C2824_13 *)((void *)expired_coord))->unk_24;
    expired_coord = ((S_800C2824_13 *)((void *)expired_coord))->unk_25;
    tile_flags = 0x3000;
    if (!expired_status) {
        goto clear_expired_tile;
    }
    tile_flags = 0x300;
clear_expired_tile:
    func_8009A3D0(expired_x, expired_coord, tile_flags);
finish_expired:
    func_8009A028(((S_800C2824_0 *)effect)->unk_00);
    finished_object = ((S_800C2824_0 *)effect)->unk_00;
    (*(u16 *)((u8 *)finished_object + -2)) = (u16) (((S_800C2824_14_pre *)finished_object)[-1].unk_00 | 0x8000);
    final_object = D_800DF560;
    flags_page = (u8 *)0x80080000;
    global_flags = ((S_800C2824_10 *)flags_page)->unk_14A0;
    final_flags = ((S_800C2824_15 *)final_object)->unk_1E;
    global_flags |= 0x8000;
    ((S_800C2824_10 *)flags_page)->unk_14A0 = global_flags;
    ((S_800C2824_15 *)final_object)->unk_1E = (u16)(final_flags | 0x8000);
mark_done:
    (*(u16 *)((u8 *)effect + -2)) = (u16) ((*(u16 *)((u8 *)effect + -2)) | 0x8000);
    ((S_800C2824_10 *)flags_page)->unk_14A0 = global_flags;
done:
    return;
}
