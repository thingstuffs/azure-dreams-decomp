#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A3820(s32);
extern void *func_800A05A4(void *, u8, u8, s16, s16);
extern s16 func_800BCB04(u16, u16, s16);
extern void func_800A56E0(s32);
extern s32 func_8009D218(void *, s32, void *);
extern void func_800C8900(void *, s32, s32);

extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_80024538[];
extern u8 D_800DEAE0[];
extern u8 D_80024684[];
extern u8 D_80024714[];
extern u8 D_800E3D68[];
extern s32 D_8008346C[];
extern s32 D_800814A0[];
extern void *jtbl_80024008[];

__asm__(".set jtbl_80024008, 0x80024008");

#ifdef __mips__
static const u32 func_80024000_prefix[] __asm__("func_80024000")
    __attribute__((section(".text.func_80024000"), aligned(4))) = {
        0x80024020,
        0,
        0x80024090,
        0x8002421C,
        0x800243E8,
        0x80024424,
        0x80024498,
        0x800244BC,
    };
__asm__(".globl func_80024000\n"
        ".size func_80024000, 1336");
#define FUNC_818DA800_BODY func_80024020
#else
#define FUNC_818DA800_BODY func_80024000
#endif

void FUNC_818DA800_BODY(void *arg0_in, void *arg1_in)
{
#ifdef __mips__
    register void *arg0 ASM_REG("$20") = arg0_in;
    register void *arg1 ASM_REG("$19") = arg1_in;
#else
    void *arg0 = arg0_in;
    void *arg1 = arg1_in;
#endif
#ifdef __mips__
    register void *inner ASM_REG("$18");
    register void *source ASM_REG("$16");
    register void *image_base ASM_REG("$22");
    register void *resource_base ASM_REG("$21");
#else
    void *inner;
    void *source;
    void *image_base;
    void *resource_base;
#endif
#ifdef __mips__
    register s32 base_or_count ASM_REG("$17");
#else
    s32 base_or_count;
#endif
    s16 timer;
    s32 index;
    s32 coord;
    void **table;
    void *target;
    static void *const keepalive[] = {
        &&finish,
        &&case0,
        &&case1,
        &&case2,
        &&case3,
        &&case4,
        &&case5,
    };

    ASM_KEEP(arg0);
    ASM_KEEP(arg1);
    inner = FIELD(arg0, void *, 0);
    ASM_SCHED_BARRIER();
    timer = (u16)FIELD(arg0, u16, 0x50);
    ASM_SCHED_BARRIER();
    timer -= 1;
    index = *(s16 *)((u8 *)arg0 + 0xA);
    ASM_SCHED_BARRIER();
    source = FIELD(inner, void *, -0x14);
    FIELD(arg0, u16, 0x50) = timer;

    if ((u32)index >= 6) {
        goto finish;
    }
    base_or_count = (s32)((u8 *)inner - 0x20);
    ASM_KEEP(base_or_count);
    table = jtbl_80024008;
    ASM_KEEP(table);
    index <<= 2;
    index = (s32)((u8 *)table + index);
    target = *(void **)(u32)index;
    (void)keepalive;
    goto *target;

case0:
        if ((FIELD(FIELD(arg0, void *, 4), u16, 0) & 0x80) == 0) {
            goto finish;
        }
        {
            void *obj;
            s16 height;

            height = (s16)func_800A3820(0x22);
            obj = func_800A05A4(inner,
                                FIELD(source, u8, 0x24),
                                FIELD(source, u8, 0x25),
                                FIELD(inner, s16, 0x2A), height);
            FIELD(inner, void *, 0x60) = obj;
            if (obj == 0) {
                FIELD(inner, u8, 0x72) = FIELD(source, u8, 0x24);
                FIELD(inner, u8, 0x73) = FIELD(source, u8, 0x25);
                goto update;
            }
            {
#ifdef __mips__
                register void *new_source ASM_REG("$6");
#else
                void *new_source;
#endif
                new_source = FIELD(obj, void *, -0x14);
                FIELD(inner, u8, 0x72) = FIELD(new_source, u8, 0x24);
                FIELD(inner, u8, 0x73) = FIELD(new_source, u8, 0x25);
            }
        }

update:
        FIELD(arg1, u16, 2) =
            FIELD(FIELD((void *)base_or_count, void *, 8), u16, 2);
        FIELD(arg1, u16, 6) =
            FIELD(FIELD((void *)base_or_count, void *, 8), u16, 6);
        FIELD(arg1, u16, 0xA) =
            FIELD(FIELD((void *)base_or_count, void *, 8), u16, 0xA);
        FIELD(arg0, u16, 0x50) = 8;
        coord = FIELD(inner, s8, 0x72);
        FIELD(arg1, s16, 0xE) =
            (coord << 6) - (FIELD(arg1, u16, 2) - 0x20);
        FIELD(arg1, s32, 0xC) = FIELD(arg1, s32, 0xC) /
            FIELD(arg0, s16, 0x50);
        coord = FIELD(inner, s8, 0x73);
        FIELD(arg1, s16, 0x12) =
            (coord << 6) - (FIELD(arg1, u16, 6) - 0x20);
        FIELD(arg1, s32, 0x10) = FIELD(arg1, s32, 0x10) /
            FIELD(arg0, s16, 0x50);
        FIELD(arg1, s16, 0x16) = func_800BCB04(
            FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
            (s16)(FIELD(FIELD((void *)base_or_count, void *, 8), u16, 0xA) -
                  0x30)) - FIELD(arg1, s16, 0xA);
        FIELD(arg1, s32, 0x14) = FIELD(arg1, s32, 0x14) /
            FIELD(arg0, s16, 0x50);
        func_800A56E0(0x300);
        FIELD(arg0, u16, 0xA)++;
        goto finish;

case1:
        FIELD(arg1, s32, 0) += FIELD(arg1, s32, 0xC);
        FIELD(arg1, s32, 4) += FIELD(arg1, s32, 0x10);
        FIELD(arg1, s32, 8) += FIELD(arg1, s32, 0x14);
        if (FIELD(arg0, s16, 0x50) > 0) {
            goto finish;
        }
        {
#ifdef __mips__
            register u8 *base_page ASM_REG("$2");
#else
            u8 *base_page;
#endif
            base_or_count = 3;
#ifdef __mips__
            base_page = (u8 *)0x80020000;
            ASM_KEEP(base_page);
            image_base = base_page + 0x4538;
            base_page = (u8 *)0x800E0000;
            ASM_KEEP(base_page);
            resource_base = base_page - 0x1520;
#else
            image_base = D_80024538;
            resource_base = D_800DEAE0;
#endif
            do {
                void *obj;
#ifdef __mips__
                register void *prim ASM_REG("$6");
#else
                void *prim;
#endif
#ifdef __mips__
                register void *state ASM_REG("$7");
#else
                void *state;
#endif
                void *resource_cursor;
#ifdef __mips__
                s32 x;
                s32 result;
                register s32 dst_or_delta ASM_REG("$4");
                register s32 prim_color ASM_REG("$5");
#else
                s32 x;
                s32 result;
                s32 dst_or_delta;
                s32 prim_color;
#endif

                obj = func_8003FD64(0x312, D_80083498);
                if (obj != 0) {
                    func_8004491C(obj, D_80045340);
                    prim = FIELD(obj, void *, 0xC);
                    dst_or_delta = (s32)FIELD(obj, void *, 8);
                    FIELD(obj, void *, 0x10) = image_base;
                    x = FIELD(arg1, s16, 2);
                    state = (u8 *)obj + 0x20;
                    if (base_or_count >> 1) {
                        result = x - 16;
                    } else {
                        result = x + 16;
                    }
                    FIELD((void *)dst_or_delta, s16, 2) = result;
                    ASM_SCHED_BARRIER();
                    dst_or_delta = (s32)FIELD(obj, void *, 8);
                    x = FIELD(arg1, s16, 6);
                    if ((base_or_count & 1) == 0) {
                        result = x + 16;
                    } else {
                        result = x - 16;
                    }
                    FIELD((void *)dst_or_delta, s16, 6) = result;
                    ASM_SCHED_BARRIER();
                    prim_color = 0xC00000;
                    ASM_KEEP(prim_color);
                    dst_or_delta = -0x100000;
                    FIELD(FIELD(obj, void *, 8), s32, 8) =
                        FIELD(arg1, s32, 8) + dst_or_delta;
                    FIELD(prim, s16, 0x1E) = 0xC00;
                    FIELD(prim, s16, 0x10) = 0x60;
                    {
                        u16 prim_flags;

                        prim_flags = FIELD(prim, u16, 0x14);
                        prim_color |= 0xC0C0;
                        FIELD(prim, void *, 0) = resource_base;
                        ASM_SCHED_BARRIER();
                        resource_cursor = resource_base;
                        ASM_KEEP(resource_cursor);
                        FIELD(prim, s16, 0x1C) = 0;
                        FIELD(prim, s32, 0xC) = prim_color;
                        prim_flags |= 0xC;
                        FIELD(prim, u16, 0x14) = prim_flags;
                        ASM_SCHED_BARRIER();
                    }
                    FIELD(prim, void *, 8) = FIELD(resource_cursor, void *, 4);
                    FIELD(prim, u8, 4) = 0;
                    FIELD(prim, u8, 5) = 0;
                    FIELD(state, void *, 0) = arg0;
                    FIELD(state, u16, 0x48) =
                        FIELD(inner, void *, 0x60) ? 0x20 : 0xA;
                    FIELD(state, u16, 0x4C) = 0;
                }
                base_or_count--;
            } while (base_or_count >= 0);
        }
        if (FIELD(inner, void *, 0x60) != 0) {
            void *obj;
            obj = func_8003FD64(0x201, D_80083498);
            if (obj != 0) {
#ifdef __mips__
                register void *state ASM_REG("$7");
                register u16 y ASM_REG("$2");
#else
                void *state;
                u16 y;
#endif
                u16 z;
                s32 last;
                func_8004491C(obj, D_80024714);
                FIELD(obj, void *, 0x10) = D_80024684;
                state = (u8 *)obj + 0x20;
                FIELD(state, u16, 4) = FIELD(arg1, u16, 2);
                y = FIELD(arg1, u16, 6);
                ASM_KEEP(y);
                FIELD(state, u16, 6) = y;
                z = FIELD(arg1, u16, 0xA);
                FIELD(state, u16, 0x12) = 1;
                FIELD(state, s32, 0xC) = -64;
                last = 40;
                FIELD(state, u16, 8) = z;
                FIELD(obj, void *, 0x20) = arg0;
                FIELD(state, u16, 0x10) = last;
            }
        }
        FIELD(arg0, u16, 0x50) = 10;
        FIELD(arg0, u16, 0xA)++;
        goto finish;

case2:
        if (FIELD(arg0, s16, 0x50) > 0) {
            goto finish;
        }
        if (FIELD(inner, void *, 0x60) == 0) {
            FIELD(arg0, u16, 0x50) = 8;
            FIELD(arg0, u16, 0xA) = 5;
            goto finish;
        }
        FIELD(arg0, u16, 0x50) = 20;
        FIELD(arg0, u16, 0xA)++;
        goto finish;

case3:
        if (FIELD(arg0, s16, 0x50) > 0) {
            goto finish;
        }
        if (FIELD(inner, void *, 0x60) != 0 &&
            func_8009D218(FIELD(inner, void *, 0x60), 1, inner) == 0 &&
            (FIELD(FIELD(inner, void *, 0x60), u32, 0x14) & 4) != 0) {
            func_800C8900(
                FIELD(inner, void *, 0x60),
                FIELD(D_800E3D68, u8, 0) == 0xFF ? 0xFF : 0x10,
                2);
        }
        FIELD(arg0, u16, 0x50) = 10;
        FIELD(arg0, u16, 0xA)++;
        goto finish;

case4:
        if (FIELD(arg0, s16, 0x50) > 0) {
            goto finish;
        }
        FIELD(arg0, u16, 0x50) = 4;
        FIELD(arg0, u16, 0xA)++;
        goto finish;

case5:
        if (FIELD(arg0, s16, 0x52) & (u16)0x8000) {
            FIELD(arg0, u16, 0x52) &= 0x7FFF;
            goto finish;
        }
        if (FIELD(arg0, s16, 0x50) > 0) {
            goto finish;
        }
        D_8008346C[0] = 0;
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        goto finish;

finish:
    ;
}
