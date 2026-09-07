#include "common.h"

typedef struct S_800CF8E4_0 {
    void * unk_00;
    u8 pad_04[0x1A];
    s16 unk_1E;
    u8 pad_20[0x1BC];
    s32 unk_1DC;
} S_800CF8E4_0;   /* var_s6 in func_800CF8E4 */

typedef struct S_800CF8E4_1 {
    u8 pad_00[0x4];
    void * unk_04;
    s32 * unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
} S_800CF8E4_1;   /* temp_s5 in func_800CF8E4 */

typedef struct S_800CF8E4_2 {
    u8 pad_00[0x8];
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u8 pad_0E[0x2];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x2];
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u8 pad_1E[0x2];
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    u8 pad_26[0x2];
    u16 unk_28;
    u16 unk_2A;
    u16 unk_2C;
    u8 pad_2E[0x56];
    s32 unk_84;
    s32 unk_88;
    u8 pad_8C[0x4];
    s32 unk_90;
    u8 pad_94[0x10];
    u16 unk_A4;
    u16 unk_A6;
    u16 unk_A8;
} S_800CF8E4_2;   /* temp_s1 in func_800CF8E4 */

typedef struct S_800CF8E4_3 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800CF8E4_3;   /* (void *)init_a3 in func_800CF8E4 */

typedef struct S_800CF8E4_4 {
    u8 pad_00[0x34];
    s32 unk_34;
    s32 unk_38;
} S_800CF8E4_4;   /* var_a0 in func_800CF8E4 */

typedef struct S_800CF8E4_5 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    u8 pad_28[0x4];
    s32 unk_2C;
    s32 unk_30;
    u8 pad_34[0x4];
    s32 unk_38;
    s32 unk_3C;
} S_800CF8E4_5;   /* var_a1 in func_800CF8E4 */

typedef struct S_800CF8E4_6 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800CF8E4_6;   /* temp_t0_2 in func_800CF8E4 */

typedef struct S_800CF8E4_7 {
    s32 unk_00;
    u16 unk_04;
} S_800CF8E4_7;   /* (void *)geom_v0 in func_800CF8E4 */

typedef struct S_800CF8E4_8 {
    s32 unk_00;
    s16 unk_04;
} S_800CF8E4_8;   /* temp_v1_11 in func_800CF8E4 */

typedef struct S_800CF8E4_9_pre {
    s8 unk_00;
    u8 pad_01[0x3];
} S_800CF8E4_9_pre;   /* the 0x4 bytes before var_a3 in func_800CF8E4, addressed as var_a3[-1] */

typedef struct S_800CF8E4_9 {
    u8 unk_00;
} S_800CF8E4_9;   /* var_a3 in func_800CF8E4 */

typedef struct S_800CF8E4_10 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_800CF8E4_10;   /* ((*(u16 *)(ram_base + 0x170) * 8) + temp_s4) in func_800CF8E4 */

typedef struct S_800CF8E4_11 {
    u8 pad_00[0x28];
    s32 unk_28;
    u8 pad_2C[0xC];
    s32 unk_38;
} S_800CF8E4_11;   /* var_v1 in func_800CF8E4 */

typedef struct S_800CF8E4_12 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800CF8E4_12;   /* ((((S_800CF8E4_6 *)temp_t0_2)->unk_06 * 8) + temp_s2) in func_800CF8E4 */

typedef struct S_800CF8E4_13 {
    s32 unk_00;
} S_800CF8E4_13;   /* (((S_800CF8E4_6 *)temp_t0_2)->unk_06 * 8) + temp_s2 in func_800CF8E4 */

typedef struct S_800CF8E4_14 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800CF8E4_14;   /* ((S_800CF8E4_0 *)var_s6)->unk_00 in func_800CF8E4 */


typedef struct {
    u16 index;
    s16 offset;
    u16 flags;
} CellRec;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_80046884();
s32 func_80046C20();
s32 func_80064624();
s32 func_80064D20();
s32 func_80064D50();
s16 func_800BCB04();
extern s32 D_80013180[0x2000];
extern u16 D_80013714[0x1000];
extern void *D_80083160[0x1000];
extern s32 D_800DCF58[0x100];

