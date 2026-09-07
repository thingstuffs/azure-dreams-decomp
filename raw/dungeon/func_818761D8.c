#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct {
    u8 bytes[32];
} Copy32;

typedef struct {
    u8 bytes[12];
} Copy12;

typedef struct {
    s16 x;
    s16 y;
    u16 z;
} Vec3s;

typedef union {
    u16 u;
    s16 s;
} H16;

typedef struct {
    H16 x;
    H16 y;
} Pair;

/* These resident data/code addresses are not present in the catalog for this
 * cold overlay row; the binds retain real link-resolved symbols. */
__asm__(".set D_80024058, 0x80024058");
__asm__(".set D_80026634, 0x80026634");
__asm__(".set D_80026640, 0x80026640");
__asm__(".set D_8002664C, 0x8002664C");
__asm__(".set D_80026664, 0x80026664");
__asm__(".set D_80024704, 0x80024704");
__asm__(".set D_80024FD4, 0x80024FD4");
__asm__(".set D_80025470, 0x80025470");
__asm__(".set D_8006CCD8, 0x8006CCD8");
__asm__(".set D_8006CCE8, 0x8006CCE8");
__asm__(".set D_800DDC40, 0x800DDC40");
__asm__(".set D_8008346C, 0x8008346C");

__asm__(".set func_80025C04, 0x80025C04");
__asm__(".set func_80025DA4, 0x80025DA4");
__asm__(".set func_80025E9C, 0x80025E9C");
__asm__(".set func_80026044, 0x80026044");
__asm__(".set func_80026204, 0x80026204");
__asm__(".set func_80026428, 0x80026428");
__asm__(".set func_80026430, 0x80026430");
__asm__(".set func_80026534, 0x80026534");
__asm__(".set func_80026590, 0x80026590");
__asm__(".set func_80026600, 0x80026600");

