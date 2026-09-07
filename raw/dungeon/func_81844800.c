#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct Vec3 {
    s16 x;
    s16 y;
    s16 z;
} Vec3;


extern u8 D_80083498[];
extern u8 D_800DEA68[];
extern u8 D_800DECF8[];
extern s32 D_8008346C[];
extern s32 D_800814A0[];

extern void *jtbl_80024008[];
__asm__(".set jtbl_80024008, 0x80024008");

extern void *func_8003FD64(s32, void *);
extern s32 func_80069EF8(void);
extern s32 func_800A3820(s32);
extern void *func_800A05A4(void *, u8, u8, s16, s16);
extern void func_8009CE1C(void *, s32, s32, s32, s32, void *, s32);
extern void *func_8003DE58(void *, void *, Vec3 *, s32);
extern s16 func_800BCB04(u16, u16, s16);
extern void func_800A56E0(s32);
extern void func_8004491C(void *, void *);

extern void func_80024020(void);
extern void func_800241AC(void);
extern void func_800243D8(void);
extern void func_80024430(void);
extern void func_8002447C(void);
extern void func_80024684(void);
extern void func_800246B4(void);
__asm__(".set func_80024020, 0x80024020");
__asm__(".set func_800241AC, 0x800241ac");
__asm__(".set func_800243D8, 0x800243d8");
__asm__(".set func_80024430, 0x80024430");
__asm__(".set func_8002447C, 0x8002447c");
__asm__(".set func_80024684, 0x80024684");
__asm__(".set func_800246B4, 0x800246b4");

extern void func_80024C84(void);
extern void func_80024868(void);
extern void func_8002472C(void);
__asm__(".set func_80024C84, 0x80024c84");
__asm__(".set func_80024868, 0x80024868");
__asm__(".set func_8002472C, 0x8002472c");

extern void func_8002428C(void) __attribute__((noreturn));
extern void func_80024468(void) __attribute__((noreturn));
extern void func_800246A0(void) __attribute__((noreturn));
extern void func_800246A4(void) __attribute__((noreturn));
extern void func_800246F8(void) __attribute__((noreturn));
__asm__(".set func_8002428C, 0x8002428c");
__asm__(".set func_80024468, 0x80024468");
__asm__(".set func_800246A0, 0x800246a0");
__asm__(".set func_800246A4, 0x800246a4");
__asm__(".set func_800246F8, 0x800246f8");

/* Retail places an 8-entry (32-byte) callee jump table immediately before this
 * function's own code, all under the func_81844800 symbol (one 1836-byte
 * span). The table is pinned to the function's own named section (not the
 * generic ".text") so it lands ahead of the compiled body in the same output
 * section, byte-for-byte and gap-free -- a naked-asm label + a bare
 * section(".text") table (the original approach) leaves the table in the
 * literal ".text" section, which the land gate's `.text.func_81844800`-scoped
 * KEEP rule never sees, so the table silently zero-fills (bare-text-pin
 * class; cf. func_81892800.c, func_808CB000.c BODY_ATTR shape). BODY_ATTR is
 * applied directly to the compiled body (not left to ccproc.py's `.ent`-name
 * rename) so both halves land in the identical named section regardless of
 * toolchain quirks. */
#ifdef __mips__
static void (*const func_81844800_table[])(void)
    __asm__("func_81844800")
    __attribute__((section(".text.func_81844800"), aligned(4))) = {
        func_80024020,
        0,
        func_800241AC,
        func_800243D8,
        func_80024430,
        func_8002447C,
        func_80024684,
        func_800246B4,
    };
__asm__(".globl func_81844800\n"
        ".type func_81844800,@function\n"
        ".size func_81844800, 1836");
#define BODY_NAME composite_body_81844800
#define BODY_STORAGE static
#define BODY_ATTR __attribute__((used, section(".text.func_81844800")))
#else
#define BODY_NAME func_81844800
#define BODY_STORAGE
#define BODY_ATTR
#endif