void func_800CF8E4(void) {
    register u8 *ram_base ASM_REG("$16");   /* MATCH pin: retail delay-slot fill depends on it */
    u16 sp10[23];
    s16 temp_a3_2;
    s16 temp_t0;
    s16 var_a1_2;
    s32 *temp_v1_18;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 delta_x;
    s32 delta_y;
    u8 *temp_s2;
    CellRec *temp_s3;
    register u8 *temp_s4 ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 temp_t5;
    s32 shl_tmp;
    s32 tail_v1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 temp_v1;
    s32 temp_v1_12;
    s32 temp_v1_15;
    s32 temp_v1_16;
    s32 temp_v1_17;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s32 temp_v1_8;
    s32 temp_a0_3;
    s32 *temp_a0_4;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_a2_3;
    u16 temp_a1;
    u16 temp_a2;
    u16 temp_a3;
    u16 temp_v0_4;
    u16 temp_v0_5;
    s32 temp_v1_10;
    u16 temp_v1_13;
    u16 fast0;
    u16 fast1;
    u16 fast2;
    u16 fast3;
    u16 fast4;
    u16 fast5;
    u16 fast6;
    u16 fast7;
    u16 fast8;
    u16 fast9;
    u16 fast10;
    u16 fast11;
    u8 *fast_page;
    u8 temp_v1_14;
    s32 var_a0_3;
    register u8 *temp_s1 ASM_REG("$17");   /* MATCH pin: retail schedule: same instructions, different order without it */
    u8 *pkt_s1;
    u8 *temp_s5;
    u8 *var_s6;
    void *temp_t0_2;
    void *temp_v1_11;
    CellRec *temp_v1_9;
    CellRec *cell_test;
    void *var_a0;
    void *var_a0_2;
    void *var_a1;
    void *var_a3;
    void *var_v1;
    void *call_a0;
    register void *call_a1 ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 call_a2 ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
    s32 minus_one;

    var_s6 = (u8 *)D_80083160;
    temp_t5 = D_80013714[0];
    ram_base = (u8 *)0x1F800000;
    temp_s1 = var_s6 + 0x18;
    temp_s5 = var_s6 + 0x1DC;
    temp_s3 = (CellRec *)((S_800CF8E4_0 *)var_s6)->unk_1DC;
    temp_s2 = (u8 *)((S_800CF8E4_1 *)temp_s5)->unk_08;
    temp_s4 = (u8 *)((S_800CF8E4_1 *)temp_s5)->unk_0C;
    if (!(temp_t5 & 2)) {
        temp_v1 = func_800BCB04(((S_800CF8E4_2 *)temp_s1)->unk_A4, ((S_800CF8E4_2 *)temp_s1)->unk_A6, (s16) (((S_800CF8E4_2 *)temp_s1)->unk_A8 - 0x20));
        if (temp_v1 < 0x201) {
            *(s32 *)(ram_base + 0x158) = temp_v1;
            goto L_CF974;
        }
        *(s32 *)(ram_base + 0x158) = 0;
L_CF974:
        func_80064D50(((void **)((s8 *)((void **)((s8 *)temp_s1 + 0x58)))));
        func_80064624(((S_800CF8E4_2 *)temp_s1)->unk_84, ((S_800CF8E4_2 *)temp_s1)->unk_88);
        func_80064D20(((void **)((s8 *)((void **)((s8 *)temp_s1 + 0x38)))));
        call_a0 = temp_s1;
        ASM_KEEP(call_a0);   /* MATCH pin: retail schedule: same instructions, different order without it */
        call_a1 = sp10;
        call_a2 = *(s32 *)(ram_base + 0x158);
        ((S_800CF8E4_0 *)var_s6)->unk_1E = 0x1BA;
        func_80046884(call_a0, call_a1, call_a2);
        fast_page = (u8 *)0x800E0000;
        if (fast_page[-0x30A8] != 0) {
            fast0 = sp10[0];
            fast1 = sp10[1];
            fast2 = sp10[2];
            fast3 = ((S_800CF8E4_2 *)temp_s1)->unk_10;
            fast4 = ((S_800CF8E4_2 *)temp_s1)->unk_12;
            fast5 = ((S_800CF8E4_2 *)temp_s1)->unk_14;
            fast6 = ((S_800CF8E4_2 *)temp_s1)->unk_18;
            fast7 = ((S_800CF8E4_2 *)temp_s1)->unk_1A;
            fast8 = ((S_800CF8E4_2 *)temp_s1)->unk_1C;
            fast9 = ((S_800CF8E4_2 *)temp_s1)->unk_20;
            fast10 = ((S_800CF8E4_2 *)temp_s1)->unk_22;
            fast11 = ((S_800CF8E4_2 *)temp_s1)->unk_24;
            fast_page[-0x30A8] = 0;
            ((S_800CF8E4_2 *)temp_s1)->unk_08 = fast0;
            ((S_800CF8E4_2 *)temp_s1)->unk_28 = fast0;
            ((S_800CF8E4_2 *)temp_s1)->unk_0A = fast1;
            ((S_800CF8E4_2 *)temp_s1)->unk_0C = fast2;
            ((S_800CF8E4_2 *)temp_s1)->unk_2C = fast2;
            ((S_800CF8E4_2 *)temp_s1)->unk_10 = fast3;
            ((S_800CF8E4_2 *)temp_s1)->unk_12 = fast4;
            ((S_800CF8E4_2 *)temp_s1)->unk_14 = fast5;
            ((S_800CF8E4_2 *)temp_s1)->unk_18 = fast6;
            ((S_800CF8E4_2 *)temp_s1)->unk_1A = fast7;
            ((S_800CF8E4_2 *)temp_s1)->unk_1C = fast8;
            ((S_800CF8E4_2 *)temp_s1)->unk_20 = fast9;
            ((S_800CF8E4_2 *)temp_s1)->unk_22 = fast10;
            ((S_800CF8E4_2 *)temp_s1)->unk_24 = fast11;
            goto L_CFB98;
        }
        {
            s32 interp_v0;
            s32 interp_v1;
            s32 interp_a0;
            s32 interp_a1;
            register s32 interp_a2 ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */

            interp_v1 = (s16)sp10[0];
            interp_v0 = (s16)((S_800CF8E4_2 *)temp_s1)->unk_08;
            interp_a0 = (s16)sp10[1];
            interp_a1 = (s16)((S_800CF8E4_2 *)temp_s1)->unk_0A;
            interp_v1 -= interp_v0;
            interp_v1 >>= 1;
            interp_a0 -= interp_a1;
            interp_a0 >>= 1;
            interp_v0 = ((S_800CF8E4_2 *)temp_s1)->unk_08;
            interp_a1 = (s16)((S_800CF8E4_2 *)temp_s1)->unk_0C;
            interp_v0 += interp_v1;
            ((S_800CF8E4_2 *)temp_s1)->unk_08 = (u16)interp_v0;
            interp_v0 = ((S_800CF8E4_2 *)temp_s1)->unk_0A;
            interp_v1 = (s16)sp10[2];
            interp_v0 += interp_a0;
            interp_v1 -= interp_a1;
            interp_v1 >>= 1;
            ((S_800CF8E4_2 *)temp_s1)->unk_0A = (u16)interp_v0;
            interp_v0 = ((S_800CF8E4_2 *)temp_s1)->unk_0C;
            interp_a0 = (s16)sp10[4];
            interp_a1 = (s16)((S_800CF8E4_2 *)temp_s1)->unk_10;
            interp_v0 += interp_v1;
            interp_a0 -= interp_a1;
            interp_a0 >>= 1;
            ((S_800CF8E4_2 *)temp_s1)->unk_0C = (u16)interp_v0;
            interp_v0 = ((S_800CF8E4_2 *)temp_s1)->unk_10;
            interp_v1 = (s16)sp10[5];
            interp_a1 = (s16)((S_800CF8E4_2 *)temp_s1)->unk_12;
            interp_v0 += interp_a0;
            interp_v1 -= interp_a1;
            interp_v1 >>= 1;
            ((S_800CF8E4_2 *)temp_s1)->unk_10 = (u16)interp_v0;
            interp_v0 = ((S_800CF8E4_2 *)temp_s1)->unk_12;
            interp_a0 = (s16)sp10[6];
            interp_a1 = (s16)((S_800CF8E4_2 *)temp_s1)->unk_14;
            interp_v0 += interp_v1;
            interp_a0 -= interp_a1;
            interp_a0 >>= 1;
            ((S_800CF8E4_2 *)temp_s1)->unk_12 = (u16)interp_v0;
            interp_v0 = ((S_800CF8E4_2 *)temp_s1)->unk_14;
            interp_v1 = (s16)sp10[8];
            interp_a1 = (s16)((S_800CF8E4_2 *)temp_s1)->unk_18;
            interp_v0 += interp_a0;
            interp_v1 -= interp_a1;
            interp_v1 >>= 1;
            ((S_800CF8E4_2 *)temp_s1)->unk_14 = (u16)interp_v0;
            interp_v0 = ((S_800CF8E4_2 *)temp_s1)->unk_18;
            interp_a0 = (s16)sp10[9];
            interp_a1 = (s16)((S_800CF8E4_2 *)temp_s1)->unk_1A;
            interp_v0 += interp_v1;
            interp_a0 -= interp_a1;
            interp_a0 >>= 1;
            ((S_800CF8E4_2 *)temp_s1)->unk_18 = (u16)interp_v0;
            interp_v0 = ((S_800CF8E4_2 *)temp_s1)->unk_1A;
            interp_v1 = (s16)sp10[10];
            interp_a1 = (s16)((S_800CF8E4_2 *)temp_s1)->unk_1C;
            interp_v0 += interp_a0;
            interp_v1 -= interp_a1;
            ((S_800CF8E4_2 *)temp_s1)->unk_1A = (u16)interp_v0;
            interp_v0 = ((S_800CF8E4_2 *)temp_s1)->unk_1C;
            interp_v1 >>= 1;
            interp_v0 += interp_v1;
            ((S_800CF8E4_2 *)temp_s1)->unk_1C = (u16)interp_v0;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            interp_v1 = (s16)sp10[12];
            interp_v0 = (s16)((S_800CF8E4_2 *)temp_s1)->unk_20;
            interp_a0 = (s16)sp10[13];
            interp_a1 = (s16)((S_800CF8E4_2 *)temp_s1)->unk_22;
            interp_a2 = ((S_800CF8E4_2 *)temp_s1)->unk_0C;
            interp_v1 -= interp_v0;
            interp_v1 >>= 1;
            interp_a0 -= interp_a1;
            interp_v0 = ((S_800CF8E4_2 *)temp_s1)->unk_20;
            interp_a1 = (s16)((S_800CF8E4_2 *)temp_s1)->unk_24;
            interp_v0 += interp_v1;
            ((S_800CF8E4_2 *)temp_s1)->unk_20 = (u16)interp_v0;
            interp_v0 = ((S_800CF8E4_2 *)temp_s1)->unk_22;
            interp_v1 = (s16)sp10[14];
            interp_a0 >>= 1;
            ((S_800CF8E4_2 *)temp_s1)->unk_2C = (u16)interp_a2;
            interp_v0 += interp_a0;
            interp_v1 -= interp_a1;
            interp_v1 >>= 1;
            ((S_800CF8E4_2 *)temp_s1)->unk_22 = (u16)interp_v0;
            interp_v0 = ((S_800CF8E4_2 *)temp_s1)->unk_24;
            interp_a0 = ((S_800CF8E4_2 *)temp_s1)->unk_08;
            interp_a1 = ((S_800CF8E4_2 *)temp_s1)->unk_0A;
            interp_v0 += interp_v1;
            ((S_800CF8E4_2 *)temp_s1)->unk_24 = (u16)interp_v0;
            ((S_800CF8E4_2 *)temp_s1)->unk_28 = (u16)interp_a0;
            ((S_800CF8E4_2 *)temp_s1)->unk_2A = (u16)interp_a1;
        }
L_CFB98:
        {
            s32 init_v0;
            s32 init_v1;
            s32 init_a3;
            register s32 init_t0 ASM_REG("$8");   /* MATCH pin: load-bearing for the whole function shape */
            register s32 init_t1 ASM_REG("$9");   /* MATCH pin: load-bearing for the whole function shape */
            register s32 init_t2 ASM_REG("$10");   /* MATCH pin: load-bearing for the whole function shape */
            register s32 init_t3 ASM_REG("$11");   /* MATCH pin: load-bearing for the whole function shape */
            register s32 init_t4 ASM_REG("$12");   /* MATCH pin: load-bearing for the whole function shape */

            call_a0 = temp_s1 + 8;
            call_a1 = ram_base + 0x01C;
            init_v0 = ((S_800CF8E4_2 *)temp_s1)->unk_90;
            call_a2 = (s32)(ram_base + 0x174);
            *(s32 *)(ram_base + 0x000) = init_v0;
            init_v0 = (s32)0x80010000;
            init_v1 = (s32)((S_800CF8E4_0 *)var_s6)->unk_00;
            init_a3 = ((S_800CF8E4_1 *)temp_s5)->unk_14;
            init_t0 = ((S_800CF8E4_1 *)temp_s5)->unk_16;
            init_t1 = ((S_800CF8E4_1 *)temp_s5)->unk_18;
            init_t2 = ((S_800CF8E4_1 *)temp_s5)->unk_1A;
            ASM_KEEP4(init_a3, init_t0, init_t1, init_t2);   /* MATCH pin: retail schedule: same instructions, different order without it */
            init_t3 = *(s32 *)(init_v0 + 0x3180);
            init_t4 = *(u8 *)(init_v0 + 0x3184);
            init_v0 = *(u8 *)(init_v0 + 0x3185);
            init_v1 += 0xB8;
            ASM_KEEP(init_v1);   /* MATCH pin: retail schedule: same instructions, different order without it */
            *(s32 *)(ram_base + 0x124) = init_a3;
            *(u16 *)(ram_base + 0x178) = (u16)init_v0;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            init_v0 = init_a3;
            ASM_KEEP(init_v0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            *(s32 *)(ram_base + 0x0BC) = init_v1;
            init_v1 = 0x40;
            init_v0 = init_v1 << init_v0;
            *(s32 *)(ram_base + 0x128) = init_t0;
            *(s32 *)(ram_base + 0x114) = init_v0;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            init_v0 = init_t0;
            ASM_KEEP(init_v0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            init_v1 <<= init_v0;
            *(s32 *)(ram_base + 0x11C) = init_t1;
            *(s32 *)(ram_base + 0x120) = init_t2;
            *(s32 *)(ram_base + 0x110) = init_t3;
            *(u16 *)(ram_base + 0x176) = (u16)init_t4;
            init_a3 = (s32)((S_800CF8E4_0 *)var_s6)->unk_00;
            init_v0 = 0xAF3A;
            *(s32 *)(ram_base + 0x118) = init_v1;
            pkt_s1 = (u8 *)((S_800CF8E4_3 *)((void *)init_a3))->unk_8D0;
            init_a3 += init_v0;
            init_v0 = 0xFFFF;
            *(s32 *)(ram_base + 0x14C) = init_v0;
            *(s32 *)(ram_base + 0x17C) = init_a3;
            *(u16 *)(ram_base + 0x174) = 4U;
            *(s32 *)(ram_base + 0x00C) = (s16)func_80046C20(call_a0, call_a1, call_a2, (void *)init_a3);
        }
        if (*(u16 *)(ram_base + 0x174) != 0) {
            s32 hold_t1;
            register s32 hold_t2 ASM_REG("$10");   /* MATCH pin: load-bearing for the whole function shape */
            s32 hold_t3;
            register s32 hold_t5 ASM_REG("$13");   /* MATCH pin: retail register colouring depends on it */

            hold_t2 = 1;
            hold_t3 = 0x7FFF;
            hold_t1 = 0xFFFFFF;
            hold_t5 = (s32)0xFF000000;
loop_9:
            call_a2 = 3;
            var_a0 = (s32 *)(ram_base + 0x78);
            do {
                ASM_KEEP(var_a0);   /* MATCH pin: load-bearing for the whole function shape */
                if (((S_800CF8E4_4 *)var_a0)->unk_38 == 0) {
                    s32 lim_v1;
                    s32 cur_v0;

                    lim_v1 = ((S_800CF8E4_4 *)var_a0)->unk_34;
                    cur_v0 = *(s32 *)(ram_base + 0x00C);
                    if (cur_v0 >= lim_v1) {
                        ((S_800CF8E4_4 *)var_a0)->unk_38 = hold_t2;
                    }
                }
                call_a2 -= 1;
                var_a0 -= 0x28;
            } while (call_a2 >= 0);
            call_a2 = 3;
            var_a1 = (s32 *)(ram_base + 0x78);
            *(s32 *)(ram_base + 0x014) = hold_t3;
            *(s32 *)(ram_base + 0x018) = -0x7FFF;
loop_15:
            if (((S_800CF8E4_5 *)var_a1)->unk_38 > 0) {
                temp_v1 = ((S_800CF8E4_5 *)var_a1)->unk_1C;
                *(s32 *)(ram_base + 0x008) = temp_v1;
                if (temp_v1 < *(s32 *)(ram_base + 0x014)) {
                    *(s32 *)(ram_base + 0x014) = temp_v1;
                    goto L_CFCFC;
                }
                if (*(s32 *)(ram_base + 0x018) < temp_v1) {
                    *(s32 *)(ram_base + 0x018) = temp_v1;
                }
L_CFCFC:
                {
                    s32 step_v0;
                    register s32 step_v1 ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
                    register s32 step_a0 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */

                    step_v1 = ((S_800CF8E4_5 *)var_a1)->unk_2C;
                    step_v0 = ((S_800CF8E4_5 *)var_a1)->unk_24;
                    step_v1 += step_v0;
                    ((S_800CF8E4_5 *)var_a1)->unk_2C = step_v1;
                    if (step_v1 >= 0) {
loop_22:
                        step_v1 = ((S_800CF8E4_5 *)var_a1)->unk_1C;
                        step_v0 = ((S_800CF8E4_5 *)var_a1)->unk_30;
                        step_a0 = ((S_800CF8E4_5 *)var_a1)->unk_20;
                        step_v1 += step_v0;
                        step_v0 = ((S_800CF8E4_5 *)var_a1)->unk_2C;
                        ((S_800CF8E4_5 *)var_a1)->unk_1C = step_v1;
                        step_v1 = ((S_800CF8E4_5 *)var_a1)->unk_3C;
                        step_v0 -= step_a0;
                        step_v1 -= 0x40;
                        ((S_800CF8E4_5 *)var_a1)->unk_2C = step_v0;
                        ((S_800CF8E4_5 *)var_a1)->unk_3C = step_v1;
                        if ((step_v1 > 0) && (step_v0 >= 0)) {
                            goto loop_22;
                        }
                    }
                }
                temp_v1_4 = ((S_800CF8E4_5 *)var_a1)->unk_1C;
                *(s32 *)(ram_base + 0x008) = temp_v1_4;
                if (temp_v1_4 < *(s32 *)(ram_base + 0x014)) {
                    *(s32 *)(ram_base + 0x014) = temp_v1_4;
                }
                temp_v1_5 = *(s32 *)(ram_base + 0x008);
                if (*(s32 *)(ram_base + 0x018) < temp_v1_5) {
                    *(s32 *)(ram_base + 0x018) = temp_v1_5;
                }
                goto block_28;
            }
block_28:
            call_a2 -= 1;
            var_a1 -= 0x28;
            if (call_a2 < 0) {
                temp_v1_6 = *(s32 *)(ram_base + 0x00C);
                if ((temp_v1_6 >= 0) && (*(s32 *)(ram_base + 0x118) >= temp_v1_6)) {
                    temp_v0_2 = (*(s32 *)(ram_base + 0x014) - 0x20) & ~0x3F;
                    *(s32 *)(ram_base + 0x014) = temp_v0_2;
                    if (temp_v0_2 < 0) {
                        *(s32 *)(ram_base + 0x014) = 0;
                    }
                    temp_v1_7 = *(s32 *)(ram_base + 0x114);
                    temp_v0_3 = (*(s32 *)(ram_base + 0x018) + 0x20) & ~0x3F;
                    *(s32 *)(ram_base + 0x018) = temp_v0_3;
                    if (temp_v1_7 < temp_v0_3) {
                        *(s32 *)(ram_base + 0x018) = temp_v1_7;
                    }
                    *(s32 *)(ram_base + 0x138) = (((u32) *(s32 *)(ram_base + 0x00C) >> 6) & *(s32 *)(ram_base + 0x120)) << *(s32 *)(ram_base + 0x124);
                    *(s32 *)(ram_base + 0x134) = ((u32) *(s32 *)(ram_base + 0x014) >> 6) & *(s32 *)(ram_base + 0x11C);
                    if (*(s32 *)(ram_base + 0x018) >= *(s32 *)(ram_base + 0x014)) {
loop_36:
                        temp_v1_8 = *(s32 *)(ram_base + 0x138) + *(s32 *)(ram_base + 0x134);
                        *(s32 *)(ram_base + 0x144) = temp_v1_8;
                        temp_v1_9 = (CellRec *)((temp_v1_8 * 6) + (s32)temp_s3);
                        var_a3 = pkt_s1 + 7;
                        if (temp_v1_9->index != 0) {
                            *(s32 *)(ram_base + 0x12C) = (s32) temp_v1_9->offset;
                            temp_t0_2 = ((void **)((S_800CF8E4_1 *)temp_s5)->unk_04)[temp_s3[*(s32 *)(ram_base + 0x144)].index];
L_CFE98:
                            {
                                register s32 geom_v0 ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */
                                s32 geom_v1;
                                s32 geom_a0;
                                s32 geom_a1;
                                u16 geom_a0h;
                                register u16 geom_a1h ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
                                register u16 geom_v0h ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */

                                geom_v0 = ((S_800CF8E4_6 *)temp_t0_2)->unk_10;
                                geom_a0h = *(volatile u16 *)(ram_base + 0x014);
                                *(volatile s32 *)(ram_base + 0x170) = geom_v0;
                                geom_v0 = ((S_800CF8E4_6 *)temp_t0_2)->unk_00;
                                geom_v1 = ((S_800CF8E4_6 *)temp_t0_2)->unk_14;
                                geom_v0 <<= 3;
                                geom_v0 += (s32)temp_s2;
                                *(volatile s32 *)(ram_base + 0x16C) = geom_v1;
                                geom_v0 = ((S_800CF8E4_7 *)((void *)geom_v0))->unk_00;
                                geom_v1 = *(volatile u16 *)(ram_base + 0x12C);
                                *(volatile s32 *)(ram_base + 0x164) = geom_v0;
                                geom_v0 = ((S_800CF8E4_6 *)temp_t0_2)->unk_00;
                                geom_a1h = *(volatile u16 *)(ram_base + 0x164);
                                geom_v0 <<= 3;
                                geom_v0 += (s32)temp_s2;
                                geom_a0 = geom_a0h + geom_a1h;
                                geom_v0 = ((S_800CF8E4_7 *)((void *)geom_v0))->unk_04;
                                geom_a0 &= 0xFFFF;
                                geom_v0 -= geom_v1;
                                *(volatile u16 *)(ram_base + 0x0E4) = (u16)geom_v0;
                                geom_v0 = *(volatile u16 *)(ram_base + 0x166);
                                geom_v1 = *(volatile s32 *)(ram_base + 0x00C);
                                geom_v0 = (s16)geom_v0;
                                geom_v1 += geom_v0;
                                geom_v1 <<= 16;
                                geom_v0 = ((S_800CF8E4_6 *)temp_t0_2)->unk_02;
                                geom_a0 |= geom_v1;
                                *(volatile s32 *)(ram_base + 0x0E0) = geom_a0;

                                geom_a0h = *(volatile u16 *)(ram_base + 0x014);
                                geom_v1 = *(volatile u16 *)(ram_base + 0x12C);
                                geom_v0 <<= 3;
                                geom_v0 += (s32)temp_s2;
                                geom_v0 = ((S_800CF8E4_7 *)((void *)geom_v0))->unk_00;
                                *(volatile s32 *)(ram_base + 0x164) = geom_v0;
                                geom_v0 = ((S_800CF8E4_6 *)temp_t0_2)->unk_02;
                                geom_a1h = *(volatile u16 *)(ram_base + 0x164);
                                geom_v0 <<= 3;
                                geom_v0 += (s32)temp_s2;
                                geom_a0 = geom_a0h + geom_a1h;
                                geom_v0 = ((S_800CF8E4_7 *)((void *)geom_v0))->unk_04;
                                geom_a0 &= 0xFFFF;
                                geom_v0 -= geom_v1;
                                *(volatile u16 *)(ram_base + 0x0EC) = (u16)geom_v0;
                                geom_v0 = *(volatile u16 *)(ram_base + 0x166);
                                geom_v1 = *(volatile s32 *)(ram_base + 0x00C);
                                geom_v0 = (s16)geom_v0;
                                geom_v1 += geom_v0;
                                geom_v1 <<= 16;
                                geom_v0 = ((S_800CF8E4_6 *)temp_t0_2)->unk_04;
                                geom_a0 |= geom_v1;
                                *(volatile s32 *)(ram_base + 0x0E8) = geom_a0;

                                geom_a0h = *(volatile u16 *)(ram_base + 0x014);
                                geom_v0 <<= 3;
                                geom_v0 += (s32)temp_s2;
                                geom_v0 = ((S_800CF8E4_7 *)((void *)geom_v0))->unk_00;
                                *(volatile s32 *)(ram_base + 0x164) = geom_v0;
                                geom_v0h = *(volatile u16 *)(ram_base + 0x164);
                                geom_v1 = *(volatile u16 *)(ram_base + 0x166);
                                geom_a0 = geom_a0h + geom_v0h;
                                geom_a0 &= 0xFFFF;
                                geom_v1 = (s16)geom_v1;
                                geom_v0 = *(volatile s32 *)(ram_base + 0x00C);
                                geom_v0 += geom_v1;
                                geom_v0 <<= 16;
                                geom_a0 |= geom_v0;
                                *(volatile s32 *)(ram_base + 0x0F0) = geom_a0;
                                geom_v0 = ((S_800CF8E4_6 *)temp_t0_2)->unk_04;
                                geom_v0 <<= 3;
                                geom_v0 += (s32)temp_s2;
                                geom_v1 = ((S_800CF8E4_7 *)((void *)geom_v0))->unk_04;
                                geom_v0 = *(volatile u16 *)(ram_base + 0x12C);
                                geom_v1 -= geom_v0;
                                *(volatile u16 *)(ram_base + 0x0F4) = (u16)geom_v1;
                            }
                            gte_ldv3(ram_base + 0xE0, ram_base + 0xE8, ram_base + 0xF0);
                            {
                                register s32 corner_hi ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
                                s32 corner_lo;

                                corner_hi = ((S_800CF8E4_12 *)(((((S_800CF8E4_6 *)temp_t0_2)->unk_06 * 8) + temp_s2)))->unk_04;
                                corner_lo = *(volatile u16 *)(ram_base + 0x12C);
                                corner_hi -= corner_lo;
                                *(u16 *)(ram_base + 0x0FC) = (u16) corner_hi;
                            }
                            gte_rtpt_nn();
                            gte_nclip();
                            gte_stopz(ram_base + 0xDC);
                            if (*(s32 *)(ram_base + 0x0DC) >= 0) {
                                gte_stflg(ram_base + 0xD8);
                                if (*(s32 *)(ram_base + 0x0D8) == 0) {
                                    gte_stsxy3_g3(pkt_s1);
                                    gte_avsz3();
                                    gte_stotz(ram_base + 0xC8);
                                    temp_v1_10 = *(u16 *)(ram_base + 0x170);
                                    if (*(s32 *)(ram_base + 0x14C) != temp_v1_10) {
                                        *(s32 *)(ram_base + 0x14C) = (s32) temp_v1_10;
                                        temp_v1_11 = (void *)((temp_v1_10 * 8) + (s32)temp_s4);
                                        if (((S_800CF8E4_8 *)temp_v1_11)->unk_04 >= 0) {
                                            temp_v1_12 = ((S_800CF8E4_8 *)temp_v1_11)->unk_00;
                                            if (!(temp_v1_12 & 0x0FFF0FFF)) {
                                                *(s32 *)(ram_base + 0x010) = temp_v1_12;
                                                temp_v0_4 = *(u16 *)(ram_base + 0x010);
                                                if ((s16) temp_v0_4 > 0) {
                                                    *(u16 *)(ram_base + 0x010) = (u16)hold_t2;
                                                    goto L_D00F4;
                                                }
                                                if ((s16) temp_v0_4 < 0) {
                                                    *(s16 *)(ram_base + 0x010) = -1;
                                                }
L_D00F4:
                                                temp_v0_5 = *(u16 *)(ram_base + 0x012);
                                                if ((s16) temp_v0_5 > 0) {
                                                    shl_tmp = hold_t2 << *(s32 *)(ram_base + 0x124);
                                                    goto L_D0130;
                                                }
                                                if ((s16) temp_v0_5 < 0) {
                                                    shl_tmp = 0 - (hold_t2 << *(s32 *)(ram_base + 0x124));
L_D0130:
                                                    *(s16 *)(ram_base + 0x012) = (s16)shl_tmp;
                                                }
                                                {
                                                    s32 h_v0;
                                                    s32 h_v1;
                                                    register s32 h_a0 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
                                                    register s32 h_a1 ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */

                                                    h_v0 = *(volatile u16 *)(ram_base + 0x010);
                                                    h_a0 = *(volatile s32 *)(ram_base + 0x134);
                                                    h_a1 = *(volatile u16 *)(ram_base + 0x012);
                                                    h_v1 = *(volatile s32 *)(ram_base + 0x120);
                                                    call_a2 = *(volatile s32 *)(ram_base + 0x124);
                                                    h_v0 = (s16)h_v0;
                                                    h_a0 += h_v0;
                                                    h_v0 = *(volatile s32 *)(ram_base + 0x11C);
                                                    h_a1 = (s16)h_a1;
                                                    h_a0 &= h_v0;
                                                    h_v0 = *(volatile s32 *)(ram_base + 0x138);
                                                    h_v1 <<= call_a2;
                                                    *(volatile s32 *)(ram_base + 0x13C) = h_a0;
                                                    h_v0 += h_a1;
                                                    h_v0 &= h_v1;
                                                    h_a0 += h_v0;
                                                    temp_a0_2 = h_a0;
                                                    *(volatile s32 *)(ram_base + 0x13C) = temp_a0_2;
                                                }
                                                cell_test = (CellRec *)((temp_a0_2 * 6) + (s32)temp_s3);
                                                temp_v1_13 = cell_test->flags;
                                                if (!(temp_v1_13 & 1)) {
                                                    if (temp_v1_13 & 0x80) {
                                                        if (temp_s3[*(s32 *)(ram_base + 0x144)].flags & 0x80) {
                                                            temp_v1_14 = *(u8 *)(ram_base + 0x16F);
                                                            if (!(temp_v1_14 & 2)) {
                                                                if ((*(u8 *)(ram_base + 0x16E) != hold_t2) || ((s8) temp_v1_14) >= 0) {
                                                                    temp_t0_2 = (u8 *)temp_t0_2 + 24;
                                                                    *(s32 *)(ram_base + 0x14C) = 0xFFFF;
                                                                    goto L_CFE98;
                                                                }
                                                                goto block_98;
                                                            }
                                                        }
                                                        goto block_63;
                                                    }
                                                    if (!(temp_v1_13 & 0x40)) {
                                                        *(s32 *)(ram_base + 0x148) = -(s32) cell_test->offset;
                                                        goto L_D0234;
                                                    }
                                                    goto block_63;
                                                }
                                                goto block_63;
                                            }
                                        }
block_63:
                                        *(s32 *)(ram_base + 0x148) = hold_t3;
L_D0234:
                                        gte_ldrgb(ram_base);
                                        gte_ldv0((u8 *)temp_s4 + (*(s32 *)(ram_base + 0x14C) * 8));
                                        gte_nccs();
                                        gte_strgb(ram_base + 0x04);
                                        goto block_64;
                                    }
block_64:
                                    temp_v1_15 = *(s32 *)(ram_base + 0x148);
                                    if (((s16) *(u16 *)(ram_base + 0x0E4) >= temp_v1_15) && ((s16) *(u16 *)(ram_base + 0x0EC) >= temp_v1_15) && ((s16) *(u16 *)(ram_base + 0x0F4) >= temp_v1_15) && ((s16) *(u16 *)(ram_base + 0x0FC) >= temp_v1_15)) {
                                        if (((s8) *(u8 *)(ram_base + 0x16F)) >= 0) {
                                            tail_v1 = *(u8 *)(ram_base + 0x16E);
                                            tail_v1 &= 0xF;
                                            goto L_D0670;
                                        }
                                        goto block_98;
                                    }
                                    *(s32 *)(ram_base + 0x164) = ((S_800CF8E4_13 *)((((S_800CF8E4_6 *)temp_t0_2)->unk_06 * 8) + temp_s2))->unk_00;
                                    *(s32 *)(ram_base + 0x0F8) = (((u16) *(s32 *)(ram_base + 0x014) + (u16) *(s32 *)(ram_base + 0x164)) & 0xFFFF) | ((*(s32 *)(ram_base + 0x00C) + (s16) *(s32 *)(ram_base + 0x166)) << 0x10);
                                    gte_ldv0(ram_base + 0xF8);
                                    (*(s32 *)((u8 *)var_a3 + 5)) = (s32) ((S_800CF8E4_6 *)temp_t0_2)->unk_08;
                                    gte_rtps_nn();
                                    (*(s32 *)((u8 *)var_a3 + 0xD)) = (s32) ((S_800CF8E4_6 *)temp_t0_2)->unk_0C;
                                    (*(u16 *)((u8 *)var_a3 + 0x15)) = (u16) *(s32 *)(ram_base + 0x172);
                                    (*(u16 *)((u8 *)var_a3 + 0x1D)) = (u16) *(s32 *)(ram_base + 0x16C);
                                    gte_stsxy(pkt_s1 + 0x20);
                                    gte_stszotz(ram_base + 0xD4);
                                    {
                                        s32 m_v0;
                                        s32 m_v1;
                                        s32 m_a0;

                                        m_v0 = *(s32 *)(ram_base + 0x0C8);
                                        m_a0 = *(s32 *)(ram_base + 0x0D4);
                                        m_v1 = m_v0 << 1;
                                        m_v0 += m_v1;
                                        m_v0 += m_a0;
                                        temp_v1_16 = m_v0 >> 2;
                                    }
                                    *(s32 *)(ram_base + 0x0C8) = temp_v1_16;
                                    if ((u32) temp_v1_16 < 0x1BEU) {
                                        ((S_800CF8E4_9_pre *)var_a3)[-1].unk_00 = 9;
                                        (*(s32 *)((u8 *)var_a3 + -3)) = (s32) *(s32 *)(ram_base + 0x004);
                                        var_a0_3 = *(u8 *)(ram_base + 0x16F);
                                        if (var_a0_3 & 1) {
                                            *(u8 *)var_a3 = (u8) (*(u8 *)var_a3 | 2);
                                            goto L_D0540;
                                        }
                                        if ((*(u16 *)(ram_base + 0x178) != 0) && (temp_s3[*(s32 *)(ram_base + 0x144)].flags & 0x80) && !(var_a0_3 & 2) && ((temp_v1_17 = *(s32 *)(ram_base + 0x158), (((s16) *(u16 *)(ram_base + 0x0E4) < temp_v1_17) != 0)) || ((s16) *(u16 *)(ram_base + 0x0EC) < temp_v1_17) || ((s16) *(u16 *)(ram_base + 0x0F4) < temp_v1_17) || ((s16) *(u16 *)(ram_base + 0x0FC) < temp_v1_17))) {
                                            (*(s32 *)((u8 *)var_a3 + 5)) = (s32) (*(s32 *)((u8 *)var_a3 + 9));
                                            (*(s32 *)((u8 *)var_a3 + 9)) = (s32) (*(s32 *)((u8 *)var_a3 + 0x11));
                                            (*(s32 *)((u8 *)var_a3 + 0xD)) = (s32) (*(s32 *)((u8 *)var_a3 + 0x19));
                                            temp_a0_3 = *(s32 *)(ram_base + 0x110);
                                            ((S_800CF8E4_9_pre *)var_a3)[-1].unk_00 = 5;
                                            (*(s32 *)((u8 *)var_a3 + -3)) = temp_a0_3;
                                            var_a3 += 0x28;
                                            *(s32 *)pkt_s1 = (*(s32 *)pkt_s1 & hold_t5) | (*(s32 *)((*(s32 *)(ram_base + 0x0C8) * 4) + *(s32 *)(ram_base + 0x0BC)) & hold_t1);
                                            temp_a0_4 = (s32 *)((*(s32 *)(ram_base + 0x0C8) * 4) + *(s32 *)(ram_base + 0x0BC));
                                            {
                                                s32 rm_v0;
                                                register s32 rm_v1 ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */

                                                rm_v0 = (s32) pkt_s1 & hold_t1;
                                                rm_v1 = *temp_a0_4;
                                                pkt_s1 += 0x28;
                                                rm_v1 &= hold_t5;
                                                rm_v1 |= rm_v0;
                                                *temp_a0_4 = rm_v1;
                                            }
                                            ((S_800CF8E4_9_pre *)var_a3)[-1].unk_00 = hold_t2;
                                            {
                                                register s32 pk_v1 ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */

                                                pk_v1 = (s32) ((*(u16 *)(ram_base + 0x176) & 0x9FF) | 0xE1000000);
                                                (*(s32 *)((u8 *)var_a3 + -3)) = pk_v1;
                                            }
                                        }
L_D0540:
                                        var_a3 += 0x28;
                                        var_a0_2 = (void *) ((s32) pkt_s1 & hold_t1);
                                        goto L_D057C;
                                    }
                                    if ((u32) temp_v1_16 < 0x1DEU) {
                                        ((S_800CF8E4_9_pre *)var_a3)[-1].unk_00 = 9;
                                        (*(s32 *)((u8 *)var_a3 + -3)) = (s32) *(s32 *)(ram_base + 0x004);
                                        var_a0_2 = (void *) ((s32) pkt_s1 & hold_t1);
                                        ((S_800CF8E4_9 *)var_a3)->unk_00 = (u8) (((S_800CF8E4_9 *)var_a3)->unk_00 | 2);
                                        var_a3 += 0x28;
L_D057C:
                                        *(s32 *)pkt_s1 = (*(s32 *)pkt_s1 & hold_t5) | (*(s32 *)((*(s32 *)(ram_base + 0x0C8) * 4) + *(s32 *)(ram_base + 0x0BC)) & hold_t1);
                                        temp_v1_18 = (*(s32 *)(ram_base + 0x0C8) * 4) + *(s32 *)(ram_base + 0x0BC);
                                        *temp_v1_18 = (*temp_v1_18 & hold_t5) | (s32) var_a0_2;
                                        pkt_s1 += 0x28;
                                        tail_v1 = *(u8 *)(ram_base + 0x16E);
                                        if ((tail_v1 & 0xF) == hold_t2) {
                                            if (((s8) *(u8 *)(ram_base + 0x16F)) < 0) {
                                                goto block_98;
                                            }
                                            temp_t0_2 = (u8 *)temp_t0_2 + ((((u32)tail_v1 >> 4) * 24) + 24);
                                            goto L_CFE98;
                                        }
                                        goto L_D063C;
                                    }
                                    goto block_98;
                                }
                                goto block_98;
                            }
                            if (((S_800CF8E4_10 *)(((*(u16 *)(ram_base + 0x170) * 8) + temp_s4)))->unk_04 >= 0) {
                                goto L_D0644;
                            }
                            {
                                s32 cmp_v0;
                                register s32 cmp_v1 ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */

                                cmp_v0 = 0x8001;
                                cmp_v1 = *(u16 *)(ram_base + 0x16E) & 0x80FF;
                                if (cmp_v1 == cmp_v0) {
                                    goto block_98;
                                }
                            }
L_D063C:
                            temp_t0_2 = (u8 *)temp_t0_2 + 24;
                            goto L_CFE98;
L_D0644:
                            tail_v1 = *(u8 *)(ram_base + 0x16E);
                            if (!(tail_v1 & 0xF0)) {
                                if (((s8) *(u8 *)(ram_base + 0x16F)) < 0) {
                                    goto block_98;
                                }
                            }
                            tail_v1 &= 0xF;
L_D0670:
                            temp_t0_2 = (u8 *)temp_t0_2 + (tail_v1 * 24);
                            goto L_CFE98;
block_98:
                            if ((u32) *(s32 *)(ram_base + 0x17C) >= (u32) pkt_s1) {
                                goto block_99;
                            }
                            goto block_106;
                        }
block_99:
                        temp_v0_6 = *(s32 *)(ram_base + 0x134) + 1;
                        *(s32 *)(ram_base + 0x134) = temp_v0_6;
                        *(s32 *)(ram_base + 0x134) = temp_v0_6 & *(s32 *)(ram_base + 0x11C);
                        temp_v0_7 = *(s32 *)(ram_base + 0x014) + 0x40;
                        *(s32 *)(ram_base + 0x014) = temp_v0_7;
                        if (*(s32 *)(ram_base + 0x018) < temp_v0_7) {
                            goto block_100;
                        }
                        goto loop_36;
                    }
                    goto block_100;
                }
block_100:
                call_a2 = 3;
                minus_one = -1;
                var_v1 = (s32 *)(ram_base + 0x78);
                *(s32 *)(ram_base + 0x00C) += 0x40;
                do {
                    ASM_KEEP(var_v1);   /* MATCH pin: load-bearing for the whole function shape */
                    if (((S_800CF8E4_11 *)var_v1)->unk_38 > 0) {
                        temp_v0_8 = ((S_800CF8E4_11 *)var_v1)->unk_28 - 0x40;
                        ((S_800CF8E4_11 *)var_v1)->unk_28 = temp_v0_8;
                        if (temp_v0_8 < -0x7F) {
                            ((S_800CF8E4_11 *)var_v1)->unk_38 = minus_one;
                            *(u16 *)(ram_base + 0x174) = (u16) (*(u16 *)(ram_base + 0x174) - 1);
                        }
                    }
                    call_a2 -= 1;
                    var_v1 -= 0x28;
                } while (call_a2 >= 0);
                if (*(u16 *)(ram_base + 0x174) == 0) {
                    goto block_106;
                }
                goto loop_9;
            }
            goto loop_15;
        }
block_106:
        ((S_800CF8E4_14 *)(((S_800CF8E4_0 *)var_s6)->unk_00))->unk_8D0 = pkt_s1;
    }
}
