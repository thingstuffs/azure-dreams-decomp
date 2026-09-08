#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80024170_arg0.h"


typedef struct S_80025954_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0x24];
    s16 unk_88;
} S_80025954_1;   /* temp_s7 in func_80025954 */

typedef struct S_80025954_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_80025954_2;   /* arg2 in func_80025954 */

typedef struct S_80025954_3 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80025954_3;   /* temp_s0 in func_80025954 */

typedef struct S_80025954_4 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80025954_4;   /* temp_a1 in func_80025954 */

typedef struct S_80025954_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80025954_5;   /* arg1 in func_80025954 */

typedef struct S_80025954_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80025954_6;   /* temp_v1_2 in func_80025954 */

typedef struct S_80025954_7_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_80025954_7_pre;   /* the 0x18 bytes before temp_v0 in func_80025954, addressed as temp_v0[-1] */

typedef struct S_80025954_8 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_08;   /* overlapping accesses */
} S_80025954_8;   /* temp_a3 in func_80025954 */

typedef struct S_80025954_9 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x10];
    u8 unk_24;
    u8 unk_25;
} S_80025954_9;   /* temp_v1_4 in func_80025954 */

typedef struct S_80025954_10 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_80025954_10;   /* var_a2 in func_80025954 */

typedef struct S_80025954_11 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
} S_80025954_11;   /* call_a1 in func_80025954 */

typedef struct S_80025954_12 {
    s32 unk_00;
} S_80025954_12;   /* stack.motion in func_80025954 */

typedef struct S_80025954_13 {
    s32 unk_00;
} S_80025954_13;   /* &D_800814A0 in func_80025954 */

typedef struct S_80025954_14 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80025954_14;   /* ((S_80025954_3 *)temp_s0)->unk_0C in func_80025954 */

typedef struct S_80025954_15 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_80025954_15;   /* ((S_80025954_1 *)temp_s7)->unk_60 in func_80025954 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80024028[];
s32 func_80024170(); /* extern */
M2C_UNK func_80025874();         /* extern */
s32 func_8003DE58();     /* extern */
M2C_UNK func_8009CE1C(); /* extern */
s32 func_800A44E0();              /* extern */
s32 func_800A56E0();                     /* extern */
s16 func_800BCB04();                   /* extern */
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern M2C_UNK D_800814A0;
extern s32 D_8008346C;
extern u8 D_800DDC40[];

typedef struct LocalStack {
    u8 motion[0x18];
    u16 distance[4];
    u16 saved_y;
} LocalStack;

void func_80025954(void *arg0, void *arg1_in, void *arg2) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6 };
    LocalStack stack;
    s8 *var_a2;
    register s32 temp_a1_2 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 temp_v0_4;
    s32 temp_v1;
    register s32 temp_v1_6 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 var_a1;
    s16 var_a1_2;
    register s32 var_v0_4 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s16 var_v1;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_6;
    s32 temp_v1_5;
    s32 adjusted_z;
    s32 temp_z;
    s32 var_s3;
    s32 var_v0_2;
    s32 var_v0_3;
    u32 temp_v1_3;
    register s32 temp_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 temp_v0_5;
    s32 var_fp;
    s32 var_s4;
    s32 var_s5;
    void *temp_a1;
    void *temp_a3;
    void *temp_s0;
    register void *temp_s7 ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    void *temp_v0;
    void *temp_v1_2;
    void *temp_v1_4;
    register void *arg1 ASM_REG("$22") = arg1_in;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s16 *x_lookup_first;
    s16 *y_lookup_first;
    s16 *x_lookup_next;
    register s16 *y_lookup_next ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 height ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s16 *final_base ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s16 *final_ptr;
    register u32 saved_t0 ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *call_a1;

    temp_v1 = ((Rec_func_80024170_arg0 *)arg0)->unk_0A;
    temp_s7 = ((Rec_func_80024170_arg0 *)arg0)->unk_00;
    ((Rec_func_80024170_arg0 *)arg0)->unk_10 = (u16) (((Rec_func_80024170_arg0 *)arg0)->unk_10 + 1);
    if ((u32) temp_v1 >= 7U) {
        goto block_49;
    }
    (void)jt_keep; goto *D_80024028[(u32)(temp_v1)];
