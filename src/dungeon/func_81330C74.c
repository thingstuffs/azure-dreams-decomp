/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800814A8.h"
#include "records/Rec_func_80167A98_arg0.h"
#include "records/Rec_func_80167A98_arg1.h"

typedef struct S_80167C74_0_pre {
    u16 unk_00;
} S_80167C74_0_pre;   /* the 0x2 bytes before arg0 in func_80167C74, addressed as arg0[-1] */


typedef struct S_80167C74_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80167C74_1;   /* temp_t1 in func_80167C74 */



typedef struct S_80167C74_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80167C74_4;   /* temp_a1_3 in func_80167C74 */

typedef struct S_80167C74_5 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80167C74_5;   /* temp_a1_4 in func_80167C74 */

typedef struct S_80167C74_6 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_80167C74_6;   /* temp_a1_5 in func_80167C74 */

typedef struct S_80167C74_7 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_80167C74_7;   /* temp_a1_6 in func_80167C74 */

typedef struct S_80167C74_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80167C74_8;   /* temp_a1_7 in func_80167C74 */

typedef struct S_80167C74_9 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    u8 pad_0C[0xC];
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    s16 unk_22;
} S_80167C74_9;   /* temp_v0_3 in func_80167C74 */

typedef struct S_80167C74_10 {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    s16 unk_22;
} S_80167C74_10;   /* temp_v1_5 in func_80167C74 */

typedef struct S_80167C74_11 {
    u8 pad_00[0xC];
    union { struct { s32 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
} S_80167C74_11;   /* arg2 in func_80167C74 */

typedef struct S_80167C74_12 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
} S_80167C74_12;   /* temp_v1_6 in func_80167C74 */

typedef struct S_80167C74_13 {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
} S_80167C74_13;   /* temp_s2 in func_80167C74 */

typedef struct S_80167C74_14 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80167C74_14;   /* temp_v0_4 in func_80167C74 */

typedef struct S_80167C74_15 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_80167C74_15;   /* temp_a0_4 in func_80167C74 */

typedef struct S_80167C74_16 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80167C74_16;   /* temp_v1_7 in func_80167C74 */

typedef struct S_80167C74_17 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_80167C74_17;   /* temp_a0_5 in func_80167C74 */

typedef struct S_80167C74_18 {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
} S_80167C74_18;   /* var_a1_3 in func_80167C74 */


typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad[0x5A];
} PositionTableEntry;

void func_8003DB94();
void *func_8003FC64();
void func_800419EC();
M2C_UNK func_8004491C();
M2C_UNK func_800A56E0();
M2C_UNK func_80165018();
M2C_UNK func_80167A98();
extern s32 D_800814A0[3];
extern Rec_D_800814A8 *D_800814A8;
extern M2C_UNK D_800DEAE0;
extern M2C_UNK D_80166D14;
extern M2C_UNK D_80167C30;
extern PositionTableEntry D_80175DD8[];

