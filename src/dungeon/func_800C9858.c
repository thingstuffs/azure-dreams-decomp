#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CEFB8_0 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800CEFB8_0;   /* global_base in func_800CEFB8 */

typedef struct S_800CEFB8_1 {
    u8 pad_00[0x8];
    void * unk_08;
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_0C;   /* overlapping accesses */
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u16 unk_22;
} S_800CEFB8_1;   /* arg2_hold in func_800CEFB8 */

typedef struct S_800CEFB8_2 {
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
} S_800CEFB8_2;   /* arg1 in func_800CEFB8 */

typedef struct S_800CEFB8_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800CEFB8_3;   /* coeff_base in func_800CEFB8 */

typedef struct S_800CEFB8_4 {
    u8 pad_00[0xB8];
    volatile u16 unk_B8;
    volatile u16 unk_BA;
    u8 pad_BC[0x34];
    volatile u16 unk_F0;
    volatile u16 unk_F2;
    u8 pad_F4[0x14];
    volatile u16 unk_108;
    volatile u16 unk_10A;
} S_800CEFB8_4;   /* scratch in func_800CEFB8 */

typedef struct S_800CEFB8_5 {
    void * unk_00;
    u8 pad_04[0xB4];
    s16 unk_B8;
    u8 pad_BA[0xA];
    s16 unk_C4;
    s16 unk_C6;
    s16 unk_C8;
} S_800CEFB8_5;   /* temp_s7 in func_800CEFB8 */

typedef struct S_800CEFB8_6 {
    u8 unk_00;
} S_800CEFB8_6;   /* temp_s4 in func_800CEFB8 */

typedef struct S_800CEFB8_7 {
    u8 unk_00;
    volatile u8 unk_01;
    volatile u8 unk_02;
    u8 pad_03[0x4];
    u8 unk_07;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
} S_800CEFB8_7;   /* temp_s1 in func_800CEFB8 */

typedef struct S_800CEFB8_8_pre {
    s8 unk_00;
} S_800CEFB8_8_pre;   /* the 0x1 bytes before temp_s0 in func_800CEFB8, addressed as temp_s0[-1] */

