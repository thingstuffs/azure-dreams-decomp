#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))
#define HI16(v) (((s16 *)&(v))[1])
#define HI16U(v) (((u16 *)&(v))[1])

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 rx;
    s32 ry;
    s32 rz;
} FixedCoords;

extern void *func_8003FD64(s32, void *);
extern s32 func_80069EF8(void);
extern s32 func_8003DE58(void *, void *, s16 *, s32);
extern void func_8004491C(void *, void *);
extern s32 func_800A3820(s32);
extern s32 func_800A05A4(void *, s32, s32, s32, s32);
extern s16 func_800BCB04(s32, s32, s32);
extern s16 func_800A4688(s32, s32, s32, s32, s32);
extern void func_8009CE1C(void *, s32, s32, s32, s32, void *, s32);
extern void func_800A56E0(s32);
extern void func_80044A50(void *);

extern u8 D_80024008[];
extern u8 D_80024B58[];
extern u8 D_800248F8[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern u8 D_80083498[];
extern s32 D_8008346C[];
extern s32 D_800814A0[3];
extern u8 D_800DEA68[];
__asm__(".set D_800DEA68, 0x800DEA68");

#ifdef __mips__
static const u32 func_80024000_prefix[] __asm__("func_80024000")
    __attribute__((section(".text.func_80024000"), used, aligned(4))) = {
    0x80024020,
    0,
    0x80024310,
    0x800246B8,
    0x800246DC,
    0x800247D0,
    0x80024844,
    0x8002486C,
};
__asm__(".globl func_80024000\n.size func_80024000, 2296");
#define FUNC_80024000_BODY func_80024020
#else
#define FUNC_80024000_BODY func_80024000
#endif

void FUNC_80024000_BODY(void *arg0, void *arg1, void *arg2)
    __attribute__((section(".text.func_80024000")));
void FUNC_80024000_BODY(void *arg0, void *arg1, void *arg2)
{
    void *inner;
    s32 obj;
    s32 ptr;
    void *sub;
    s32 i;
    s32 ax;
    s32 ay;
    FixedCoords coords;
    s16 temp_pos[3];
    void *base;
    void *other;
    void *hit;
    s32 step_x;
    s32 step_y;
    s32 idx;
    s32 t;
    s32 t73;
    s32 tabs;
    s32 tc2;
    s32 v;
    s32 vq;
    s32 dy;
    s32 n;
    s32 count;
    s32 state_code;
    static void *const keepalive[] __attribute__((used)) = {
        &&L0, &&L1, &&L2, &&L3, &&L4, &&L5
    };

    register u8 *ccd8 ASM_REG("$4") = D_8006CCD8;   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    register s32 idx_reg ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    register u32 temp ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    inner = FIELD(arg0, void *, 0);
    temp = FIELD(inner, u16, 0x2A);
    base = (u8 *)inner - 0x20;
    other = FIELD(inner, void *, -0x14);
    idx_reg = temp >> 8;
    idx_reg &= 0xE;
    step_x = *(s16 *)(ccd8 + idx_reg);
    step_y = *(s16 *)(D_8006CCE8 + idx_reg);

    if ((u32)(FIELD(arg0, u16, 0x0A) - 1) < 3) {
        i = 9;
        do {
            obj = (s32)func_8003FD64(0x312, &D_80083498);
            if (obj != 0) {
                ptr = (s32)FIELD((void *)obj, void *, 0x0C);
                FIELD((void *)obj, void *, 0x10) = D_80024B58;
                FIELD(FIELD((void *)obj, void *, 8), s32, 0) =
                    FIELD(arg1, s32, 0) + (((func_80069EF8() & 0x3FF) - 511) << 9);
                FIELD(FIELD((void *)obj, void *, 8), s32, 4) =
                    FIELD(arg1, s32, 4) + (((func_80069EF8() & 0x3FF) - 511) << 9);
                FIELD(FIELD((void *)obj, void *, 8), s32, 8) =
                    FIELD(arg1, s32, 8) + (((func_80069EF8() & 0x3FF) - 511) << 9);
                if (FIELD(arg0, s16, 0x0A) == 2) {
                    FIELD(FIELD((void *)obj, void *, 8), s32, 0x0C) =
                        FIELD(arg1, s32, 0x0C) >> 2;
                    FIELD(FIELD((void *)obj, void *, 8), s32, 0x10) =
                        FIELD(arg1, s32, 0x10) >> 2;
                    FIELD(FIELD((void *)obj, void *, 8), s32, 0) +=
                        (step_x << 21) -
                        (((step_x * FIELD(arg0, s32, 0x0C)) << 20) / 12);
                    FIELD(FIELD((void *)obj, void *, 8), s32, 4) +=
                        (step_y << 21) -
                        (((step_y * FIELD(arg0, s32, 0x0C)) << 20) / 12);
                    sub = (u8 *)obj + 0x20;
                } else {
                    sub = (u8 *)obj + 0x20;
                }
                FIELD(FIELD((void *)obj, void *, 8), s32, 0x14) = -func_80069EF8() << 1;
                FIELD((void *)ptr, u16, 0x1E) = 0x1000;
                FIELD((void *)ptr, u16, 0x1C) = 0x1000;
                FIELD((void *)ptr, u16, 0x14) |= 0xC;
                if (func_80069EF8() & 1) {
                    FIELD((void *)ptr, u16, 0x14) |= 1;
                }
                FIELD((void *)ptr, s16, 0x10) = 96;
                FIELD((void *)ptr, void *, 0) = D_800DEA68;
                FIELD((void *)ptr, void *, 8) = *(void **)(D_800DEA68 + 4);
                FIELD((void *)ptr, u8, 4) = 0;
                FIELD((void *)ptr, u8, 5) = 0;
                FIELD((void *)ptr, s32, 0x0C) = 0x3030C0;
                FIELD(sub, void *, 0) = arg0;
                FIELD(sub, u16, 0x4C) = 0;
                FIELD(sub, u16, 0x48) = func_80069EF8() & 3;
                FIELD(sub, u16, 0x4A) = i + 40;
                FIELD(sub, s16, 4) = (s8)FIELD(inner, u8, 0x72);
                FIELD(sub, s16, 6) = (s8)FIELD(inner, u8, 0x73);
            }
            i--;
        } while (i >= 0);
    }

    FIELD(arg0, u16, 0x50) = FIELD(arg0, u16, 0x50) - 1;
    state_code = FIELD(arg0, s16, 0x0A);
    if ((u32)state_code >= 6) {
        goto Lend;
    }
    goto *(void (**)(void))((void **)D_80024008)[state_code];

L0:
    if ((FIELD(FIELD(arg0, void *, 4), u16, 0) & 0x80) == 0) {
        goto Lend;
    }
    if (func_8003DE58(FIELD(FIELD(base, void *, 0x0C), void *, 8),
                      FIELD(base, void *, 0x0C), temp_pos, 0) == 0) {
        temp_pos[1] = 0;
        temp_pos[0] = 0;
        temp_pos[2] = (FIELD(other, u16, 0x14) & 0x8000) ? -48 : 0;
    }
    FIELD(arg1, s32, 0) = FIELD(FIELD(base, void *, 8), s32, 0) +
                          ((s32)temp_pos[0] << 16);
    FIELD(arg1, s32, 4) = FIELD(FIELD(base, void *, 8), s32, 4) +
                          ((s32)temp_pos[1] << 16);
    FIELD(arg1, s32, 8) = FIELD(FIELD(base, void *, 8), s32, 8) +
                          ((s32)temp_pos[2] << 16);
    func_8004491C((u8 *)arg0 - 0x20, D_800248F8);
    t = (s16)func_800A3820(7);
    hit = (void *)func_800A05A4(inner, FIELD(other, u8, 0x24),
                                FIELD(other, u8, 0x25),
                                FIELD(inner, s16, 0x2A), t);
    FIELD(inner, void *, 0x60) = hit;
    if (hit != 0) {
        goto Lhit;
    }
    {
    n = 0;
    ay = n;
    ax = n;
    while (n < func_800A3820(7)) {

        i = (FIELD(other, u8, 0x24) + ax) * 64 + 32;
        dy = (FIELD(other, u8, 0x25) + ay) * 64 + 32;
        ptr = i & 0xFFFF;
        {
            register s32 a0_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            a0_arg = ptr;
            obj = dy & 0xFFFF;
            vq = func_800BCB04(a0_arg, obj,
                               (s16)(FIELD(FIELD(base, void *, 8), u16, 0x0A) - 128));
        }
        if (func_800A4688(ptr, obj, vq, FIELD(inner, s16, 0x2A),
                          FIELD(inner, s32, 0x60)) != 0) {
            goto Ldone;
        }
        ay += step_y;
        n++;
        ax += step_x;
    }
Ldone:
    FIELD(inner, u8, 0x72) = FIELD(other, u8, 0x24) + step_x * n;
    t73 = FIELD(other, u8, 0x25) + step_y * n;
    }
    goto Lset73;

Lhit:
    ptr = (s32)FIELD(hit, void *, -0x14);
    if ((FIELD((void *)ptr, u16, 0x14) & 0x8000) && (FIELD(arg2, u16, 0x14) & 0x8000)) {
        FIELD(arg0, s16, 0x0A) = 3;
        goto Lend;
    }
    FIELD(inner, u8, 0x72) = FIELD((void *)ptr, u8, 0x24);
    t73 = FIELD((void *)ptr, u8, 0x25);
Lset73:
    FIELD(inner, u8, 0x73) = t73;
    t73 = FIELD(inner, s8, 0x72);
    HI16(coords.x) = (t73 << 6) + 32;
    t73 = FIELD(inner, s8, 0x73);
    HI16(coords.y) = (t73 << 6) + 32;
    HI16(coords.z) = func_800BCB04(HI16U(coords.x), HI16U(coords.y),
                                   (s16)(FIELD(FIELD(base, void *, 8), u16, 0x0A) - 48));
    if (HI16(coords.z) >= 512) {
        HI16(coords.z) = FIELD(FIELD(base, void *, 8), u16, 0x0A);
    }
    HI16(coords.z) -= 48;
    i = HI16(coords.x) - FIELD(arg1, s16, 2);
    dy = HI16(coords.y) - FIELD(arg1, s16, 6);
    n = i;
    if (i < 0) {
        ASM_KEEP_NV(n);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        n = -n;
    }
    tabs = dy;
    if (dy < 0) {
        ASM_KEEP_NV(tabs);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        tabs = -tabs;
    }
    if (n < tabs) {
        n = tabs;
    }
    count = n / 8;
    count++;
    FIELD(arg0, s16, 0x50) = count;
    FIELD(arg1, s32, 0x0C) = (i << 16) / FIELD(arg0, s16, 0x50);
    FIELD(arg1, s32, 0x10) = (dy << 16) / FIELD(arg0, s16, 0x50);
    FIELD(arg1, s32, 0x14) = (coords.z - FIELD(arg1, s32, 8)) /
                             FIELD(arg0, s16, 0x50);
    FIELD(arg0, s32, 0x0C) = 8;
    FIELD(arg0, u16, 0x50) = FIELD(arg0, u16, 0x50) + FIELD(arg0, u16, 0x0C);
    func_800A56E0(0x300);
    FIELD(arg0, u16, 0x0A) = FIELD(arg0, u16, 0x0A) + 1;
    goto Lend;

L1:
    FIELD(arg0, s32, 0x0C) = FIELD(arg0, s32, 0x0C) - 1;
    if (FIELD(arg0, s32, 0x0C) > 0) {
        goto Lend;
    }
    FIELD(arg0, s32, 0x0C) = 12;
    FIELD(arg0, u16, 0x0A) = FIELD(arg0, u16, 0x0A) + 1;
    goto Lend;

L2:
    FIELD(arg0, s32, 0x0C) = FIELD(arg0, s32, 0x0C) - 1;
    if (FIELD(arg0, s32, 0x0C) > 0) {
        FIELD(arg1, s32, 0x0C) += step_x << 16;
        FIELD(arg1, s32, 0x10) += step_y << 16;
    }
    FIELD(arg1, s32, 0) += FIELD(arg1, s32, 0x0C);
    FIELD(arg1, s32, 4) += FIELD(arg1, s32, 0x10);
    FIELD(arg1, s32, 8) += FIELD(arg1, s32, 0x14);
    idx = FIELD(arg1, s16, 2);
    if (idx < 0) {
        idx += 63;
    }
    if ((idx >> 6) == (s8)FIELD(inner, u8, 0x72)) {
        tc2 = FIELD(arg1, s16, 6);
        if (tc2 < 0) {
            tc2 += 63;
        }
        if ((tc2 >> 6) == (s8)FIELD(inner, u8, 0x73)) {
            FIELD(arg0, u16, 0x50) = 0;
        }
    }
    if (FIELD(arg0, s16, 0x50) > 0) {
        goto Lend;
    }
    FIELD(arg0, u16, 0x0A) = FIELD(arg0, u16, 0x0A) + 1;
    FIELD(arg1, s32, 0x0C) = step_x << 16;
    FIELD(arg1, s32, 0x10) = step_y << 16;
    goto Lend;

L3:
    FIELD(arg1, s32, 0) += FIELD(arg1, s32, 0x0C);
    FIELD(arg1, s32, 4) += FIELD(arg1, s32, 0x10);
    FIELD(arg1, s32, 8) += FIELD(arg1, s32, 0x14);
    if (FIELD(inner, s32, 0x60) != 0) {
        func_8009CE1C(FIELD(inner, void *, 0x60), 10, FIELD(arg0, u8, 9), 1,
                      FIELD(inner, s16, 0x2A), inner, 2);
    }
    FIELD(arg0, s16, 0x50) = 16;
    FIELD(arg0, u16, 0x0A) = FIELD(arg0, u16, 0x0A) + 1;
    goto Lend;

L4:
    func_80044A50((u8 *)arg0 - 0x20);
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    FIELD(arg0, u16, 0x0A) = FIELD(arg0, u16, 0x0A) + 1;
    goto Lend;

L5:
    v = FIELD(arg0, s32, 0x10);
    if (v & 0x8000) {
        FIELD(arg0, s32, 0x10) = v & ~0x8000;
        goto Lend;
    }
    if (FIELD(arg0, s16, 0x50) > 0) {
        goto Lend;
    }
    D_8008346C[0] = 0;
    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0[0] |= 0x8000;
Lend:
    return;
}
