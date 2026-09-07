#include "common.h"

#define F(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern u8 D_800DEA68[];
extern u8 D_800DE990[];
extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_800247D8[];
extern void *D_80024008[];
extern s32 D_8008346C[];
extern u32 D_800814A0[];

extern void *func_8003FD64(s32, void *);
extern s32 func_80069EF8(void);
extern s32 func_800A3820(s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern s32 func_8003DE58(void *, void *, void *, s32);
extern s32 func_800BCB04(u16, u16, s16);
extern void func_800A56E0(s32);
extern void func_8004491C(void *, void *);
extern void D_80024688(void);
extern void func_8009CE1C(void *, s32, u8, s32, s16, void *, s32);

#ifdef __mips__
static const u32 func_80024000_prefix[] __asm__("func_80024000")
    __attribute__((section(".text.func_80024000"), aligned(4))) = {
    0x80024020,
    0,
    0x800241A8,
    0x8002437C,
    0x800243D4,
    0x8002441C,
    0x80024594,
    0x800245FC,
};
__asm__(".globl func_80024000\n"
        ".size func_80024000, 1672");
#define FUNC_8183E800_BODY jt_body_8183E800
#define FUNC_8183E800_LINKAGE static
#else
#define FUNC_8183E800_BODY func_80024000
#define FUNC_8183E800_LINKAGE
#endif

FUNC_8183E800_LINKAGE void FUNC_8183E800_BODY(u8 *self, u8 *motion)
{
    register u8 *owner;
    u8 *record;
    register u8 *base;
    u8 *created;
    u8 *part;
    u8 *sub;
    u8 *image;
    u8 *global;
    s16 state;
    s16 timer;
    s32 delta;
    u32 index;
    s32 i;
    s32 random;
    u32 color;
    s16 buf[3];
    static void *const keepalive[] = {
        &&state_2,
        0,
        &&state_3,
        &&state_4,
        &&state_5,
        &&advance_state,
        &&state_7,
    };

    owner = F(self, u8 *, 0);
    base = owner - 32;
    state = F(self, s16, 10);
    record = F(owner, u8 *, -20);
    if (state != 0 && state < 5) {
        i = 16;
        global = D_800DEA68;
        do {
            created = func_8003FD64(0x312, D_80083498);
            if (created != 0) {
                part = created + 32;
                sub = F(created, u8 *, 12);
                F(created, void *, 16) = &D_80024688;

                F(F(created, u8 *, 8), u32, 0) = F(motion, u32, 0) +
                    (((func_80069EF8() & 0x1ff) - 255) << 13);
                F(F(created, u8 *, 8), u32, 4) = F(motion, u32, 4) +
                    (((func_80069EF8() & 0x1ff) - 255) << 13);
                color = 0xf00000;
                F(F(created, u8 *, 8), u32, 8) = F(motion, u32, 8) +
                    (((func_80069EF8() & 0x1ff) - 255) << 11);

                F(sub, u16, 20) |= 0xc;
                F(sub, u16, 30) = 0x1000;
                F(sub, u16, 28) = 0x1000;
                F(sub, u16, 16) = 0x60;
                F(sub, void *, 0) = global;
                F(sub, u32, 8) = F(global, u32, 4);
                color |= 0x8080;
                F(sub, u8, 4) = 0;
                F(sub, u8, 5) = 0;
                F(sub, u32, 12) = color;
                F(created, void *, 32) = self;
                F(part, u16, 72) = func_80069EF8() & 3;
                F(part, u16, 74) = 24;
                F(part, u16, 76) = 0;
            }
            i--;
        } while (i >= 0);
    }

    state = F(self, s16, 10);
    index = state;
    if (index >= 6)
        goto return_done;
    (void)keepalive;
    goto *D_80024008[index];

state_2:
    image = F(self, u8 *, 4);
    if ((F(image, u16, 0) & 0x80) == 0)
        goto return_done;
    if ((F(owner, u8 *, 96) = func_800A05A4(
             owner, F(record, u8, 36), F(record, u8, 37),
             F(owner, s16, 42), (s16)func_800A3820(8))) == 0) {
        F(owner, u8, 114) = F(record, u8, 36);
        F(owner, u8, 115) = F(record, u8, 37);
        goto state_2_common;
    }
    sub = F(F(owner, u8 *, 96), u8 *, -20);
    F(owner, u8, 114) = F(sub, u8, 36);
    F(owner, u8, 115) = F(sub, u8, 37);

state_2_common:
    if (func_8003DE58(F(F(base, u8 *, 12), u8 *, 8),
                      F(base, u8 *, 12), buf, 0) == 0) {
        buf[2] = 0;
        buf[1] = 0;
        buf[0] = 0;
    }
    F(motion, u16, 2) = F(F(base, u8 *, 8), u16, 2) + buf[0];
    F(motion, u16, 6) = F(F(base, u8 *, 8), u16, 6) + buf[1];
    F(motion, u16, 10) = F(F(base, u8 *, 8), u16, 10) + buf[2];
    F(self, u16, 80) = 8;
    {
        s32 scaled = F(owner, s8, 114) * 64;
        s32 axis = F(motion, u16, 2) - 32;
        F(motion, u16, 14) = scaled - axis;
    }
    F(motion, s32, 12) /= F(self, s16, 80);
    {
        s32 scaled = F(owner, s8, 115) * 64;
        s32 axis = F(motion, u16, 6) - 32;
        F(motion, u16, 18) = scaled - axis;
    }
    F(motion, s32, 16) /= F(self, s16, 80);
    F(motion, s16, 22) = func_800BCB04(
        F(motion, u16, 2), F(motion, u16, 6),
        (s16)(F(F(base, u8 *, 8), u16, 10) - 48)) -
        (F(motion, u16, 10) + 176);
    F(motion, s32, 20) /= F(self, s16, 80);
    func_800A56E0(0x300);
    goto advance_simple;

advance_simple:
    state = F(self, s16, 10) + 1;
    F(self, s16, 10) = state;
    goto return_done;

state_3:
    F(motion, u32, 0) += F(motion, s32, 12);
    F(motion, u32, 4) += F(motion, s32, 16);
    F(motion, u32, 8) += F(motion, s32, 20);
    timer = F(self, u16, 80) - 1;
    F(self, u16, 80) = timer;
    if (timer > 0)
        goto return_done;
    F(self, u16, 80) = 12;
    state = F(self, s16, 10) + 1;
    F(self, s16, 10) = state;
    goto return_done;

state_4:
    timer = F(self, u16, 80) - 1;
    F(self, u16, 80) = timer;
    if (timer > 0)
        goto return_done;
    if (F(owner, s32, 96) == 0) {
        F(self, u16, 80) = 8;
        F(self, u16, 10) = 5;
        goto return_done;
    }
    state = F(self, s16, 10) + 1;
    F(self, u16, 80) = 20;
    F(self, s16, 10) = state;
    goto return_done;

state_5:
    timer = F(self, s16, 80);
    if (timer % 3 == 0) {
        created = func_8003FD64(0x312, D_80083498);
        if (created != 0) {
            F(created, void *, 16) = D_800247D8;
            func_8004491C(created, D_80045340);
            sub = F(created, u8 *, 12);

            random = func_80069EF8();
            delta = func_80069EF8();
            random &= 0x1ff;
            random += delta & 0x1ff;
            random -= 510;
            random <<= 13;
            random >>= 1;
            random += F(motion, u32, 0);
            F(F(created, u8 *, 8), u32, 0) = random;

            random = func_80069EF8();
            delta = func_80069EF8();
            random &= 0x1ff;
            random += delta & 0x1ff;
            random -= 510;
            random <<= 13;
            random >>= 1;
            random += F(motion, u32, 4);
            F(F(created, u8 *, 8), u32, 4) = random;

            F(F(created, u8 *, 8), u32, 8) = F(motion, u32, 8) + 0x100000;
            F(F(created, u8 *, 8), u32, 20) = 0x40000;

            F(sub, u16, 30) = 0xa00;
            F(sub, u16, 28) = 0xa00;
            F(sub, u16, 16) = 0x20;
            F(sub, void *, 0) = D_800DE990;
            F(sub, u16, 20) |= 0xe;
            F(sub, u32, 8) = F(D_800DE990, u32, 4);
            part = created + 32;
            F(sub, u8, 4) = 0;
            F(sub, u8, 5) = 0;
            F(sub, u32, 12) = 0;
            F(created, void *, 32) = self;
            F(part, u16, 72) = 8;
            F(part, u16, 76) = 0;
        }
    }
    timer = F(self, u16, 80) - 1;
    F(self, u16, 80) = timer;
    if (timer > 0)
        goto return_done;
    state = F(self, s16, 10) + 1;
    F(self, u16, 80) = 13;
    F(self, s16, 10) = state;
    goto return_done;

advance_state:
    timer = F(self, u16, 80) - 1;
    F(self, u16, 80) = timer;
    if (timer > 0)
        goto return_done;
    if (F(owner, s32, 96) != 0) {
        func_8009CE1C(F(owner, void *, 96), 10, F(self, u8, 9), 2,
                      F(owner, s16, 42), owner, 2);
    }
    F(self, u16, 80) = 16;
    state = F(self, s16, 10) + 1;
    F(self, s16, 10) = state;
    goto return_done;

state_7:
    timer = F(self, u16, 80) - 1;
    F(self, u16, 80) = timer;
    if ((F(self, s16, 82) & 0x8000) != 0) {
        F(self, u16, 82) &= 0x7fff;
        goto return_done;
    }
    if (timer > 0)
        goto return_done;
    D_8008346C[0] = 0;
    F(self, u16, -2) |= 0x8000;
    D_800814A0[0] |= 0x8000;

return_done:
    return;
}
