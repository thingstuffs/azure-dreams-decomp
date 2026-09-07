#include "common.h"

#define FIELD(base, type, off) (*(type *)((u8 *)(base) + (off)))

extern u8 D_80083160[];
extern void func_80065034(void *arg0, void *arg1, void *arg2);
extern void func_8006658C(s32 arg0, void *arg1);

void func_800D1824(u8 *arg0)
{
    register u8 *scratch ASM_REG("$16") = (u8 *)0x1F800000;
    u8 *globals = D_80083160;
    u8 *input = arg0;
    u8 *style;
    register u8 *prim ASM_REG("$18");
    u8 *rec;
    register u8 *cmd ASM_REG("$17");
    u8 *gte0;
    u8 *root;
    u8 *draw_prim;
    u8 *vertex1;
    u8 *vertex2;
    s32 x;
    s32 y;
    s32 depth;
    s32 otz;
    u16 rec_value;

    FIELD(scratch, volatile s32, 0x28) = 0;
    root = FIELD(globals, u8 *, 0);
    style = FIELD(FIELD(globals, u8 *, 0x1E0), u8 *, 0x10);
    prim = FIELD(root, u8 *, 0x8D0);
    FIELD(scratch, volatile s16, 0x2C) = -0x1000;
    FIELD(scratch, volatile u8 *, 0x20) = root + 0xB0;

    ASM_KEEP(input);
    if (*input != 0) {
        ASM_SCHED_BARRIER();
        gte0 = scratch + 0x70;
        ASM_KEEP_NV(scratch);
        rec = arg0 + 2;
        cmd = prim + 3;

        do {
            if (FIELD(rec, u16, 0) != 0x8000) {
                do { vertex1 = scratch + 0x78; } while (0);
                x = (s32)*input << 6;
                FIELD(scratch, volatile s16, 0x80) = (s16)x;
                FIELD(scratch, volatile s16, 0x70) = (s16)x;
                x += 0x40;
                FIELD(scratch, volatile s16, 0x88) = (s16)x;
                FIELD(scratch, volatile s16, 0x78) = (s16)x;

                y = (s32)FIELD(rec, u8, -1) << 6;
                FIELD(scratch, volatile s16, 0x7A) = (s16)y;
                FIELD(scratch, volatile s16, 0x72) = (s16)y;
                y += 0x40;
                FIELD(scratch, volatile s16, 0x8A) = (s16)y;
                FIELD(scratch, volatile s16, 0x82) = (s16)y;

                rec_value = FIELD(rec, u16, 0);
                FIELD(scratch, volatile u16, 0x84) = rec_value;
                FIELD(scratch, volatile u16, 0x7C) = rec_value;
                FIELD(scratch, volatile u16, 0x74) = rec_value;

                vertex2 = scratch + 0x80;
                gte_ldv3(gte0, vertex1, vertex2);
                FIELD(scratch, volatile u16, 0x8C) =
                    FIELD(rec, volatile u16, 0);
                gte_rtpt_nn();
                gte_nclip();
                gte_stopz(scratch + 0x114);

                if (FIELD(scratch, volatile s32, 0x114) > 0) {
                    gte_stsxy3_g3(prim);
                    gte_avsz3();
                    gte_stotz(scratch + 0xC0);
                    gte_ldv0(scratch + 0x88);
                    otz = FIELD(scratch, volatile s32, 0xC0);
                    otz = otz * 3;
                    FIELD(scratch, volatile s32, 0xC0) = otz;

                    gte_rtps_nn();
                    gte_stszotz(scratch + 0xCC);
                    depth = (FIELD(scratch, volatile s32, 0xC0) +
                             FIELD(scratch, volatile s32, 0xCC)) >> 2;
                    FIELD(scratch, volatile s32, 0xC0) = depth;

                    if ((u32)depth < 0x1E0) {
                        gte_stsxy(prim + 0x20);
                        draw_prim = prim;
                        func_80065034(scratch + 0x28, globals + 0xA8,
                                     prim + 4);

                        FIELD(cmd, u32, 9) = FIELD(style, u32, 8);
                        FIELD(cmd, u32, 0x11) = FIELD(style, u32, 0xC);
                        FIELD(cmd, u16, 0x19) = FIELD(style, u16, 0x12);
                        prim += 0x28;
                        FIELD(cmd, u16, 0x21) = FIELD(style, u16, 0x14);
                        cmd[0] = 9;
                        cmd += 0x28;
                        func_8006658C(
                            (s32)FIELD(scratch, volatile u8 *, 0x20) +
                                (FIELD(scratch, volatile s32, 0xC0) << 2),
                            draw_prim);
                    }
                }
            }

            input += 4;
            rec += 4;
        } while (*input != 0);
    }

    FIELD(FIELD(globals, u8 *, 0), u8 *, 0x8D0) = prim;
}