jt_c0:
    ((Rec_func_80024170_arg0 *)arg0)->unk_10 = 0U;
    ((Rec_func_80024170_arg0 *)arg0)->unk_0A = (s16) ((u16) ((Rec_func_80024170_arg0 *)arg0)->unk_0A + 1);
    ((Rec_func_80024170_arg0 *)arg0)->unk_0E = (u16) (((u16) ((S_80025954_1 *)temp_s7)->unk_2A >> 9) & 7);
    ((S_80025954_2 *)arg2)->unk_0C = 0x808080;
jt_c1:
    temp_s0 = temp_s7 - 0x20;
    temp_a1 = ((S_80025954_3 *)temp_s0)->unk_0C;
    if (func_8003DE58(((S_80025954_4 *)temp_a1)->unk_08, temp_a1, stack.distance, 0) != 0) {
        goto block_5;
    }
    if (!(((S_80025954_14 *)(((S_80025954_3 *)temp_s0)->unk_0C))->unk_14 & 0x8000)) {
        goto block_49;
    }
block_5:
    temp_v1_2 = ((S_80025954_3 *)temp_s0)->unk_08;
    ((S_80025954_5 *)arg1)->unk_00.at02.v = (u16) ((S_80025954_6 *)temp_v1_2)->unk_02;
    ((S_80025954_5 *)arg1)->unk_04.at02.v = (u16) ((S_80025954_6 *)temp_v1_2)->unk_06;
    temp_v1_3 = ((S_80025954_6 *)temp_v1_2)->unk_0A;
    ((S_80025954_5 *)arg1)->unk_08.at02.v = temp_v1_3;
    if (((S_80025954_14 *)(((S_80025954_3 *)temp_s0)->unk_0C))->unk_14 & 0x8000) {
        goto block_7;
    }
    ((S_80025954_5 *)arg1)->unk_00.at02.v = (u16) (((S_80025954_5 *)arg1)->unk_00.at02.v + stack.distance[0]);
    ((S_80025954_5 *)arg1)->unk_04.at02.v = (u16) (((S_80025954_5 *)arg1)->unk_04.at02.v + stack.distance[1]);
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    var_v0_4 = ((S_80025954_5 *)arg1)->unk_08.at02.v;
    temp_v1_6 = stack.distance[2];
    var_v0_4 += temp_v1_6;
    goto block_8;
block_7:
    var_v0_4 = temp_v1_3 - 0x40;
block_8:
    ((S_80025954_5 *)arg1)->unk_08.at02.v = var_v0_4;
    if (!(*((Rec_func_80024170_arg0 *)arg0)->unk_04 & 0x80)) {
        goto block_49;
    }
    temp_v0 = ((S_80025954_1 *)temp_s7)->unk_60;
    var_s3 = 1;
    if (temp_v0 == NULL) {
        goto block_23;
    }
    temp_a3 = ((S_80025954_7_pre *)temp_v0)[-1].unk_00;
    var_a1 = ((S_80025954_8 *)temp_a3)->unk_00.at02.v;
    var_a1 -= ((S_80025954_5 *)arg1)->unk_00.at02u.v;
    if (var_a1 >= 0) {
        goto block_12;
    }
    var_a1 = 0 - var_a1;