extern Copy32 D_80024058;
extern Copy12 D_80026634;
extern Copy12 D_80026640;
extern Copy12 D_8002664C;
extern s16 D_80026664[8];
extern u8 D_80045340[];
extern u8 D_80024704[];
extern u8 D_80025814[];
extern u8 D_80024FD4[];
extern u8 D_80025470[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern u8 D_800DDC40[];
extern s32 D_8008346C[3];
extern s32 D_800814A0[3];

extern s32 func_8003DF74(void *, void *, Vec3s *, s32);
extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 func_80069EF8(void);
extern s32 func_800A4778(u16, u16, s16, void *);
extern void func_800A56E0(s32);
extern void func_80025338(void *, s32, s32, s32, s32, s32, s32);
extern void func_80024098(void *, u8, void *);
extern s32 func_80064584(s32);
extern s32 func_800644B8(s32);

extern void func_80025C04(void) __attribute__((noreturn));
extern void func_80025DA4(void) __attribute__((noreturn));
extern void func_80025E9C(void) __attribute__((noreturn));
extern void func_80026044(void) __attribute__((noreturn));
extern void func_80026204(void) __attribute__((noreturn));
extern void func_80026428(void) __attribute__((noreturn));
extern void func_80026430(void) __attribute__((noreturn));
extern void func_80026534(void) __attribute__((noreturn));
extern void func_80026590(void) __attribute__((noreturn));
extern void func_80026600(void) __attribute__((noreturn));

void func_800259D8(void *in0, void *in1, void *in2)
{
    Vec3s delta;
    Copy32 copy;
    register void *obj ASM_REG("$23");
    register void *base ASM_REG("$16");
    register void *entry ASM_REG("$17");
    void *node;
    void *work;
    register void *dst ASM_REG("$19");
    u32 state;
    register u16 old_count ASM_REG("$3");
    s16 count;
    s32 result;
    s32 index;
    s32 value;
    register s32 phase ASM_REG("$2");
    register s32 i ASM_REG("$21");
    register void *arg0 ASM_REG("$20");
    register void *arg1 ASM_REG("$22");
    void *arg2;
    void *spawn_code;

    arg0 = in0;
    arg1 = in1;
    arg2 = in2;

    ASM_KEEP_NV(arg0);
    ASM_KEEP_NV(arg1);

    obj = FIELD(arg0, void *, 0);
    copy = D_80024058;
    spawn_code = D_80025814;
    ASM_USE(dst);
    state = FIELD(arg0, s16, 0xA);
    base = (u8 *)obj - 0x20;
    entry = FIELD(base, void *, 8);
    switch (state) {
    case 0:
    {
        register s32 setup ASM_REG("$2");
        setup = 0x00808080;
        FIELD(arg2, s32, 0x0C) = setup;
        setup = 0x1000;
        FIELD(arg2, s16, 0x1E) = setup;
        FIELD(arg2, s16, 0x1C) = setup;
    }
    *(Copy12 *)((u8 *)arg0 + 0xA2) = D_80026634;
    {
        s32 init_value;
        u16 init_count;
        FIELD(arg2, void *, 8) = (u8 *)arg0 + 0xA2;
        init_value = (FIELD(obj, u16, 0x2A) >> 9) & 7;
        D_80026664[0] = 1;
        init_count = FIELD(arg0, u16, 0x0A) + 1;
        FIELD(arg0, s16, 0x80) = init_value;
        FIELD(arg0, u16, 0x0A) = init_count;
    }
    case 1:
    result = func_8003DF74(
        FIELD(FIELD(base, void *, 0x0C), void *, 8),
        FIELD(base, void *, 0x0C), &delta, 0);
    if (result == 0) {
        if (!(FIELD(FIELD(base, void *, 0x0C), u16, 0x14) & 0x8000U)) {
            goto done;
        }
    }
    {
    u16 z_value;
    FIELD(arg1, s16, 2) = FIELD(entry, s16, 2);
    FIELD(arg1, s16, 6) = FIELD(entry, s16, 6);
    z_value = FIELD(entry, u16, 0x0A);
    FIELD(arg1, u16, 0x0A) = z_value;
    if (FIELD(FIELD(base, void *, 0x0C), u16, 0x14) & 0x8000U) {
        goto L0_adjust_z;
    }
    ASM_SCHED_BARRIER();
    {
        register s32 tail_z ASM_REG("$2");
        FIELD(arg1, s16, 2) += delta.x;
        FIELD(arg1, s16, 6) += delta.y;
        ASM_SCHED_BARRIER();
        tail_z = FIELD(arg1, u16, 0x0A);
        tail_z = tail_z + delta.z;
        ASM_TAILSLOT_PIN(tail_z);
        func_80025C04();
    }
L0_adjust_z:
    ASM_SCHED_BARRIER();
    FIELD(arg1, s16, 0x0A) = z_value - 0x40;
    }
    if (!(FIELD(FIELD(arg0, void *, 4), u16, 0) & 0x80U)) {
        goto done;
    }
    if (!(FIELD(arg0, u8, 0x7A) & 4U)) {
        func_8004491C((u8 *)arg0 - 0x20, D_80045340);
        FIELD(arg2, s16, 0x10) = 0x20;
        FIELD(arg2, u8, 0x0E) = 0x80;
        FIELD(arg2, u8, 0x0D) = 0x80;
        FIELD(arg2, u8, 0x0C) = 0x80;
        FIELD(arg2, u16, 0x14) |= 0xC;
        FIELD(arg0, u8, 0x7A) |= 4;
    }
    if (FIELD(obj, void *, 0x60) != 0) {
        register void *resident_work ASM_REG("$5");
        entry = FIELD(FIELD(obj, void *, 0x60), void *, -0x18);
        FIELD(arg0, u16, 0x74) = FIELD(entry, u16, 2);
        FIELD(arg0, u16, 0x76) = FIELD(entry, u16, 6);
        {
            register s32 depth_bias ASM_REG("$3");
            register s32 resident_value ASM_REG("$2");
            depth_bias = D_800DDC40[FIELD(FIELD(obj, void *, 0x60), u8, 0x13)];
            resident_value = FIELD(entry, u16, 0x0A) - depth_bias - 0x60;
            FIELD(arg0, u16, 0x78) = resident_value;
        }
        resident_work = FIELD(obj, void *, -0x14);
        FIELD(arg0, u8, 0xAE) = FIELD(resident_work, u8, 0x24) +
            D_8006CCD8[FIELD(arg0, s16, 0x80) << 1];
        ASM_SCHED_BARRIER();
        FIELD(arg0, u8, 0xAF) = FIELD(resident_work, u8, 0x25) +
            D_8006CCE8[FIELD(arg0, s16, 0x80) << 1];
        entry = FIELD(FIELD(obj, void *, 0x60), void *, -0x18);
        if (FIELD(obj, s8, 0x72) != FIELD(resident_work, u8, 0x24)) {
            register s32 resident_delta ASM_REG("$3");
            register s32 resident_copy ASM_REG("$2");
            resident_delta = FIELD(arg1, s16, 2);
            resident_delta = resident_delta - FIELD(entry, s16, 2);
            resident_copy = FIELD(arg0, s16, 0x80) << 2;
            resident_copy = *(s16 *)((u8 *)&copy + resident_copy);
            if (resident_delta < 0) {
                resident_delta = -resident_delta;
            }
            ASM_USE2(resident_delta, resident_copy);
            func_80025DA4();
        }
        {
            register s32 resident_delta ASM_REG("$3");
            register s32 resident_copy ASM_REG("$2");
            Pair *cp;
            s32 cidx;
            ASM_SCHED_BARRIER();
            resident_delta = FIELD(arg1, s16, 6);
            cidx = FIELD(arg0, s16, 0x80) << 2;
            resident_delta = resident_delta - FIELD(entry, s16, 6);
            ASM_SCHED_BARRIER();
            cp = (Pair *)&copy;
            ASM_KEEP_NV(cp);
            resident_copy = ((Pair *)((u8 *)cp + cidx))->y.u;
            if (resident_delta < 0) {
                resident_delta = -resident_delta;
            }
            resident_copy = (s32)((u32)resident_copy << 16) >> 16;
            if (resident_copy < 0) {
                resident_copy = -resident_copy;
            }
            resident_delta = resident_delta / resident_copy;
            FIELD(arg0, s16, 0x7C) = resident_delta;
        }
        goto L_calc2;
    }
    {
    FIELD(arg0, s16, 0x7C) = 0x80;
    FIELD(arg0, s16, 0x74) = FIELD(arg1, u16, 2) +
        (((Pair *)((u8 *)&copy + (FIELD(arg0, s16, 0x80) << 2)))->x.u << 7);
    FIELD(arg0, s16, 0x76) = FIELD(arg1, u16, 6) +
        (((Pair *)((u8 *)&copy + (FIELD(arg0, s16, 0x80) << 2)))->y.u *
         FIELD(arg0, u16, 0x7C));
    FIELD(arg0, s16, 0x78) = FIELD(obj, u16, 0x88) - 0x50;
    }
L_calc2:
    {
    Pair *cp = (Pair *)&copy;
    FIELD(arg1, s32, 0x0C) =
        ((Pair *)((u8 *)cp + (FIELD(arg0, s16, 0x80) << 2)))->x.s << 16;
    FIELD(arg1, s32, 0x10) =
        ((Pair *)((u8 *)cp + (FIELD(arg0, s16, 0x80) << 2)))->y.u << 16;
    }
    FIELD(arg1, s32, 0x14) =
        ((FIELD(arg0, s16, 0x78) << 16) - FIELD(arg1, s32, 8)) /
        FIELD(arg0, s16, 0x7C);
    FIELD(arg0, u16, 0x84) = 0;
    FIELD(arg0, u16, 0x9C) = 55;
    FIELD(arg0, u16, 0x0A)++;
    i = 0;
    do {
        register void *spawn ASM_REG("$18");
        spawn = func_8003FC64(0x12);
        if (spawn != 0) {
                entry = (u8 *)spawn + 0x20;
            {
            register void *sp0 ASM_REG("$4") = spawn;
            register u8 *tbl ASM_REG("$5") = D_80024704;
                FIELD(entry, void *, 0x38) = obj;
                FIELD(entry, void *, 0x44) = arg1;
                FIELD(entry, void *, 0x48) = arg2;
                FIELD(entry, void *, 0x4C) = arg0;
            ASM_USE2(sp0, tbl);
            FIELD(spawn, void *, 0x10) = spawn_code;
            func_8004491C(sp0, tbl);
            }
            work = FIELD(spawn, void *, 0x0C);
            FIELD(work, u16, 0x14) |= 0xC;
            FIELD(work, s16, 0x10) = 0x20;
            dst = FIELD(spawn, void *, 8);
            ASM_KEEP_NV(i);
            ASM_KEEP(arg2);
            FIELD(entry, s16, 0x0A) = (func_80069EF8() & 7) + 12;
            FIELD(entry, s16, 0x0C) = func_80069EF8() & 0xFFF;
            FIELD(work, s16, 0x16) = (func_80069EF8() & 0xFF) << 4;
            FIELD(work, s16, 0x18) = (func_80069EF8() & 0xFF) << 4;
            FIELD(work, s16, 0x1A) = (func_80069EF8() & 0xFF) << 4;
            value = func_80064584(FIELD(entry, s16, 0x0C));
            FIELD(dst, s32, 0) = (FIELD(entry, s16, 0x0A) * value) << 4;
            value = func_800644B8(FIELD(entry, s16, 0x0C));
            FIELD(dst, s32, 4) = (FIELD(entry, s16, 0x0A) * value) << 4;
            FIELD(dst, s16, 0x0A) = FIELD(arg1, u16, 0x0A);
            work = FIELD(spawn, void *, 0x0C);
            {
                register s32 scale1 ASM_REG("$2");
                scale1 = 0x1000;
                FIELD(work, s16, 0x1E) = scale1;
                FIELD(work, s16, 0x1C) = scale1;
            }
            {
                register s32 alpha ASM_REG("$2");
                alpha = 0x80;
                FIELD(work, u8, 0x0E) = alpha;
                FIELD(work, u8, 0x0D) = alpha;
                FIELD(work, u8, 0x0C) = alpha;
            }
            *(Copy12 *)((u8 *)spawn + 0x4C) = D_80026640;
            FIELD(work, void *, 8) = (u8 *)spawn + 0x4C;
        }
        i++;
        if (i < 8) {
            ASM_USE2(i, spawn);
            func_80025E9C();
        }
    } while (i < 8);
    goto done;

    case 2:
    if (FIELD(arg0, s16, 0xA0) == 0) {
        FIELD(arg0, s16, 0xA0) = 1;
        phase = FIELD(arg0, u8, 0xAA) + 0x18;
        ASM_TAILSLOT_PIN(phase);
        func_80026044();
    }
    phase = FIELD(arg0, u8, 0xAA) - 0x18;
    FIELD(arg0, s16, 0xA0) = 0;
    FIELD(arg0, u8, 0xAA) = phase;
    result = func_800A4778(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                           FIELD(arg1, s16, 0x0A), FIELD(obj, void *, 0x60));
    if ((result << 16) != 0) {
        goto L1_state7;
    }
    node = FIELD(obj, void *, 0x60);
    if (node == 0) {
        FIELD(arg2, u8, 0x0C) -= 4;
        FIELD(arg2, u8, 0x0D) -= 4;
        FIELD(arg2, u8, 0x0E) -= 4;
        if (FIELD(arg2, u8, 0x0C) == 0) {
            FIELD(arg0, u16, 0x7C) = 1;
        }
    }
    count = FIELD(arg0, u16, 0x7C) - 1;
    FIELD(arg0, u16, 0x7C) = count;
    if (count > 0) {
        goto L1_calc;
    }
    if (FIELD(obj, void *, 0x60) != 0) {
        FIELD(arg0, u16, 0x0A) = 3;
        FIELD(arg0, u16, 0x84) = 0;
        entry = FIELD(FIELD(obj, void *, 0x60), void *, -0x18);
        FIELD(arg1, u16, 2) = FIELD(entry, u16, 2);
        FIELD(arg1, u16, 6) = FIELD(entry, u16, 6);
        FIELD(arg1, u16, 0x0A) = FIELD(arg0, u16, 0x78);
        func_800A56E0(0x300);
        goto done;
    }
L1_state7:
    FIELD(arg0, u16, 0x0A) = 7;
    FIELD(arg0, u16, 0x84) = 0;
    FIELD(arg2, u8, 0x0E) = 0;
    FIELD(arg2, u8, 0x0D) = 0;
    FIELD(arg2, u8, 0x0C) = 0;
    func_80026600();

L1_calc:
    FIELD(arg1, s32, 0x0C) =
        ((FIELD(arg0, s16, 0x74) << 16) - FIELD(arg1, s32, 0)) / count;
    FIELD(arg1, s32, 0x10) =
        ((FIELD(arg0, s16, 0x76) << 16) - FIELD(arg1, s32, 4)) /
        FIELD(arg0, s16, 0x7C);
    FIELD(arg1, s32, 0x14) =
        ((FIELD(arg0, s16, 0x78) << 16) - FIELD(arg1, s32, 8)) /
        FIELD(arg0, s16, 0x7C);
    FIELD(arg1, s32, 0) += FIELD(arg1, s32, 0x0C);
    FIELD(arg1, s32, 4) += FIELD(arg1, s32, 0x10);
    FIELD(arg1, s32, 8) += FIELD(arg1, s32, 0x14);
    func_80026600();

    case 3:
    if (FIELD(arg0, s16, 0xA0) == 0) {
        FIELD(arg0, s16, 0xA0) = 1;
        phase = FIELD(arg0, u8, 0xAA) + 0x18;
        ASM_TAILSLOT_PIN(phase);
        func_80026204();
    }
    phase = FIELD(arg0, u8, 0xAA) - 0x18;
    FIELD(arg0, s16, 0xA0) = 0;
    FIELD(arg0, u8, 0xAA) = phase;
    {
    register void *spawn ASM_REG("$18");
    ASM_SCHED_BARRIER();
    spawn = func_8003FC64(0x12);
    if (spawn != 0) {
        entry = (u8 *)spawn + 0x20;
        FIELD(entry, s16, 2) = 0;
        FIELD(entry, void *, 0x38) = obj;
        FIELD(entry, void *, 0x3C) = FIELD(obj, void *, 0x60);
        FIELD(entry, void *, 0x40) = arg0;
        FIELD(entry, s16, 0x0A) = 0x0C;
        FIELD(entry, s16, 0x0C) = 8;
        FIELD(entry, s16, 0x0E) = 0;
        FIELD(entry, s16, 0x10) = 0;
        FIELD(entry, s16, 0x12) = 0;
        FIELD(entry, s16, 0x1C) = 0;
        FIELD(entry, s16, 0x1A) = 0x40;
        entry = FIELD(FIELD(obj, void *, 0x60), void *, -0x18);
        FIELD(spawn, void *, 0x10) = D_80025470;
        func_8004491C(spawn, D_80024FD4);
        work = FIELD(spawn, void *, 0x0C);
        FIELD(work, s16, 0x10) = 0x20;
        FIELD(work, u16, 0x14) |= 0x000C;
        dst = FIELD(spawn, void *, 8);
        FIELD(dst, s32, 0) = FIELD(entry, s32, 0);
        FIELD(dst, s32, 4) = FIELD(entry, s32, 4);
        index = FIELD(obj, void *, 0x60) != 0;
        index = FIELD(FIELD(obj, void *, 0x60), u8, 0x13);
        FIELD(dst, s32, 8) = FIELD(entry, s32, 8) -
            (D_800DDC40[index] << 15);
        work = FIELD(spawn, void *, 0x0C);
        {
            s16 scale2 = 0x1000;
            FIELD(work, s16, 0x1E) = scale2;
            FIELD(work, s16, 0x1C) = scale2;
        }
        FIELD(work, u8, 0x0E) = 0x80;
        FIELD(work, u8, 0x0D) = 0x80;
        FIELD(work, u8, 0x0C) = 0x80;
        *(Copy12 *)((u8 *)spawn + 0x4C) = D_8002664C;
        FIELD(work, void *, 8) = (u8 *)spawn + 0x4C;
        ASM_USE(spawn);
    }
    }
        FIELD(arg0, u16, 0x0A) = 4;
    FIELD(arg0, u16, 0x84) = 0;
    func_80026600();

    case 4:
    count = FIELD(arg0, u16, 0x84) + 1;
    FIELD(arg0, u16, 0x84) = count;
    if (count < 30) {
        FIELD(arg2, s8, 0x0C) = ((30 - FIELD(arg0, s16, 0x84)) * 0x80) / 30;
        FIELD(arg2, s8, 0x0D) = ((30 - FIELD(arg0, s16, 0x84)) * 0x80) / 30;
        FIELD(arg2, s8, 0x0E) = ((30 - FIELD(arg0, s16, 0x84)) * 0xE0) / 30;
        if (FIELD(arg0, s16, 0xA0) == 0) {
            FIELD(arg0, s16, 0xA0) = 1;
            phase = FIELD(arg0, u8, 0xAA) + 0x18;
            ASM_TAILSLOT_PIN(phase);
            func_80026428();
        }
        phase = FIELD(arg0, u8, 0xAA) - 0x18;
        FIELD(arg0, s16, 0xA0) = 0;
        FIELD(arg0, u8, 0xAA) = phase;
        ASM_SCHED_BARRIER();
        i = 0;
        ASM_KEEP_NV(i);
        value = func_80069EF8();
        i++;
        {
        register void *p0 ASM_REG("$4");
        register s32 p1 ASM_REG("$5");
        register s32 c2 ASM_REG("$6");
        register s32 a3v ASM_REG("$7");
        p0 = (u8 *)arg0 - 0x20;
        c2 = 0x00E02020;
        a3v = (value & 0xFF) | 0x80;
        p1 = FIELD(arg0, s16, 0x80);
        ASM_USE2(p0, c2);
        func_80025338(p0, p1, c2, a3v, 0, 0, 0);
        }
        if (i < 4) {
            ASM_USE(i);
            func_80026430();
        }
        goto done;
    }
    FIELD(arg0, u16, 0x0A)++;
    FIELD(arg0, u16, 0x84) = 0;
    FIELD(arg2, u16, 0x14) |= 0x80;
    func_80026600();

    case 5:
    if (FIELD(arg0, s16, 0x88) == 0) {
        goto done;
    }
    {
        register s32 tail_a ASM_REG("$2");
        tail_a = FIELD(arg0, u16, 0x0A);
        ASM_KEEP(tail_a);
        FIELD(arg0, u16, 0x84) = 0;
        func_80026590();
    }

    case 6:
    {
    register void *fade_node ASM_REG("$4");
    register void *fade_entry ASM_REG("$5");
    s32 fade14;
    count = FIELD(arg0, u16, 0x84) + 1;
    FIELD(arg0, u16, 0x84) = count;
    fade_node = FIELD(obj, void *, 0x60);
    FIELD(fade_node, s32, 0x1C) |= 0x10000000;
    fade_entry = FIELD(fade_node, void *, -0x14);
    if (FIELD(arg0, s16, 0x84) >= 36) {
        FIELD(fade_entry, u8, 0x0C) += 2;
        fade14 = FIELD(fade_entry, u8, 0x0E);
        ASM_SCHED_BARRIER();
        phase = FIELD(fade_entry, u8, 0x0D);
        FIELD(fade_entry, u8, 0x0E) = fade14 - 3;
        phase = phase + 2;
        ASM_TAILSLOT_PIN(phase);
        func_80026534();
    }
    FIELD(fade_entry, u8, 0x0C) -= 2;
    FIELD(fade_entry, u8, 0x0D) -= 2;
    FIELD(fade_entry, u8, 0x0E) += 3;
    if (FIELD(arg0, s16, 0x84) < 71) {
        goto done;
    }
    {
        register void *tail_node ASM_REG("$3");
        tail_node = FIELD(obj, void *, 0x60);
        FIELD(tail_node, s32, 0x1C) &= 0xEFFFFFFF;
        fade_entry = FIELD(tail_node, void *, -0x14);
        FIELD(fade_entry, u8, 0x0E) = 0x80;
        FIELD(fade_entry, u8, 0x0D) = 0x80;
        FIELD(fade_entry, u8, 0x0C) = 0x80;
        func_80024098(FIELD(obj, void *, 0x60), FIELD(arg0, u8, 9), obj);
    }
    FIELD(arg0, u16, 0x84) = 13;
    FIELD(arg0, u16, 0x0A)++;
    func_80026600();
    }

    case 7:
    old_count = FIELD(arg0, u16, 0x84);
    FIELD(arg0, u16, 0x84) = old_count + 1;
    if ((s16)old_count < 15) {
        goto done;
    }
    {
        register s32 seen ASM_REG("$2");
        seen = D_80026664[0];
        FIELD(arg0, u16, 0x84) = old_count;
        if (seen == 0) {
            ASM_KEEP_NV(seen);
            D_8008346C[0] = 0;
            FIELD(arg0, u16, -2) |= 0x8000;
            D_800814A0[0] |= 0x8000;
            func_80026600();
        }
    }
    D_80026664[0] = 0;
    goto done;
    }

done:
    return;
}
