#include "common.h"

#define F(p, t, o) (*(t *)((u8 *)(p) + (o)))

typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} D_80083460_t;

typedef struct {
    u8 bytes[12];
} __attribute__((packed)) Packed12;

extern volatile void *jtbl_80024048[];
__asm__(".set jtbl_80024048, 0x80024048");
extern void *D_800814A8[4];
extern u8 D_80082E80[32];
extern u8 D_80083780[32];
extern D_80083460_t D_80083460;
extern u8 D_8002492C[16];
extern u8 D_80025704[16];
extern u8 D_80025710[16];
extern u16 D_8002571C[8];
extern u8 D_80045340[16];
extern u8 D_800256EC[16];
extern u8 D_800DED28[];
extern u8 D_800DEB28[];
extern u8 D_800DE870[];
extern s32 D_800814A0[];

extern s32 func_800249F0(void *, void *, void *, void *, s32, s32, s32, s32);
extern s32 func_800243D8(void *, void *, void *);
extern s32 func_800B8FC8(void *, void *, void *, s32, s32);
extern s32 func_8003DF74(void *, void *, void *, s32);
extern s32 func_80069EF8(void);
extern s32 func_80024798(void *, s32, s32, s32, s32, s32, s32);
extern void *func_8003FC64(s32);
extern s32 func_8004491C(void *, void *);
extern s32 func_80053EF0(s32);
extern void func_800A56E0(s32);
extern void func_8003DB94(void *, void *, void *);
extern void func_800256AC(void) __attribute__((noreturn));
extern void func_80024FC4() __attribute__((noreturn));
extern void func_80025228() __attribute__((noreturn));
extern void func_8002555C() __attribute__((noreturn));