block_12:
    stack.distance[0] = (u16) var_a1;
    var_v0_4 = ((S_80025954_8 *)temp_a3)->unk_04.at02.v;
    var_v0_2 = ((S_80025954_5 *)arg1)->unk_04.at02u.v;
    ASM_CLOBBER("$6");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    var_a2 = (s8 *) &stack.motion[2];
    ASM_KEEP(var_a2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    var_v0_4 -= var_v0_2;
    if (var_v0_4 >= 0) {
        goto block_14;
    }
    var_v0_4 = 0 - var_v0_4;
block_14:
    stack.distance[1] = (u16) var_v0_4;
    temp_v1_4 = ((S_80025954_1 *)temp_s7)->unk_60;
    temp_v1_6 = D_800DDC40[((S_80025954_9 *)temp_v1_4)->unk_13] << 0x10;
    var_v0_4 = ((S_80025954_8 *)temp_a3)->unk_08.at02.v - temp_v1_6;
    temp_v1_6 = ((S_80025954_5 *)arg1)->unk_08.at02u.v;
    temp_v1_6 += 0x300000;
    var_v0_4 -= temp_v1_6;
    if (var_v0_4 >= 0) {
        goto block_16;
    }
    var_v0_4 = 0 - var_v0_4;
block_16:
    stack.distance[2] = (u16) var_v0_4;
    ((Rec_func_80024170_arg0 *)arg0)->unk_12.as_s16 = var_a1;
loop_17:
    if (((S_80025954_10 *)var_a2)->unk_18 <= ((Rec_func_80024170_arg0 *)arg0)->unk_12.as_s16) {
        goto block_19;
    }
    ((Rec_func_80024170_arg0 *)arg0)->unk_12.as_s16 = (s16) (u16) ((S_80025954_10 *)var_a2)->unk_18;
block_19:
    var_s3 += 1;
    var_a2 += 2;
    if (var_s3 < 3) {
        goto loop_17;
    }
    temp_v0_2 = (s32) ((u16) ((Rec_func_80024170_arg0 *)arg0)->unk_12.as_s16 << 0x10) >> 0x14;
    ((Rec_func_80024170_arg0 *)arg0)->unk_12.as_s16 = (s16) temp_v0_2;
    if (temp_v0_2 != 0) {
        goto block_22;
    }
    ((Rec_func_80024170_arg0 *)arg0)->unk_12.as_s16 = 1;
block_22:
    var_v0_4 = ((S_80025954_8 *)temp_a3)->unk_00.at00.v;
    temp_a0 = ((S_80025954_5 *)arg1)->unk_00.at00.v;
    var_v0_4 -= temp_a0;
    var_v0_4 /= ((Rec_func_80024170_arg0 *)arg0)->unk_12.as_s16;
    temp_a0 = ((S_80025954_5 *)arg1)->unk_04.at00.v;
    ((S_80025954_5 *)arg1)->unk_0C = var_v0_4;
    var_v0_4 = ((S_80025954_8 *)temp_a3)->unk_04.at00.v - temp_a0;
    var_v0_4 /= ((Rec_func_80024170_arg0 *)arg0)->unk_12.as_s16;
    ((S_80025954_5 *)arg1)->unk_10 = var_v0_4;
    temp_v1_4 = ((S_80025954_1 *)temp_s7)->unk_60;
    var_v0_4 = D_800DDC40[((S_80025954_9 *)temp_v1_4)->unk_13] << 0x10;
    temp_v1_6 = ((S_80025954_8 *)temp_a3)->unk_08.at00.v - var_v0_4;
    var_v0_4 = ((S_80025954_5 *)arg1)->unk_08.at00.v;
    var_v0_4 += 0x300000;
    temp_v1_6 -= var_v0_4;
    temp_v1_6 /= ((Rec_func_80024170_arg0 *)arg0)->unk_12.as_s16;
    call_a1 = arg1;
    ASM_KEEP(call_a1);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    ((S_80025954_11 *)call_a1)->unk_14 = temp_v1_6;
    ASM_JALDELAY_PIN(temp_v1_6);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    func_80024170(arg0, call_a1, var_a2, temp_a3);
    var_v0_4 = (u16) ((Rec_func_80024170_arg0 *)arg0)->unk_0A + 1;
    goto block_48;
block_23:
    var_s3 = 0;
    temp_v1_4 = ((S_80025954_3 *)temp_s0)->unk_0C;
    ASM_KEEP(temp_v1_4);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    var_v0_4 = 0x80070000;
    ASM_KEEP(var_v0_4);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    var_s4 = ((S_80025954_9 *)temp_v1_4)->unk_24;
    var_s5 = ((S_80025954_9 *)temp_v1_4)->unk_25;
    var_fp = var_s4;
    stack.saved_y = (u16) var_s5;
loop_24:
    if ((func_800A44E0(((s16) var_s4 << 6) & 0xFFC0, ((s16) var_s5 << 6) & 0xFFC0, ((S_80025954_1 *)temp_s7)->unk_88, (s16) (((Rec_func_80024170_arg0 *)arg0)->unk_0E << 9)) << 0x10) != 0) {
        goto block_28;
    }
    {
        register s16 *lookup_base ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
        lookup_base = D_8006CCD8;
#else
        lookup_base = (s16 *) 0x80070000U;
        ASM_KEEP(lookup_base);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        lookup_base = (s16 *) ((u8 *) lookup_base - 0x3328);
#endif
        temp_v0_3 = (s16) ((Rec_func_80024170_arg0 *)arg0)->unk_0E;
        height = (u16) ((S_80025954_1 *)temp_s7)->unk_88;
        x_lookup_first = (s16 *) ((temp_v0_3 << 1) + (u32) lookup_base);
        ASM_KEEP(x_lookup_first);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    }
    height = (s16) (height - 0x20);
    {
        register s16 *lookup_base ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
        lookup_base = D_8006CCE8;
#else
        lookup_base = (s16 *) 0x80070000U;
        ASM_KEEP(lookup_base);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        lookup_base = (s16 *) ((u8 *) lookup_base - 0x3318);
#endif
        y_lookup_first = (s16 *) ((temp_v0_3 << 1) + (u32) lookup_base);
        ASM_KEEP(y_lookup_first);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    }
    temp_v0_4 = func_800BCB04(((((s16) var_s4 + *x_lookup_first) << 6) + 0x20) & 0xFFE0, ((((s16) var_s5 + *y_lookup_first) << 6) + 0x20) & 0xFFE0, height);
    ASM_CLOBBER("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_CLOBBER("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    temp_a3 = stack.motion;
    if (temp_v0_4 >= 0x201) {
        goto block_29;
    }
    if ((s16) (temp_v0_4 - (u16) ((S_80025954_1 *)temp_s7)->unk_88) < -0x3F) {
        goto block_29;
    }
    {
        register s16 *lookup_base ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
        lookup_base = D_8006CCD8;
#else
        lookup_base = (s16 *) 0x80070000U;
        ASM_KEEP(lookup_base);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        lookup_base = (s16 *) ((u8 *) lookup_base - 0x3328);
#endif
        temp_v1_5 = (s16) ((Rec_func_80024170_arg0 *)arg0)->unk_0E;
        var_s3 += 1;
        x_lookup_next = (s16 *) ((temp_v1_5 << 1) + (u32) lookup_base);
    }
    {
        register s16 *lookup_base ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
        lookup_base = D_8006CCE8;
#else
        lookup_base = (s16 *) 0x80070000U;
        ASM_KEEP(lookup_base);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        lookup_base = (s16 *) ((u8 *) lookup_base - 0x3318);
#endif
        y_lookup_next = (s16 *) ((temp_v1_5 << 1) + (u32) lookup_base);
        ASM_KEEP(y_lookup_next);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    }
    temp_a0 = var_s4 + (u16) *x_lookup_next;
    var_s4 = temp_a0;
    ASM_KEEP_NV(var_s4);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    var_v0_4 = var_s5 + (u16) *y_lookup_next;
    var_s5 = var_v0_4;
    stack.saved_y = (u16) var_v0_4;
    var_fp = temp_a0;
    if (var_s3 < 8) {
        goto loop_24;
    }
block_28:
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    temp_a3 = stack.motion;
block_29:
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    temp_v1_6 = (u32) var_fp << 0x10;
    final_base = D_8006CCD8;
    temp_v1_6 >>= 0xA;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    var_v0_4 = (s16) ((Rec_func_80024170_arg0 *)arg0)->unk_0E;
    var_v0_4 <<= 1;
    final_ptr = (s16 *) ((u8 *) final_base + var_v0_4);
    final_base = D_8006CCE8;
    var_v0_4 = *final_ptr;
    var_v0_4 = (var_v0_4 + 1) << 5;
    temp_v1_6 += var_v0_4;
    ((S_80025954_8 *)temp_a3)->unk_00.at02.v = temp_v1_6;
    temp_v1_6 = (u32) temp_v1_6 << 0x10;
    saved_t0 = stack.saved_y;
    var_v0_4 = (s16) ((Rec_func_80024170_arg0 *)arg0)->unk_0E;
    temp_a1_2 = (u32) saved_t0 << 0x10;
    var_v0_4 <<= 1;
    final_ptr = (s16 *) ((u8 *) final_base + var_v0_4);
    var_v0_4 = *final_ptr;
    temp_a1_2 >>= 0xA;
    var_v0_4 = (var_v0_4 + 1) << 5;
    temp_a1_2 += var_v0_4;
    ((S_80025954_8 *)temp_a3)->unk_04.at02.v = temp_a1_2;
    var_v0_4 = ((S_80025954_5 *)arg1)->unk_08.at02.v;
    temp_v1_6 >>= 0x10;
    ((S_80025954_8 *)temp_a3)->unk_08.at02u.v = var_v0_4;
    var_v0_4 = ((S_80025954_5 *)arg1)->unk_00.at02u.v;
    ASM_KEEP_DEP_NV(temp_a1_2, var_v0_4);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    temp_a1_2 = (u32) temp_a1_2 << 0x10;
    ASM_KEEP(temp_a1_2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    temp_v1_6 -= var_v0_4;
    if (temp_v1_6 >= 0) {
        goto block_31;
    }
    temp_v1_6 = 0 - temp_v1_6;
block_31:
    stack.distance[0] = temp_v1_6;
    var_v0_4 = ((S_80025954_5 *)arg1)->unk_04.at02u.v;
    temp_a1_2 >>= 0x10;
    temp_a1_2 -= var_v0_4;
    if (temp_a1_2 >= 0) {
        goto block_33;
    }
    temp_a1_2 = 0 - temp_a1_2;
block_33:
    stack.distance[1] = temp_a1_2;
    ((Rec_func_80024170_arg0 *)arg0)->unk_12.as_s16 = temp_v1_6;
    if ((s16) stack.distance[1] <= (s16) temp_v1_6) {
        goto block_35;
    }
    ((Rec_func_80024170_arg0 *)arg0)->unk_12.as_s16 = (s16) (u16) stack.distance[1];
block_35:
    var_v0_4 = (s32) ((u16) ((Rec_func_80024170_arg0 *)arg0)->unk_12.as_s16 << 0x10) >> 0x14;
    ((Rec_func_80024170_arg0 *)arg0)->unk_12.as_s16 = (s16) var_v0_4;
    if (var_v0_4 != 0) {
        goto block_37;
    }
    ((Rec_func_80024170_arg0 *)arg0)->unk_12.as_s16 = 1;
block_37:
    var_v0_4 = ((S_80025954_12 *)(stack.motion))->unk_00;
    temp_a0 = ((S_80025954_5 *)arg1)->unk_00.at00.v;
    var_v0_4 -= temp_a0;
    var_v0_4 /= ((Rec_func_80024170_arg0 *)arg0)->unk_12.as_s16;
    temp_a0 = ((S_80025954_5 *)arg1)->unk_04.at00.v;
    ((S_80025954_5 *)arg1)->unk_0C = var_v0_4;
    var_v0_4 = ((S_80025954_8 *)temp_a3)->unk_04.at00.v - temp_a0;
    var_v0_4 /= ((Rec_func_80024170_arg0 *)arg0)->unk_12.as_s16;
    call_a1 = arg1;
    ((S_80025954_11 *)call_a1)->unk_14 = 0;
    ((S_80025954_11 *)call_a1)->unk_10 = var_v0_4;
    ASM_JALDELAY_PIN(var_v0_4);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    func_80024170(arg0, call_a1);
    var_v0_4 = 6;
    goto block_48;
jt_c2:
    ((S_80025954_5 *)arg1)->unk_00.at00.v = (s32) (((S_80025954_5 *)arg1)->unk_00.at00.v + ((S_80025954_5 *)arg1)->unk_0C);
    ((S_80025954_5 *)arg1)->unk_04.at00.v = (s32) (((S_80025954_5 *)arg1)->unk_04.at00.v + ((S_80025954_5 *)arg1)->unk_10);
    ((S_80025954_5 *)arg1)->unk_08.at00.v = (s32) (((S_80025954_5 *)arg1)->unk_08.at00.v + ((S_80025954_5 *)arg1)->unk_14);
    if ((s16) ((Rec_func_80024170_arg0 *)arg0)->unk_10 < ((Rec_func_80024170_arg0 *)arg0)->unk_12.as_s16) {
        goto block_49;
    }
    func_80025874(arg0, arg1, ((S_80025954_15 *)(((S_80025954_1 *)temp_s7)->unk_60))->unk_88);
    func_800A56E0(0x300);
    goto block_44;
jt_c3:
    if ((s16) ((Rec_func_80024170_arg0 *)arg0)->unk_10 >= 8) {
        goto block_44;
    }
    ((Rec_func_80024170_arg0 *)arg0)->unk_14 = 0;
    return;
jt_c4:
    if ((s16) ((Rec_func_80024170_arg0 *)arg0)->unk_10 < 0x44) {
        goto block_49;
    }
    func_8009CE1C(((S_80025954_1 *)temp_s7)->unk_60, 0x18, ((Rec_func_80024170_arg0 *)arg0)->unk_09, 1, (s32) (s16) (((Rec_func_80024170_arg0 *)arg0)->unk_0E << 9), temp_s7, 1);
block_44:
    ((Rec_func_80024170_arg0 *)arg0)->unk_10 = 0U;
    ((Rec_func_80024170_arg0 *)arg0)->unk_0A = (s16) ((u16) ((Rec_func_80024170_arg0 *)arg0)->unk_0A + 1);
    goto block_49;
jt_c5:
    if (((Rec_func_80024170_arg0 *)arg0)->unk_14 != 0) {
        goto block_49;
    }
    D_8008346C = 0;
    (*(u16 *)((u8 *)arg0 + -2)) = (u16) ((*(u16 *)((u8 *)arg0 + -2)) | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (((S_80025954_13 *)(&D_800814A0))->unk_00 | 0x8000);
    goto block_49;
jt_c6:
    ((S_80025954_5 *)arg1)->unk_00.at00.v = (s32) (((S_80025954_5 *)arg1)->unk_00.at00.v + ((S_80025954_5 *)arg1)->unk_0C);
    ((S_80025954_5 *)arg1)->unk_04.at00.v = (s32) (((S_80025954_5 *)arg1)->unk_04.at00.v + ((S_80025954_5 *)arg1)->unk_10);
    ((S_80025954_5 *)arg1)->unk_08.at00.v = (s32) (((S_80025954_5 *)arg1)->unk_08.at00.v + ((S_80025954_5 *)arg1)->unk_14);
    if ((s16) ((Rec_func_80024170_arg0 *)arg0)->unk_10 < ((Rec_func_80024170_arg0 *)arg0)->unk_12.as_s16) {
        goto block_49;
    }
    var_v0_4 = 5;
block_48:
    ((Rec_func_80024170_arg0 *)arg0)->unk_0A = var_v0_4;
    ((Rec_func_80024170_arg0 *)arg0)->unk_10 = 0U;
block_49:
    ((Rec_func_80024170_arg0 *)arg0)->unk_14 = 0;
    return;
}