/* Update trail motion, emit interpolated particles, and build fading trail segments. */
void func_80167C74(void *effect_data, Rec_func_80167A98_arg1 *origin, S_80167C74_11 *color) {
    void *self = effect_data;
    u8 *motion_table;
    register u8 *table_join ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register u8 *clamp_base ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    u8 *table_page;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s16 *clamp_coord;
    s16 life_left;
    s16 phase;
    s32 trail_index;
    s32 scaled_z;
    s32 velocity_y;
    s32 clamp_axis_offset;
    s32 copy_axis_offset;
    s32 object_axis_offset;
    register void *effect_object ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 color_weight;
    register s32 particle_life ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 step_y;
    s32 delta_x;
    s32 delta_z;
    s32 delta_y;
    s32 object_limit;
    s32 step_z;
    s32 step_x;
    s32 move_x0;
    s32 move_y0;
    s32 move_z0;
    s32 move_x1;
    s32 move_y1;
    s32 move_z1;
    s32 clamp_axis;
    s32 copy_axis;
    s32 object_axis;
    s32 phase_threshold;
    s32 clamp_pair_offset;
    register s32 copy_pair_offset ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 clamp_pair_stride;
    s32 copy_pair_stride;
    s32 particle_count;
    register s32 history_index ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 particle_index ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 color_index ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 sum_x;
    s32 sum_y;
    register s32 object_index ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 sum_z;
    register s32 history_offset ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 limit_or_offset ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 copy_row_offset ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 clamp_pair;
    s32 copy_pair;
    s32 object_pair;
    register s32 object_pair_offset ASM_REG("$11");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 scaled_red;
    s32 scaled_green;
    s32 scaled_blue;
    s32 clamp_row;
    register s32 clamp_index ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 clamp_min;
    u16 *pos_x0;
    u16 *object_pos;
    u16 *object_prev_pos;
    u16 copy_value;
    s16 phase_tick;
    S_80167C74_15 *object_flags;
    S_80167C74_17 *object_render;
    S_80167C74_4 *pos_y0;
    S_80167C74_5 *pos_z0;
    S_80167C74_6 *pos_x1;
    S_80167C74_7 *pos_y1;
    S_80167C74_8 *pos_z1;
    register u8 *object_data ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_80167C74_1 *target_pos;
    u8 *copy_row;
    u8 *trail_row;
    void *object;
    u8 *interp_row;
    u8 *head_pos;
    u8 *table_base;
    u8 *case_base;
    u8 *interp_base;
    u8 *copy_dst;
    u8 *copy_src;
    u8 *object_table_base;
    u8 *object_base;
    S_80167C74_16 *object_origin;
    register u8 *vertex_color ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register u8 *object_pair_data ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 object_offset;
    register s32 object_copy_index ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

    phase = ((Rec_func_80167A98_arg0 *)self)->unk_12;
    target_pos = ((Rec_func_80167A98_arg0 *)self)->unk_24;
    switch (phase) {
    case 0:
        velocity_y = ((Rec_func_80167A98_arg0 *)self)->unk_60;
        phase_threshold = 0;
        ((Rec_func_80167A98_arg0 *)self)->unk_5C = (s32) ((((Rec_func_80167A98_arg0 *)self)->unk_5C * 4) / 5);
        trail_index = ((Rec_func_80167A98_arg0 *)self)->unk_1C;
        ((Rec_func_80167A98_arg0 *)self)->unk_60 = (s32) ((velocity_y * 4) / 5);
        ((Rec_func_80167A98_arg0 *)self)->unk_64 = (s32) ((((Rec_func_80167A98_arg0 *)self)->unk_64 * 4) / 5);
        if (trail_index == 0) phase_threshold = 0x46;
        if (trail_index == 1) phase_threshold = 0x32;
        if (trail_index == 2) phase_threshold = 0x1E;
        motion_table = (u8 *)0x80170000;
        if (phase_threshold >= ((Rec_func_80167A98_arg0 *)self)->unk_18) {
            ((Rec_func_80167A98_arg0 *)self)->unk_12 = (s16) ((u16) ((Rec_func_80167A98_arg0 *)self)->unk_12 + 1);
            case_base = (u8 *)D_80175DD8;
            ((Rec_func_80167A98_arg0 *)self)->unk_68 = (s32) ((s32) ((target_pos->unk_00 - (((Rec_func_80167A98_arg0 *)self)->unk_5C * 0x14)) - (origin->unk_00 + (*(s16 *)(case_base + (((Rec_func_80167A98_arg0 *)self)->unk_1C * 0x60)) << 0x11))) >> 7);
            ((Rec_func_80167A98_arg0 *)self)->unk_6C = (s32) ((s32) ((target_pos->unk_04 - (((Rec_func_80167A98_arg0 *)self)->unk_60 * 0x14)) - (origin->unk_04 + (*(s16 *)((((Rec_func_80167A98_arg0 *)self)->unk_1C * 0x60) + case_base + 2) << 0x11))) >> 7);
            scaled_z = (((Rec_func_80167A98_arg0 *)self)->unk_64 * 0x14) + 0x200000;
            ((Rec_func_80167A98_arg0 *)self)->unk_70 = (s32) ((s32) ((target_pos->unk_08 - scaled_z) - (origin->unk_08 + (*(s16 *)((((Rec_func_80167A98_arg0 *)self)->unk_1C * 0x60) + case_base + 4) << 0x11))) >> 7);
            ((Rec_func_80167A98_arg0 *)self)->unk_1E = 0U;
            goto load_motion_table;
        }
        break;
    case 1:
        phase_tick = ((Rec_func_80167A98_arg0 *)self)->unk_1E + 1;
        ((Rec_func_80167A98_arg0 *)self)->unk_1E = phase_tick;
        if (phase_tick == 0xC) {
            func_80167A98(self, origin, color);
            D_800814A8->unk_10C = (u16) (D_800814A8->unk_10C | 1);
            D_800814A8->unk_6A = (s16) (D_800814A8->unk_2A.as_u16 + 0x800);
            func_800419EC(6, 0xC, D_800814A8);
            func_800A56E0(0x601);
        }
        if ((s16) ((Rec_func_80167A98_arg0 *)self)->unk_1E >= 0x10) {
            ((Rec_func_80167A98_arg0 *)self)->unk_18 = 0;
        }
        ((Rec_func_80167A98_arg0 *)self)->unk_5C = (s32) (((Rec_func_80167A98_arg0 *)self)->unk_5C + ((Rec_func_80167A98_arg0 *)self)->unk_68);
        ((Rec_func_80167A98_arg0 *)self)->unk_60 = (s32) (((Rec_func_80167A98_arg0 *)self)->unk_60 + ((Rec_func_80167A98_arg0 *)self)->unk_6C);
        ((Rec_func_80167A98_arg0 *)self)->unk_64 = (s32) (((Rec_func_80167A98_arg0 *)self)->unk_64 + ((Rec_func_80167A98_arg0 *)self)->unk_70);
        goto load_motion_table;
    default:
        motion_table = (u8 *)D_80175DD8;
        goto update_positions;
    }

load_motion_table:
    motion_table = (u8 *)D_80175DD8;
update_positions:
    table_join = motion_table;
    move_x0 = ((Rec_func_80167A98_arg0 *)self)->unk_5C;
    pos_x0 = (u16 *)((((Rec_func_80167A98_arg0 *)self)->unk_1C * 0x60) + (s32)table_join);
    if (move_x0 < 0) move_x0 += 0xFFFF;
    *pos_x0 += move_x0 >> 0x10;
    move_y0 = ((Rec_func_80167A98_arg0 *)self)->unk_60;
    pos_y0 = (void *)((((Rec_func_80167A98_arg0 *)self)->unk_1C * 0x60) + (s32)table_join);
    if (move_y0 < 0) move_y0 += 0xFFFF;
    pos_y0->unk_02 = (u16) (pos_y0->unk_02 + (move_y0 >> 0x10));
    move_z0 = ((Rec_func_80167A98_arg0 *)self)->unk_64;
    pos_z0 = (void *)((((Rec_func_80167A98_arg0 *)self)->unk_1C * 0x60) + (s32)table_join);
    if (move_z0 < 0) move_z0 += 0xFFFF;
    pos_z0->unk_04 = (u16) (pos_z0->unk_04 + (move_z0 >> 0x10));
    move_x1 = ((Rec_func_80167A98_arg0 *)self)->unk_5C;
    pos_x1 = (void *)((((Rec_func_80167A98_arg0 *)self)->unk_1C * 0x60) + (s32)table_join);
    if (move_x1 < 0) move_x1 += 0xFFFF;
    pos_x1->unk_06 = (u16) (pos_x1->unk_06 + (move_x1 >> 0x10));
    move_y1 = ((Rec_func_80167A98_arg0 *)self)->unk_60;
    pos_y1 = (void *)((((Rec_func_80167A98_arg0 *)self)->unk_1C * 0x60) + (s32)table_join);
    if (move_y1 < 0) move_y1 += 0xFFFF;
    pos_y1->unk_08 = (u16) (pos_y1->unk_08 + (move_y1 >> 0x10));
    move_z1 = ((Rec_func_80167A98_arg0 *)self)->unk_64;
    pos_z1 = (void *)((((Rec_func_80167A98_arg0 *)self)->unk_1C * 0x60) + (s32)table_join);
    if (move_z1 < 0) move_z1 += 0xFFFF;
    clamp_pair = 0;
    clamp_base = table_join;
    limit_or_offset = 0x190;
    clamp_pair_stride = clamp_pair;
    pos_z1->unk_0A = (u16) (pos_z1->unk_0A + (move_z1 >> 0x10));
    do {
        clamp_axis = 0;
        clamp_pair_offset = clamp_pair_stride;
clamp_axes:
        clamp_row = ((Rec_func_80167A98_arg0 *)self)->unk_1C;
        ASM_KEEP_NV(clamp_row);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        clamp_axis_offset = clamp_axis * 2;
        ASM_KEEP_NV(clamp_axis_offset);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        clamp_index = clamp_row * 0x60;
        clamp_index = clamp_index + (s32)clamp_base;
        clamp_index = clamp_pair_offset + clamp_index;
        clamp_index = clamp_axis_offset + clamp_index;
        clamp_coord = (s16 *)clamp_index;
        if (*clamp_coord >= 0x191) *clamp_coord = limit_or_offset;
        clamp_row = ((Rec_func_80167A98_arg0 *)self)->unk_1C;
        clamp_index = clamp_row * 0x60;
        clamp_index = clamp_index + (s32)clamp_base;
        clamp_index = clamp_pair_offset + clamp_index;
        clamp_index = clamp_axis_offset + clamp_index;
        clamp_coord = (s16 *)clamp_index;
        if (*clamp_coord < -0x190) {
            clamp_min = -0x190;
            ASM_KEEP(clamp_min);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            *clamp_coord = clamp_min;
        }
        clamp_axis += 1;
        if (clamp_axis < 3) goto clamp_axes;
        clamp_pair += 1;
        clamp_pair_stride += 6;
    } while (clamp_pair < 2);
    history_index = 7;
    table_base = (u8 *)D_80175DD8;
    limit_or_offset = 0x54;
    do {
        copy_pair = 0;
        copy_row_offset = limit_or_offset;
        copy_pair_stride = copy_pair;
copy_pairs:
        copy_axis = 0;
        copy_pair_offset = copy_pair_stride;
copy_axes:
        copy_axis_offset = copy_axis * 2;
        copy_axis += 1;
        copy_row = (u8 *)(copy_row_offset + ((((Rec_func_80167A98_arg0 *)self)->unk_1C * 0x60) + (s32)table_base));
        copy_dst = (u8 *)(copy_pair_offset + (s32)copy_row);
        copy_row -= 0xC;
        copy_src = (u8 *)(copy_pair_offset + (s32)copy_row);
        copy_value = *(u16 *)(copy_axis_offset + (s32)copy_src);
        copy_axis_offset += (s32)copy_dst;
        *(u16 *)copy_axis_offset = copy_value;
        if (copy_axis < 3) goto copy_axes;
        copy_pair += 1;
        copy_pair_stride += 6;
        if (copy_pair < 2) goto copy_pairs;
        history_index -= 1;
        limit_or_offset -= 0xC;
    } while (history_index > 0);
    particle_count = 0xA;
    interp_base = (u8 *)D_80175DD8;
    trail_row = (((Rec_func_80167A98_arg0 *)self)->unk_1C * 0x60) + interp_base;
    delta_x = (((S_80167C74_9 *)trail_row)->unk_00 + ((S_80167C74_9 *)trail_row)->unk_06) - (((S_80167C74_9 *)trail_row)->unk_18 + ((S_80167C74_9 *)trail_row)->unk_1E);
    delta_y = (((S_80167C74_9 *)trail_row)->unk_02 + ((S_80167C74_9 *)trail_row)->unk_08) - (((S_80167C74_9 *)trail_row)->unk_1A + ((S_80167C74_9 *)trail_row)->unk_20);
    delta_z = (((S_80167C74_9 *)trail_row)->unk_04 + ((S_80167C74_9 *)trail_row)->unk_0A) - (((S_80167C74_9 *)trail_row)->unk_1C + ((S_80167C74_9 *)trail_row)->unk_22);
    if (((Rec_func_80167A98_arg0 *)self)->unk_12 == 0) particle_count = 3;
    particle_index = 1;
    if (particle_index < (particle_count + 1)) {
        sum_z = delta_z;
        sum_y = delta_y;
        sum_x = delta_x;
        do {
            s32 interp_y0;
            s32 interp_y1;
            s32 interp_x1;
            s32 interp_z0;
            s32 interp_x0;
            s32 interp_z1;
            step_y = sum_y / particle_count;
            step_z = sum_z / particle_count;
            step_x = sum_x / particle_count;
            effect_object = self - 0x20;
            particle_life = 0xA;
            ASM_KEEP_NV(particle_life);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            sum_z += delta_z;
            sum_y += delta_y;
            sum_x += delta_x;
            particle_index += 1;
            interp_row = (((Rec_func_80167A98_arg0 *)self)->unk_1C * 0x60) + (u8 *)D_80175DD8;
            interp_y0 = ((S_80167C74_10 *)interp_row)->unk_1A;
            interp_y1 = ((S_80167C74_10 *)interp_row)->unk_20;
            interp_x1 = ((S_80167C74_10 *)interp_row)->unk_1E;
            interp_z0 = ((S_80167C74_10 *)interp_row)->unk_1C;
            interp_x0 = ((S_80167C74_10 *)interp_row)->unk_18;
            interp_z1 = ((S_80167C74_10 *)interp_row)->unk_22;
            func_80165018(effect_object, color->unk_0C.at00.v, particle_life, (s16) (interp_x0 + interp_x1 + step_x), (s32) (s16) (interp_y0 + interp_y1 + step_y), (s32) (s16) (interp_z0 + interp_z1 + step_z));
        } while (particle_index < (particle_count + 1));
    }
    table_page = (u8 *)0x80170000;
    ASM_KEEP_NV(table_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    object_table_base = table_page + 0x5DD8;
    head_pos = (u8 *)((((Rec_func_80167A98_arg0 *)self)->unk_1C * 0x60) + (s32)object_table_base);
    if ((((S_80167C74_12 *)head_pos)->unk_00 != 0x190) && (((S_80167C74_12 *)head_pos)->unk_02 != 0x190) && (((S_80167C74_12 *)head_pos)->unk_04 != 0x190)) {
        object_index = 0;
        object_limit = 8;
        object_base = object_table_base;
        history_offset = 0;
        do {
            object = func_8003FC64(0x212);
            if (object != NULL) {
                object_data = object + 0x20;
                ((S_80167C74_13 *)object_data)->unk_18 = 1;
                ((S_80167C74_13 *)object_data)->unk_1A = 1;
                ((S_80167C74_14 *)object)->unk_10 = &D_80167C30;
                func_8004491C(object, &D_80166D14);
                object_flags = ((S_80167C74_14 *)object)->unk_0C;
                object_flags->unk_10 = 0x20;
                object_flags->unk_14 = (u16) (object_flags->unk_14 | 0xC);
                object_origin = ((S_80167C74_14 *)object)->unk_08;
                color_index = 0;
                object_origin->unk_00 = (s32) origin->unk_00;
                color_weight = object_limit - object_index;
                object_origin->unk_04 = (s32) origin->unk_04;
                vertex_color = object_data;
                object_origin->unk_08 = (s32) origin->unk_08;
                object_render = ((S_80167C74_14 *)object)->unk_0C;
                object_render->unk_1E = 0x1000;
                object_render->unk_1C = 0x1000;
                object_render->unk_0E = 0x80;
                object_render->unk_0D = 0x80;
                object_render->unk_0C = 0x80;
                do {
                    scaled_red = (u8) color->unk_0C.at00.v * color_weight;
                    if (scaled_red < 0) scaled_red += 7;
                    ((S_80167C74_18 *)vertex_color)->unk_00 = (s8) (scaled_red >> 3);
                    scaled_green = color->unk_0C.at01.v * color_weight;
                    if (scaled_green < 0) scaled_green += 7;
                    ((S_80167C74_18 *)vertex_color)->unk_01 = (s8) (scaled_green >> 3);
                    scaled_blue = color->unk_0C.at02.v * color_weight;
                    if (scaled_blue < 0) scaled_blue += 7;
                    ((S_80167C74_18 *)vertex_color)->unk_02 = (s8) (scaled_blue >> 3);
                    color_index += 1;
                    vertex_color += 4;
                } while (color_index < 4);
                object_render->unk_06 = 0;
                func_8003DB94(object_render, &D_800DEAE0, 0);
                object_pair = 0;
                object_offset = history_offset;
                object_pair_data = object_data;
                object_pair_offset = object_pair;
                do {
                    object_axis = 0;
                    limit_or_offset = object_pair_offset;
                    object_prev_pos = object_pair_data + 0x80;
                    object_pos = object_pair_data + 0x74;
copy_object_axes:
                    object_axis_offset = object_axis * 2;
                    *object_pos = *(u16 *)(object_axis_offset + (limit_or_offset + (object_offset + ((((Rec_func_80167A98_arg0 *)self)->unk_1C * 0x60) + (s32)object_base))));
                    object_axis += 1;
                    object_pos += 1;
                    object_copy_index = object_offset + ((((Rec_func_80167A98_arg0 *)self)->unk_1C * 0x60) + (s32)object_base);
                    object_copy_index += 0xC;
                    object_copy_index = limit_or_offset + object_copy_index;
                    object_axis_offset += object_copy_index;
                    *object_prev_pos = *(u16 *)object_axis_offset;
                    object_prev_pos += 1;
                    if (object_axis < 3) goto copy_object_axes;
                    object_pair_data += 6;
                    object_pair += 1;
                    object_pair_offset += 6;
                } while (object_pair < 2);
            }
            object_index += 1;
            history_offset += 0xC;
        } while (object_index < 7);
    }
    life_left = (u16) ((Rec_func_80167A98_arg0 *)self)->unk_18 - 1;
    ((Rec_func_80167A98_arg0 *)self)->unk_18 = life_left;
    if ((life_left << 0x10) <= 0) {
        ((S_80167C74_0_pre *)self)[-1].unk_00 = (u16) (((S_80167C74_0_pre *)self)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
