/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_80167C74_0_pre {
    u16 unk_00;
} S_80167C74_0_pre;   /* the 0x2 bytes before arg0 in func_80167C74, addressed as arg0[-1] */

typedef struct S_80167C74_0 {
    u8 pad_00[0x12];
    s16 unk_12;
    u8 pad_14[0x4];
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    void * unk_24;
    u8 pad_28[0x34];
    s32 unk_5C;
    s32 unk_60;
    s32 unk_64;
    s32 unk_68;
    s32 unk_6C;
    s32 unk_70;
} S_80167C74_0;   /* arg0 in func_80167C74 */

typedef struct S_80167C74_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80167C74_1;   /* temp_t1 in func_80167C74 */

typedef struct S_80167C74_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80167C74_2;   /* arg1 in func_80167C74 */


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

void func_80167C74(void *arg0, S_80167C74_2 *arg1, S_80167C74_11 *arg2) {
    void *self = arg0;
#define arg0 self
    u8 *var_v0;
    register u8 *table_join ASM_REG("$6");   /* MATCH pin: retail delay-slot fill depends on it */
    register u8 *clamp_base ASM_REG("$8");   /* MATCH pin: retail delay-slot fill depends on it */
    u8 *var_v0_2;   /* MATCH pin: keeps a constant in a register as retail does */
    s16 *temp_v1_3;
    s16 *temp_v1_4;
    s16 temp_v0_5;
    s16 temp_v1;
    s32 temp_v1_2;
    s32 scaled_z;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_6;
    register void *interp_call_a0 ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 temp_a2_2;
    register s32 interp_call_a2 ASM_REG("$6");   /* MATCH pin: retail delay-slot fill depends on it */
    s32 temp_a3;
    s32 temp_fp;
    s32 temp_s6;
    s32 temp_s7;
    s32 object_limit;
    s32 temp_t1_2;
    s32 temp_t2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a0_4;
    s32 var_a0_5;
    s32 var_a0_6;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a1_4;
    s32 var_a2;
    s32 var_a2_clamp;
    register s32 var_a2_4 ASM_REG("$6");   /* MATCH pin: retail delay-slot fill depends on it */
    s32 var_a3;
    s32 var_a3_2;
    s32 var_s0;
    register s32 var_s1 ASM_REG("$17");   /* MATCH pin: retail register colouring depends on it */
    register s32 var_s1_2 ASM_REG("$17");   /* MATCH pin: retail register colouring depends on it */
    register s32 var_s1_3 ASM_REG("$17");   /* MATCH pin: retail register colouring depends on it */
    s32 var_s2;
    s32 var_s3;
    register s32 var_s3_2 ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 var_s4;
    register s32 var_s4_2 ASM_REG("$20");   /* MATCH pin: keeps a constant in a register as retail does */
    register s32 var_t1 ASM_REG("$9");   /* MATCH pin: retail register colouring depends on it */
    register s32 var_t0_2 ASM_REG("$8");   /* MATCH pin: retail delay-slot fill depends on it */
    s32 var_t2;
    s32 var_t2_2;
    s32 var_t2_3;
    register s32 var_t3 ASM_REG("$11");   /* MATCH pin: retail register colouring depends on it */
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 clamp_row;
    register s32 clamp_index ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 clamp_min;
    u16 *temp_a1_2;
    u16 *var_a2_2;
    u16 *var_a3_3;
    u16 copy_value;
    s16 temp_v0;
    S_80167C74_15 *temp_a0_4;
    S_80167C74_17 *temp_a0_5;
    S_80167C74_4 *temp_a1_3;
    S_80167C74_5 *temp_a1_4;
    S_80167C74_6 *temp_a1_5;
    S_80167C74_7 *temp_a1_6;
    S_80167C74_8 *temp_a1_7;
    register u8 *temp_s2 ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    S_80167C74_1 *temp_t1;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    void *temp_v0_4;
    u8 *temp_v1_5;
    u8 *temp_v1_6;
    u8 *table_base;
    u8 *case_base;
    u8 *interp_base;
    u8 *copy_dst;
    u8 *copy_src;
    u8 *object_table_base;
    u8 *object_base;
    S_80167C74_16 *temp_v1_7;
    register u8 *var_a1_3 ASM_REG("$5");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register u8 *var_t0 ASM_REG("$8");   /* MATCH pin: retail delay-slot fill depends on it */
    s32 object_offset;
    register s32 object_copy_index ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */

    temp_v1 = ((S_80167C74_0 *)arg0)->unk_12;
    temp_t1 = ((S_80167C74_0 *)arg0)->unk_24;
    switch (temp_v1) {
    case 0:
        temp_a0 = ((S_80167C74_0 *)arg0)->unk_60;
        var_a2 = 0;
        ((S_80167C74_0 *)arg0)->unk_5C = (s32) ((((S_80167C74_0 *)arg0)->unk_5C * 4) / 5);
        temp_v1_2 = ((S_80167C74_0 *)arg0)->unk_1C;
        ((S_80167C74_0 *)arg0)->unk_60 = (s32) ((temp_a0 * 4) / 5);
        ((S_80167C74_0 *)arg0)->unk_64 = (s32) ((((S_80167C74_0 *)arg0)->unk_64 * 4) / 5);
        if (temp_v1_2 == 0) var_a2 = 0x46;
        if (temp_v1_2 == 1) var_a2 = 0x32;
        if (temp_v1_2 == 2) var_a2 = 0x1E;
        var_v0 = (u8 *)0x80170000;
        if (var_a2 >= ((S_80167C74_0 *)arg0)->unk_18) {
            ((S_80167C74_0 *)arg0)->unk_12 = (s16) ((u16) ((S_80167C74_0 *)arg0)->unk_12 + 1);
            case_base = (u8 *)D_80175DD8;
            ((S_80167C74_0 *)arg0)->unk_68 = (s32) ((s32) ((temp_t1->unk_00 - (((S_80167C74_0 *)arg0)->unk_5C * 0x14)) - (arg1->unk_00 + (*(s16 *)(case_base + (((S_80167C74_0 *)arg0)->unk_1C * 0x60)) << 0x11))) >> 7);
            ((S_80167C74_0 *)arg0)->unk_6C = (s32) ((s32) ((temp_t1->unk_04 - (((S_80167C74_0 *)arg0)->unk_60 * 0x14)) - (arg1->unk_04 + (*(s16 *)((((S_80167C74_0 *)arg0)->unk_1C * 0x60) + case_base + 2) << 0x11))) >> 7);
            scaled_z = (((S_80167C74_0 *)arg0)->unk_64 * 0x14) + 0x200000;
            ((S_80167C74_0 *)arg0)->unk_70 = (s32) ((s32) ((temp_t1->unk_08 - scaled_z) - (arg1->unk_08 + (*(s16 *)((((S_80167C74_0 *)arg0)->unk_1C * 0x60) + case_base + 4) << 0x11))) >> 7);
            ((S_80167C74_0 *)arg0)->unk_1E = 0U;
            goto block_base;
        }
        break;
    case 1:
        temp_v0 = ((S_80167C74_0 *)arg0)->unk_1E + 1;
        ((S_80167C74_0 *)arg0)->unk_1E = temp_v0;
        if (temp_v0 == 0xC) {
            func_80167A98(arg0, arg1, arg2);
            D_800814A8->unk_10C = (u16) (D_800814A8->unk_10C | 1);
            D_800814A8->unk_6A = (s16) (D_800814A8->unk_2A.as_u16 + 0x800);
            func_800419EC(6, 0xC, D_800814A8);
            func_800A56E0(0x601);
        }
        if ((s16) ((S_80167C74_0 *)arg0)->unk_1E >= 0x10) {
            ((S_80167C74_0 *)arg0)->unk_18 = 0;
        }
        ((S_80167C74_0 *)arg0)->unk_5C = (s32) (((S_80167C74_0 *)arg0)->unk_5C + ((S_80167C74_0 *)arg0)->unk_68);
        ((S_80167C74_0 *)arg0)->unk_60 = (s32) (((S_80167C74_0 *)arg0)->unk_60 + ((S_80167C74_0 *)arg0)->unk_6C);
        ((S_80167C74_0 *)arg0)->unk_64 = (s32) (((S_80167C74_0 *)arg0)->unk_64 + ((S_80167C74_0 *)arg0)->unk_70);
        goto block_base;
    default:
        var_v0 = (u8 *)D_80175DD8;
        goto block_18;
    }

block_base:
    var_v0 = (u8 *)D_80175DD8;
block_18:
    table_join = var_v0;
    var_a0 = ((S_80167C74_0 *)arg0)->unk_5C;
    temp_a1_2 = (u16 *)((((S_80167C74_0 *)arg0)->unk_1C * 0x60) + (s32)table_join);
    if (var_a0 < 0) var_a0 += 0xFFFF;
    *temp_a1_2 += var_a0 >> 0x10;
    var_a0_2 = ((S_80167C74_0 *)arg0)->unk_60;
    temp_a1_3 = (void *)((((S_80167C74_0 *)arg0)->unk_1C * 0x60) + (s32)table_join);
    if (var_a0_2 < 0) var_a0_2 += 0xFFFF;
    temp_a1_3->unk_02 = (u16) (temp_a1_3->unk_02 + (var_a0_2 >> 0x10));
    var_a0_3 = ((S_80167C74_0 *)arg0)->unk_64;
    temp_a1_4 = (void *)((((S_80167C74_0 *)arg0)->unk_1C * 0x60) + (s32)table_join);
    if (var_a0_3 < 0) var_a0_3 += 0xFFFF;
    temp_a1_4->unk_04 = (u16) (temp_a1_4->unk_04 + (var_a0_3 >> 0x10));
    var_a0_4 = ((S_80167C74_0 *)arg0)->unk_5C;
    temp_a1_5 = (void *)((((S_80167C74_0 *)arg0)->unk_1C * 0x60) + (s32)table_join);
    if (var_a0_4 < 0) var_a0_4 += 0xFFFF;
    temp_a1_5->unk_06 = (u16) (temp_a1_5->unk_06 + (var_a0_4 >> 0x10));
    var_a0_5 = ((S_80167C74_0 *)arg0)->unk_60;
    temp_a1_6 = (void *)((((S_80167C74_0 *)arg0)->unk_1C * 0x60) + (s32)table_join);
    if (var_a0_5 < 0) var_a0_5 += 0xFFFF;
    temp_a1_6->unk_08 = (u16) (temp_a1_6->unk_08 + (var_a0_5 >> 0x10));
    var_a0_6 = ((S_80167C74_0 *)arg0)->unk_64;
    temp_a1_7 = (void *)((((S_80167C74_0 *)arg0)->unk_1C * 0x60) + (s32)table_join);
    if (var_a0_6 < 0) var_a0_6 += 0xFFFF;
    var_t2 = 0;
    clamp_base = table_join;
    var_t1 = 0x190;
    var_a3 = var_t2;
    temp_a1_7->unk_0A = (u16) (temp_a1_7->unk_0A + (var_a0_6 >> 0x10));
    do {
        var_a1 = 0;
        var_a2_clamp = var_a3;
loop_32:
        clamp_row = ((S_80167C74_0 *)arg0)->unk_1C;
        ASM_KEEP_NV(clamp_row);   /* MATCH pin: keeps a statement from moving across a call/branch */
        temp_a0_2 = var_a1 * 2;
        ASM_KEEP_NV(temp_a0_2);   /* MATCH pin: retail delay-slot fill depends on it */
        clamp_index = clamp_row * 0x60;
        clamp_index = clamp_index + (s32)clamp_base;
        clamp_index = var_a2_clamp + clamp_index;
        clamp_index = temp_a0_2 + clamp_index;
        temp_v1_3 = (s16 *)clamp_index;
        if (*temp_v1_3 >= 0x191) *temp_v1_3 = var_t1;
        clamp_row = ((S_80167C74_0 *)arg0)->unk_1C;
        clamp_index = clamp_row * 0x60;
        clamp_index = clamp_index + (s32)clamp_base;
        clamp_index = var_a2_clamp + clamp_index;
        clamp_index = temp_a0_2 + clamp_index;
        temp_v1_3 = (s16 *)clamp_index;
        if (*temp_v1_3 < -0x190) {
            clamp_min = -0x190;
            ASM_KEEP(clamp_min);   /* MATCH pin: keeps a statement from moving across a call/branch */
            *temp_v1_3 = clamp_min;
        }
        var_a1 += 1;
        if (var_a1 < 3) goto loop_32;
        var_t2 += 1;
        var_a3 += 6;
    } while (var_t2 < 2);
    var_s1 = 7;
    table_base = (u8 *)D_80175DD8;
    var_t1 = 0x54;
    do {
        var_t2_2 = 0;
        var_t0_2 = var_t1;
        var_a3_2 = var_t2_2;
loop_40:
        var_a1_2 = 0;
        var_a2_4 = var_a3_2;
loop_41:
        temp_a0_3 = var_a1_2 * 2;
        var_a1_2 += 1;
        temp_v0_2 = (u8 *)(var_t0_2 + ((((S_80167C74_0 *)arg0)->unk_1C * 0x60) + (s32)table_base));
        copy_dst = (u8 *)(var_a2_4 + (s32)temp_v0_2);
        temp_v0_2 -= 0xC;
        copy_src = (u8 *)(var_a2_4 + (s32)temp_v0_2);
        copy_value = *(u16 *)(temp_a0_3 + (s32)copy_src);
        temp_a0_3 += (s32)copy_dst;
        *(u16 *)temp_a0_3 = copy_value;
        if (var_a1_2 < 3) goto loop_41;
        var_t2_2 += 1;
        var_a3_2 += 6;
        if (var_t2_2 < 2) goto loop_40;
        var_s1 -= 1;
        var_t1 -= 0xC;
    } while (var_s1 > 0);
    var_s0 = 0xA;
    interp_base = (u8 *)D_80175DD8;
    temp_v0_3 = (((S_80167C74_0 *)arg0)->unk_1C * 0x60) + interp_base;
    temp_fp = (((S_80167C74_9 *)temp_v0_3)->unk_00 + ((S_80167C74_9 *)temp_v0_3)->unk_06) - (((S_80167C74_9 *)temp_v0_3)->unk_18 + ((S_80167C74_9 *)temp_v0_3)->unk_1E);
    temp_s7 = (((S_80167C74_9 *)temp_v0_3)->unk_02 + ((S_80167C74_9 *)temp_v0_3)->unk_08) - (((S_80167C74_9 *)temp_v0_3)->unk_1A + ((S_80167C74_9 *)temp_v0_3)->unk_20);
    temp_s6 = (((S_80167C74_9 *)temp_v0_3)->unk_04 + ((S_80167C74_9 *)temp_v0_3)->unk_0A) - (((S_80167C74_9 *)temp_v0_3)->unk_1C + ((S_80167C74_9 *)temp_v0_3)->unk_22);
    if (((S_80167C74_0 *)arg0)->unk_12 == 0) var_s0 = 3;
    var_s1_2 = 1;
    if (var_s1_2 < (var_s0 + 1)) {
        var_s4 = temp_s6;
        var_s3 = temp_s7;
        var_s2 = temp_fp;
        do {
            s32 interp_y0;
            s32 interp_y1;
            s32 interp_x1;
            s32 interp_z0;
            s32 interp_x0;
            s32 interp_z1;
            temp_a3 = var_s3 / var_s0;
            temp_t1_2 = var_s4 / var_s0;
            temp_t2 = var_s2 / var_s0;
            interp_call_a0 = arg0 - 0x20;
            interp_call_a2 = 0xA;
            ASM_KEEP_NV(interp_call_a2);   /* MATCH pin: retail schedule: same instructions, different order without it */
            var_s4 += temp_s6;
            var_s3 += temp_s7;
            var_s2 += temp_fp;
            var_s1_2 += 1;
            temp_v1_5 = (((S_80167C74_0 *)arg0)->unk_1C * 0x60) + (u8 *)D_80175DD8;
            interp_y0 = ((S_80167C74_10 *)temp_v1_5)->unk_1A;
            interp_y1 = ((S_80167C74_10 *)temp_v1_5)->unk_20;
            interp_x1 = ((S_80167C74_10 *)temp_v1_5)->unk_1E;
            interp_z0 = ((S_80167C74_10 *)temp_v1_5)->unk_1C;
            interp_x0 = ((S_80167C74_10 *)temp_v1_5)->unk_18;
            interp_z1 = ((S_80167C74_10 *)temp_v1_5)->unk_22;
            func_80165018(interp_call_a0, arg2->unk_0C.at00.v, interp_call_a2, (s16) (interp_x0 + interp_x1 + temp_t2), (s32) (s16) (interp_y0 + interp_y1 + temp_a3), (s32) (s16) (interp_z0 + interp_z1 + temp_t1_2));
        } while (var_s1_2 < (var_s0 + 1));
    }
    var_v0_2 = (u8 *)0x80170000;
    ASM_KEEP_NV(var_v0_2);   /* MATCH pin: keeps a constant in a register as retail does */
    object_table_base = var_v0_2 + 0x5DD8;
    temp_v1_6 = (u8 *)((((S_80167C74_0 *)arg0)->unk_1C * 0x60) + (s32)object_table_base);
    if ((((S_80167C74_12 *)temp_v1_6)->unk_00 != 0x190) && (((S_80167C74_12 *)temp_v1_6)->unk_02 != 0x190) && (((S_80167C74_12 *)temp_v1_6)->unk_04 != 0x190)) {
        var_s3_2 = 0;
        object_limit = 8;
        object_base = object_table_base;
        var_s4_2 = 0;
        do {
            temp_v0_4 = func_8003FC64(0x212);
            if (temp_v0_4 != NULL) {
                temp_s2 = temp_v0_4 + 0x20;
                ((S_80167C74_13 *)temp_s2)->unk_18 = 1;
                ((S_80167C74_13 *)temp_s2)->unk_1A = 1;
                ((S_80167C74_14 *)temp_v0_4)->unk_10 = &D_80167C30;
                func_8004491C(temp_v0_4, &D_80166D14);
                temp_a0_4 = ((S_80167C74_14 *)temp_v0_4)->unk_0C;
                temp_a0_4->unk_10 = 0x20;
                temp_a0_4->unk_14 = (u16) (temp_a0_4->unk_14 | 0xC);
                temp_v1_7 = ((S_80167C74_14 *)temp_v0_4)->unk_08;
                var_s1_3 = 0;
                temp_v1_7->unk_00 = (s32) arg1->unk_00;
                temp_a2_2 = object_limit - var_s3_2;
                temp_v1_7->unk_04 = (s32) arg1->unk_04;
                var_a1_3 = temp_s2;
                temp_v1_7->unk_08 = (s32) arg1->unk_08;
                temp_a0_5 = ((S_80167C74_14 *)temp_v0_4)->unk_0C;
                temp_a0_5->unk_1E = 0x1000;
                temp_a0_5->unk_1C = 0x1000;
                temp_a0_5->unk_0E = 0x80;
                temp_a0_5->unk_0D = 0x80;
                temp_a0_5->unk_0C = 0x80;
                do {
                    var_v0_3 = (u8) arg2->unk_0C.at00.v * temp_a2_2;
                    if (var_v0_3 < 0) var_v0_3 += 7;
                    ((S_80167C74_18 *)var_a1_3)->unk_00 = (s8) (var_v0_3 >> 3);
                    var_v0_4 = arg2->unk_0C.at01.v * temp_a2_2;
                    if (var_v0_4 < 0) var_v0_4 += 7;
                    ((S_80167C74_18 *)var_a1_3)->unk_01 = (s8) (var_v0_4 >> 3);
                    var_v0_5 = arg2->unk_0C.at02.v * temp_a2_2;
                    if (var_v0_5 < 0) var_v0_5 += 7;
                    ((S_80167C74_18 *)var_a1_3)->unk_02 = (s8) (var_v0_5 >> 3);
                    var_s1_3 += 1;
                    var_a1_3 += 4;
                } while (var_s1_3 < 4);
                temp_a0_5->unk_06 = 0;
                func_8003DB94(temp_a0_5, &D_800DEAE0, 0);
                var_t2_3 = 0;
                object_offset = var_s4_2;
                var_t0 = temp_s2;
                var_t3 = var_t2_3;
                do {
                    var_a1_4 = 0;
                    var_t1 = var_t3;
                    var_a3_3 = var_t0 + 0x80;
                    var_a2_2 = var_t0 + 0x74;
loop_64:
                    temp_a0_6 = var_a1_4 * 2;
                    *var_a2_2 = *(u16 *)(temp_a0_6 + (var_t1 + (object_offset + ((((S_80167C74_0 *)arg0)->unk_1C * 0x60) + (s32)object_base))));
                    var_a1_4 += 1;
                    var_a2_2 += 1;
                    object_copy_index = object_offset + ((((S_80167C74_0 *)arg0)->unk_1C * 0x60) + (s32)object_base);
                    object_copy_index += 0xC;
                    object_copy_index = var_t1 + object_copy_index;
                    temp_a0_6 += object_copy_index;
                    *var_a3_3 = *(u16 *)temp_a0_6;
                    var_a3_3 += 1;
                    if (var_a1_4 < 3) goto loop_64;
                    var_t0 += 6;
                    var_t2_3 += 1;
                    var_t3 += 6;
                } while (var_t2_3 < 2);
            }
            var_s3_2 += 1;
            var_s4_2 += 0xC;
        } while (var_s3_2 < 7);
    }
    temp_v0_5 = (u16) ((S_80167C74_0 *)arg0)->unk_18 - 1;
    ((S_80167C74_0 *)arg0)->unk_18 = temp_v0_5;
    if ((temp_v0_5 << 0x10) <= 0) {
        ((S_80167C74_0_pre *)arg0)[-1].unk_00 = (u16) (((S_80167C74_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
#undef arg0
