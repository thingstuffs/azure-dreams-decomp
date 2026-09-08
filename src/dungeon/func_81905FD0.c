#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

typedef struct {
    u8 bytes[8];
} Copy8;

typedef struct {
    u8 bytes[12];
} Copy12;

typedef struct {
    u8 bytes[32];
} Copy32;

typedef struct {
    s16 a;
    s16 b;
    s16 c;
} Vec3;

__asm__(".set D_80024004, 0x80024004");
__asm__(".set D_80024014, 0x80024014");
__asm__(".set D_800251A0, 0x800251A0");
__asm__(".set D_80025294, 0x80025294");
__asm__(".set D_800252E4, 0x800252E4");
__asm__(".set D_80025408, 0x80025408");
__asm__(".set D_80026760, 0x80026760");
__asm__(".set D_8002676C, 0x8002676C");
__asm__(".set D_80026778, 0x80026778");
__asm__(".set D_80026784, 0x80026784");
__asm__(".set D_800267A8, 0x800267A8");
__asm__(".set D_800267B8, 0x800267B8");
__asm__(".set D_800DDC40, 0x800DDC40");
__asm__(".set D_800E3D68, 0x800E3D68");
__asm__(".set D_8006CCD8, 0x8006CCD8");
__asm__(".set D_8006CCE8, 0x8006CCE8");

extern u8 D_80024004[9];
extern u8 D_80024014[32];
extern u8 D_800251A0[12];
extern u8 D_80025294[12];
extern u8 D_800252E4[12];
extern u8 D_80025408[12];
extern u8 D_80026760[12];
extern u8 D_8002676C[12];
extern u8 D_80026778[12];
extern u8 D_80026784[24];
extern u8 D_800267A8[12];
extern u8 D_800267B8[9];
extern u8 D_800DDC40[];
extern u8 D_800E3D68[1];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern s32 D_8008346C;
extern s32 D_800814A0;
extern u8 D_80045340[];

extern s32 func_8003DF74(void *, void *, Vec3 *, s32);
extern void func_8004491C(void *, void *);
extern s32 func_80069EF8(void);
extern void func_80025080(void *, s32, s32, s32, s32, s32, s32);
extern s32 func_800A4778(u16, u16, s16, void *);
extern void func_800A56E0(s32);
extern void *func_8003FC64(s32);
extern void func_800B8FC8(void *, void *, void *, s32, s32);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_8002405C(void *, s32, void *);

extern void func_80025A14(void) __attribute__((noreturn));
extern void func_80025B70(void) __attribute__((noreturn));
extern void func_80025D08(void) __attribute__((noreturn));
extern void func_80025EC4(void) __attribute__((noreturn));
extern void func_8002652C(void) __attribute__((noreturn));
extern void func_80026730(void) __attribute__((noreturn));

