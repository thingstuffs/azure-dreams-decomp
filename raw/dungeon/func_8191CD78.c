#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))
#define LOCAL(t, o) FIELD(local, t, o)
#define DELTA(i) FIELD(local, s16, 0x18 + ((i) * 2))

extern void *jtbl_80024008[];
__asm__(".set jtbl_80024008, 0x80024008");

extern s32 func_8003DE58(void *, void *, s16 *, s32);
extern s32 func_800A44E0(s32, s32, s16, s32);
extern s16 func_800BCB04(s32, s32, s16);
extern void func_80024138(void *);
extern void func_800243CC(void *, void *);
extern void func_800419EC(u16, u16);
extern s32 func_80053EF0(s32);
extern void func_800542BC(void);
extern void func_8009CE1C(void *, s32, u8, s32, s32, void *, s32);
extern void func_800A56E0(s32);

extern s32 D_8008346C[];
extern s32 D_800814A0[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern u8 D_800DDC40[];

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Coord;

void func_80024578(void *arg0, void *arg1, void *arg2)
{
    register void *self ASM_REG("$17") = arg0;
    register void *out ASM_REG("$22");
    register void *root;
    register void *arg2_reg = arg2;
    void **table;
    register void *base;
    void *source;
    register void *source2 ASM_REG("$3");
    void *part;
    void *object;
    s32 state;
    u16 ctr;
    s32 i;
    register s32 delta_x ASM_REG("$4");
    s32 delta_y;
    s32 delta_z;
    u16 copied_z;
    u16 next_state;
    register s32 x_base ASM_REG("$7");
    register s32 y_base;
    u8 local[32];
    u16 saved_y;
    s16 step;
    s16 *scan1;
    register u32 dead_page ASM_REG("$2");
    register s16 final_floor ASM_REG("$2");
    static void *const keepalive[] = {
        &&case_0, &&case_1_entry, &&case_7, &&case_motion_flags,
        &&case_1, &&case_10, &&case_2, &&case_3,
        &&case_4, &&case_5, &&case_6, &&case_7,
        &&case_8, &&case_9, &&case_10, &&case_11,
    };

    ASM_KEEP_NV(self);
    ctr = FIELD(self, u16, 0x10);
    state = FIELD(self, s16, 0xA);
    root = FIELD(self, void *, 0);
    out = arg1;
    FIELD(self, u16, 0x10) = (u16)(ctr + 1);
    if ((u32)state >= 16U) {
        goto finish;
    }
    table = jtbl_80024008;
    (void)keepalive;
    goto *table[state];

case_0:
    FIELD(self, u16, 0x10) = 0;
    FIELD(self, u16, 0xA) = (u16)(FIELD(self, u16, 0xA) + 1);
    FIELD(self, u16, 0xE) = (u16)((FIELD(root, u16, 0x2A) >> 9) & 7);
    FIELD(arg2_reg, s32, 0xC) = 0x808080;
case_1_entry:
    base = (u8 *)root - 0x20;
    ASM_KEEP(base);
    source = FIELD(base, void *, 0xC);
    if (func_8003DE58(FIELD(source, void *, 8), source, (s16 *)(local + 0x18), 0) == 0) {
        if ((FIELD(FIELD(base, void *, 0xC), u16, 0x14) & 0x8000) == 0) {
            goto finish;
        }
    }
    part = FIELD(base, void *, 8);
    FIELD(out, u16, 2) = FIELD(part, u16, 2);
    FIELD(out, u16, 6) = FIELD(part, u16, 6);
    copied_z = FIELD(part, u16, 0xA);
    FIELD(out, u16, 0xA) = copied_z;
    {
        register u16 next_z ASM_REG("$2");

        if ((FIELD(FIELD(base, void *, 0xC), u16, 0x14) & 0x8000) == 0) {
            FIELD(out, u16, 2) = (u16)(FIELD(out, u16, 2) + DELTA(0));
            FIELD(out, u16, 6) = (u16)(FIELD(out, u16, 6) + DELTA(1));
            ASM_MEM_BARRIER();
            {
                register u16 blk_z ASM_REG("$2");
                register u16 blk_dz ASM_REG("$3");

                blk_z = FIELD(out, u16, 0xA);
                blk_dz = (u16)DELTA(2);
                next_z = (u16)(blk_z + blk_dz);
            }
        } else {
            next_z = (u16)(copied_z - 64);
        }
        FIELD(out, u16, 0xA) = next_z;
    }
    if ((FIELD(FIELD(self, void *, 4), u16, 0) & 0x80) == 0) {
        goto finish;
    }
    object = FIELD(root, void *, 0x60);
    i = 1;
    if (object != 0) {
        base = FIELD(FIELD(root, void *, 0x60), void *, -0x18);
        FIELD(self, void *, 0x20) = base;
        FIELD(self, void *, 0x1C) = FIELD(root, void *, 0x60);
        FIELD(self, void *, 0x24) =
            FIELD(FIELD(root, void *, 0x60), void *, -0x14);
        FIELD(self, u16, 0x16) = FIELD(FIELD(self, void *, 0x1C), u16, 0x88);
        FIELD(self, u16, 0x18) = FIELD(FIELD(self, void *, 0x1C), u16, 0x2A);

        delta_x = FIELD(base, s16, 2);
        delta_x -= FIELD(out, s16, 2);
        if (delta_x < 0) delta_x = -delta_x;
        DELTA(0) = (s16)delta_x;
        {
            register s32 dy ASM_REG("$2");
            register s32 ty ASM_REG("$3");
            dy = FIELD(base, s16, 6);
            ty = FIELD(out, s16, 6);
            dy -= ty;
            if (dy < 0) dy = -dy;
            DELTA(1) = (s16)dy;
        }
        {
            register s32 dz ASM_REG("$2");
            register s32 tz ASM_REG("$3");
            tz = FIELD(out, s16, 0xA);
            dz = FIELD(FIELD(root, void *, 0x60), s16, 0x88);
            ASM_SCHED_BARRIER();
            scan1 = (s16 *)(local + 2);
            ASM_KEEP(scan1);
            dz -= tz;
            if (dz < 0) dz = -dz;
            DELTA(2) = (s16)dz;
        }
        FIELD(self, s16, 0x12) = DELTA(0);
        i = 1;
        do {
            if (FIELD(scan1, s16, 0x18) > FIELD(self, s16, 0x12)) {
                FIELD(self, s16, 0x12) = FIELD(scan1, u16, 0x18);
            }
            i++;
            scan1++;
        } while (i < 3);
        step = (s16)(((u16)FIELD(self, s16, 0x12) << 16) >> 20);
        FIELD(self, s16, 0x12) = step;
        if (step == 0) {
            FIELD(self, s16, 0x12) = 1;
        }
        FIELD(out, s32, 0xC) =
            (FIELD(base, s32, 0) - FIELD(out, s32, 0)) / FIELD(self, s16, 0x12);
        FIELD(out, s32, 0x10) =
            (FIELD(base, s32, 4) - FIELD(out, s32, 4)) / FIELD(self, s16, 0x12);
        FIELD(out, s32, 0x14) =
            (((s32)FIELD(FIELD(root, void *, 0x60), s16, 0x88) << 16) -
             FIELD(out, s32, 8)) / FIELD(self, s16, 0x12);
        next_state = (u16)(FIELD(self, u16, 0xA) + 1);
        goto set_state;
    }

    i = 0;
    ASM_SCHED_BARRIER();
    source2 = FIELD(base, void *, 0xC);
    ASM_SCHED_BARRIER();
    dead_page = 0x80070000;
    ASM_KEEP(dead_page);
    {
        register s32 x ASM_REG("$20");
        register s32 y ASM_REG("$21");
        register s32 first_x;
        u16 stored_y;
        register s32 arg_x ASM_REG("$4");
        register s32 arg_z ASM_REG("$6");
        register s32 arg_y ASM_REG("$5");
        s32 signed_x;
        s32 signed_y;
        s32 x_adjust;
        s32 y_adjust;
        s16 *x_adjust_table;

        x = FIELD(source2, u8, 0x24);
        ASM_SCHED_BARRIER();
        y = FIELD(source2, u8, 0x25);
        ASM_SCHED_BARRIER();
        first_x = x;
        ASM_SCHED_BARRIER();
        saved_y = (u16)y;
        do {
            signed_x = (s16)x;
            signed_y = (s16)y;
            if ((func_800A44E0((signed_x << 6) & 0xFFC0, (signed_y << 6) & 0xFFC0,
                               FIELD(root, s16, 0x88),
                               (s16)(FIELD(self, u16, 0xE) << 9)) << 16) == 0) {
                s16 floor = func_800BCB04(
                    ((signed_x + ((s16 *)D_8006CCD8)[(s16)FIELD(self, u16, 0xE)]) << 6) + 0x20 & 0xFFE0,
                    ((signed_y + ((s16 *)D_8006CCE8)[(s16)FIELD(self, u16, 0xE)]) << 6) + 0x20 & 0xFFE0,
                    (s16)(FIELD(root, s16, 0x88) - 0x20));
                if ((floor < 513) && ((s16)(floor - FIELD(root, s16, 0x88)) >= -63)) {
                    register s32 next_x ASM_REG("$4");
                    register s32 next_y ASM_REG("$2");

                    i++;
                    next_x = x + ((u16 *)D_8006CCD8)[(s16)FIELD(self, u16, 0xE)];
                    x = next_x;
                    ASM_KEEP_NV(x);
                    next_y = y + ((u16 *)D_8006CCE8)[(s16)FIELD(self, u16, 0xE)];
                    y = next_y;
                    saved_y = (u16)next_y;
                    first_x = next_x;
                    if (i < 8) {
                        continue;
                    }
                }
            }
            break;
        } while (i < 8);

        base = local;
        x_base = (first_x << 16) >> 10;
        arg_x = (x_base + 0x20) & 0xFFE0;
        x_adjust_table = (s16 *)D_8006CCD8;
        ASM_CLOBBER("$6");
        arg_z = -0x400;
        i = 1;
        ASM_KEEP(i);
        stored_y = saved_y;
        y_base = (s32)stored_y << 16;
        y_base >>= 10;
        ASM_KEEP_DEP_NV(y_base, x_adjust_table);
        arg_y = y_base + 0x20;
        ASM_KEEP_NV(arg_y);
        x_adjust = x_adjust_table[(s16)FIELD(self, u16, 0xE)];
        FIELD(base, u16, 2) = (u16)(x_base + ((x_adjust + 1) << 5));
        y_adjust = ((s16 *)D_8006CCE8)[(s16)FIELD(self, u16, 0xE)];
        arg_y &= 0xFFE0;
        FIELD(base, u16, 6) = (u16)(y_base + ((y_adjust + 1) << 5));
        final_floor = func_800BCB04(arg_x, arg_y, arg_z);
        {
            register s32 expanded_floor ASM_REG("$2");
            register s32 widened_y ASM_REG("$3");
            register s32 out_y ASM_REG("$5");
            s16 *delta_scan = (s16 *)(local + 2);

            ASM_KEEP(delta_scan);
            FIELD(base, s16, 0xA) = final_floor;
            expanded_floor = (s32)final_floor << 16;
            ASM_KEEP(expanded_floor);
            delta_x = (s16)FIELD(base, u16, 2) - FIELD(out, s16, 2);
            if (delta_x < 0) delta_x = -delta_x;
            DELTA(0) = (s16)delta_x;
            widened_y = FIELD(base, u16, 6);
            out_y = FIELD(out, s16, 6);
            ASM_KEEP_DEP_NV(widened_y, out_y);
            widened_y <<= 16;
            widened_y >>= 16;
            widened_y -= out_y;
            if (widened_y < 0) widened_y = -widened_y;
            DELTA(1) = (s16)widened_y;
            expanded_floor >>= 16;
            expanded_floor -= FIELD(out, s16, 0xA);
            if (expanded_floor < 0) expanded_floor = -expanded_floor;
            DELTA(2) = (s16)expanded_floor;
            FIELD(self, s16, 0x12) = DELTA(0);
            do {
                if (FIELD(delta_scan, s16, 0x18) > FIELD(self, s16, 0x12)) {
                    FIELD(self, s16, 0x12) = FIELD(delta_scan, s16, 0x18);
                }
                i++;
                delta_scan++;
            } while (i < 3);
        }
    }
    step = (s16)(((u16)FIELD(self, s16, 0x12) << 16) >> 20);
    FIELD(self, s16, 0x12) = step;
    if (step == 0) {
        FIELD(self, s16, 0x12) = 1;
    }
    FIELD(out, s32, 0xC) =
        (FIELD(base, s32, 0) - FIELD(out, s32, 0)) / FIELD(self, s16, 0x12);
    FIELD(out, s32, 0x10) =
        (FIELD(base, s32, 4) - FIELD(out, s32, 4)) / FIELD(self, s16, 0x12);
    FIELD(out, s32, 0x14) =
        (FIELD(base, s32, 8) - FIELD(out, s32, 8)) / FIELD(self, s16, 0x12);
    ASM_CLOBBER("$3");
    next_state = 11;
set_state:
    FIELD(self, u16, 0xA) = next_state;
    FIELD(self, u16, 0x10) = 0;
    ASM_CLOBBER("$4");
    func_800243CC(self, out);
    goto finish;

case_motion_flags:
    FIELD(out, s32, 0) += FIELD(out, s32, 0xC);
    FIELD(out, s32, 4) += FIELD(out, s32, 0x10);
    FIELD(out, s32, 8) += FIELD(out, s32, 0x14);
    if (FIELD(self, s16, 0x10) < FIELD(self, s16, 0x12)) {
        goto finish;
    }
    func_800A56E0(0x300);
    func_800542BC();
    {
        void *owner = FIELD(self, void *, 0x1C);
        s32 flags;

        FIELD(self, u16, 0x1A) = 0;
        flags = FIELD(owner, s32, 0x14);
        if ((flags & 0x100000) != 0) {
            goto advance_state;
        }
        FIELD(owner, s32, 0x14) = flags | 0x100000;
        FIELD(self, u16, 0x1A) = 1;
    }
    goto advance_state;

case_1:
    if (func_80053EF0(4) == 1) {
        goto advance_state;
    }
    goto finish;

case_2:
    FIELD(FIELD(self, void *, 0x20), u16, 0xA) =
        (u16)(FIELD(FIELD(self, void *, 0x20), u16, 0xA) - FIELD(self, u16, 0x10));
    FIELD(FIELD(self, void *, 0x1C), u16, 0x2A) =
        (u16)(FIELD(FIELD(self, void *, 0x1C), u16, 0x2A) + 0x200);
    if (FIELD(self, s16, 0x10) >= 28) {
        register void *tail ASM_REG("$2") = FIELD(self, void *, 0x24);

        FIELD(tail, u16, 0x1A) = (u16)(FIELD(tail, u16, 0x1A) + 0x800);
        goto advance_state;
    }
    goto finish;

case_3:
    FIELD(FIELD(self, void *, 0x20), u16, 0xA) =
        (u16)(FIELD(FIELD(self, void *, 0x20), u16, 0xA) + FIELD(self, s16, 0x10) * 4);
    FIELD(FIELD(self, void *, 0x1C), u16, 0x2A) =
        (u16)(FIELD(FIELD(self, void *, 0x1C), u16, 0x2A) + 0x200);
    {
        register u8 *height_base ASM_REG("$2");
        register void *moving ASM_REG("$8");
        register u8 *height_entry ASM_REG("$7");
        register u16 max_height ASM_REG("$6");
        void *owner;
        register s32 fx_b ASM_REG("$5");
        register s32 fx_a ASM_REG("$4");

        height_base = D_800DDC40;
        owner = FIELD(self, void *, 0x1C);
        moving = FIELD(self, void *, 0x20);
        height_entry = height_base + FIELD(owner, u8, 0x13);
        fx_b = 16;
        if (FIELD(moving, s16, 0xA) >=
            FIELD(self, s16, 0x16) - FIELD(height_entry, u8, 0)) {
            fx_a = 8;
            ASM_CLOBBER("$16");
            i = 0;
            max_height = FIELD(self, u16, 0x16);
            FIELD(moving, u16, 0xA) =
                (u16)(max_height - FIELD(height_entry, u8, 0));
            func_800419EC(fx_a, fx_b);
case_3_loop:
            func_80024138(self);
            i++;
            if (i >= 8) {
                goto advance_state;
            }
            goto case_3_loop;
        }
    }
    goto finish;

case_4:
    FIELD(FIELD(self, void *, 0x1C), u16, 0x2A) =
        (u16)(FIELD(FIELD(self, void *, 0x1C), u16, 0x2A) + 0x200);
    i = 0;
    if (FIELD(self, s16, 0x10) == 2) {
        do {
            func_80024138(self);
            i++;
        } while (i < 8);
    }
    if (FIELD(self, s16, 0x10) < 12) {
        goto finish;
    }
    goto advance_state;

case_5:
    if (FIELD(self, s16, 0x10) < 4) {
        goto finish;
    }
    FIELD(FIELD(self, void *, 0x20), s32, 8) = FIELD(self, s32, 0x28);
    FIELD(FIELD(self, void *, 0x1C), u16, 0x2A) = FIELD(self, u16, 0x18);
    if (FIELD(self, s16, 0x1A) != 0) {
        FIELD(FIELD(self, void *, 0x1C), s32, 0x14) &= 0xFFEFFFFF;
    }
    FIELD(FIELD(self, void *, 0x24), u16, 0x1A) -= 0x800;
    func_8009CE1C(FIELD(root, void *, 0x60), 24, FIELD(self, u8, 9), 4,
                  (s16)(FIELD(self, u16, 0xE) << 9), root, 1);
    goto advance_state;

case_6:
    if (FIELD(self, s16, 0x14) != 0) {
        goto finish;
    }
    D_8008346C[0] = 0;
    FIELD(self, u16, -2) |= 0x8000;
    D_800814A0[0] |= 0x8000;
    goto finish;

case_7:
    func_800243CC(self, out);
    if (FIELD(self, s16, 0x10) < 15) {
        goto finish;
    }
    {
        void *next_part = FIELD(FIELD(self, void *, 0x20), void *, 8);

        FIELD(self, u16, 0xA) = (u16)(FIELD(self, u16, 0xA) + 1);
        FIELD(self, u16, 0x10) = 0;
        FIELD(self, void *, 0x28) = next_part;
    }
    goto finish;

case_8:
    FIELD(out, s32, 0) += FIELD(out, s32, 0xC);
    FIELD(out, s32, 4) += FIELD(out, s32, 0x10);
    FIELD(out, s32, 8) += FIELD(out, s32, 0x14);
    if (FIELD(self, s16, 0x10) < FIELD(self, s16, 0x12)) {
        goto finish;
    }
    func_800A56E0(0x300);
    func_800542BC();
    goto advance_state;

case_9:
    if (func_80053EF0(4) != 1) {
        goto finish;
    }
    goto advance_state;

case_10:
    if (FIELD(self, s16, 0x10) < 7) {
        goto finish;
    }

advance_state:
    FIELD(self, u16, 0xA) = (u16)(FIELD(self, u16, 0xA) + 1);
    FIELD(self, u16, 0x10) = 0;
    goto finish;

case_11:
    if (FIELD(self, s16, 0x10) >= 28) {
        func_800A56E0(116);
        FIELD(self, u16, 0xA) = 10;
        FIELD(self, u16, 0x10) = 0;
    }
    goto finish;

finish:
    FIELD(self, u16, 0x14) = 0;
}
