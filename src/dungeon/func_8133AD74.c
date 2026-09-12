/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80171D74_0 {
    s32 unk_00;
} S_80171D74_0;   /* D_8008333C in func_80171D74 */

typedef struct S_80171D74_1 {
    u8 pad_00[0x92];
    union { s16 s; u16 u; } unk_92;   /* accessed as both */
    s16 unk_94;
    u16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 pad_9B[0x3];
    s16 unk_9E;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_A0;   /* overlapping accesses */
} S_80171D74_1;   /* arg0 in func_80171D74 */

typedef struct S_80171D74_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80171D74_2;   /* D_80175D50[0] in func_80171D74 */

typedef struct S_80171D74_3 {
    union { struct { s32 v; } at00; struct { volatile s32 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { volatile s32 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    union { s32 n; volatile s32 v; } unk_0C;   /* accessed as both */
    union { s32 n; volatile s32 v; } unk_10;   /* accessed as both */
    s32 unk_14;
} S_80171D74_3;   /* arg1 in func_80171D74 */

typedef struct S_80171D74_4 {
    u8 pad_00[0x2A];
    union { u16 n; volatile u16 v; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80171D74_4;   /* temp_s3 in func_80171D74 */

typedef struct S_80171D74_5 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0x16];
    union { M2C_UNK * p; u8 * p2; } unk_2C;   /* accessed as both */
} S_80171D74_5;   /* arg2 in func_80171D74 */

typedef struct S_80171D74_6 {
    s16 unk_00;
} S_80171D74_6;   /* D_80083228 in func_80171D74 */

typedef struct S_80171D74_7 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
} S_80171D74_7;   /* temp_s4 in func_80171D74 */

typedef struct S_80171D74_8 {
    u8 pad_00[0x27];
    u8 unk_27;
    u8 pad_28[0x2];
    u16 unk_2A;
} S_80171D74_8;   /* temp_a1_2 in func_80171D74 */


typedef struct S_80171D74_10 {
    u8 pad_00[0x32];
    s16 unk_32;
} S_80171D74_10;   /* D_80175DB8[0] in func_80171D74 */

typedef struct S_80171D74_11 {
    s16 unk_00;
    u16 unk_02;
} S_80171D74_11;   /* sp2_base16 in func_80171D74 */

typedef struct S_80171D74_12 {
    u8 pad_00[0x14];
    s16 unk_14;
} S_80171D74_12;   /* base833c in func_80171D74 */

typedef struct S_80171D74_13 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_13;   /* temp_v0_12 in func_80171D74 */

typedef struct S_80171D74_14 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_14;   /* temp_v0_13 in func_80171D74 */

typedef struct S_80171D74_15 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_15;   /* temp_v0_14 in func_80171D74 */

typedef struct S_80171D74_16 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_16;   /* temp_v0_15 in func_80171D74 */

typedef struct S_80171D74_17 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_17;   /* temp_v0_16 in func_80171D74 */

typedef struct S_80171D74_18 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_18;   /* temp_v0_17 in func_80171D74 */

typedef struct S_80171D74_19 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_19;   /* temp_v0_18 in func_80171D74 */

typedef struct S_80171D74_20 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_20;   /* temp_v0_19 in func_80171D74 */

typedef struct S_80171D74_21 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_21;   /* temp_v0_20 in func_80171D74 */


typedef struct { u32 v; } __attribute__((packed)) UA32;
typedef struct { UA32 word[8]; } __attribute__((packed)) Table32;

#define SP1_X(a) M2C_FIELD((u8 *)&offset_table + ((((u16)(a)) >> 7) & 0x1C), s16 *, 0)
#define SP1_Y(a) M2C_FIELD((u8 *)&offset_table + ((((u16)(a)) >> 7) & 0x1C), u16 *, 2)
#define SP2_X(a) M2C_FIELD((u8 *)&direction_table + ((((u16)(a)) >> 7) & 0x1C), s16 *, 0)
#define SP2_Y(a) M2C_FIELD((u8 *)&direction_table + ((((u16)(a)) >> 7) & 0x1C), u16 *, 2)
#define SP1_X_AT(base, a) M2C_FIELD((u8 *)(base) + ((((u16)(a)) >> 7) & 0x1C), s16 *, 0)
#define SP1_Y_AT(base, a) M2C_FIELD((u8 *)(base) + ((((u16)(a)) >> 7) & 0x1C), u16 *, 2)
#define SP2_X_AT(base, a) M2C_FIELD((u8 *)(base) + ((((u16)(a)) >> 7) & 0x1C), s16 *, 0)
#define SP2_Y_AT(base, a) M2C_FIELD((u8 *)(base) + ((((u16)(a)) >> 7) & 0x1C), u16 *, 2)

void func_80041094(); /* extern */
void func_80047738();              /* extern */
void func_80047784();         /* extern */
void func_800478B8();  /* extern */
s32 func_800644B8();                     /* extern */
void func_800945E8();                 /* extern */
void func_800948BC();                            /* extern */
void func_800A56E0();             /* extern */
s32 func_800F685C();                      /* extern */
void func_80166F3C();             /* extern */
void func_8016738C();                      /* extern */
void func_801676CC();                      /* extern */
void func_801677FC();                  /* extern */
void func_8016F5D8();      /* extern */
void func_8016F79C();      /* extern */
void func_801715D0();                            /* extern */
extern u8 D_8006CCF8[16];
extern u16 D_80082E76[8];
extern s16 D_80083228[8];
extern s32 D_8008333C[8192];
extern u16 D_80083460[8];
extern s32 D_80083780[8192];
extern s32 D_800E3D7C[3];
extern Table32 D_8016482C;
extern Table32 D_80164AC0;
extern void *D_80164AE0[];
extern u8 D_80173DA4[16];
extern u8 D_80173DAC[16];
extern u8 D_80173DB4[16];
extern void *D_80175D50[3];
extern void *D_80175D54[3];
extern void *D_80175DB8[16];

/* Advances a scripted movement sequence and updates the sprite facing. */
void func_80171D74(void *state_in, void *motion_in, void *sprite_in) {
    Table32 offset_table;
    Table32 direction_table;
    static void *const phase_labels[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6,
        &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12, &&jt_c13,
        &&jt_c14, &&jt_c15, &&jt_c16, &&jt_c17, &&jt_c18, &&jt_c19, &&jt_c20,
        &&jt_c21, &&jt_c22, &&jt_c23, &&jt_c24, &&jt_c25, &&jt_c26, &&jt_c27,
        &&jt_c28, &&jt_c29, &&jt_c30, &&jt_c31, &&jt_c32, &&jt_c33, &&jt_c34,
        &&jt_c35, &&jt_c36, &&jt_c37, &&jt_c38, &&jt_c39, &&jt_c40, &&jt_c41,
        &&jt_c42, &&jt_c43, &&jt_c44, &&jt_c45, &&jt_c46, &&jt_c47, &&jt_c48
    };
    s16 right_angle;
    s16 quarter_turn;
    s16 sprite_dir;
    s16 turn_frame;
    s16 spin_frame;
    s16 owner_height;
    s16 turn_value;
    s16 facing_angle;
    s32 move_component;
    s32 speed;
    void *sprite;
    Table32 *copy_base;
    register s32 *map_info ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 map_tiles;
    u8 tail_phase;
    u16 left_angle;
    u16 wait_frame;
    u16 return_frames;
    u16 arc_frame;
    u16 approach_frames;
    u16 bounce_frame;
    u16 spin_up_frame;
    u16 launch_frame;
    u16 hop_frame;
    u16 wobble_frame;
    u16 frame_or_height;
    u16 spiral_frame;
    u16 effect_wait_frame;
    u16 rise_frame;
    u16 finish_frame;
    u16 pause_frame;
    u16 sway_frame;
    u16 lift_frame;
    u16 slide_frame;
    u16 appear_frame;
    u16 travel_frame;
    u16 turned_angle;
    u16 old_angle;
    s32 phase;
    s32 hop_vel_y;
    s32 launch_vel_y;
    S_80171D74_8 *target_state;
    s32 launch_vel_z;
    s32 hop_vel_z;
    S_80171D74_4 *owner_state;
    register void *target_pos ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_80171D74_13 *tile_nw;
    S_80171D74_14 *tile_n;
    S_80171D74_15 *tile_ne;
    S_80171D74_16 *tile_w;
    S_80171D74_17 *tile_center;
    S_80171D74_18 *tile_e;
    S_80171D74_19 *tile_sw;
    S_80171D74_20 *tile_s;
    S_80171D74_21 *tile_se;

    sprite = sprite_in;
    ASM_KEEP_NV(motion_in);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
       /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    copy_base = &D_8016482C;
    offset_table = *copy_base;
    copy_base = &D_80164AC0;
    direction_table = *copy_base;
    map_info = D_8008333C;
    map_tiles = ((S_80171D74_0 *)D_8008333C)->unk_00;
    owner_state = D_80175D54[0] + 0x20;
    func_800478B8(sprite);
    phase = ((S_80171D74_1 *)state_in)->unk_9A;
    target_pos = ((S_80171D74_2 *)(D_80175D50[0]))->unk_08;
    target_state = D_80175D50[0] + 0x20;
    if ((u32)phase >= 49U) {
        goto update_sprite;
    }
    (void)phase_labels;
    goto *D_80164AE0[(u32)phase];
jt_c0:
        wait_frame = ((S_80171D74_1 *)state_in)->unk_96;
        ((S_80171D74_1 *)state_in)->unk_96 = (u16) (wait_frame + 1);
        if ((s16) wait_frame >= 0x1E) {
            ((S_80171D74_1 *)state_in)->unk_96 = 0U;
            ((S_80171D74_1 *)state_in)->unk_9A = (u8) (((S_80171D74_1 *)state_in)->unk_9A + 1);
            ((S_80171D74_3 *)motion_in)->unk_10.n = (s32) 0xFFF80000;
            goto update_height;
        }
        goto update_height;
jt_c1:
        ((S_80171D74_3 *)motion_in)->unk_04.at00.v = ((S_80171D74_3 *)motion_in)->unk_04.at00.v + ((S_80171D74_3 *)motion_in)->unk_10.n;
        rise_frame = ((S_80171D74_1 *)state_in)->unk_96 + 1;
        ((S_80171D74_1 *)state_in)->unk_96 = rise_frame;
        if ((s16) rise_frame >= 0x38) {
            ((S_80171D74_1 *)state_in)->unk_96 = 0U;
            ((S_80171D74_1 *)state_in)->unk_9A = (u8) (((S_80171D74_1 *)state_in)->unk_9A + 1);
            ASM_SCHED_BARRIER(); /* MATCH: preserve the distinct case tail and its delay-slot store. */
            ((S_80171D74_3 *)motion_in)->unk_0C.n = 0;
            goto update_height;
        }
        goto update_height;
jt_c2:
        pause_frame = ((S_80171D74_1 *)state_in)->unk_96;
        ((S_80171D74_1 *)state_in)->unk_96 = (u16) (pause_frame + 1);
        if ((s16) pause_frame >= 0x1E) {
            u8 next_phase;
            next_phase = ((S_80171D74_1 *)state_in)->unk_9A;
            ((S_80171D74_1 *)state_in)->unk_96 = 0U;
            next_phase = next_phase + 1;
            ASM_SCHED_BARRIER(); /* MATCH: preserve the distinct case tail and its delay-slot store. */
            ((S_80171D74_1 *)state_in)->unk_9A = (u8) next_phase;
            goto update_height;
        }
        goto update_height;
jt_c3:
        sway_frame = ((S_80171D74_1 *)state_in)->unk_96 + 1;
        ((S_80171D74_1 *)state_in)->unk_96 = sway_frame;
        if ((s16) sway_frame == 3) {
            owner_state->unk_2A.n = (u16) (owner_state->unk_2A.n + 0x200);
        }
        if ((s16) ((S_80171D74_1 *)state_in)->unk_96 == 4) {
            owner_state->unk_2A.n = (u16) (owner_state->unk_2A.n + 0x200);
        }
        if ((s16) ((S_80171D74_1 *)state_in)->unk_96 == 0x12) {
            owner_state->unk_2A.n = (u16) (owner_state->unk_2A.n - 0x200);
        }
        if ((s16) ((S_80171D74_1 *)state_in)->unk_96 == 0x14) {
            owner_state->unk_2A.n = (u16) (owner_state->unk_2A.n - 0x200);
        }
        if ((s16) ((S_80171D74_1 *)state_in)->unk_96 == 0x1E) {
            ((S_80171D74_1 *)state_in)->unk_96 = 0U;
            ((S_80171D74_1 *)state_in)->unk_9A = (u8) (((S_80171D74_1 *)state_in)->unk_9A + 1);
            ((S_80171D74_3 *)motion_in)->unk_0C.n = 0;
            ((S_80171D74_3 *)motion_in)->unk_10.n = (s32) 0xFFF80000;
            goto update_height;
        }
        goto update_height;
jt_c4:
        ((S_80171D74_3 *)motion_in)->unk_04.at00.v = ((S_80171D74_3 *)motion_in)->unk_04.at00.v + ((S_80171D74_3 *)motion_in)->unk_10.n;
        lift_frame = ((S_80171D74_1 *)state_in)->unk_96 + 1;
        ((S_80171D74_1 *)state_in)->unk_96 = lift_frame;
        if ((s16) lift_frame >= 0x10) {
            ((S_80171D74_1 *)state_in)->unk_96 = 0U;
            ((S_80171D74_1 *)state_in)->unk_9A = (u8) (((S_80171D74_1 *)state_in)->unk_9A + 1);
            ((S_80171D74_3 *)motion_in)->unk_0C.n = 0;
            goto update_height;
        }
        goto update_height;
jt_c6:
        ((S_80171D74_5 *)sprite)->unk_2C.p = &D_80173DAC;
        func_80047784(sprite, D_80173DAC[((s32) (((S_80171D74_6 *)D_80083228)->unk_00 + (s16) owner_state->unk_2A.n + 0x100) >> 9) & 7], 3);
        ((S_80171D74_1 *)state_in)->unk_96 = 0U;
        ((S_80171D74_1 *)state_in)->unk_9A = (u8) (((S_80171D74_1 *)state_in)->unk_9A + 1);
        ((S_80171D74_3 *)motion_in)->unk_0C.n = (s32) 0x00020000;
        goto update_sprite;
jt_c7:
        ((S_80171D74_3 *)motion_in)->unk_00.at00.v = (s32) (((S_80171D74_3 *)motion_in)->unk_00.at00.v + ((S_80171D74_3 *)motion_in)->unk_0C.n);
        slide_frame = ((S_80171D74_1 *)state_in)->unk_96 + 1;
        ((S_80171D74_1 *)state_in)->unk_96 = slide_frame;
        if ((s16) slide_frame >= 8) {
            ((S_80171D74_1 *)state_in)->unk_96 = 0U;
            ((S_80171D74_1 *)state_in)->unk_9A = (u8) (((S_80171D74_1 *)state_in)->unk_9A + 1);
            ((S_80171D74_3 *)motion_in)->unk_0C.n = 0;
            ((S_80171D74_5 *)sprite)->unk_14 = (u16) (((S_80171D74_5 *)sprite)->unk_14 | 0x80);
            ((S_80171D74_3 *)motion_in)->unk_04.at02.v = 1;
            ((S_80171D74_3 *)motion_in)->unk_00.at02.v = 1U;
        }
        if ((s16) ((S_80171D74_1 *)state_in)->unk_96 == 3) {
            func_80166F3C(target_pos, 0);
            func_80166F3C(target_pos, 1);
            func_8016738C(target_pos);
            func_801676CC(target_pos);
            goto update_sprite;
        }
        goto update_sprite;
jt_c9:
        func_801677FC(phase, target_state);
        tail_phase = ((S_80171D74_1 *)state_in)->unk_9A;
        ((S_80171D74_1 *)state_in)->unk_96 = 0;
        goto advance_phase;
jt_c10:
        appear_frame = ((S_80171D74_1 *)state_in)->unk_96 + 1;
        ((S_80171D74_1 *)state_in)->unk_96 = appear_frame;
        if ((s16) appear_frame >= 2) {
            u8 *offset_base = (u8 *)&offset_table;
            u8 *direction_base;
            register s32 angle_input ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
            s32 angle_tmp;
            register s32 angle_result ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
            ((S_80171D74_1 *)state_in)->unk_96 = 0U;
            ((S_80171D74_1 *)state_in)->unk_9A = (u8) (((S_80171D74_1 *)state_in)->unk_9A + 1);
            ((S_80171D74_5 *)sprite)->unk_14 = (u16) (((S_80171D74_5 *)sprite)->unk_14 & 0xFF7F);
            ((S_80171D74_3 *)motion_in)->unk_00.at02.v = (u16) (((S_80171D74_7 *)target_pos)->unk_00.at02.v + (SP1_X_AT(offset_base, target_state->unk_2A) * 0x28));
            ((S_80171D74_3 *)motion_in)->unk_04.at02.v = (s16) (((S_80171D74_7 *)target_pos)->unk_04.at02.v + ((s16) SP1_Y_AT(offset_base, target_state->unk_2A) * 0x28));
            ((S_80171D74_1 *)state_in)->unk_92.s = -0x18;
            ((S_80171D74_1 *)state_in)->unk_9E = 0;
            ((S_80171D74_1 *)state_in)->unk_A0.at00.v = 0;
            angle_input = target_state->unk_2A;
            angle_tmp = angle_input - 0x400;
            angle_result = angle_tmp;
            if ((angle_tmp << 0x10) < 0) {
                angle_result = angle_tmp + 0x1000;
            }
            owner_state->unk_2A.n = angle_result;
            ((S_80171D74_1 *)state_in)->unk_94 = 1;
            ((S_80171D74_5 *)sprite)->unk_2C.p = &D_80173DB4;
            func_80047784(sprite, D_80173DB4[((s32) (((S_80171D74_6 *)D_80083228)->unk_00 + (s16) owner_state->unk_2A.n + 0x100) >> 9) & 7], 0);
            direction_base = (u8 *)&direction_table;
            ((S_80171D74_3 *)motion_in)->unk_0C.n = (s32) (0 - (SP2_X_AT(direction_base, owner_state->unk_2A.n) << 0x10));
            ((S_80171D74_3 *)motion_in)->unk_10.n = (void *) (0 - (SP2_Y_AT(direction_base, owner_state->unk_2A.n) << 0x10));
            func_801715D0();
            goto update_height;
        }
        goto update_sprite;
jt_c11:
        {
            s32 pos_x = ((S_80171D74_3 *)motion_in)->unk_00.at00.v;
            s32 vel_x = ((S_80171D74_3 *)motion_in)->unk_0C.n;
            s32 pos_y = ((S_80171D74_3 *)motion_in)->unk_04.at00.v;
            s32 vel_y = ((S_80171D74_3 *)motion_in)->unk_10.n;
            ((S_80171D74_3 *)motion_in)->unk_00.at00.v = pos_x + vel_x;
            ((S_80171D74_3 *)motion_in)->unk_04.at00.v = pos_y + vel_y;
        }
        travel_frame = ((S_80171D74_1 *)state_in)->unk_96 + 1;
        ((S_80171D74_1 *)state_in)->unk_96 = travel_frame;
        if ((s16) travel_frame >= 0x14) {
            ((S_80171D74_1 *)state_in)->unk_96 = 0U;
            ((S_80171D74_1 *)state_in)->unk_9A = (u8) (((S_80171D74_1 *)state_in)->unk_9A + 1);
            goto update_height;
        }
        goto update_height;
jt_c13:
        old_angle = owner_state->unk_2A.n;
        turned_angle = old_angle + 0x200;
        owner_state->unk_2A.n = turned_angle;
        if ((s16) turned_angle >= 0x1000) {
            owner_state->unk_2A.n = (u16) (old_angle - 0xE00);
        }
        ((S_80171D74_1 *)state_in)->unk_96 = 0U;
        ((S_80171D74_1 *)state_in)->unk_9A = (u8) (((S_80171D74_1 *)state_in)->unk_9A + 1);
        target_state->unk_27 = 3;
        goto update_height;
jt_c15:
        ((S_80171D74_1 *)state_in)->unk_96 = 0x1EU;
        ((S_80171D74_1 *)state_in)->unk_9A = (u8) (((S_80171D74_1 *)state_in)->unk_9A + 1);
        /* fallthrough */
jt_c16:
        {
            s32 target_x = ((Rec_D_800E3D7C *)(&D_80083780))->unk_00.at00_vs32.v;
            move_component = ((S_80171D74_3 *)motion_in)->unk_00.at00u.v;
            ((S_80171D74_3 *)motion_in)->unk_0C.n = (target_x - move_component) / (s16) ((S_80171D74_1 *)state_in)->unk_96;
        }
        {
            s32 next_y = (((Rec_D_800E3D7C *)(&D_80083780))->unk_04.at00_s32.v - ((S_80171D74_3 *)motion_in)->unk_04.at00.v) / (s16) ((S_80171D74_1 *)state_in)->unk_96;
            s32 vel_x = ((S_80171D74_3 *)motion_in)->unk_0C.v;
            s32 pos_y = ((S_80171D74_3 *)motion_in)->unk_04.at00u.v;
            s32 next_x;
            ((S_80171D74_3 *)motion_in)->unk_10.v = next_y;
            next_x = move_component;
            move_component = ((S_80171D74_3 *)motion_in)->unk_10.v;
            ((S_80171D74_3 *)motion_in)->unk_00.at00.v = next_x + vel_x;
            ((S_80171D74_3 *)motion_in)->unk_04.at00.v = pos_y + move_component;
        }
        return_frames = ((S_80171D74_1 *)state_in)->unk_96 - 1;
        ((S_80171D74_1 *)state_in)->unk_96 = return_frames;
        if ((return_frames << 0x10) <= 0) {
            u8 *direction_entry;
            register s32 angle_input ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
            s32 angle_tmp;
            register s32 angle_result ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
            register u32 direction_offset ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            ((S_80171D74_1 *)state_in)->unk_96 = 0U;
            ((S_80171D74_1 *)state_in)->unk_9A = (u8) (((S_80171D74_1 *)state_in)->unk_9A + 1);
            ((S_80171D74_10 *)(D_80175DB8[0]))->unk_32 = 3;
            ((S_80171D74_5 *)sprite)->unk_2C.p = &D_80173DA4;
            func_80047784(sprite, D_80173DA4[((s32) (((S_80171D74_6 *)D_80083228)->unk_00 + (s16) owner_state->unk_2A.n + 0x100) >> 9) & 7], 0);
            angle_input = owner_state->unk_2A.n;
            angle_tmp = angle_input + 0x200;
            angle_result = angle_tmp;
            if ((s16) angle_tmp >= 0x1000) {
                angle_result = angle_tmp - 0x1000;
            }
            direction_offset = ((u16) angle_result >> 7) & 0x1C;
            direction_entry = (u8 *)&direction_table;
            direction_entry += direction_offset;
            ((S_80171D74_3 *)motion_in)->unk_0C.n = (s32) (((S_80171D74_11 *)direction_entry)->unk_00 << 0x10);
            ((S_80171D74_3 *)motion_in)->unk_10.n = (s32) (((S_80171D74_11 *)direction_entry)->unk_02 << 0x10);
            goto update_height;
        }
        goto update_height;
jt_c17:
        {
            s32 pos_x = ((S_80171D74_3 *)motion_in)->unk_00.at00.v;
            s32 vel_x = ((S_80171D74_3 *)motion_in)->unk_0C.n;
            s32 pos_y = ((S_80171D74_3 *)motion_in)->unk_04.at00.v;
            s32 vel_y = ((S_80171D74_3 *)motion_in)->unk_10.n;
            ((S_80171D74_3 *)motion_in)->unk_00.at00.v = pos_x + vel_x;
            ((S_80171D74_3 *)motion_in)->unk_04.at00.v = pos_y + vel_y;
        }
        {
            s32 height_offset;
            u16 next_frame;
            height_offset = ((S_80171D74_1 *)state_in)->unk_92.u;
            next_frame = ((S_80171D74_1 *)state_in)->unk_96;
            height_offset = height_offset - 2;
            next_frame = next_frame + 1;
            arc_frame = next_frame;
            ((S_80171D74_1 *)state_in)->unk_96 = arc_frame;
            ((S_80171D74_1 *)state_in)->unk_92.u = height_offset;
        }
        if ((s16) arc_frame >= 0x28) {
            ((S_80171D74_1 *)state_in)->unk_96 = 0U;
            ((S_80171D74_1 *)state_in)->unk_9A = (u8) (((S_80171D74_1 *)state_in)->unk_9A + 1);
            ((S_80171D74_3 *)motion_in)->unk_10.n = NULL;
            ((S_80171D74_3 *)motion_in)->unk_0C.n = 0;
        }
        turn_frame = (s16) ((S_80171D74_1 *)state_in)->unk_96;
        if ((turn_frame == 0xA) || (turn_frame == 0x14) || (turn_frame == 0x1E)) {
            register s32 angle_input ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
            s32 angle_tmp;
            register s32 angle_result ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
            angle_input = owner_state->unk_2A.n;
            angle_tmp = angle_input - 0x200;
            angle_result = angle_tmp;
            if ((angle_tmp << 0x10) < 0) {
                angle_result = angle_tmp + 0x1000;
            }
            owner_state->unk_2A.n = angle_result;
            if ((s16) ((S_80171D74_1 *)state_in)->unk_96 == 0x1E) {
                func_800A56E0(0x81A);
                goto update_height;
            }
            goto update_height;
        }
        goto update_height;
jt_c19:
        ((S_80171D74_1 *)state_in)->unk_96 = 0x14U;
        ((S_80171D74_1 *)state_in)->unk_9A = (u8) (((S_80171D74_1 *)state_in)->unk_9A + 1);
        tile_nw = ((0x1F << ((S_80171D74_12 *)map_info)->unk_14) * 6) + map_tiles + 0xBA;
        tile_nw->unk_04 = (u16) (tile_nw->unk_04 & 0x7FFF);
        tile_n = ((0x1F << ((S_80171D74_12 *)map_info)->unk_14) * 6) + map_tiles + 0xC0;
        tile_n->unk_04 = (u16) (tile_n->unk_04 & 0x7FFF);
        tile_ne = ((0x1F << ((S_80171D74_12 *)map_info)->unk_14) * 6) + map_tiles + 0xC6;
        tile_ne->unk_04 = (u16) (tile_ne->unk_04 & 0x7FFF);
        tile_w = ((0x20 << ((S_80171D74_12 *)map_info)->unk_14) * 6) + map_tiles + 0xBA;
        tile_w->unk_04 = (u16) (tile_w->unk_04 & 0x7FFF);
        tile_center = ((0x20 << ((S_80171D74_12 *)map_info)->unk_14) * 6) + map_tiles + 0xC0;
        tile_center->unk_04 = (u16) (tile_center->unk_04 & 0x7FFF);
        tile_e = ((0x20 << ((S_80171D74_12 *)map_info)->unk_14) * 6) + map_tiles + 0xC6;
        tile_e->unk_04 = (u16) (tile_e->unk_04 & 0x7FFF);
        tile_sw = ((0x21 << ((S_80171D74_12 *)map_info)->unk_14) * 6) + map_tiles + 0xBA;
        tile_sw->unk_04 = (u16) (tile_sw->unk_04 & 0x7FFF);
        tile_s = ((0x21 << ((S_80171D74_12 *)map_info)->unk_14) * 6) + map_tiles + 0xC0;
        tile_s->unk_04 = (u16) (tile_s->unk_04 & 0x7FFF);
        tile_se = ((0x21 << ((S_80171D74_12 *)map_info)->unk_14) * 6) + map_tiles + 0xC6;
        tile_se->unk_04 = (u16) (tile_se->unk_04 & 0x7FFF);
        ((S_80171D74_3 *)motion_in)->unk_0C.n = (s32) ((S_80171D74_7 *)target_pos)->unk_00.at00.v;
        ((S_80171D74_3 *)motion_in)->unk_10.n = (void *) ((S_80171D74_7 *)target_pos)->unk_04.at00.v;
        ((S_80171D74_3 *)motion_in)->unk_14 = (void *) ((S_80171D74_7 *)target_pos)->unk_08;
        /* fallthrough */
jt_c20:
        ((S_80171D74_3 *)motion_in)->unk_00.at00.v += (((S_80171D74_3 *)motion_in)->unk_0C.n - ((S_80171D74_3 *)motion_in)->unk_00.at00.v) / (s16) ((S_80171D74_1 *)state_in)->unk_96;
        ((S_80171D74_3 *)motion_in)->unk_04.at00.v += (((S_80171D74_3 *)motion_in)->unk_10.n - ((S_80171D74_3 *)motion_in)->unk_04.at00.v) / (s16) ((S_80171D74_1 *)state_in)->unk_96;
        ((S_80171D74_3 *)motion_in)->unk_08.at00.v += (((S_80171D74_3 *)motion_in)->unk_14 - ((S_80171D74_3 *)motion_in)->unk_08.at00.v) / (s16) ((S_80171D74_1 *)state_in)->unk_96;
        approach_frames = ((S_80171D74_1 *)state_in)->unk_96 - 1;
        ((S_80171D74_1 *)state_in)->unk_96 = approach_frames;
        if ((approach_frames << 0x10) <= 0) {
            tail_phase = ((S_80171D74_1 *)state_in)->unk_9A;
            ASM_KEEP(tail_phase);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            ((S_80171D74_1 *)state_in)->unk_96 = 0;
            goto advance_phase;
        }
        goto update_sprite;
jt_c21:
        if (((S_80171D74_5 *)sprite)->unk_04 == 0) {
            ((S_80171D74_5 *)sprite)->unk_14 = (u16) (((S_80171D74_5 *)sprite)->unk_14 | 0x800);
            goto update_sprite;
        }
        goto update_sprite;
jt_c22:
        {
            u16 next_frame;
            if (((S_80171D74_5 *)sprite)->unk_04 == 0) {
                ((S_80171D74_5 *)sprite)->unk_14 = (u16) (((S_80171D74_5 *)sprite)->unk_14 | 0x800);
            }
            bounce_frame = ((S_80171D74_1 *)state_in)->unk_96;
            next_frame = bounce_frame + 1;
            ASM_KEEP_NV(next_frame);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            ((S_80171D74_1 *)state_in)->unk_96 = next_frame;
            if ((u32) (bounce_frame - 0xA) < 8U) {
                ((S_80171D74_1 *)state_in)->unk_A0.at00.v = (s32) (func_800644B8(((s32) (next_frame << 0x10) >> 8) - 0xA00) << 8);
                ((S_80171D74_3 *)motion_in)->unk_08.at02.v = (u16) (owner_state->unk_88 - ((S_80171D74_1 *)state_in)->unk_A0.at02.v);
            }
        }
        spin_frame = (s16) ((S_80171D74_1 *)state_in)->unk_96;
        if ((spin_frame == 0x19) || (spin_frame == 0x1E) || (spin_frame == 0x23) || (spin_frame == 0x28)) {
            register s32 angle_input ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
            s32 angle_tmp;
            register s32 angle_result ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
            angle_input = owner_state->unk_2A.n;
            angle_tmp = angle_input - 0x200;
            angle_result = angle_tmp;
            if ((angle_tmp << 0x10) < 0) {
                angle_result = angle_tmp + 0x1000;
            }
            owner_state->unk_2A.n = angle_result;
        }
        if ((s16) ((S_80171D74_1 *)state_in)->unk_96 >= 0x2D) {
            ((S_80171D74_1 *)state_in)->unk_96 = 0U;
            ((S_80171D74_1 *)state_in)->unk_92.s = -0x18;
            ((S_80171D74_1 *)state_in)->unk_9E = 0;
            ((S_80171D74_1 *)state_in)->unk_A0.at00.v = 0;
            ((S_80171D74_1 *)state_in)->unk_9A = (u8) (((S_80171D74_1 *)state_in)->unk_9A + 1);
            ((S_80171D74_3 *)motion_in)->unk_08.at02.v = owner_state->unk_88;
            goto update_sprite;
        }
        goto update_sprite;
jt_c24:
        spin_up_frame = ((S_80171D74_1 *)state_in)->unk_96 + 1;
        ((S_80171D74_1 *)state_in)->unk_96 = spin_up_frame;
        if (((s16) spin_up_frame == 5) || ((s16) spin_up_frame == 0xA) || ((s16) spin_up_frame == 0xF) || ((s16) spin_up_frame == 0x14)) {
            register s32 angle_input ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
            s32 angle_tmp;
            register s32 angle_result ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
            angle_input = owner_state->unk_2A.n;
            angle_tmp = angle_input - 0x200;
            angle_result = angle_tmp;
            if ((angle_tmp << 0x10) < 0) {
                angle_result = angle_tmp + 0x1000;
            }
            owner_state->unk_2A.n = angle_result;
        }
        if ((s16) ((S_80171D74_1 *)state_in)->unk_96 >= 0x18) {
            u8 *direction_base;
            ((S_80171D74_1 *)state_in)->unk_96 = 0U;
            ((S_80171D74_1 *)state_in)->unk_9A = (u8) (((S_80171D74_1 *)state_in)->unk_9A + 1);
            ((S_80171D74_5 *)sprite)->unk_2C.p = &D_80173DA4;
            ((S_80171D74_5 *)sprite)->unk_14 = (u16) (((S_80171D74_5 *)sprite)->unk_14 & 0xF7FF);
            func_80047784(sprite, D_80173DA4[((s32) (((S_80171D74_6 *)D_80083228)->unk_00 + (s16) owner_state->unk_2A.n + 0x100) >> 9) & 7], 0);
            direction_base = (u8 *)&direction_table;
            ((S_80171D74_3 *)motion_in)->unk_0C.n = (s32) (SP2_X_AT(direction_base, owner_state->unk_2A.n) << 0x14);
            ((S_80171D74_3 *)motion_in)->unk_10.n = (s32) (SP2_Y_AT(direction_base, owner_state->unk_2A.n) << 0x14);
            ((S_80171D74_3 *)motion_in)->unk_14 = (void *)0xFFF00000;
            goto update_sprite;
        }
        goto update_sprite;
jt_c25:
        launch_vel_y = ((S_80171D74_3 *)motion_in)->unk_10.n;
        launch_vel_z = ((S_80171D74_3 *)motion_in)->unk_14;
        ((S_80171D74_3 *)motion_in)->unk_00.at00.v = (s32) (((S_80171D74_3 *)motion_in)->unk_00.at00.v + ((S_80171D74_3 *)motion_in)->unk_0C.n);
        ((S_80171D74_3 *)motion_in)->unk_04.at00.v = (void *) (((S_80171D74_3 *)motion_in)->unk_04.at00.v + launch_vel_y);
        ((S_80171D74_3 *)motion_in)->unk_08.at00.v = (void *) (((S_80171D74_3 *)motion_in)->unk_08.at00.v + launch_vel_z);
        launch_frame = ((S_80171D74_1 *)state_in)->unk_96 + 1;
        ((S_80171D74_1 *)state_in)->unk_96 = launch_frame;
        if ((s16) launch_frame >= 0x28) {
            tail_phase = ((S_80171D74_1 *)state_in)->unk_9A;
            ASM_KEEP(tail_phase);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            ((S_80171D74_1 *)state_in)->unk_96 = 0;
            goto advance_phase;
        }
        goto update_sprite;
jt_c30: {
        u8 *direction_base;
        u16 angle;
        u16 direction_y;
        angle = owner_state->unk_2A.v;
        direction_base = (u8 *)&direction_table;
        ((S_80171D74_3 *)motion_in)->unk_0C.n = (s32) (SP2_X_AT(direction_base, angle) << 0x13);
        direction_y = SP2_Y_AT(direction_base, owner_state->unk_2A.n);
        ((S_80171D74_3 *)motion_in)->unk_14 = (void *)0xFFFB0000;
        ((S_80171D74_3 *)motion_in)->unk_10.n = (void *) (direction_y << 0x13);
        tail_phase = ((S_80171D74_1 *)state_in)->unk_9A;
        ASM_KEEP(tail_phase);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        ((S_80171D74_1 *)state_in)->unk_96 = 0;
        goto advance_phase;
    }
jt_c31:
        hop_vel_y = ((S_80171D74_3 *)motion_in)->unk_10.n;
        hop_vel_z = ((S_80171D74_3 *)motion_in)->unk_14;
        ((S_80171D74_3 *)motion_in)->unk_00.at00.v = (s32) (((S_80171D74_3 *)motion_in)->unk_00.at00.v + ((S_80171D74_3 *)motion_in)->unk_0C.n);
        ((S_80171D74_3 *)motion_in)->unk_04.at00.v = (void *) (((S_80171D74_3 *)motion_in)->unk_04.at00.v + hop_vel_y);
        ((S_80171D74_3 *)motion_in)->unk_08.at00.v = (void *) (((S_80171D74_3 *)motion_in)->unk_08.at00.v + hop_vel_z);
        hop_frame = ((S_80171D74_1 *)state_in)->unk_96 + 1;
        ((S_80171D74_1 *)state_in)->unk_96 = hop_frame;
        if ((s16) hop_frame >= 5) {
            ((S_80171D74_1 *)state_in)->unk_96 = 0U;
            ((S_80171D74_1 *)state_in)->unk_9A = (u8) (((S_80171D74_1 *)state_in)->unk_9A + 1);
            ((S_80171D74_3 *)motion_in)->unk_14 = NULL;
            ((S_80171D74_3 *)motion_in)->unk_10.n = NULL;
            ((S_80171D74_3 *)motion_in)->unk_0C.n = 0;
            goto update_sprite;
        }
        goto update_sprite;
jt_c32:
        wobble_frame = ((S_80171D74_1 *)state_in)->unk_96 + 1;
        ((S_80171D74_1 *)state_in)->unk_96 = wobble_frame;
        if (((s16) wobble_frame == 2) || ((s16) wobble_frame == 8) || ((s16) wobble_frame == 0xA) || ((s16) wobble_frame == 0x10) || ((s16) wobble_frame == 0x12)) {
            turn_value = owner_state->unk_2A.n;
            right_angle = turn_value + 0x200;
            turn_value = right_angle;
            if (right_angle >= 0x1000) {
                turn_value = right_angle - 0x1000;
            }
            owner_state->unk_2A.n = (u16) turn_value;
        }
        turn_value = (s16) ((S_80171D74_1 *)state_in)->unk_96;
        if ((turn_value == 4) || (turn_value == 6) || (turn_value == 0xC) || (turn_value == 0xE) || (turn_value == 0x14)) {
            turn_value = owner_state->unk_2A.n;
            left_angle = turn_value - 0x200;
            turn_value = left_angle;
            if ((s16) left_angle < 0) {
                turn_value = left_angle + 0x1000;
            }
            owner_state->unk_2A.n = turn_value;
        }
        turn_value = (s16) ((S_80171D74_1 *)state_in)->unk_96;
        if (turn_value == 0x1A) {
            ((S_80171D74_5 *)sprite)->unk_2C.p = &D_80173DA4;
            ((S_80171D74_5 *)sprite)->unk_14 = (u16) (((S_80171D74_5 *)sprite)->unk_14 & 0xF7FF);
            func_80047784(sprite, D_80173DA4[((s32) (((S_80171D74_6 *)D_80083228)->unk_00 + (s16) owner_state->unk_2A.n + 0x100) >> 9) & 7], 0);
        }
        if ((s16) ((S_80171D74_1 *)state_in)->unk_96 >= 0x1E) {
            ((S_80171D74_1 *)state_in)->unk_96 = 0U;
            ((S_80171D74_1 *)state_in)->unk_9A = (u8) (((S_80171D74_1 *)state_in)->unk_9A + 1);
            ((S_80171D74_3 *)motion_in)->unk_14 = (void *)0xFFF80000;
            goto update_sprite;
        }
        goto update_sprite;
jt_c33:
        ((S_80171D74_3 *)motion_in)->unk_08.at00.v = (void *) (((S_80171D74_3 *)motion_in)->unk_08.at00.v + ((S_80171D74_3 *)motion_in)->unk_14);
        frame_or_height = ((S_80171D74_1 *)state_in)->unk_96 + 1;
        ((S_80171D74_1 *)state_in)->unk_96 = frame_or_height;
        if ((s16) frame_or_height >= 0xA) {
            ((S_80171D74_1 *)state_in)->unk_96 = 0U;
            ((S_80171D74_1 *)state_in)->unk_9A = (u8) (((S_80171D74_1 *)state_in)->unk_9A + 1);
            frame_or_height = ((S_80171D74_3 *)motion_in)->unk_08.at02.v;
            ((S_80171D74_3 *)motion_in)->unk_14 = NULL;
            ((S_80171D74_3 *)motion_in)->unk_10.n = NULL;
            ((S_80171D74_3 *)motion_in)->unk_0C.n = 0;
            owner_height = owner_state->unk_88;
            ((S_80171D74_1 *)state_in)->unk_9E = 0;
            ((S_80171D74_1 *)state_in)->unk_A0.at00.v = 0;
            ((S_80171D74_1 *)state_in)->unk_92.u = (u16) (frame_or_height - owner_height);
            facing_angle = owner_state->unk_2A.n;
            quarter_turn = facing_angle + 0x400;
            facing_angle = quarter_turn;
            if (quarter_turn >= 0x1000) {
                facing_angle = quarter_turn - 0x1000;
            }
            owner_state->unk_2A.n = (u16) facing_angle;
            func_80047784(sprite, *(((S_80171D74_5 *)sprite)->unk_2C.p2 + (((s32) (((S_80171D74_6 *)D_80083228)->unk_00 + facing_angle + 0x100) >> 9) & 7)), 0);
        }
        goto update_sprite;
jt_c34: {
        spiral_frame = ((S_80171D74_1 *)state_in)->unk_96 + 1;
        ((S_80171D74_1 *)state_in)->unk_96 = spiral_frame;
        if ((spiral_frame & 3) == 3) {
            register s32 angle_input ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
            s32 angle_tmp;
            register s32 angle_result ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
            angle_input = owner_state->unk_2A.n;
            angle_tmp = angle_input - 0x200;
            angle_result = angle_tmp;
            if ((angle_tmp << 0x10) < 0) {
                angle_result = angle_tmp + 0x1000;
            }
            owner_state->unk_2A.n = angle_result;
        }
        speed = ((0x61 - (s16) ((S_80171D74_1 *)state_in)->unk_96) * 0x60000) / 97;
        {
            u8 *direction_base = (u8 *)&direction_table;
            s32 direction_x = SP2_X_AT(direction_base, owner_state->unk_2A.n);
            ((S_80171D74_3 *)motion_in)->unk_0C.n = speed * direction_x;
            direction_base = (u8 *)&direction_table;
            {
                s16 direction_y = (s16) SP2_Y_AT(direction_base, owner_state->unk_2A.n);
                ((S_80171D74_3 *)motion_in)->unk_10.n = speed * direction_y;
            }
            ((S_80171D74_3 *)motion_in)->unk_00.at00.v += ((S_80171D74_3 *)motion_in)->unk_0C.n;
            ((S_80171D74_3 *)motion_in)->unk_04.at00.v += ((S_80171D74_3 *)motion_in)->unk_10.n;
        }
        if ((s16) ((S_80171D74_1 *)state_in)->unk_96 >= 0x58) {
            ((S_80171D74_1 *)state_in)->unk_96 = 0U;
            ((S_80171D74_1 *)state_in)->unk_9A = (u8) (((S_80171D74_1 *)state_in)->unk_9A + 1);
            {
                u16 *reset_base = (u16 *)D_80083780;
                ((S_80171D74_3 *)motion_in)->unk_00.at02.v = reset_base[1];
                ((S_80171D74_3 *)motion_in)->unk_04.at02u.v = reset_base[3];
            }
            goto update_height;
        }
        goto update_height;
    }
jt_c40:
        if ((func_800F685C(phase, target_state) << 0x10) != 0) {
            ((S_80171D74_1 *)state_in)->unk_96 = 0U;
            ((S_80171D74_1 *)state_in)->unk_9A = (u8) (((S_80171D74_1 *)state_in)->unk_9A + 1);
            D_80083460[5] = (u16) (D_80083460[5] + 1);
        }
        goto update_sprite;
jt_c41:
        effect_wait_frame = ((S_80171D74_1 *)state_in)->unk_96 + 1;
        ((S_80171D74_1 *)state_in)->unk_96 = effect_wait_frame;
        if ((s16) effect_wait_frame >= 0x3C) {
            tail_phase = ((S_80171D74_1 *)state_in)->unk_9A;
            ASM_KEEP(tail_phase);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            ((S_80171D74_1 *)state_in)->unk_96 = 0;
            goto advance_phase;
        }
        goto update_sprite;
jt_c45:
        if ((func_800F685C(phase, target_state) << 0x10) != 0) {
            ((S_80171D74_1 *)state_in)->unk_96 = 0U;
            ((S_80171D74_1 *)state_in)->unk_9A = (u8) (((S_80171D74_1 *)state_in)->unk_9A + 1);
            D_80083460[5] = (u16) (D_80083460[5] + 1);
        }
        goto update_motion;
jt_c46:
        finish_frame = ((S_80171D74_1 *)state_in)->unk_96 + 1;
        ((S_80171D74_1 *)state_in)->unk_96 = finish_frame;
        if ((s16) finish_frame >= 0x3C) {
            ((S_80171D74_1 *)state_in)->unk_96 = 0U;
            ((S_80171D74_1 *)state_in)->unk_9A = (u8) (((S_80171D74_1 *)state_in)->unk_9A + 1);
        }
        goto update_motion;
jt_c35:
update_motion:
        func_8016F79C(state_in, motion_in, sprite);
        goto update_height;
jt_c5:
jt_c12:
jt_c14:
jt_c18:
update_height:
    func_8016F5D8(state_in, motion_in, sprite);
    goto update_sprite;

jt_c42:
jt_c47:
        func_800945E8(D_800E3D7C[0], target_state);
        {
            s32 effect_arg_0;
            s32 effect_arg_1;
            s32 effect_arg_2;
            s32 effect_arg_3;
            ASM_SET(effect_arg_0);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            ASM_SET(effect_arg_1);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            ASM_SET(effect_arg_2);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            ASM_SET(effect_arg_3);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            func_800948BC(effect_arg_0, effect_arg_1, effect_arg_2, effect_arg_3);
        }
        D_80082E76[0] = 0x8000;
        func_80041094(6, 0, 0, 0, 0x8000);
        tail_phase = ((S_80171D74_1 *)state_in)->unk_9A;
advance_phase:
        ((S_80171D74_1 *)state_in)->unk_9A = (u8) (tail_phase + 1);
        goto update_sprite;
jt_c8:
jt_c23:
jt_c26:
jt_c27:
jt_c28:
jt_c29:
jt_c36:
jt_c37:
jt_c38:
jt_c39:
jt_c43:
jt_c44:
jt_c48:
update_sprite:
    if (D_80175D54[0] != 0) {
        sprite_dir = ((s32) (((S_80171D74_6 *)D_80083228)->unk_00 + (s16) owner_state->unk_2A.n + 0x100) >> 9) & 7;
        if (((S_80171D74_1 *)state_in)->unk_94 != sprite_dir) {
            func_80047738(sprite, *(((S_80171D74_5 *)sprite)->unk_2C.p2 + sprite_dir), ((S_80171D74_5 *)sprite)->unk_04);
            ((S_80171D74_1 *)state_in)->unk_94 = sprite_dir;
        }
        {
            u16 sprite_flags;
            if ((*(u8 *)((u8 *)D_8006CCF8 + sprite_dir)) != 0) {
                sprite_flags = ((S_80171D74_5 *)sprite)->unk_14 | 1;
            } else {
                sprite_flags = ((S_80171D74_5 *)sprite)->unk_14 & 0xFFFE;
            }
            ((S_80171D74_5 *)sprite)->unk_14 = sprite_flags;
        }
    }
    return;

}