void func_81941338(void *arg0, void *arg1, void *arg2)
{
    register void *base ASM_REG("$21") = arg0;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *dest = arg1;
    register void *ctx ASM_REG("$18") = arg2;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    static void *const keepalive[] = { &&L0, &&L1, &&L2, &&L3, &&L4 };
    s32 one;
    void *s0;
    void *s3;
    u8 *s6;
    u8 *s7;
    u8 *ptr2492c;
    s32 s4;
    s32 t0;
    s32 particle_color;
    s32 particle_alpha;
    register void *special_obj ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register void *special_data ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 state;
    s16 timer;
    u16 oldtimer;
    u16 tail0;
    u16 tail1;
    u16 tail2;
    s32 particle_level;
    s32 particle_x;
    s16 buf[6];
    s32 i;
    register u32 r ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */

    ASM_KEEP_NV(base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    F(base, u16, 0x2A) = (u16)(F(base, u16, 0x2A) + 1);
    state = F(base, s16, 0xA);
    ctx = arg2;
    if ((u32)state >= 5) {
        return;
    }
    (void)keepalive;
    goto *jtbl_80024048[(u32)state];

L0:
    one = 1;
    t0 = 0x00808080;
    F(D_800814A8[0], s32, 0xF4) = 0;
    F(D_80082E80, u16, 6) = 6;
    F(base, void *, 0x64) = func_800249F0(base, dest, ctx, D_80025704,
                                            one, 0x1000, 0x1000, t0);
    F(base, void *, 0x68) = func_800249F0(base, dest, ctx, D_80025710,
                                            2, 0xE00, 0xE00, 0x00E0E0E0);
    oldtimer = F(base, u16, 0xA);
    F(D_8002571C, u16, 0) = (u16)one;
    F(base, u16, 0xA) = (u16)(oldtimer + 1);

L1:
    if ((F(F(base, void *, 4), u16, 0) & 0x80) == 0) {
        return;
    }
    special_obj = base;
    {
        void *global = D_800814A8[0];
        r = 0x14;
        F(base, u16, 0x20) = (u16)r;
        F(global, u16, 0xA6) = (u16)(F(global, u16, 0xA6) - 1);
        F(global, u8, 0xA8) = F(base, u8, 8);
    }
    i = F(D_800814A8[0], u16, 0x2A);
    F(base, u16, 0xA) = (u16)(F(base, u16, 0xA) + 1);
    F(base, u16, 0x26) = (u16)i;
    func_800243D8(special_obj, dest, ctx);
    if (F(base, void *, 0x68) != 0) {
        buf[0] = 0x340;
        buf[1] = 0x100;
        buf[2] = 0x40;
        buf[3] = 0x40;
        buf[4] = 0x360;
        buf[5] = 0x120;
        func_800B8FC8(F(base, void *, 0x68), buf, &buf[4], 0, 1);
    }
    if (F(base, void *, 0x64) == 0) {
        return;
    }
    {
        buf[0] = 0x340;
        buf[1] = 0x100;
        buf[2] = 0x40;
        buf[3] = 0x40;
        buf[4] = 0x360;
        buf[5] = 0x120;
        func_800B8FC8(F(base, void *, 0x64), buf, &buf[4], 1, 1);
    }
    func_800256AC();

L2:
    timer = (s16)((u16)F(base, u16, 0x20) - 1);
    F(base, u16, 0x20) = (u16)timer;
    if (timer <= 0) {
        F(base, u16, 0x20) = 0x10;
        F(base, u16, 0xA) = (u16)(F(base, u16, 0xA) + 1);
    }
    if (F(base, s16, 0x20) == 0x13) {
        if (func_80053EF0(4) != 2) {
            func_800A56E0(0x300);
        } else {
            func_800A56E0(0x4300);
        }
    }
    if (F(base, s16, 0x20) >= 11) {
        goto L2_post_short;
    }
        {
            u8 *dungeon = D_80082E80;
            if (func_8003DF74(F(dungeon, void *, 8), dungeon,
                              (u8 *)base + 0xC, 0) == 0) {
                goto L2_post_short;
            }
        }
        s4 = 0;
        do {
            r = (u32)func_80069EF8();
            particle_color = 0x200000;
            ASM_KEEP_NV(particle_color);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            r &= 0x7F;
            particle_alpha = (s32)(r | 0x60);
            particle_level = F(base, s16, 0x26);
            particle_x = F(base, s16, 0xC);
            particle_color |= 0x20F0;
            func_80024798((u8 *)D_800814A8[0] - 0x20,
                          particle_level, particle_color,
                          particle_alpha,
                          particle_x, F(base, s16, 0xE),
                          F(base, s16, 0x10));
            s4++;
        } while (s4 < 4);
        s4 = 0;
        s7 = D_8002492C;
        s6 = D_80083780;
        ctx = 0x80;
        do {
            s3 = func_8003FC64(0x212);
            if (s3 != 0) {
                F(s3, s16, 0x4A) = 8;
                F(s3, void *, 0x10) = s7;
                func_8004491C(s3, D_80045340);
                s0 = F(s3, void *, 0xC);
                F(s0, u16, 0x14) = (u16)(F(s0, u16, 0x14) | 0xC);
                dest = F(s3, void *, 8);
                if ((func_80069EF8() & 1) == 0) {
                    F(s0, u16, 0x14) = (u16)(F(s0, u16, 0x14) | 1);
                }
                F(dest, u16, 2) = F(base, u16, 0xC);
                F(dest, u16, 6) = F(base, u16, 0xE);
                F(dest, u16, 0xA) = F(base, u16, 0x10);
                F(dest, u16, 2) = (u16)(F(dest, u16, 2) + F(s6, u16, 2));
                F(dest, u16, 6) = (u16)(F(dest, u16, 6) + F(s6, u16, 6));
                F(dest, u16, 0xA) = (u16)(F(dest, u16, 0xA) + F(s6, u16, 0xA));
                if (s4 != 0) {
                    r = (u32)func_80069EF8() & 0x1F;
                    i = F(dest, u16, 2);
                    i -= 0x10;
                    i += r;
                    F(dest, u16, 2) = (u16)i;
                    r = (u32)func_80069EF8() & 0x1F;
                    i = F(dest, u16, 6);
                    i -= 0x10;
                    i += r;
                    F(dest, u16, 6) = (u16)i;
                    r = (u32)func_80069EF8() & 0x1F;
                    i = F(dest, u16, 0xA);
                    i -= 0x10;
                    i += r;
                    F(dest, u16, 0xA) = (u16)i;
                }
                s0 = F(s3, void *, 0xC);
                {
                    register void *tail_obj ASM_REG("$4") = s0;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                    if (s4 != 0) {
                        register void *tail_a1 ASM_REG("$5") = D_800DED28;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                        register void *tail_a2 ASM_REG("$6") = 0;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                        ASM_USE2(tail_a1, tail_a2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                        r = 0x20;
                        F(s0, u16, 0x10) = (u16)r;
                        F(s0, u16, 0x1E) = 0x1000;
                        F(s0, u16, 0x1C) = 0x1000;
                        return func_80024FC4(tail_obj, tail_a1, tail_a2);
                    } else {
                        register void *tail_a1 ASM_REG("$5") = D_800DEB28;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                        register void *tail_a2 ASM_REG("$6") = 0;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                        ASM_USE2(tail_a1, tail_a2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                        F(s0, u16, 0x1E) = 0x2000;
                        F(s0, u16, 0x1C) = 0x2000;
                        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                        r = 0x20;
                        F(s0, u16, 0x10) = (u16)r;
                        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                        func_8003DB94(tail_obj, tail_a1, tail_a2);
                    }
                }
                    F(s0, u8, 0xE) = (u8)ctx;
                    F(s0, u8, 0xD) = (u8)ctx;
                    F(s0, u8, 0xC) = (u8)ctx;
            }
            s4++;
        } while (s4 < 4);
    if (F(base, s16, 0x20) < 6) {
        F(base, s16, 0x18) =
            (F(base, s16, 0xC) + F(base, s16, 0x12)) / 2;
        F(base, s16, 0x1A) =
            (F(base, s16, 0xE) + F(base, s16, 0x14)) / 2;
        F(base, s16, 0x1C) =
            (F(base, s16, 0x10) + F(base, s16, 0x16)) / 2;
        s4 = 0;
        do {
            r = (u32)func_80069EF8();
            particle_color = 0x200000;
            ASM_KEEP_NV(particle_color);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            r &= 0x7F;
            particle_alpha = (s32)(r | 0x60);
            particle_level = F(base, s16, 0x26);
            particle_x = F(base, s16, 0x18);
            particle_color |= 0x20F0;
            func_80024798((u8 *)D_800814A8[0] - 0x20,
                          particle_level, particle_color,
                          particle_alpha,
                          particle_x, F(base, s16, 0x1A),
                          F(base, s16, 0x1C));
            s4++;
        } while (s4 < 4);
        s4 = 0;
        s7 = D_8002492C;
        s6 = D_80083780;
        ctx = 0x80;
        do {
            s3 = func_8003FC64(0x212);
            if (s3 != 0) {
                F(s3, s16, 0x4A) = 8;
                F(s3, void *, 0x10) = s7;
                func_8004491C(s3, D_80045340);
                s0 = F(s3, void *, 0xC);
                F(s0, u16, 0x14) = (u16)(F(s0, u16, 0x14) | 0xC);
                dest = F(s3, void *, 8);
                if ((func_80069EF8() & 1) == 0) {
                    F(s0, u16, 0x14) = (u16)(F(s0, u16, 0x14) | 1);
                }
                F(dest, u16, 2) = F(base, u16, 0x18);
                F(dest, u16, 6) = F(base, u16, 0x1A);
                F(dest, u16, 0xA) = F(base, u16, 0x1C);
                F(dest, u16, 2) = (u16)(F(dest, u16, 2) + F(s6, u16, 2));
                F(dest, u16, 6) = (u16)(F(dest, u16, 6) + F(s6, u16, 6));
                F(dest, u16, 0xA) = (u16)(F(dest, u16, 0xA) + F(s6, u16, 0xA));
                if (s4 != 0) {
                    r = (u32)func_80069EF8() & 0xF;
                    i = F(dest, u16, 2);
                    i -= 8;
                    i += r;
                    F(dest, u16, 2) = (u16)i;
                    r = (u32)func_80069EF8() & 0xF;
                    i = F(dest, u16, 6);
                    i -= 8;
                    i += r;
                    F(dest, u16, 6) = (u16)i;
                    r = (u32)func_80069EF8() & 0x1F;
                    i = F(dest, u16, 0xA);
                    i -= 0x10;
                    i += r;
                    F(dest, u16, 0xA) = (u16)i;
                }
                s0 = F(s3, void *, 0xC);
                ASM_KEEP_NV(s0);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                {
                    register void *tail_obj ASM_REG("$4") = s0;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                    if (s4 != 0) {
                        register void *tail_a1 ASM_REG("$5") = D_800DED28;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                        register void *tail_a2 ASM_REG("$6") = 0;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                        ASM_USE2(tail_a1, tail_a2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                        r = 0x20;
                        F(tail_obj, u16, 0x10) = (u16)r;
                        F(tail_obj, u16, 0x1E) = 0x1000;
                        F(tail_obj, u16, 0x1C) = 0x1000;
                        return func_80025228(tail_obj, tail_a1, tail_a2);
                    } else {
                        register void *tail_a1 ASM_REG("$5") = D_800DEB28;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                        register void *tail_a2 ASM_REG("$6") = 0;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                        ASM_USE2(tail_a1, tail_a2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                        F(tail_obj, u16, 0x1E) = 0x2000;
                        F(tail_obj, u16, 0x1C) = 0x2000;
                        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                        r = 0x20;
                        F(tail_obj, u16, 0x10) = (u16)r;
                        F(tail_obj, u8, 0xE) = (u8)ctx;
                        F(tail_obj, u8, 0xD) = (u8)ctx;
                        F(tail_obj, u8, 0xC) = (u8)ctx;
                        func_8003DB94(tail_obj, tail_a1, tail_a2);
                    }
                }
            }
            s4++;
        } while (s4 < 4);
    }
    {
        register u32 tail_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        r = F(base, u16, 0xC);
        i = F(base, u16, 0xE);
        tail_a0 = F(base, u16, 0x10);
        F(base, u16, 0x12) = (u16)r;
        F(base, u16, 0x14) = (u16)i;
        F(base, u16, 0x16) = (u16)tail_a0;
    }
L2_post_short:
    if (F(base, s16, 0x20) != 11) {
        return;
    }
    s3 = func_8003FC64(0x212);
    if (s3 == 0) {
        return;
    }
    special_obj = s3;
    special_data = D_80045340;
    ASM_KEEP_NV(special_data);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    F(s3, s16, 0x4A) = 6;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    r = (u32)0x80020000;
    ASM_KEEP_NV(r);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    r += 0x48B8;
    F(s3, void *, 0x10) = (void *)r;
    func_8004491C(special_obj, special_data);
    r = 0x20;
    s0 = F(s3, void *, 0xC);
    {
        void *p;
        F(s0, u16, 0x10) = (u16)r;
        F(s0, u16, 6) = 8;
        p = D_800814A8[0];
        F(s0, u16, 0x14) = (u16)(F(s0, u16, 0x14) | 0xC);
        dest = F(s3, void *, 8);
        p = F(p, void *, -24);
        F(dest, u32, 0) = F(p, u32, 0);
        F(dest, u32, 4) = F(p, u32, 4);
        F(dest, u32, 8) = F(p, u32, 8);
    }
    {
        u8 *dungeon = D_80082E80;
        if (func_8003DF74(F(dungeon, void *, 8), dungeon,
                          (u8 *)base + 0xC, 0) != 0) {
        F(dest, u32, 0) += (u32)(F(base, s16, 0xC) << 16);
        F(dest, u32, 4) += (u32)(F(base, s16, 0xE) << 16);
        F(dest, u32, 8) += (u32)(F(base, s16, 0x10) << 16);
        }
    }
    s0 = F(s3, void *, 0xC);
    F(s0, u16, 0x1E) = 0x80;
    F(s0, u16, 0x1C) = 0x80;
    F(s0, u8, 0xE) = 0x80;
    F(s0, u8, 0xD) = 0x80;
    F(s0, u8, 0xC) = 0x80;
    *(Packed12 *)((u8 *)s3 + 146) = *(Packed12 *)D_800256EC;
    F(s0, void *, 8) = (u8 *)s3 + 146;
    func_800256AC();

L3:
    if (F(base, s16, 0x20) < 13) {
        goto L3_tail;
    }
    s4 = 0;
    ptr2492c = D_8002492C;
    s7 = D_80082E80;
    s6 = D_80083780;
    ctx = 0x80;
    do {
        s3 = func_8003FC64(0x212);
        if (s3 != 0) {
            special_obj = s3;
            special_data = D_80045340;
            ASM_KEEP_NV(special_data);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            ctx = (u8 *)s3 + 0x20;
            F(ctx, s16, 0x2A) = 12;
            F(s3, void *, 0x10) = ptr2492c;
            func_8004491C(special_obj, special_data);
            s0 = F(s3, void *, 0xC);
            F(s0, u16, 0x14) = (u16)(F(s0, u16, 0x14) | 0xC);
            F(s0, u16, 0x10) = 0x60;
            if ((func_80069EF8() & 1) == 0) {
                F(s0, u16, 0x14) = (u16)(F(s0, u16, 0x14) | 1);
            }
            dest = F(s3, void *, 8);
            if (func_8003DF74(F(s7, void *, 8), s7, (u8 *)base + 0xC, 0) != 0) {
                F(base, u16, 0xC) = (u16)(F(base, u16, 0xC) + F(s6, u16, 2));
                F(base, u16, 0xE) = (u16)(F(base, u16, 0xE) + F(s6, u16, 6));
                F(base, u16, 0x10) = (u16)(F(base, u16, 0x10) + F(s6, u16, 0xA));
                if (s4 != 0) {
                    F(ctx, s16, 0x2A) = 8;
                    F(s0, u16, 0x10) = 0x20;
                    r = (u32)func_80069EF8() & 0x3F;
                    i = F(base, u16, 0xC);
                    i -= 0x20;
                    i += r;
                    F(base, u16, 0xC) = (u16)i;
                    r = (u32)func_80069EF8() & 0x3F;
                    i = F(base, u16, 0xE);
                    i -= 0x20;
                    i += r;
                    F(base, u16, 0xE) = (u16)i;
                    r = (u32)func_80069EF8() & 0x3F;
                    i = F(base, u16, 0x10);
                    i -= 0x20;
                    i += r;
                    F(base, u16, 0x10) = (u16)i;
                }
            }
            F(dest, u16, 2) = F(base, u16, 0xC);
            F(dest, u16, 6) = F(base, u16, 0xE);
            F(dest, u16, 0xA) = F(base, u16, 0x10);
            s0 = F(s3, void *, 0xC);
            F(s0, u16, 0x1E) = 0x1000;
            F(s0, u16, 0x1C) = 0x1000;
            F(s0, u8, 0xE) = 0x80;
            F(s0, u8, 0xD) = 0x80;
            F(s0, u8, 0xC) = 0x80;
            if (s4 != 0) {
                register void *tail_obj ASM_REG("$4") = s0;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                void *tail_a1 = D_800DEB28;
                ASM_TAILSLOT_PIN(tail_a1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                return func_8002555C(tail_obj, tail_a1);
            } else {
                func_8003DB94(s0, D_800DE870, 0);
            }
        }
        s4++;
    } while (s4 < 4);

L3_tail:
    {
        register void *obj ASM_REG("$5") = F(D_800814A8[0], void *, 0x60);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 v;
        if (obj != 0) {
            F(obj, u32, 0x1C) |= 0x10000000;
            {
                register void *sub ASM_REG("$6") = F(obj, void *, -20);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                v = F(base, s16, 0x20) * 0x7F;
                if (v < 0) {
                    v += 15;
                }
                F(sub, s8, 0xC) = (s8)((v >> 4) - 0x80);
                v = (16 - F(base, s16, 0x20)) << 3;
                F(sub, s8, 0xE) = (s8)v;
                F(sub, s8, 0xD) = (s8)v;
            }
        }
    }
    if ((F(D_80082E80, u16, 0x14) & 0x8000) == 0) {
        F(base, u16, 0x20) = (u16)(F(base, u16, 0x20) - 1);
        if (F(base, s16, 0x20) >= 0) {
            return;
        }
    }
    F(base, u16, 0xA) = 4;
    func_800256AC();

L4:
    if (F(D_8002571C, s16, 0) == 0) {
        void *l4_obj =
            F(D_800814A8[0], void *, 0x60);
        register s32 l4_color ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        if (l4_obj != 0) {
            r = (u32)0xEFFFFFFF;
            l4_color = 0x00808080;
            i = (s32)F(l4_obj, u32, 0x1C);
            particle_color = (s32)F(l4_obj, void *, -20);
            i &= (s32)r;
            F(l4_obj, u32, 0x1C) = (u32)i;
            F((void *)particle_color, u32, 0xC) = (u32)l4_color;
        }
        {
            D_80083460_t *dstate = &D_80083460;
            r = dstate->fieldA;
            F(dstate, u32, 0xC) = 0;
            F(D_80082E80, u16, 6) = 0;
            dstate->fieldA = (u16)(r - 1);
        }
        F(base, u16, -2) = (u16)(F(base, u16, -2) | 0x8000);
        D_800814A0[0] |= 0x8000;
        func_800256AC();
    }
    F(D_8002571C, s16, 0) = 0;
}