void func_81905FD0(void *in0, void *in1, void *in2)
{
    void *arg0 = in0;
    register void *arg1 ASM_REG("$18") = in1;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *arg2 = in2;
    void *part;
    u8 local[56];
    s32 i;
    s32 result;
    s32 random;
    s32 state;
    u8 level;
    register u8 *rect_ptr ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *copy_base = D_80024004;

    void *owner;
    void *base;
    void *initial_source;
    ASM_KEEP(arg0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    owner = FIELD(arg0, void *, 0);
    *(Copy8 *)(local + 8) = *(Copy8 *)copy_base;
    *(Copy32 *)(local + 24) = *(Copy32 *)D_80024014;
    state = *(s16 *)((u8 *)arg0 + 0xA);
    base = (u8 *)owner - 0x20;
    initial_source = FIELD(base, void *, 8);

    switch (state) {
    case 0:
        FIELD(arg2, u32, 0xC) = 0x00808080;
        *(Copy12 *)((u8 *)arg0 + 0xA2) = *(Copy12 *)D_800267A8;
        FIELD(arg2, void *, 8) = (u8 *)arg0 + 0xA2;
        {
            u16 spin = (FIELD(owner, u16, 0x2A) >> 9) & 7;
            FIELD(D_800267B8, u16, 0) = 1;
            FIELD(arg0, u16, 0x7E) = spin;
        }
        FIELD(arg0, u16, 0xA)++;

    case 1:
        result = func_8003DF74(FIELD(FIELD(base, void *, 0xC), void *, 8),
                               FIELD(base, void *, 0xC),
                               (Vec3 *)local, 0);
        if (result == 0) {
            if ((FIELD(FIELD(base, void *, 0xC), u16, 0x14) & 0x8000) == 0) {
                goto done;
            }
        }
        {
            u16 keep;

            FIELD(arg1, u16, 2) = FIELD(initial_source, u16, 2);
            FIELD(arg1, u16, 6) = FIELD(initial_source, u16, 6);
            keep = FIELD(initial_source, u16, 0xA);
            FIELD(arg1, u16, 0xA) = keep;
            if ((FIELD(FIELD(base, void *, 0xC), u16, 0x14) & 0x8000) == 0) {
                u16 tail_y;

                FIELD(arg1, u16, 2) += FIELD(local, u16, 0);
                FIELD(arg1, u16, 6) += FIELD(local, u16, 2);
                tail_y = FIELD(arg1, u16, 0xA) + FIELD(local, u16, 4);
                ASM_TAILSLOT_PIN(tail_y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                func_80025A14();
            } else {
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                FIELD(arg1, u16, 0xA) = keep - 0x40;
            }
        }
        if ((FIELD(FIELD(arg0, void *, 4), u16, 0) & 0x80) == 0) {
            goto done;
        }
        if ((FIELD(arg0, u8, 0x7A) & 4) == 0) {
            func_8004491C((u8 *)arg0 - 0x20, D_80045340);
            FIELD(arg2, u16, 0x10) = 32;
            FIELD(arg2, u8, 0xE) = 128;
            FIELD(arg2, u8, 0xD) = 128;
            FIELD(arg2, u8, 0xC) = 128;
            FIELD(arg2, u16, 0x1E) = 2000;
            FIELD(arg2, u16, 0x1C) = 2000;
            FIELD(arg2, u16, 0x14) |= 0xC;
            FIELD(arg0, u8, 0x7A) |= 4;
        }
        {
            void *source = FIELD(owner, void *, 0x60);
            if (source != 0) {
                register void *coords ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                void *info;
                register s32 difference ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                s32 source_height;

                coords = FIELD(source, void *, -0x18);
                level = FIELD(source, u8, 0x13);
                source_height = D_800DDC40[level] + 64;
                FIELD(arg0, u16, 0x78) = FIELD(coords, u16, 0xA) - source_height;
                info = FIELD(owner, void *, -0x14);
                FIELD(arg0, u8, 0xBA) = FIELD(info, u8, 0x24) +
                    D_8006CCD8[FIELD(arg0, s16, 0x7E) * 2];
                FIELD(arg0, u8, 0xBB) = FIELD(info, u8, 0x25) +
                    D_8006CCE8[FIELD(arg0, s16, 0x7E) * 2];
                {
                    s32 gb;
                    s32 ib;

                    gb = FIELD(owner, s8, 0x72);
                    ib = FIELD(info, u8, 0x24);
                    if (gb == ib) {
                        gb = FIELD(owner, s8, 0x73);
                        ib = FIELD(info, u8, 0x25);
                        difference = gb - ib;
                    } else {
                        difference = gb - ib;
                    }
                }
                if (difference < 0) {
                    difference = -difference;
                }
                FIELD(arg0, u8, 0x7B) = difference * 2 - 1;
                func_80025B70();
            } else {
                u16 top = FIELD(owner, u16, 0x88);

                FIELD(arg0, u8, 0x7B) = 32;
                FIELD(arg0, u16, 0x78) = top - 80;
            }
        }
        {
            u8 *steps = local + 24;
            u8 *p;
            u8 *q;

            p = steps + FIELD(arg0, s16, 0x7E) * 4;
            FIELD(arg1, u32, 0xC) = (s32)FIELD(p, s16, 0) << 16;
            q = steps + FIELD(arg0, s16, 0x7E) * 4;
            FIELD(arg1, u32, 0x10) = (s32)FIELD(q, u16, 2) << 16;
        }
        FIELD(arg1, s32, 0x14) =
            (((s32)FIELD(arg0, s16, 0x78) << 16) - FIELD(arg1, s32, 8)) /
            (s8)FIELD(arg0, u8, 0x7B);
        FIELD(arg0, u16, 0x82) = 0;
        FIELD(arg0, u16, 0x90) = 0;
        FIELD(arg0, u16, 0x92) = 0;
        FIELD(arg0, u16, 0x94) = 5;
        FIELD(arg0, u16, 0x96) = 200;
        FIELD(arg0, u16, 0xA)++;
        FIELD(arg0, u16, 0x88) = (s8)FIELD(arg0, u8, 0x7B);
        FIELD(arg0, u16, 0x8A) =
            (s8)FIELD(arg0, u8, 0x7B) * (s8)FIELD(arg0, u8, 0x7B);
        func_80026730();

    case 2:
        i = 0;
        do {
            register void *a0v ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            register s32 a2v ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            register s32 a3v ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

            i++;
            random = func_80069EF8();
            a0v = (u8 *)arg0 - 0x20;
            a2v = 0xE02020;
            ASM_KEEP_NV(a2v);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            a3v = (random & 0xFF) | 0x80;
            ASM_KEEP_NV(a3v);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            func_80025080(a0v, FIELD(arg0, s16, 0x7E), a2v, a3v, 0, 0, 0);
        } while (i < 4);
        result = func_800A4778(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                               FIELD(arg1, s16, 0xA), FIELD(owner, void *, 0x60));
        if ((s16)result != 0) {
            goto reset_state8;
        }
        {
            u16 old_value = FIELD(arg2, u16, 0x1A);
            u16 timer = old_value + 0x190;
            FIELD(arg2, u16, 0x1A) = timer;
            if (timer >= 0x1001) {
                FIELD(arg2, u16, 0x1A) = old_value - 0xE70;
            }
        }
        if (FIELD(arg0, s16, 0x90) == 0) {
            u16 tail_w;

            FIELD(arg2, u16, 0x1C) += FIELD(arg0, u16, 0x96);
            tail_w = FIELD(arg2, u16, 0x1E) + FIELD(arg0, u16, 0x96);
            ASM_TAILSLOT_PIN(tail_w);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_80025D08();
        } else {
            FIELD(arg2, u16, 0x1C) -= FIELD(arg0, u16, 0x96);
            FIELD(arg2, u16, 0x1E) -= FIELD(arg0, u16, 0x96);
        }
        {
            u16 timer = FIELD(arg0, u16, 0x92) + 1;
            FIELD(arg0, u16, 0x92) = timer;
            if ((s16)timer >= FIELD(arg0, s16, 0x94)) {
                FIELD(arg0, u16, 0x92) = 0;
                FIELD(arg0, u16, 0x90) = FIELD(arg0, u16, 0x90) ^ 1;
            }
        }
        FIELD(arg0, u8, 0x7B) = FIELD(arg0, u8, 0x7B) - 1;
        if ((s8)FIELD(arg0, u8, 0x7B) > 0) {
            goto update_coords;
        }
        if (FIELD(owner, void *, 0x60) == 0) {
            goto reset_state8;
        }
        FIELD(arg0, u16, 0xA) = 3;
        FIELD(arg0, u16, 0x82) = 0;
        func_800A56E0(0x300);
        {
            void *source = FIELD(owner, void *, 0x60);
            level = FIELD(source, u8, 0x13);
            part = FIELD(source, void *, -0x14);
            if ((u32)(level - 0x33) >= 4) {
                FIELD(part, u16, 0x14) |= 0x800;
                FIELD(FIELD(owner, void *, 0x60), u32, 0x14) |= 0x100000;
            }
        }
        {
            register void *source_coords ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

            source_coords = FIELD(FIELD(owner, void *, 0x60), void *, -0x18);
            FIELD(arg1, u16, 2) = FIELD(source_coords, u16, 2);
            FIELD(arg1, u16, 6) = FIELD(source_coords, u16, 6);
        }
        FIELD(arg1, u16, 0xA) = FIELD(arg0, u16, 0x78);
        func_80026730();

    reset_state8:
        FIELD(arg0, u16, 0xA) = 8;
        FIELD(arg0, u16, 0x82) = 0;
        FIELD(arg2, u8, 0xE) = 0;
        FIELD(arg2, u8, 0xD) = 0;
        FIELD(arg2, u8, 0xC) = 0;
        func_80026730();

    update_coords:
        FIELD(arg1, u32, 0) += FIELD(arg1, u32, 0xC);
        FIELD(arg1, u32, 4) += FIELD(arg1, u32, 0x10);
        FIELD(arg1, u32, 8) += FIELD(arg1, u32, 0x14);
        func_80026730();

    case 3: {
        {
            u16 old_value = FIELD(arg2, u16, 0x1A);
            u16 timer = old_value + 0x190;
            FIELD(arg2, u16, 0x1A) = timer;
            if (timer >= 0x1001) {
                FIELD(arg2, u16, 0x1A) = old_value - 0xE70;
            }
        }
        if (FIELD(arg0, s16, 0x90) == 0) {
            u16 tail_w;

            FIELD(arg2, u16, 0x1C) += FIELD(arg0, u16, 0x96);
            tail_w = FIELD(arg2, u16, 0x1E) + FIELD(arg0, u16, 0x96);
            ASM_TAILSLOT_PIN(tail_w);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_80025EC4();
        } else {
            FIELD(arg2, u16, 0x1C) -= FIELD(arg0, u16, 0x96);
            FIELD(arg2, u16, 0x1E) -= FIELD(arg0, u16, 0x96);
        }
        {
            u16 timer = FIELD(arg0, u16, 0x92) + 1;
            FIELD(arg0, u16, 0x92) = timer;
            if ((s16)timer >= FIELD(arg0, s16, 0x94)) {
                FIELD(arg0, u16, 0x92) = 0;
                FIELD(arg0, u16, 0x90) = FIELD(arg0, u16, 0x90) ^ 1;
            }
        }
        {
            s16 phase;
            register u8 *scratch_source ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

            FIELD(arg0, u16, 0x82) = FIELD(arg0, u16, 0x82) + 1;
            phase = (s16)FIELD(arg0, u16, 0x82);
            if (phase == 1) {
                s32 mid;
                register void *carry_rect ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                register void *carry_scratch ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                s32 c880;
                s32 c84;
                s32 c832;

                rect_ptr = local + 8;
                carry_rect = rect_ptr;
                scratch_source = local + 16;
                carry_scratch = scratch_source;
                ASM_SET(c832);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                c832 = 832;
                mid = 340;
                FIELD(local, s16, 10) = mid;
                mid = 96;
                ASM_SET(c84);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                c84 = 84;
                ASM_SET(c880);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                c880 = 880;
                FIELD(local, s16, 12) = mid;
                mid = 410;
                FIELD(local, s16, 8) = c832;
                FIELD(local, s16, 14) = c84;
                FIELD(local, s16, 16) = c880;
                FIELD(local, s16, 18) = mid;
                func_800B8FC8(FIELD(owner, void *, 0x60), carry_rect,
                              carry_scratch, 1, phase);
                carry_rect = rect_ptr;
                ASM_KEEP_NV(carry_rect);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                carry_scratch = scratch_source;
                ASM_KEEP_NV(carry_scratch);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                mid = 424;
                FIELD(local, s16, 10) = mid;
                mid = 96;
                FIELD(local, s16, 12) = mid;
                mid = 495;
                FIELD(local, s16, 8) = c832;
                FIELD(local, s16, 14) = c84;
                FIELD(local, s16, 16) = c880;
                FIELD(local, s16, 18) = mid;
                func_800B8FC8(FIELD(owner, void *, 0x60), carry_rect,
                              carry_scratch, 1, phase);
            }
            if (FIELD(arg0, s16, 0x82) != 4) {
                goto done;
            }
        }
        {
        register void *node1 ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        void *node2;
        void *node3;
        register void *node4 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        void *subnode;
        register void *obj_part ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        void *obj_coords;

        node1 = func_8003FC64(0x212);
        if (node1 != 0) {
            subnode = (u8 *)node1 + 0x20;
            FIELD(subnode, s16, 2) = 120;
            FIELD(node1, void *, 0x10) = D_80025294;
            func_8004491C(node1, D_80045340);
            obj_part = FIELD(node1, void *, 0xC);
            FIELD(obj_part, u16, 6) = 0;
            {
                register u16 tmpf ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                register u16 flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

                tmpf = FIELD(obj_part, u16, 0x14) | 0xC;
                FIELD(obj_part, u16, 0x14) = tmpf;
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                flags = tmpf;
                ASM_KEEP(flags);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                FIELD(obj_part, u16, 0x10) = 64;
                FIELD(obj_part, u16, 0x14) = flags | 0x80;
            }
            obj_coords = FIELD(node1, void *, 8);
            FIELD(subnode, u16, 0xA) = 0;
            FIELD(subnode, u16, 0xC) = 0;
            {
                register void *src ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

                src = FIELD(FIELD(owner, void *, 0x60), void *, -0x18);
                FIELD(obj_coords, u32, 0) = FIELD(src, u32, 0);
                FIELD(obj_coords, u32, 4) = FIELD(src, u32, 4);
                FIELD(obj_coords, u32, 8) = FIELD(src, u32, 8);
            }
            obj_part = FIELD(node1, void *, 0xC);
            FIELD(obj_part, s16, 0x1C) = 4100;
            FIELD(obj_part, s16, 0x1E) = 4100;
            {
                u8 lvl = D_800DDC40[FIELD(FIELD(owner, void *, 0x60), u8, 0x13)];

                FIELD(obj_part, u8, 0xE) = 128;
                FIELD(obj_part, u8, 0xD) = 128;
                FIELD(obj_part, u8, 0xC) = 128;
                FIELD(obj_part, s16, 0x22) = (-lvl) / 2;
            }
            *(Copy12 *)((u8 *)node1 + 0x40) = *(Copy12 *)D_8002676C;
            FIELD(obj_part, void *, 8) = (u8 *)node1 + 0x40;
            FIELD(FIELD(obj_part, void *, 8), u16, 4) =
                func_80066460(2, 1, 832, 340);
        }
        node2 = func_8003FC64(0x212);
        if (node2 != 0) {
            subnode = (u8 *)node2 + 0x20;
            FIELD(subnode, s16, 2) = 140;
            FIELD(node2, void *, 0x10) = D_800252E4;
            func_8004491C(node2, D_80045340);
            obj_part = FIELD(node2, void *, 0xC);
            FIELD(obj_part, u16, 0x14) &= 0xFFF3;
            FIELD(obj_part, s16, 0x10) = 32;
            FIELD(obj_part, u16, 0x14) |= 0x80;
            FIELD(subnode, void *, 0x38) = owner;
            FIELD(subnode, void *, 0x3C) = FIELD(owner, void *, 0x60);
            FIELD(subnode, void *, 0x40) = arg0;
            FIELD(obj_part, u16, 6) = 0;
            obj_coords = FIELD(node2, void *, 8);
            FIELD(subnode, u16, 0xA) = 0;
            FIELD(subnode, u16, 0xC) = 0;
            {
                register void *src ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

                src = FIELD(FIELD(owner, void *, 0x60), void *, -0x18);
                FIELD(obj_coords, u32, 0) = FIELD(src, u32, 0);
                FIELD(obj_coords, u32, 4) = FIELD(src, u32, 4);
                FIELD(obj_coords, u32, 8) = FIELD(src, u32, 8);
            }
            obj_part = FIELD(node2, void *, 0xC);
            FIELD(obj_part, s16, 0x1E) = 4096;
            FIELD(obj_part, s16, 0x1C) = 4096;
            FIELD(obj_part, u8, 0xE) = 128;
            FIELD(obj_part, u8, 0xD) = 128;
            FIELD(obj_part, u8, 0xC) = 128;
            *(Copy12 *)((u8 *)node2 + 0x40) = *(Copy12 *)D_80026778;
            FIELD(obj_part, void *, 8) = (u8 *)node2 + 0x40;
            FIELD(FIELD(obj_part, void *, 8), u16, 4) =
                func_80066460(2, 1, 832, 424);
        }
        node3 = func_8003FC64(0x212);
        if (node3 != 0) {
            subnode = (u8 *)node3 + 0x20;
            FIELD(subnode, s16, 2) = 120;
            FIELD(node3, void *, 0x10) = D_800251A0;
            func_8004491C(node3, D_80045340);
            obj_part = FIELD(node3, void *, 0xC);
            FIELD(obj_part, u16, 6) = 0;
            {
                register u16 tmpf ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                register u16 flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

                tmpf = FIELD(obj_part, u16, 0x14) & 0xFFF3;
                FIELD(obj_part, u16, 0x14) = tmpf;
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                flags = tmpf;
                ASM_KEEP(flags);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                FIELD(obj_part, s16, 0x10) = 32;
                FIELD(obj_part, u16, 0x14) = flags | 0x80;
            }
            obj_coords = FIELD(node3, void *, 8);
            FIELD(subnode, u16, 0xA) = 0;
            FIELD(subnode, u16, 0xC) = 0;
            i = 0;
            {
                register void *src ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

                src = FIELD(FIELD(owner, void *, 0x60), void *, -0x18);
                FIELD(obj_coords, u32, 0) = FIELD(src, u32, 0);
                FIELD(obj_coords, u32, 4) = FIELD(src, u32, 4);
                FIELD(obj_coords, u32, 8) = FIELD(src, u32, 8);
            }
            obj_part = FIELD(node3, void *, 0xC);
            FIELD(obj_part, s16, 0x1C) = 4096;
            FIELD(obj_part, s16, 0x1E) = 4096;
            FIELD(obj_part, u8, 0xE) = 128;
            FIELD(obj_part, u8, 0xD) = 128;
            FIELD(obj_part, u8, 0xC) = 128;
            {
                u8 *src = D_80026784;
                u8 *dst = subnode;

                do {
                    *(Copy12 *)(dst + 0x20) = *(Copy12 *)src;
                    src += 12;
                    dst += 12;
                    i++;
                } while (i < 2);
            }
            {
                s16 *slot;

                i = 1;
                slot = (s16 *)((u8 *)subnode + 2);
                do {
                    slot[40] = i << 9;
                    i++;
                    slot++;
                } while (i < 9);
            }
            FIELD(obj_part, void *, 8) = (u8 *)subnode + 0x20;
        }
        node4 = func_8003FC64(0x212);
        if (node4 != 0) {
            register void *a0v ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            void *a1v;
            void *d408;
            void *own60;

            subnode = (u8 *)node4 + 0x20;
            a0v = node4;
            a1v = D_80045340;
            ASM_KEEP_NV(a1v);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            FIELD(subnode, void *, 0x38) = owner;
            own60 = FIELD(owner, void *, 0x60);
            FIELD(subnode, void *, 0x44) = (u8 *)node1 + 0x20;
            FIELD(subnode, void *, 0x48) = (u8 *)node3 + 0x20;
            FIELD(subnode, void *, 0x4C) = (u8 *)node2 + 0x20;
            ASM_KEEP(node1);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            d408 = D_80025408;
            FIELD(subnode, void *, 0x40) = arg0;
            FIELD(subnode, void *, 0x3C) = own60;
            FIELD(node4, void *, 0x10) = d408;
            func_8004491C(a0v, a1v);
            obj_part = FIELD(node4, void *, 0xC);
            FIELD(obj_part, u16, 6) = 0;
            {
                register u16 tmpf ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                register u16 flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

                tmpf = FIELD(obj_part, u16, 0x14) | 0xC;
                FIELD(obj_part, u16, 0x14) = tmpf;
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                flags = tmpf;
                ASM_KEEP(flags);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                FIELD(obj_part, s16, 0x10) = 32;
                FIELD(obj_part, u16, 0x14) = flags | 0x80;
            }
            obj_coords = FIELD(node4, void *, 8);
            FIELD(subnode, u16, 0xA) = 0;
            FIELD(subnode, u16, 0xC) = 0;
            {
                register void *src ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

                src = FIELD(FIELD(owner, void *, 0x60), void *, -0x18);
                FIELD(obj_coords, u32, 0) = FIELD(src, u32, 0);
                FIELD(obj_coords, u32, 4) = FIELD(src, u32, 4);
                FIELD(obj_coords, u32, 8) = FIELD(src, u32, 8);
            }
            obj_part = FIELD(node4, void *, 0xC);
            FIELD(obj_part, s16, 0x1E) = 4096;
            FIELD(obj_part, s16, 0x1C) = 4096;
            FIELD(obj_part, u8, 0xE) = 128;
            FIELD(obj_part, u8, 0xD) = 128;
            FIELD(obj_part, u8, 0xC) = 128;
            *(Copy12 *)((u8 *)node4 + 0x40) = *(Copy12 *)D_80026760;
            FIELD(obj_part, void *, 8) = (u8 *)node4 + 0x40;
            ASM_KEEP(node4);
        }
        if (FIELD(arg0, s16, 0x82) == 4) {
            FIELD(arg0, u16, 0xA) = 4;
            FIELD(arg0, u16, 0x82) = 0;
            FIELD(arg0, u16, 0x9C) = 0;
            func_80026730();
        }
        }
        goto done;
    }

    case 4:
        FIELD(arg0, u16, 0x82)++;
        i = 4;
        do {
            i--;
        } while (i >= 0);
        i++;
        {
            u16 old_value = FIELD(arg2, u16, 0x1A);
            u16 timer = old_value + 0x190;
            FIELD(arg2, u16, 0x1A) = timer;
            if (timer >= 0x1001) {
                FIELD(arg2, u16, 0x1A) = old_value - 0xE70;
            }
        }
        if (FIELD(arg0, s16, 0x90) == 0) {
            u16 tail_w;

            FIELD(arg2, u16, 0x1C) += FIELD(arg0, u16, 0x96);
            tail_w = FIELD(arg2, u16, 0x1E) + FIELD(arg0, u16, 0x96);
            ASM_TAILSLOT_PIN(tail_w);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_8002652C();
        } else {
            FIELD(arg2, u16, 0x1C) -= FIELD(arg0, u16, 0x96);
            FIELD(arg2, u16, 0x1E) -= FIELD(arg0, u16, 0x96);
        }
        {
            u16 timer = FIELD(arg0, u16, 0x92) + 1;
            FIELD(arg0, u16, 0x92) = timer;
            if ((s16)timer >= FIELD(arg0, s16, 0x94)) {
                FIELD(arg0, u16, 0x92) = 0;
                FIELD(arg0, u16, 0x90) = FIELD(arg0, u16, 0x90) ^ 1;
            }
        }
        if ((u32)(FIELD(arg0, u16, 0x82) - 11) < 20) {
            level = FIELD(arg2, u8, 0xE) - 3;
            FIELD(arg2, u8, 0xE) = level;
            FIELD(arg2, u8, 0xD) = level;
            FIELD(arg2, u8, 0xC) = level;
        }
        if (FIELD(arg0, s16, 0x82) >= 100 && FIELD(arg2, u8, 0xC) >= 6) {
            level = FIELD(arg2, u8, 0xE) - 4;
            FIELD(arg2, u8, 0xE) = level;
            FIELD(arg2, u8, 0xD) = level;
            FIELD(arg2, u8, 0xC) = level;
        }
        if (FIELD(arg0, s16, 0x82) >= 120) {
            goto advance_state;
        }
        func_80026730();

    case 5:
        if (FIELD(arg0, s16, 0x9C) == 0) {
            goto done;
        }
        result = 0xFF;
        if (FIELD(D_800E3D68, u8, 0) != result) {
            result = FIELD(arg0, u8, 9);
        }
        func_8002405C(FIELD(owner, void *, 0x60), result, owner);

    advance_state:
        FIELD(arg0, u16, 0x82) = 0;
        FIELD(arg0, u16, 0xA) = FIELD(arg0, u16, 0xA) + 1;
        func_80026730();

    case 6:
        FIELD(arg0, u16, 0x82) = FIELD(arg0, u16, 0x82) + 1;
        if (FIELD(arg0, s16, 0x82) < 11) {
            goto done;
        }
        part = FIELD(FIELD(owner, void *, 0x60), void *, -0x14);
        FIELD(part, u16, 0x14) &= 0xF7FF;
        FIELD(FIELD(owner, void *, 0x60), u32, 0x14) &= 0xFFEFFFFF;
        FIELD(FIELD(owner, void *, 0x60), u32, 0x1C) &= 0xEFFFFFFF;
        FIELD(part, u8, 0xE) = 128;
        FIELD(part, u8, 0xD) = 128;
        FIELD(part, u8, 0xC) = 128;
        FIELD(arg0, u16, 0xA) = 8;
        FIELD(arg0, u16, 0x82) = 30;
        func_80026730();

    case 8: {
        u16 old_value = FIELD(arg0, u16, 0x82);
        u16 timer = old_value + 1;

        FIELD(arg0, u16, 0x82) = timer;
        if ((s16)timer < 31) {
            goto done;
        }
        {
            s32 flag = FIELD(D_800267B8, s16, 0);

            FIELD(arg0, u16, 0x82) = old_value;
            if (flag != 0) {
                goto clear_flag;
            }
        }
        D_8008346C = 0;
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        func_80026730();
    }

    clear_flag:
        FIELD(D_800267B8, u16, 0) = 0;

    case 7:
    default:
    done:
        return;
    }
}