typedef struct S_800CEFB8_8 {
    s32 unk_00;
    union { u16 u; s16 s; } unk_04;   /* accessed as both */
    u16 unk_06;
    s16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    union { s16 s16; u8 u8; } unk_10;   /* accessed as both */
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    union { struct { s16 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; } unk_18;   /* overlapping accesses */
    u8 pad_1A[0x2];
    union { u16 u; s16 s; } unk_1C;   /* accessed as both */
    u16 unk_1E;
    union { struct { s16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_20;   /* overlapping accesses */
} S_800CEFB8_8;   /* temp_s0 in func_800CEFB8 */

typedef struct S_800CEFB8_9 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800CEFB8_9;   /* ((S_800CEFB8_5 *)temp_s7)->unk_00 in func_800CEFB8 */


M2C_UNK func_80064840();
M2C_UNK func_800649A0();
M2C_UNK func_80064A40();
M2C_UNK func_80064BC0();
M2C_UNK func_80064CF0();
M2C_UNK func_80064D80();
s32 func_80065420();
M2C_UNK func_800654B0();
M2C_UNK func_80065820();
u16 func_80065F90();
M2C_UNK func_8006658C();
M2C_UNK func_800CF270();
M2C_UNK func_800CF31C();
M2C_UNK func_800CF390();
M2C_UNK func_800CF5C4();
M2C_UNK func_800CF5D8();
M2C_UNK func_800CF75C();
M2C_UNK func_800CF764();
M2C_UNK func_800CF7B4();
extern s32 D_8006CD30[];
extern s8 D_80083160[];

void func_800CEFB8(void *unused, void *arg1, void *arg2, s16 arg3, s32 arg4) {
    s32 temp_c4;
    s32 temp_c6;
    s32 temp_c8;
    s16 temp_v0_10;
    s16 temp_v0_5;
    s16 temp_v0_6;
    s16 temp_v0_7;
    s16 temp_v0_8;
    s16 temp_v0_9;
    s32 var_v1;
    s32 temp_a0;
    register s32 temp_a1_2 ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    s32 arg4_copy;
    s32 temp_v0;
    s32 a3x;
    s32 temp_v0_2;
    register s32 range_v0 ASM_REG("$2");   /* MATCH pin: retail basic-block layout depends on it */
    register s32 range_v1 ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 var_a0;
    s32 var_a1;
    s32 var_v1_2;
    s32 var_v1_3;
    u16 temp_f2;
    u16 call_f2;
    u16 call_ba;
    u16 call_f0;
    u16 call_b8;
    u16 second_coord;
    s32 first_result;
    s32 second_result;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u16 temp_v1_5;
    register u16 temp_10e ASM_REG("$2");   /* MATCH pin: retail basic-block layout depends on it */
    s32 continuation_flag;
    register s32 continuation_v0 ASM_REG("$2");   /* MATCH pin: retail basic-block layout depends on it */
    register u8 temp_a0_2 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    u8 temp_v1_3;
    u8 temp_v1_4;
    register u8 var_v0 ASM_REG("$2");   /* MATCH pin: retail basic-block layout depends on it */
    void *temp_a1_3;
    void *global_base;
    register u8 *global_page ASM_REG("$8") = (u8 *)0x80080000;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register u8 *scratch_base ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    register u8 *first_a1 ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    register u8 *first_a2 ASM_REG("$6");   /* MATCH pin: retail immediate-load split depends on it */
    u8 *second_a0;
    u8 *second_a3;
    void *temp_s0;
    void *temp_s1;
    register void *temp_s4 ASM_REG("$20");   /* MATCH pin: retail basic-block layout depends on it */
    void *temp_s7;
    void *s7_partner;
    s32 *coeff_base;
    void *var_s3;
    register void *arg2_hold ASM_REG("$21") = arg2;   /* MATCH pin: retail basic-block layout depends on it */
    register s16 arg3_hold ASM_REG("$17") = arg3;   /* MATCH pin: retail schedule: same instructions, different order without it */
    s16 color_a3 = arg3;
    s32 arg4_hold = arg4;
    register u32 page_color;
    u8 *scratch;
    scratch_base = (u8 *)0x1F800000;
    first_a1 = scratch_base;
    first_a1 = (u8 *)((u32)first_a1 | 0xB8);
    first_a2 = scratch_base;
    ASM_KEEP_MEM_NV(first_a1, *(u8 **)D_80083160);   /* MATCH pin: retail schedule: same instructions, different order without it */
    scratch = scratch_base;
    ASM_KEEP_NV(arg4_hold);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    global_base = *(void **)D_80083160;
    ASM_KEEP_DEP_NV(first_a2, global_base);   /* MATCH pin: load-bearing for the whole function shape */
    first_a2 = (u8 *)((u32)first_a2 | 0x90);
    ASM_KEEP_NV(arg3_hold);   /* MATCH pin: keeps a statement from moving across a call/branch */

#define SP8(off) M2C_FIELD(scratch, u8 *, (off))
#define SPS8(off) M2C_FIELD(scratch, s8 *, (off))
#define SP16(off) M2C_FIELD(scratch, u16 *, (off))
#define SPS16(off) M2C_FIELD(scratch, s16 *, (off))
#define SP32(off) M2C_FIELD(scratch, s32 *, (off))
#define SPA(off) ((void *)(scratch + (off)))

    SP32(0xEC) = 0;
    SP16(0x8C) = 0;
    SP16(0x84) = 0;
    SP16(0x7C) = 0;
    SP16(0x74) = 0;
    SP32(0x20) = global_base + 0xB0;
    var_s3 = ((S_800CEFB8_0 *)global_base)->unk_8D0;
    ((S_800CEFB8_1 *)arg2_hold)->unk_14 = (u16) (((S_800CEFB8_1 *)arg2_hold)->unk_14 | 0x8000);
    ASM_KEEP_MEMDEP(arg2_hold, page_color, *(u8 **)D_80083160);   /* MATCH pin: keeps a statement from moving across a call/branch */
    ASM_SET(global_page);   /* MATCH pin: retail delay-slot fill depends on it */
    ASM_KEEP(color_a3);   /* MATCH pin: retail register colouring depends on it */
    SP16(0x00) = (u16) ((S_800CEFB8_2 *)arg1)->unk_02;
    SP16(0x02) = (u16) ((S_800CEFB8_2 *)arg1)->unk_06;
    temp_s7 = global_page + 0x3160;
    s7_partner = temp_s7;
    SP16(0x04) = (u16) ((S_800CEFB8_2 *)arg1)->unk_0A;
    first_result = func_80065420(scratch_base,
                                 first_a1,
                                 first_a2,
                                 (void *)0x1F800094);
    ASM_KEEP_NV(scratch);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    second_a0 = scratch;
    ASM_KEEP_NV(second_a0);   /* MATCH pin: keeps a statement from moving across a call/branch */
    first_a1 = second_a0;
    ASM_KEEP_NV(first_a1);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    first_a1 = (u8 *)((u32)first_a1 | 0xF0);
    first_a2 = second_a0;
    SP32(0xC0) = first_result;
    second_coord = ((S_800CEFB8_2 *)arg1)->unk_0E;
    ASM_KEEP_DEP_NV(first_a2, second_coord);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    first_a2 = (u8 *)((u32)first_a2 | 0x90);
    SP16(0x00) = second_coord;
    second_coord = ((S_800CEFB8_2 *)arg1)->unk_12;
    ASM_KEEP_DEP_NV(second_a0, second_coord);   /* MATCH pin: retail schedule: same instructions, different order without it */
    second_a3 = second_a0;
    ASM_KEEP_NV(second_a3);   /* MATCH pin: load-bearing for the whole function shape */
    SP16(0x02) = second_coord;
    second_coord = ((S_800CEFB8_2 *)arg1)->unk_16;
    second_a3 = (u8 *)((u32)second_a3 | 0x94);
    SP16(0x04) = second_coord;
    second_result = func_80065420(second_a0, first_a1, first_a2, second_a3);
    call_f2 = SP16(0xF2);
    call_ba = SP16(0xBA);
    call_f0 = SP16(0xF0);
    call_b8 = SP16(0xB8);
    SP32(0xC0) = (s32)(SP32(0xC0) + second_result) >> 1;
    SP16(0x10E) = func_80065F90((s16)call_f2 - (s16)call_ba,
                                (s16)call_f0 - (s16)call_b8,
                                (s16)call_f0);
    {
        register u8 *coeff_page ASM_REG("$3") = (u8 *)0x80070000;   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        ASM_KEEP_NV(coeff_page);   /* MATCH pin: retail immediate-load split depends on it */
        coeff_base = (s32 *)(coeff_page - 0x32D0);
    }
    a3x = arg3_hold;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_v0 = SP32(0xC0);
    ((S_800CEFB8_3 *)coeff_base)->unk_1C = (s32) (temp_v0 * 4);
    temp_v0_2 = temp_v0 - a3x;
    SP32(0xC0) = temp_v0_2;
    if ((u32) temp_v0_2 < 0x1E0U) {
        arg4_copy = arg4_hold;
        ASM_KEEP(arg4_copy);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        func_800649A0();
        range_v0 = ((S_800CEFB8_4 *)scratch)->unk_B8;
        range_v1 = ((S_800CEFB8_4 *)scratch)->unk_BA;
        range_v0 -= 0xA0;
        ((S_800CEFB8_4 *)scratch)->unk_B8 = range_v0;
        range_v0 = ((S_800CEFB8_4 *)scratch)->unk_F0;
        range_v1 -= 0x78;
        ((S_800CEFB8_4 *)scratch)->unk_BA = range_v1;
        range_v0 -= 0xA0;
        ((S_800CEFB8_4 *)scratch)->unk_F0 = range_v0;
        range_v0 = ((S_800CEFB8_4 *)scratch)->unk_F2;
        temp_c4 = ((S_800CEFB8_5 *)temp_s7)->unk_C4;
        temp_c6 = ((S_800CEFB8_5 *)temp_s7)->unk_C6;
        temp_c8 = ((S_800CEFB8_5 *)temp_s7)->unk_C8;
        range_v0 -= 0x78;
        ((S_800CEFB8_4 *)scratch)->unk_F2 = range_v0;
        SP32(0x30) = temp_c4;
        SP32(0x34) = temp_c6;
        SP32(0x38) = temp_c8;
        SP16(0x100) = (u16) ((S_800CEFB8_1 *)arg2_hold)->unk_16;
        var_v1 = (((S_800CEFB8_1 *)arg2_hold)->unk_1A - temp_c6) + ((S_800CEFB8_5 *)temp_s7)->unk_B8;
        if (((u32)arg4_hold << 0x10) == 0) {
            ASM_KEEP(arg4_hold);   /* MATCH pin: load-bearing for the whole function shape */
            temp_10e = SP16(0x10E);
            var_v1 += (s16)temp_10e;
        }
        {
            register void *call_a0 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
            register u8 *call_a1 ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
            s32 f18;
            call_a0 = (void *)0x1F800100;
            SP16(0x104) = var_v1;
            f18 = ((S_800CEFB8_1 *)arg2_hold)->unk_18;
            SP16(0x102) = (s16) ((((u16) SP32(0x38) + 0x100) & 0x1FF) + (s16) (f18 - 0x100));
            call_a1 = (u8 *)0x1F800000;
            ASM_KEEP(call_a1);   /* MATCH pin: retail keeps a computation the compiler would drop */
            temp_v0_3 = ((S_800CEFB8_1 *)arg2_hold)->unk_20;
            call_a1 = (u8 *)((u32)call_a1 | 0xD0);
            SP32(0xE4) = (s32) temp_v0_3;
            SP16(0x108) = temp_v0_3;
            temp_v0_4 = ((S_800CEFB8_1 *)arg2_hold)->unk_22;
            temp_s0 = var_s3 + 4;
            SP32(0xE8) = (s32) temp_v0_4;
            SP16(0x10A) = temp_v0_4;
            func_80065820(call_a0, call_a1);
        }
        {
            s32 bc_field1c;
            s32 bc_field1e;
            s32 bc_scale;
            bc_field1c = ((S_800CEFB8_1 *)arg2_hold)->unk_1C;
            SP32(0x30) = bc_field1c;
            bc_field1e = ((S_800CEFB8_1 *)arg2_hold)->unk_1E;
            bc_scale = 0x1000;
            SP32(0x38) = bc_scale;
            SP32(0x34) = bc_field1e;
            func_80064BC0((void *)0x1F8000D0, (void *)0x1F800030);
        }
        func_80064840(coeff_base, (void *)0x1F8000D0, (void *)0x1F800050);
        func_80064D80((void *)0x1F800050);
        func_80064CF0((void *)0x1F800050);
        temp_s4 = ((S_800CEFB8_1 *)arg2_hold)->unk_08;
        temp_s1 = temp_s4 + 1;
        SP16(0x24) = (u16) ((S_800CEFB8_1 *)arg2_hold)->unk_14;
entry_loop:
        if (!(((S_800CEFB8_6 *)temp_s4)->unk_00 & 0x20)) {
            SP32(0x08) = (s32) ((S_800CEFB8_7 *)temp_s1)->unk_07;
            SP32(0x0C) = (s32) ((S_800CEFB8_7 *)temp_s1)->unk_08;
            SP32(0x10) = (s32) ((S_800CEFB8_7 *)temp_s1)->unk_09;
            SP32(0x14) = (s32) ((S_800CEFB8_7 *)temp_s1)->unk_0A;
            {
                s16 val_v0;
                u16 axis_adjust;
                s32 axis_extent;
                if ((((S_800CEFB8_6 *)temp_s4)->unk_00 ^ SP16(0x24)) & 1) {
                    val_v0 = (s8) ((S_800CEFB8_7 *)temp_s1)->unk_01;
                    axis_adjust = ((S_800CEFB8_4 *)scratch)->unk_108;
                    axis_extent = (u16) SP32(0x10);
                    val_v0 = -val_v0 - axis_adjust;
                    SP16(0x80) = val_v0;
                    SP16(0x70) = val_v0;
                    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
                    val_v0 -= axis_extent;
                    goto axis_x_join;
                }
                val_v0 = (s8) ((S_800CEFB8_7 *)temp_s1)->unk_01;
                axis_adjust = ((S_800CEFB8_4 *)scratch)->unk_108;
                axis_extent = (u16) SP32(0x10);
                val_v0 -= axis_adjust;
                SP16(0x80) = val_v0;
                SP16(0x70) = val_v0;
                ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
                val_v0 += axis_extent;
axis_x_join:
                SP16(0x88) = val_v0;
                SP16(0x78) = val_v0;
            }
            {
                s16 val_v0;
                u16 axis_adjust;
                s32 axis_extent;
                if ((((S_800CEFB8_6 *)temp_s4)->unk_00 ^ SP16(0x24)) & 2) {
                    val_v0 = (s8) ((S_800CEFB8_7 *)temp_s1)->unk_02;
                    axis_adjust = ((S_800CEFB8_4 *)scratch)->unk_10A;
                    axis_extent = (u16) SP32(0x14);
                    val_v0 = -val_v0 - axis_adjust;
                    SP16(0x7A) = val_v0;
                    SP16(0x72) = val_v0;
                    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
                    val_v0 -= axis_extent;
                    goto axis_y_join;
                }
                val_v0 = (s8) ((S_800CEFB8_7 *)temp_s1)->unk_02;
                axis_adjust = ((S_800CEFB8_4 *)scratch)->unk_10A;
                axis_extent = (u16) SP32(0x14);
                val_v0 -= axis_adjust;
                SP16(0x7A) = val_v0;
                SP16(0x72) = val_v0;
                ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
                val_v0 += axis_extent;
axis_y_join:
                SP16(0x8A) = val_v0;
                SP16(0x82) = val_v0;
                ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            }
            func_800654B0(SPA(0x70), SPA(0x78), SPA(0x80), SPA(0x88),
                         var_s3 + 8, var_s3 + 0x10, var_s3 + 0x18,
                         var_s3 + 0x20, SPA(0x90), SPA(0x94));
            if (((u32)arg4_copy << 0x10) != 0) {
                if ((SP16(0xBA) << 0x10) < (SP16(0xF2) << 0x10)) {
                    ((S_800CEFB8_8 *)temp_s0)->unk_04.u = (u16) (((S_800CEFB8_8 *)temp_s0)->unk_04.u + SP16(0xB8));
                    ((S_800CEFB8_8 *)temp_s0)->unk_0C = (u16) (((S_800CEFB8_8 *)temp_s0)->unk_0C + SP16(0xB8));
                    ((S_800CEFB8_8 *)temp_s0)->unk_06 = (u16) (((S_800CEFB8_8 *)temp_s0)->unk_06 + SP16(0xBA));
                    ((S_800CEFB8_8 *)temp_s0)->unk_0E = (u16) (((S_800CEFB8_8 *)temp_s0)->unk_0E + SP16(0xBA));
                    ((S_800CEFB8_8 *)temp_s0)->unk_14 = (u16) (((S_800CEFB8_8 *)temp_s0)->unk_14 + SP16(0xF0));
                    ((S_800CEFB8_8 *)temp_s0)->unk_1C.u = (u16) (((S_800CEFB8_8 *)temp_s0)->unk_1C.u + SP16(0xF0));
                    ((S_800CEFB8_8 *)temp_s0)->unk_16 = (u16) (((S_800CEFB8_8 *)temp_s0)->unk_16 + SP16(0xF2));
                    func_800CF5C4();
                    return;
                }
                ((S_800CEFB8_8 *)temp_s0)->unk_14 = (u16) (((S_800CEFB8_8 *)temp_s0)->unk_14 + SP16(0xB8));
                ((S_800CEFB8_8 *)temp_s0)->unk_1C.u = (u16) (((S_800CEFB8_8 *)temp_s0)->unk_1C.u + SP16(0xB8));
                ((S_800CEFB8_8 *)temp_s0)->unk_16 = (u16) (((S_800CEFB8_8 *)temp_s0)->unk_16 + SP16(0xBA));
                ((S_800CEFB8_8 *)temp_s0)->unk_1E = (u16) (((S_800CEFB8_8 *)temp_s0)->unk_1E + SP16(0xBA));
                ((S_800CEFB8_8 *)temp_s0)->unk_04.u = (u16) (((S_800CEFB8_8 *)temp_s0)->unk_04.u + SP16(0xF0));
                ((S_800CEFB8_8 *)temp_s0)->unk_0C = (u16) (((S_800CEFB8_8 *)temp_s0)->unk_0C + SP16(0xF0));
                ((S_800CEFB8_8 *)temp_s0)->unk_06 = (u16) (((S_800CEFB8_8 *)temp_s0)->unk_06 + SP16(0xF2));
                ((S_800CEFB8_8 *)temp_s0)->unk_0E = (u16) (((S_800CEFB8_8 *)temp_s0)->unk_0E + SP16(0xF2));
                func_800CF5D8();
                return;
            }
            ((S_800CEFB8_8 *)temp_s0)->unk_14 = (u16) (((S_800CEFB8_8 *)temp_s0)->unk_14 + SP16(0xB8));
            ((S_800CEFB8_8 *)temp_s0)->unk_16 = (u16) (((S_800CEFB8_8 *)temp_s0)->unk_16 + SP16(0xBA));
            ((S_800CEFB8_8 *)temp_s0)->unk_0C = (u16) (((S_800CEFB8_8 *)temp_s0)->unk_0C + SP16(0xF0));
            ((S_800CEFB8_8 *)temp_s0)->unk_0E = (u16) (((S_800CEFB8_8 *)temp_s0)->unk_0E + SP16(0xF2));
            ((S_800CEFB8_8 *)temp_s0)->unk_04.u = (u16) (((S_800CEFB8_8 *)temp_s0)->unk_04.u + SP16(0xB8));
            ((S_800CEFB8_8 *)temp_s0)->unk_06 = (u16) (((S_800CEFB8_8 *)temp_s0)->unk_06 + SP16(0xBA));
            ((S_800CEFB8_8 *)temp_s0)->unk_1C.u = (u16) (((S_800CEFB8_8 *)temp_s0)->unk_1C.u + SP16(0xF0));
            ((S_800CEFB8_8 *)temp_s0)->unk_1E = (u16) (((S_800CEFB8_8 *)temp_s0)->unk_1E + SP16(0xF2));
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            var_a1 = 0;
            if ((u32) ((((S_800CEFB8_8 *)temp_s0)->unk_04.u + 0x20) & 0xFFFF) < 0x181U) {
                range_v0 = (((S_800CEFB8_8 *)temp_s0)->unk_06 + 0x20) & 0xFFFF;
                var_a1 = (u32) range_v0 < 0x121U;
            }
            var_v1_2 = 0;
            if ((u32) ((((S_800CEFB8_8 *)temp_s0)->unk_0C + 0x20) & 0xFFFF) < 0x181U) {
                range_v0 = (((S_800CEFB8_8 *)temp_s0)->unk_0E + 0x20) & 0xFFFF;
                var_v1_2 = (u32) range_v0 < 0x121U;
            }
            var_a0 = 0;
            temp_a1_2 = var_a1 | var_v1_2;
            if ((u32) ((((S_800CEFB8_8 *)temp_s0)->unk_14 + 0x20) & 0xFFFF) < 0x181U) {
                range_v0 = (((S_800CEFB8_8 *)temp_s0)->unk_16 + 0x20) & 0xFFFF;
                var_a0 = (u32) range_v0 < 0x121U;
            }
            var_v1_3 = 0;
            temp_a0 = temp_a1_2 | var_a0;
            if ((u32) ((((S_800CEFB8_8 *)temp_s0)->unk_1C.u + 0x20) & 0xFFFF) < 0x181U) {
                range_v0 = (((S_800CEFB8_8 *)temp_s0)->unk_1E + 0x20) & 0xFFFF;
                var_v1_3 = (u32) range_v0 < 0x121U;
            }
            range_v0 = temp_a0 | var_v1_3;
            if (range_v0 != 0) {
                ((S_800CEFB8_8_pre *)temp_s0)[-1].unk_00 = 9;
                ((S_800CEFB8_1 *)arg2_hold)->unk_14 = (u16) (((S_800CEFB8_1 *)arg2_hold)->unk_14 & 0x7FFF);
                range_v0 = SP32(0x10);
                range_v1 = SP32(0x08);
                range_v0 -= 1;
                range_v1 = range_v0 + range_v1;
                SP32(0x10) = range_v1;
                if (range_v1 & 0x100) {
                    range_v0 = range_v1 - 1;
                    SP32(0x10) = range_v0;
                }
                range_v0 = SP32(0x14);
                range_v1 = SP32(0x0C);
                range_v0 -= 1;
                range_v1 = range_v0 + range_v1;
                SP32(0x14) = range_v1;
                if (range_v1 & 0x100) {
                    range_v0 = range_v1 - 1;
                    SP32(0x14) = range_v0;
                }
                SP32(0x14) <<= 8;
                SP32(0x0C) <<= 8;
                continuation_flag = ((S_800CEFB8_1 *)arg2_hold)->unk_12;
                if (continuation_flag != 0) {
                    if (SP16(0x24) & 0x100) {
                        ((S_800CEFB8_8 *)temp_s0)->unk_0A = continuation_flag;
                        func_800CF764(temp_a0, temp_a1_2);
                        return;
                    }
                    continuation_v0 = (*(u16 *)((u8 *)temp_s1 + 5));
                    continuation_v0 = continuation_flag + continuation_v0;
                    ASM_TAILSLOT_PIN(continuation_v0);
                    func_800CF75C(temp_a0, temp_a1_2);
                    return;
                }
                ((S_800CEFB8_8 *)temp_s0)->unk_0A = (u16) (*(u16 *)((u8 *)temp_s1 + 5));
                ((S_800CEFB8_8 *)temp_s0)->unk_08 = (s16) ((u16) SP32(0x0C) + (u16) SP32(0x08));
                ((S_800CEFB8_8 *)temp_s0)->unk_10.s16 = (s16) ((u16) SP32(0x0C) + (u16) SP32(0x10));
                continuation_flag = ((S_800CEFB8_1 *)arg2_hold)->unk_10;
                if (continuation_flag != 0) {
                    continuation_v0 = (*(u16 *)((u8 *)temp_s1 + 3));
                    continuation_v0 &= 0xFF9F;
                    continuation_v0 = continuation_flag + continuation_v0;
                    ASM_TAILSLOT_PIN(continuation_v0);
                    func_800CF7B4(temp_a0, temp_a1_2);
                    return;
                }
                ((S_800CEFB8_8 *)temp_s0)->unk_12 = (u16) (*(u16 *)((u8 *)temp_s1 + 3));
                {
                    s32 field_4;
                    register u16 packed_y ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                    register u16 pack_a0 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
                    ((S_800CEFB8_8 *)temp_s0)->unk_18.at00.v = (s16) (SP16(0x14) | SP16(0x08));
                    field_4 = ((S_800CEFB8_8 *)temp_s0)->unk_04.s;
                    packed_y = SP16(0x14);
                    pack_a0 = SP16(0x10);
                    packed_y |= pack_a0;
                    ((S_800CEFB8_8 *)temp_s0)->unk_20.at00.v = (s16) packed_y;
                    if (((S_800CEFB8_8 *)temp_s0)->unk_1C.s < field_4) {
                        temp_v1_3 = ((S_800CEFB8_8 *)temp_s0)->unk_20.at00u.v;
                        ((S_800CEFB8_8 *)temp_s0)->unk_20.at00u.v = (u8) (temp_v1_3 + 0xFF);
                        ((S_800CEFB8_8 *)temp_s0)->unk_10.u8 = temp_v1_3;
                    }
                }
                if ((s16) ((S_800CEFB8_8 *)temp_s0)->unk_06 > (s16) ((S_800CEFB8_8 *)temp_s0)->unk_1E) {
                    temp_v1_4 = ((S_800CEFB8_8 *)temp_s0)->unk_20.at01.v;
                    ((S_800CEFB8_8 *)temp_s0)->unk_20.at01.v = (u8) (temp_v1_4 + 0xFF);
                    ((S_800CEFB8_8 *)temp_s0)->unk_18.at01.v = temp_v1_4;
                }
                temp_a0_2 = ((S_800CEFB8_7 *)temp_s1)->unk_00;
                ((S_800CEFB8_1 *)arg2_hold)->unk_0C.at03.v = temp_a0_2;
                temp_v1_5 = SP16(0x24);
                if (temp_v1_5 & 8) {
                    if (temp_v1_5 & 4) {
                        var_v0 = temp_a0_2 | 2;
                    } else {
                        var_v0 = temp_a0_2 & 0xFD;
                    }
                    ((S_800CEFB8_1 *)arg2_hold)->unk_0C.at03.v = var_v0;
                }
                temp_a1_3 = var_s3;
                var_s3 += 0x28;
                ((S_800CEFB8_8 *)temp_s0)->unk_00 = (s32) ((S_800CEFB8_1 *)arg2_hold)->unk_0C.at00.v;
                temp_s0 += 0x28;
                func_8006658C(SP32(0x20) + (SP32(0xC0) * 4), temp_a1_3);
                goto block_47;
            }
            goto block_47;
        }
block_47:
        if ((s8) ((S_800CEFB8_6 *)temp_s4)->unk_00 >= 0) {
            temp_s1 += 0xC;
            temp_s4 += 0xC;
            goto entry_loop;
        }
        func_80064A40();
        ((S_800CEFB8_9 *)(((S_800CEFB8_5 *)temp_s7)->unk_00))->unk_8D0 = var_s3;
        return;
    }
    ((S_800CEFB8_9 *)(((S_800CEFB8_5 *)temp_s7)->unk_00))->unk_8D0 = var_s3;
}