BODY_STORAGE void BODY_NAME(void *arg0_in, void *arg1_in, void *arg2) BODY_ATTR;
BODY_STORAGE void BODY_NAME(void *arg0_in, void *arg1_in, void *arg2) {
    static void *const jt_keep[] = {
        &&case0, &&case1, &&case2, &&case3, &&case4, &&case5
    };
    register void *arg0 ASM_REG("$22") = arg0_in;
    register void *arg1_reg ASM_REG("$20");
    register void *root ASM_REG("$19");
    Vec3 delta;
    void * volatile base;
    register void *info ASM_REG("$23");
    register void *object ASM_REG("$17");
    register void *part ASM_REG("$18");
    register void *render ASM_REG("$16");
    register s32 count ASM_REG("$21");
    void *s8_page;
    s16 state;

    ASM_KEEP(arg0);

    root = FIELD(arg0, void *, 0);
    {
        register void *initial_base ASM_REG("$8");
        initial_base = (u8 *)root - 0x20;
        base = initial_base;
    }
    ASM_SCHED_BARRIER();
    state = FIELD(arg0, s16, 0xA);
    info = FIELD(root, void *, -0x14);
    arg1_reg = arg1_in;
    if (state == 0) {
        goto dispatch;
    }
    ASM_KEEP(arg1_reg);
    if (state < 5) {
        count = 12;
        s8_page = D_800DEA68;
        ASM_KEEP(s8_page);
        do {
            object = func_8003FD64(0x312, &D_80083498);
            if (object != 0) {
                part = (u8 *)object + 0x20;
                ASM_KEEP(part);
                render = FIELD(object, void *, 0xC);
                ASM_KEEP(render);
                {
                    register void *callback ASM_REG("$8");
                    callback = func_80024C84;
                    FIELD(object, void *, 0x10) = callback;
                }
                FIELD(FIELD(object, void *, 8), s32 *, 0) =
                    FIELD(arg1_reg, s32, 0) + (((func_80069EF8() & 0x1FF) - 255) << 13);
                FIELD(FIELD(object, void *, 8), s32 *, 4) =
                    FIELD(arg1_reg, s32, 4) + (((func_80069EF8() & 0x1FF) - 255) << 13);
                FIELD(FIELD(object, void *, 8), s32 *, 8) =
                    FIELD(arg1_reg, s32, 8) + (((func_80069EF8() & 0x1FF) - 255) << 10);

                {
                    u16 flags = FIELD(render, u16, 0x14);
                    FIELD(render, s16, 0x1E) = 0x1000;
                    FIELD(render, s16, 0x1C) = 0x1000;
                    FIELD(render, s16, 0x10) = 0x40;
                    FIELD(render, void *, 0) = s8_page;
                    FIELD(render, u16, 0x14) = flags | 0xC;
                    {
                        u32 page_value = FIELD(s8_page, u32, 4);
                        FIELD(render, u8, 4) = 0;
                        FIELD(render, u8, 5) = 0;
                        FIELD(render, u32, 0xC) = 0x00404040;
                        FIELD(render, u32, 8) = page_value;
                    }
                }
                FIELD(object, void *, 0x20) = arg0;
                FIELD(part, u16, 0x48) = func_80069EF8() & 3;
                FIELD(part, u16, 0x4A) = 8;
                FIELD(part, u16, 0x4C) = 0;
            }
            count--;
        } while (count >= 0);
    }

dispatch:
    {
        s32 state_idx = FIELD(arg0, s16, 0xA);
        if ((u32)state_idx >= 6) {
            goto done;
        }
        (void)jt_keep;
        goto *jtbl_80024008[state_idx];
    }

case0:
    {
    void *created;
    if ((FIELD(FIELD(arg0, void *, 4), u16, 0) & 0x80) == 0) {
        goto done;
    }
    created = func_800A05A4(
        root,
        FIELD(info, u8, 0x24),
        FIELD(info, u8, 0x25),
        FIELD(root, s16, 0x2A),
        (s16)func_800A3820(9));
    FIELD(root, void *, 0x60) = created;
    if (created == 0) {
        FIELD(root, u8, 0x72) = FIELD(info, u8, 0x24);
        FIELD(root, u8, 0x73) = FIELD(info, u8, 0x25);
        func_8002428C();
        return;
    }
    render = FIELD(created, void *, -0x14);
    if ((FIELD(render, u16, 0x14) & 0x8000) != 0) {
        register void *arg2_reg ASM_REG("$8");
        arg2_reg = arg2;
        ASM_KEEP(arg2_reg);
        if ((FIELD(arg2_reg, u16, 0x14) & 0x8000) != 0) {
            func_8009CE1C(
                FIELD(root, void *, 0x60),
                10,
                FIELD(arg0, u8, 9),
                4,
                FIELD(root, s16, 0x2A),
                root,
                2);
            {
                register s32 ret5 ASM_REG("$2") = 5;
                ASM_TAILSLOT_PIN_TIED(ret5);
                func_80024468();
                return;
            }
        }
    }
    FIELD(root, u8, 0x72) = FIELD(render, u8, 0x24);
    FIELD(root, u8, 0x73) = FIELD(render, u8, 0x25);
    {
    register void *base_before ASM_REG("$8");
    base_before = base;
    if (func_8003DE58(
            FIELD(FIELD(base_before, void *, 0xC), void *, 8),
            FIELD(base_before, void *, 0xC), &delta, 0) == 0) {
        delta.z = 0;
        delta.y = 0;
        delta.x = 0;
    }
    {
    register void *base_after ASM_REG("$8");
    base_after = base;
    FIELD(arg1_reg, u16, 2) = FIELD(FIELD(base_after, void *, 8), u16, 2) + delta.x;
    FIELD(arg1_reg, u16, 6) = FIELD(FIELD(base_after, void *, 8), u16, 6) + delta.y;
    FIELD(arg1_reg, u16, 0xA) = FIELD(FIELD(base_after, void *, 8), u16, 0xA) + delta.z;
    FIELD(arg0, u16, 0x50) = 8;
    {
        register s32 root_x ASM_REG("$3");
        root_x = FIELD(root, s8, 0x72);
        ASM_KEEP(root_x);
        {
            s16 base_x = FIELD(arg1_reg, u16, 2) - 0x20;
            FIELD(arg1_reg, u16, 0xE) = (root_x << 6) - base_x;
        }
    }
    FIELD(arg1_reg, s32, 0xC) /= FIELD(arg0, s16, 0x50);
    {
        register s32 root_y ASM_REG("$3");
        root_y = FIELD(root, s8, 0x73);
        ASM_KEEP(root_y);
        {
            s16 base_y = FIELD(arg1_reg, u16, 6) - 0x20;
            FIELD(arg1_reg, u16, 0x12) = (root_y << 6) - base_y;
        }
    }
    FIELD(arg1_reg, s32, 0x10) /= FIELD(arg0, s16, 0x50);
    FIELD(arg1_reg, s16, 0x16) = func_800BCB04(
        FIELD(arg1_reg, u16, 2),
        FIELD(arg1_reg, u16, 6),
        (s16)(FIELD(FIELD(base_after, void *, 8), u16, 0xA) - 48)) -
        (FIELD(arg1_reg, u16, 0xA) + 176);
    }
    FIELD(arg1_reg, s32, 0x14) /= FIELD(arg0, s16, 0x50);
    func_800A56E0(0x300);
    func_800246A0();
    return;
    }
    }

case1:
    FIELD(arg1_reg, s32, 0) += FIELD(arg1_reg, s32, 0xC);
    FIELD(arg1_reg, s32, 4) += FIELD(arg1_reg, s32, 0x10);
    FIELD(arg1_reg, s32, 8) += FIELD(arg1_reg, s32, 0x14);
    state = FIELD(arg0, u16, 0x50) - 1;
    FIELD(arg0, u16, 0x50) = state;
    if ((state << 16) > 0) {
        goto done;
    }
    {
        register u16 timer_reset ASM_REG("$3") = 12;
        state = FIELD(arg0, u16, 0xA);
        ASM_KEEP(state);
        FIELD(arg0, u16, 0x50) = timer_reset;
        func_800246A4();
        return;
    }

case2:
    {
    register u16 nonzero_timer ASM_REG("$3");
    state = FIELD(arg0, u16, 0x50) - 1;
    FIELD(arg0, u16, 0x50) = state;
    if ((state << 16) > 0) {
        goto done;
    }
    if (FIELD(root, void *, 0x60) != 0) {
        nonzero_timer = 10;
        goto case2_nonzero;
    }
    FIELD(arg0, u16, 0x50) = 8;
    FIELD(arg0, u16, 0xA) = 5;
    func_800246F8();
    return;

case2_nonzero:
    state = FIELD(arg0, u16, 0xA);
    ASM_KEEP(state);
    FIELD(arg0, u16, 0x50) = nonzero_timer;
    func_800246A4();
    return;
    }

case3:
    if ((FIELD(arg0, u16, 0x52) & 0x7FFF) == 0) {
        object = func_8003FD64(0x201, &D_80083498);
        if (object != 0) {
            void *initial_part = (u8 *)object + 0x20;
            FIELD(object, void *, 0x10) = func_8002472C;
            func_8004491C(object, func_80024868);
            FIELD(initial_part, u16, 0x2A) = 8;
            FIELD(object, void *, 0x20) = arg0;
            FIELD(initial_part, u16, 4) = FIELD(arg1_reg, u16, 2);
            FIELD(initial_part, u16, 6) = FIELD(arg1_reg, u16, 6);
            FIELD(initial_part, u16, 8) = FIELD(arg1_reg, u16, 0xA);
            FIELD(arg0, u16, 0x52)++;
            FIELD(initial_part, u16, 0x2C) = 0;
        }
    }
    if (FIELD(arg0, s16, 0x50) == 7 &&
        FIELD(root, void *, 0x60) != 0) {
        func_8009CE1C(
            FIELD(root, void *, 0x60),
            10,
            FIELD(arg0, u8, 9),
            4,
            FIELD(root, s16, 0x2A),
            root,
            2);
    }
    count = 20;
    do {
        object = func_8003FD64(0x312, &D_80083498);
        if (object != 0) {
            part = (u8 *)object + 0x20;
            ASM_KEEP(part);
            render = FIELD(object, void *, 0xC);
            FIELD(object, void *, 0x10) = func_80024C84;
            FIELD(FIELD(object, void *, 8), s32, 0) = FIELD(arg1_reg, s32, 0);
            FIELD(FIELD(object, void *, 8), s32, 4) = FIELD(arg1_reg, s32, 4);
            state = (func_80069EF8() & 0x3F) - 176;
            FIELD(FIELD(object, void *, 8), s16, 0xA) = FIELD(arg1_reg, u16, 0xA) - state;
            FIELD(FIELD(object, void *, 8), s16, 0xE) = (func_80069EF8() & 0xF) - 8;
            FIELD(FIELD(object, void *, 8), s16, 0x12) = (func_80069EF8() & 0xF) - 8;
            FIELD(FIELD(object, void *, 8), s16, 0x16) = -(func_80069EF8() & 7);
            {
                u16 flags = FIELD(render, u16, 0x14);
                FIELD(render, s16, 0x1E) = 0x1000;
                FIELD(render, s16, 0x1C) = 0x1000;
                FIELD(render, s16, 0x10) = 0x60;
                FIELD(render, void *, 0) = D_800DECF8;
                FIELD(render, u16, 0x14) = flags | 0xC;
                {
                    u32 page_value = FIELD(D_800DECF8, u32, 4);
                    FIELD(render, u8, 4) = 0;
                    FIELD(render, u8, 5) = 0;
                    FIELD(render, u32, 0xC) = 0x00404040;
                    FIELD(render, u32, 8) = page_value;
                }
            }
            FIELD(object, void *, 0x20) = arg0;
            FIELD(part, u16, 0x48) = func_80069EF8() & 3;
            FIELD(part, u16, 0x4A) = 16;
            FIELD(part, u16, 0x4C) = 0;
        }
        count--;
    } while (count >= 0);
    state = FIELD(arg0, u16, 0x50) - 1;
    FIELD(arg0, u16, 0x50) = state;
    if ((state << 16) > 0) {
        goto done;
    }
    {
        register u16 timer_reset ASM_REG("$3") = 8;
        state = FIELD(arg0, u16, 0xA);
        ASM_KEEP(state);
        FIELD(arg0, u16, 0x50) = timer_reset;
        func_800246A4();
        return;
    }

case4:
    state = FIELD(arg0, u16, 0x50) - 1;
    FIELD(arg0, u16, 0x50) = state;
    if ((state << 16) > 0) {
        goto done;
    }
    FIELD(arg0, u16, 0xA)++;
    func_800246F8();
    return;

case5:
    {
        register u16 masked ASM_REG("$2");
        if ((FIELD(arg0, s16, 0x52) & 0x8000) != 0) {
            masked = FIELD(arg0, u16, 0x52) & 0x7FFF;
            ASM_KEEP(masked);
            FIELD(arg0, u16, 0x52) = masked;
            func_800246F8();
            return;
        }
        ASM_SCHED_BARRIER();
        D_8008346C[0] = 0;
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }

done:
    return;
}
