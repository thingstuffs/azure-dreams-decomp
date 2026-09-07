#include "common.h"

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
    register u8 *ram_base ASM_REG("$16");
    u16 sp10[23];
    s16 temp_a3_2;
    s16 temp_t0;
    s16 var_a1_2;
    s32 *temp_v1_18;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 delta_x;
    s32 delta_y;
    register u8 *temp_s2 ASM_REG("$18");
    register CellRec *temp_s3 ASM_REG("$19");
    register u8 *temp_s4 ASM_REG("$20");
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
    register u8 *temp_s1 ASM_REG("$17");
    u8 *pkt_s1;
    register u8 *temp_s5 ASM_REG("$21");
    u8 *var_s6;
    register void *temp_t0_2 ASM_REG("$8");
    void *temp_v1_11;
    CellRec *temp_v1_9;
    CellRec *cell_test;
    void *var_a0;
    void *var_a0_2;
    void *var_a1;
    void *var_a3;
    void *var_v1;
    register void *call_a0 ASM_REG("$4");
    register void *call_a1 ASM_REG("$5");
    register s32 call_a2 ASM_REG("$6");
    register s32 minus_one ASM_REG("$4");

    var_s6 = (u8 *)D_80083160;
    temp_t5 = D_80013714[0];
    ram_base = (u8 *)0x1F800000;
    temp_s1 = var_s6 + 0x18;
    temp_s5 = var_s6 + 0x1DC;
    temp_s3 = (CellRec *)M2C_FIELD(var_s6, s32 *, 0x1DC);
    temp_s2 = (u8 *)M2C_FIELD(temp_s5, s32 **, 8);
    temp_s4 = (u8 *)M2C_FIELD(temp_s5, s32 *, 0xC);
    if (!(temp_t5 & 2)) {
        temp_v1 = func_800BCB04(M2C_FIELD(temp_s1, u16 *, 0xA4), M2C_FIELD(temp_s1, u16 *, 0xA6), (s16) (M2C_FIELD(temp_s1, u16 *, 0xA8) - 0x20));
        if (temp_v1 < 0x201) {
            *(s32 *)(ram_base + 0x158) = temp_v1;
            goto L_CF974;
        }
        *(s32 *)(ram_base + 0x158) = 0;
L_CF974:
        ASM_USE(temp_s1);
        func_80064D50(((void **)((s8 *)((void **)((s8 *)temp_s1 + 0x58)))));
        func_80064624(M2C_FIELD(temp_s1, s32 *, 0x84), M2C_FIELD(temp_s1, s32 *, 0x88));
        func_80064D20(((void **)((s8 *)((void **)((s8 *)temp_s1 + 0x38)))));
        call_a0 = temp_s1;
        ASM_KEEP(call_a0);
        call_a1 = sp10;
        ASM_KEEP(call_a1);
        call_a2 = *(s32 *)(ram_base + 0x158);
        ASM_KEEP(call_a2);
        M2C_FIELD(var_s6, s16 *, 0x1E) = 0x1BA;
        func_80046884(call_a0, call_a1, call_a2);
        fast_page = (u8 *)0x800E0000;
        if (fast_page[-0x30A8] != 0) {
            ASM_SCHED_BARRIER();
            fast0 = sp10[0];
            fast1 = sp10[1];
            fast2 = sp10[2];
            fast3 = M2C_FIELD(temp_s1, u16 *, 0x10);
            fast4 = M2C_FIELD(temp_s1, u16 *, 0x12);
            fast5 = M2C_FIELD(temp_s1, u16 *, 0x14);
            fast6 = M2C_FIELD(temp_s1, u16 *, 0x18);
            fast7 = M2C_FIELD(temp_s1, u16 *, 0x1A);
            fast8 = M2C_FIELD(temp_s1, u16 *, 0x1C);
            fast9 = M2C_FIELD(temp_s1, u16 *, 0x20);
            fast10 = M2C_FIELD(temp_s1, u16 *, 0x22);
            fast11 = M2C_FIELD(temp_s1, u16 *, 0x24);
            fast_page[-0x30A8] = 0;
            M2C_FIELD(temp_s1, u16 *, 8) = fast0;
            M2C_FIELD(temp_s1, u16 *, 0x28) = fast0;
            M2C_FIELD(temp_s1, u16 *, 0xA) = fast1;
            M2C_FIELD(temp_s1, u16 *, 0xC) = fast2;
            M2C_FIELD(temp_s1, u16 *, 0x2C) = fast2;
            M2C_FIELD(temp_s1, u16 *, 0x10) = fast3;
            M2C_FIELD(temp_s1, u16 *, 0x12) = fast4;
            M2C_FIELD(temp_s1, u16 *, 0x14) = fast5;
            M2C_FIELD(temp_s1, u16 *, 0x18) = fast6;
            M2C_FIELD(temp_s1, u16 *, 0x1A) = fast7;
            M2C_FIELD(temp_s1, u16 *, 0x1C) = fast8;
            M2C_FIELD(temp_s1, u16 *, 0x20) = fast9;
            M2C_FIELD(temp_s1, u16 *, 0x22) = fast10;
            M2C_FIELD(temp_s1, u16 *, 0x24) = fast11;
            goto L_CFB98;
        }
        ASM_SCHED_BARRIER();
        {
            register s32 interp_v0 ASM_REG("$2");
            register s32 interp_v1 ASM_REG("$3");
            register s32 interp_a0 ASM_REG("$4");
            register s32 interp_a1 ASM_REG("$5");
            register s32 interp_a2 ASM_REG("$6");

            interp_v1 = (s16)sp10[0];
            interp_v0 = (s16)M2C_FIELD(temp_s1, u16 *, 8);
            interp_a0 = (s16)sp10[1];
            interp_a1 = (s16)M2C_FIELD(temp_s1, u16 *, 0xA);
            interp_v1 -= interp_v0;
            interp_v1 >>= 1;
            interp_a0 -= interp_a1;
            interp_a0 >>= 1;
            interp_v0 = M2C_FIELD(temp_s1, u16 *, 8);
            interp_a1 = (s16)M2C_FIELD(temp_s1, u16 *, 0xC);
            interp_v0 += interp_v1;
            M2C_FIELD(temp_s1, u16 *, 8) = (u16)interp_v0;
            interp_v0 = M2C_FIELD(temp_s1, u16 *, 0xA);
            interp_v1 = (s16)sp10[2];
            interp_v0 += interp_a0;
            interp_v1 -= interp_a1;
            interp_v1 >>= 1;
            M2C_FIELD(temp_s1, u16 *, 0xA) = (u16)interp_v0;
            interp_v0 = M2C_FIELD(temp_s1, u16 *, 0xC);
            interp_a0 = (s16)sp10[4];
            interp_a1 = (s16)M2C_FIELD(temp_s1, u16 *, 0x10);
            interp_v0 += interp_v1;
            interp_a0 -= interp_a1;
            interp_a0 >>= 1;
            M2C_FIELD(temp_s1, u16 *, 0xC) = (u16)interp_v0;
            interp_v0 = M2C_FIELD(temp_s1, u16 *, 0x10);
            interp_v1 = (s16)sp10[5];
            interp_a1 = (s16)M2C_FIELD(temp_s1, u16 *, 0x12);
            interp_v0 += interp_a0;
            interp_v1 -= interp_a1;
            interp_v1 >>= 1;
            M2C_FIELD(temp_s1, u16 *, 0x10) = (u16)interp_v0;
            interp_v0 = M2C_FIELD(temp_s1, u16 *, 0x12);
            interp_a0 = (s16)sp10[6];
            interp_a1 = (s16)M2C_FIELD(temp_s1, u16 *, 0x14);
            interp_v0 += interp_v1;
            interp_a0 -= interp_a1;
            interp_a0 >>= 1;
            M2C_FIELD(temp_s1, u16 *, 0x12) = (u16)interp_v0;
            interp_v0 = M2C_FIELD(temp_s1, u16 *, 0x14);
            interp_v1 = (s16)sp10[8];
            interp_a1 = (s16)M2C_FIELD(temp_s1, u16 *, 0x18);
            interp_v0 += interp_a0;
            interp_v1 -= interp_a1;
            interp_v1 >>= 1;
            M2C_FIELD(temp_s1, u16 *, 0x14) = (u16)interp_v0;
            interp_v0 = M2C_FIELD(temp_s1, u16 *, 0x18);
            interp_a0 = (s16)sp10[9];
            interp_a1 = (s16)M2C_FIELD(temp_s1, u16 *, 0x1A);
            interp_v0 += interp_v1;
            interp_a0 -= interp_a1;
            interp_a0 >>= 1;
            M2C_FIELD(temp_s1, u16 *, 0x18) = (u16)interp_v0;
            interp_v0 = M2C_FIELD(temp_s1, u16 *, 0x1A);
            interp_v1 = (s16)sp10[10];
            interp_a1 = (s16)M2C_FIELD(temp_s1, u16 *, 0x1C);
            interp_v0 += interp_a0;
            interp_v1 -= interp_a1;
            M2C_FIELD(temp_s1, u16 *, 0x1A) = (u16)interp_v0;
            interp_v0 = M2C_FIELD(temp_s1, u16 *, 0x1C);
            ASM_SCHED_BARRIER();
            interp_v1 >>= 1;
            interp_v0 += interp_v1;
            M2C_FIELD(temp_s1, u16 *, 0x1C) = (u16)interp_v0;
            ASM_SCHED_BARRIER();
            interp_v1 = (s16)sp10[12];
            interp_v0 = (s16)M2C_FIELD(temp_s1, u16 *, 0x20);
            interp_a0 = (s16)sp10[13];
            interp_a1 = (s16)M2C_FIELD(temp_s1, u16 *, 0x22);
            interp_a2 = M2C_FIELD(temp_s1, u16 *, 0xC);
            interp_v1 -= interp_v0;
            interp_v1 >>= 1;
            interp_a0 -= interp_a1;
            interp_v0 = M2C_FIELD(temp_s1, u16 *, 0x20);
            interp_a1 = (s16)M2C_FIELD(temp_s1, u16 *, 0x24);
            interp_v0 += interp_v1;
            M2C_FIELD(temp_s1, u16 *, 0x20) = (u16)interp_v0;
            interp_v0 = M2C_FIELD(temp_s1, u16 *, 0x22);
            interp_v1 = (s16)sp10[14];
            interp_a0 >>= 1;
            M2C_FIELD(temp_s1, u16 *, 0x2C) = (u16)interp_a2;
            interp_v0 += interp_a0;
            interp_v1 -= interp_a1;
            interp_v1 >>= 1;
            M2C_FIELD(temp_s1, u16 *, 0x22) = (u16)interp_v0;
            interp_v0 = M2C_FIELD(temp_s1, u16 *, 0x24);
            interp_a0 = M2C_FIELD(temp_s1, u16 *, 8);
            interp_a1 = M2C_FIELD(temp_s1, u16 *, 0xA);
            interp_v0 += interp_v1;
            M2C_FIELD(temp_s1, u16 *, 0x24) = (u16)interp_v0;
            M2C_FIELD(temp_s1, u16 *, 0x28) = (u16)interp_a0;
            M2C_FIELD(temp_s1, u16 *, 0x2A) = (u16)interp_a1;
        }
L_CFB98:
        {
            register s32 init_v0 ASM_REG("$2");
            register s32 init_v1 ASM_REG("$3");
            register s32 init_a3 ASM_REG("$7");
            register s32 init_t0 ASM_REG("$8");
            register s32 init_t1 ASM_REG("$9");
            register s32 init_t2 ASM_REG("$10");
            register s32 init_t3 ASM_REG("$11");
            register s32 init_t4 ASM_REG("$12");

            call_a0 = temp_s1 + 8;
            ASM_KEEP(call_a0);
            call_a1 = ram_base + 0x01C;
            ASM_KEEP(call_a1);
            init_v0 = M2C_FIELD(temp_s1, s32 *, 0x90);
            ASM_KEEP(init_v0);
            call_a2 = (s32)(ram_base + 0x174);
            ASM_KEEP(call_a2);
            *(s32 *)(ram_base + 0x000) = init_v0;
            ASM_SCHED_BARRIER();
            init_v0 = (s32)0x80010000;
            ASM_KEEP(init_v0);
            init_v1 = (s32)M2C_FIELD(var_s6, void **, 0);
            init_a3 = M2C_FIELD(temp_s5, s16 *, 0x14);
            init_t0 = M2C_FIELD(temp_s5, s16 *, 0x16);
            init_t1 = M2C_FIELD(temp_s5, s16 *, 0x18);
            init_t2 = M2C_FIELD(temp_s5, s16 *, 0x1A);
            ASM_KEEP4(init_a3, init_t0, init_t1, init_t2);
            init_t3 = *(s32 *)(init_v0 + 0x3180);
            init_t4 = *(u8 *)(init_v0 + 0x3184);
            init_v0 = *(u8 *)(init_v0 + 0x3185);
            init_v1 += 0xB8;
            ASM_KEEP(init_v1);
            *(s32 *)(ram_base + 0x124) = init_a3;
            ASM_SCHED_BARRIER();
            *(u16 *)(ram_base + 0x178) = (u16)init_v0;
            ASM_SCHED_BARRIER();
            init_v0 = init_a3;
            ASM_KEEP(init_v0);
            *(s32 *)(ram_base + 0x0BC) = init_v1;
            ASM_SCHED_BARRIER();
            init_v1 = 0x40;
            ASM_KEEP(init_v1);
            init_v0 = init_v1 << init_v0;
            ASM_KEEP(init_v0);
            *(s32 *)(ram_base + 0x128) = init_t0;
            ASM_SCHED_BARRIER();
            *(s32 *)(ram_base + 0x114) = init_v0;
            ASM_SCHED_BARRIER();
            init_v0 = init_t0;
            ASM_KEEP(init_v0);
            init_v1 <<= init_v0;
            ASM_KEEP(init_v1);
            *(s32 *)(ram_base + 0x11C) = init_t1;
            ASM_SCHED_BARRIER();
            *(s32 *)(ram_base + 0x120) = init_t2;
            ASM_SCHED_BARRIER();
            *(s32 *)(ram_base + 0x110) = init_t3;
            ASM_SCHED_BARRIER();
            *(u16 *)(ram_base + 0x176) = (u16)init_t4;
            ASM_SCHED_BARRIER();
            init_a3 = (s32)M2C_FIELD(var_s6, void **, 0);
            init_v0 = 0xAF3A;
            *(s32 *)(ram_base + 0x118) = init_v1;
            ASM_SCHED_BARRIER();
            pkt_s1 = (u8 *)M2C_FIELD((void *)init_a3, void **, 0x8D0);
            ASM_SCHED_BARRIER();
            init_a3 += init_v0;
            init_v0 = 0xFFFF;
            *(s32 *)(ram_base + 0x14C) = init_v0;
            *(s32 *)(ram_base + 0x17C) = init_a3;
            *(u16 *)(ram_base + 0x174) = 4U;
            *(s32 *)(ram_base + 0x00C) = (s16)func_80046C20(call_a0, call_a1, call_a2, (void *)init_a3);
        }
        if (*(u16 *)(ram_base + 0x174) != 0) {
            register s32 hold_t1 ASM_REG("$9");
            register s32 hold_t2 ASM_REG("$10");
            register s32 hold_t3 ASM_REG("$11");
            register s32 hold_t5 ASM_REG("$13");

            hold_t2 = 1;
            hold_t3 = 0x7FFF;
            hold_t1 = 0xFFFFFF;
            hold_t5 = (s32)0xFF000000;
            ASM_KEEP4(hold_t2, hold_t3, hold_t1, hold_t5);
loop_9:
            call_a2 = 3;
            var_a0 = (s32 *)(ram_base + 0x78);
            do {
                ASM_KEEP(var_a0);
                if (M2C_FIELD(var_a0, s32 *, 0x38) == 0) {
                    s32 lim_v1;
                    s32 cur_v0;

                    lim_v1 = M2C_FIELD(var_a0, s32 *, 0x34);
                    cur_v0 = *(s32 *)(ram_base + 0x00C);
                    if (cur_v0 >= lim_v1) {
                        M2C_FIELD(var_a0, s32 *, 0x38) = hold_t2;
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
            if (M2C_FIELD(var_a1, s32 *, 0x38) > 0) {
                temp_v1 = M2C_FIELD(var_a1, s32 *, 0x1C);
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
                    register s32 step_v0 ASM_REG("$2");
                    register s32 step_v1 ASM_REG("$3");
                    register s32 step_a0 ASM_REG("$4");

                    step_v1 = M2C_FIELD(var_a1, s32 *, 0x2C);
                    step_v0 = M2C_FIELD(var_a1, s32 *, 0x24);
                    step_v1 += step_v0;
                    M2C_FIELD(var_a1, s32 *, 0x2C) = step_v1;
                    if (step_v1 >= 0) {
loop_22:
                        step_v1 = M2C_FIELD(var_a1, s32 *, 0x1C);
                        step_v0 = M2C_FIELD(var_a1, s32 *, 0x30);
                        step_a0 = M2C_FIELD(var_a1, s32 *, 0x20);
                        step_v1 += step_v0;
                        step_v0 = M2C_FIELD(var_a1, s32 *, 0x2C);
                        M2C_FIELD(var_a1, s32 *, 0x1C) = step_v1;
                        step_v1 = M2C_FIELD(var_a1, s32 *, 0x3C);
                        step_v0 -= step_a0;
                        step_v1 -= 0x40;
                        M2C_FIELD(var_a1, s32 *, 0x2C) = step_v0;
                        M2C_FIELD(var_a1, s32 *, 0x3C) = step_v1;
                        if ((step_v1 > 0) && (step_v0 >= 0)) {
                            goto loop_22;
                        }
                    }
                }
                temp_v1_4 = M2C_FIELD(var_a1, s32 *, 0x1C);
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
                            temp_t0_2 = ((void **)M2C_FIELD(temp_s5, void **, 4))[temp_s3[*(s32 *)(ram_base + 0x144)].index];
L_CFE98:
                            {
                                register s32 geom_v0 ASM_REG("$2");
                                register s32 geom_v1 ASM_REG("$3");
                                register s32 geom_a0 ASM_REG("$4");
                                register s32 geom_a1 ASM_REG("$5");
                                register u16 geom_a0h ASM_REG("$4");
                                register u16 geom_a1h ASM_REG("$5");
                                register u16 geom_v0h ASM_REG("$2");

                                geom_v0 = M2C_FIELD(temp_t0_2, s32 *, 0x10);
                                geom_a0h = *(volatile u16 *)(ram_base + 0x014);
                                *(volatile s32 *)(ram_base + 0x170) = geom_v0;
                                geom_v0 = M2C_FIELD(temp_t0_2, u16 *, 0);
                                geom_v1 = M2C_FIELD(temp_t0_2, s32 *, 0x14);
                                geom_v0 <<= 3;
                                geom_v0 += (s32)temp_s2;
                                *(volatile s32 *)(ram_base + 0x16C) = geom_v1;
                                geom_v0 = M2C_FIELD((void *)geom_v0, s32 *, 0);
                                geom_v1 = *(volatile u16 *)(ram_base + 0x12C);
                                *(volatile s32 *)(ram_base + 0x164) = geom_v0;
                                geom_v0 = M2C_FIELD(temp_t0_2, u16 *, 0);
                                geom_a1h = *(volatile u16 *)(ram_base + 0x164);
                                geom_v0 <<= 3;
                                geom_v0 += (s32)temp_s2;
                                geom_a0 = geom_a0h + geom_a1h;
                                geom_v0 = M2C_FIELD((void *)geom_v0, u16 *, 4);
                                geom_a0 &= 0xFFFF;
                                geom_v0 -= geom_v1;
                                *(volatile u16 *)(ram_base + 0x0E4) = (u16)geom_v0;
                                geom_v0 = *(volatile u16 *)(ram_base + 0x166);
                                geom_v1 = *(volatile s32 *)(ram_base + 0x00C);
                                geom_v0 = (s16)geom_v0;
                                geom_v1 += geom_v0;
                                geom_v1 <<= 16;
                                geom_v0 = M2C_FIELD(temp_t0_2, u16 *, 2);
                                geom_a0 |= geom_v1;
                                *(volatile s32 *)(ram_base + 0x0E0) = geom_a0;

                                geom_a0h = *(volatile u16 *)(ram_base + 0x014);
                                geom_v1 = *(volatile u16 *)(ram_base + 0x12C);
                                geom_v0 <<= 3;
                                geom_v0 += (s32)temp_s2;
                                geom_v0 = M2C_FIELD((void *)geom_v0, s32 *, 0);
                                *(volatile s32 *)(ram_base + 0x164) = geom_v0;
                                geom_v0 = M2C_FIELD(temp_t0_2, u16 *, 2);
                                geom_a1h = *(volatile u16 *)(ram_base + 0x164);
                                geom_v0 <<= 3;
                                geom_v0 += (s32)temp_s2;
                                geom_a0 = geom_a0h + geom_a1h;
                                geom_v0 = M2C_FIELD((void *)geom_v0, u16 *, 4);
                                geom_a0 &= 0xFFFF;
                                geom_v0 -= geom_v1;
                                *(volatile u16 *)(ram_base + 0x0EC) = (u16)geom_v0;
                                geom_v0 = *(volatile u16 *)(ram_base + 0x166);
                                geom_v1 = *(volatile s32 *)(ram_base + 0x00C);
                                geom_v0 = (s16)geom_v0;
                                geom_v1 += geom_v0;
                                geom_v1 <<= 16;
                                geom_v0 = M2C_FIELD(temp_t0_2, u16 *, 4);
                                geom_a0 |= geom_v1;
                                *(volatile s32 *)(ram_base + 0x0E8) = geom_a0;

                                geom_a0h = *(volatile u16 *)(ram_base + 0x014);
                                geom_v0 <<= 3;
                                geom_v0 += (s32)temp_s2;
                                geom_v0 = M2C_FIELD((void *)geom_v0, s32 *, 0);
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
                                geom_v0 = M2C_FIELD(temp_t0_2, u16 *, 4);
                                geom_v0 <<= 3;
                                geom_v0 += (s32)temp_s2;
                                geom_v1 = M2C_FIELD((void *)geom_v0, u16 *, 4);
                                geom_v0 = *(volatile u16 *)(ram_base + 0x12C);
                                geom_v1 -= geom_v0;
                                *(volatile u16 *)(ram_base + 0x0F4) = (u16)geom_v1;
                            }
                            gte_ldv3(ram_base + 0xE0, ram_base + 0xE8, ram_base + 0xF0);
                            {
                                register s32 corner_hi ASM_REG("$3");
                                register s32 corner_lo ASM_REG("$2");

                                corner_hi = M2C_FIELD(((M2C_FIELD(temp_t0_2, u16 *, 6) * 8) + temp_s2), u16 *, 4);
                                ASM_SCHED_BARRIER();
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
                                        if (M2C_FIELD(temp_v1_11, s16 *, 4) >= 0) {
                                            temp_v1_12 = M2C_FIELD(temp_v1_11, s32 *, 0);
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
                                                    register s32 h_v0 ASM_REG("$2");
                                                    register s32 h_v1 ASM_REG("$3");
                                                    register s32 h_a0 ASM_REG("$4");
                                                    register s32 h_a1 ASM_REG("$5");

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
                                    *(s32 *)(ram_base + 0x164) = M2C_FIELD((M2C_FIELD(temp_t0_2, u16 *, 6) * 8) + temp_s2, s32 *, 0);
                                    *(s32 *)(ram_base + 0x0F8) = (((u16) *(s32 *)(ram_base + 0x014) + (u16) *(s32 *)(ram_base + 0x164)) & 0xFFFF) | ((*(s32 *)(ram_base + 0x00C) + (s16) *(s32 *)(ram_base + 0x166)) << 0x10);
                                    gte_ldv0(ram_base + 0xF8);
                                    M2C_FIELD(var_a3, s32 *, 5) = (s32) M2C_FIELD(temp_t0_2, s32 *, 8);
                                    gte_rtps_nn();
                                    M2C_FIELD(var_a3, s32 *, 0xD) = (s32) M2C_FIELD(temp_t0_2, s32 *, 0xC);
                                    M2C_FIELD(var_a3, u16 *, 0x15) = (u16) *(s32 *)(ram_base + 0x172);
                                    M2C_FIELD(var_a3, u16 *, 0x1D) = (u16) *(s32 *)(ram_base + 0x16C);
                                    gte_stsxy(pkt_s1 + 0x20);
                                    gte_stszotz(ram_base + 0xD4);
                                    {
                                        register s32 m_v0 ASM_REG("$2");
                                        register s32 m_v1 ASM_REG("$3");
                                        register s32 m_a0 ASM_REG("$4");

                                        m_v0 = *(s32 *)(ram_base + 0x0C8);
                                        m_a0 = *(s32 *)(ram_base + 0x0D4);
                                        m_v1 = m_v0 << 1;
                                        m_v0 += m_v1;
                                        m_v0 += m_a0;
                                        temp_v1_16 = m_v0 >> 2;
                                    }
                                    *(s32 *)(ram_base + 0x0C8) = temp_v1_16;
                                    if ((u32) temp_v1_16 < 0x1BEU) {
                                        M2C_FIELD(var_a3, s8 *, -4) = 9;
                                        M2C_FIELD(var_a3, s32 *, -3) = (s32) *(s32 *)(ram_base + 0x004);
                                        var_a0_3 = *(u8 *)(ram_base + 0x16F);
                                        if (var_a0_3 & 1) {
                                            *(u8 *)var_a3 = (u8) (*(u8 *)var_a3 | 2);
                                            goto L_D0540;
                                        }
                                        if ((*(u16 *)(ram_base + 0x178) != 0) && (temp_s3[*(s32 *)(ram_base + 0x144)].flags & 0x80) && !(var_a0_3 & 2) && ((temp_v1_17 = *(s32 *)(ram_base + 0x158), (((s16) *(u16 *)(ram_base + 0x0E4) < temp_v1_17) != 0)) || ((s16) *(u16 *)(ram_base + 0x0EC) < temp_v1_17) || ((s16) *(u16 *)(ram_base + 0x0F4) < temp_v1_17) || ((s16) *(u16 *)(ram_base + 0x0FC) < temp_v1_17))) {
                                            M2C_FIELD(var_a3, s32 *, 5) = (s32) M2C_FIELD(var_a3, s32 *, 9);
                                            M2C_FIELD(var_a3, s32 *, 9) = (s32) M2C_FIELD(var_a3, s32 *, 0x11);
                                            M2C_FIELD(var_a3, s32 *, 0xD) = (s32) M2C_FIELD(var_a3, s32 *, 0x19);
                                            temp_a0_3 = *(s32 *)(ram_base + 0x110);
                                            M2C_FIELD(var_a3, s8 *, -4) = 5;
                                            M2C_FIELD(var_a3, s32 *, -3) = temp_a0_3;
                                            var_a3 += 0x28;
                                            *(s32 *)pkt_s1 = (*(s32 *)pkt_s1 & hold_t5) | (*(s32 *)((*(s32 *)(ram_base + 0x0C8) * 4) + *(s32 *)(ram_base + 0x0BC)) & hold_t1);
                                            temp_a0_4 = (s32 *)((*(s32 *)(ram_base + 0x0C8) * 4) + *(s32 *)(ram_base + 0x0BC));
                                            {
                                                s32 rm_v0;
                                                register s32 rm_v1 ASM_REG("$3");

                                                rm_v0 = (s32) pkt_s1 & hold_t1;
                                                rm_v1 = *temp_a0_4;
                                                pkt_s1 += 0x28;
                                                rm_v1 &= hold_t5;
                                                rm_v1 |= rm_v0;
                                                *temp_a0_4 = rm_v1;
                                            }
                                            M2C_FIELD(var_a3, s8 *, -4) = hold_t2;
                                            {
                                                register s32 pk_v1 ASM_REG("$3");

                                                pk_v1 = (s32) ((*(u16 *)(ram_base + 0x176) & 0x9FF) | 0xE1000000);
                                                M2C_FIELD(var_a3, s32 *, -3) = pk_v1;
                                            }
                                        }
L_D0540:
                                        var_a3 += 0x28;
                                        var_a0_2 = (void *) ((s32) pkt_s1 & hold_t1);
                                        goto L_D057C;
                                    }
                                    if ((u32) temp_v1_16 < 0x1DEU) {
                                        M2C_FIELD(var_a3, s8 *, -4) = 9;
                                        M2C_FIELD(var_a3, s32 *, -3) = (s32) *(s32 *)(ram_base + 0x004);
                                        var_a0_2 = (void *) ((s32) pkt_s1 & hold_t1);
                                        M2C_FIELD(var_a3, u8 *, 0) = (u8) (M2C_FIELD(var_a3, u8 *, 0) | 2);
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
                            if (M2C_FIELD(((*(u16 *)(ram_base + 0x170) * 8) + temp_s4), s16 *, 4) >= 0) {
                                goto L_D0644;
                            }
                            {
                                register s32 cmp_v0 ASM_REG("$2");
                                register s32 cmp_v1 ASM_REG("$3");

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
                    ASM_KEEP(var_v1);
                    if (M2C_FIELD(var_v1, s32 *, 0x38) > 0) {
                        temp_v0_8 = M2C_FIELD(var_v1, s32 *, 0x28) - 0x40;
                        M2C_FIELD(var_v1, s32 *, 0x28) = temp_v0_8;
                        if (temp_v0_8 < -0x7F) {
                            M2C_FIELD(var_v1, s32 *, 0x38) = minus_one;
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
        M2C_FIELD(M2C_FIELD(var_s6, void **, 0), void **, 0x8D0) = pkt_s1;
    }
}
