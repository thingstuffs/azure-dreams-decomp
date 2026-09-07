#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect;

extern void func_8003E4FC();
extern void func_8003F6D4();
extern void func_8004068C();
extern void func_800672D8();

extern s32 D_8003E140[];
extern s32 *D_80126D44[];
extern u8 D_8012A998[];
extern u8 D_8012E998[];
extern u8 D_80133198[];

void func_80124DB0(void *arg0)
{
    Rect rect0;
    Rect rect1;
    register Rect *out ASM_REG("$4");
    register u8 *pixels ASM_REG("$5");
    register s32 size ASM_REG("$6");
    s32 one;
    u8 state;

    state = FIELD(arg0, u8, 0xB);
    if (state != 0) {
        if (state != 1) {
            return;
        }
        goto active;
    }

    func_8003F6D4(8, D_8012A998, D_80133198,
                  D_80126D44[FIELD(arg0, u8, 0x13)][1]);
    func_8003E4FC(6, D_80133198, 0);
    FIELD(arg0, u8, 0xD) = 0;
    func_8003E4FC(0xFF, D_8003E140, (u8 *)arg0 + 0xD);
    FIELD(arg0, u8, 0xB)++;

active:
    if (FIELD(arg0, u8, 0xD) == 0) {
        return;
    }

    rect1.x = 0;
    rect1.y = FIELD(arg0, u8, 0x16) + 0x1CA;
    rect1.w = 0x100;
    one = 1;
    rect1.h = one;
    func_800672D8(&rect1, D_8012A998);

    func_8004068C(D_8012A998 + 0x200, D_8012E998);

    out = &rect0;
    pixels = D_8012E998;
    ASM_KEEP(out);
    ASM_KEEP(pixels);
    size = 0x80;
    ASM_KEEP(size);
    rect0.x = (FIELD(arg0, u8, 0x16) << 6) + 0x240;
    rect0.y = size;
    rect0.w = 0x40;
    rect0.h = size;
    func_800672D8(out, pixels, size);

    FIELD((u8 *)arg0 + FIELD(arg0, u8, 0x16), u8, 0x17) =
        FIELD(arg0, u8, 0x13);
    FIELD(arg0, u8, 0xA) = 6;
    FIELD(arg0, u8, 0xB) = 0;
    FIELD(arg0, s16, 4) = one;
    FIELD(arg0, s16, 6) = 0x19;
}

/* MECHANISM: Sibling 8-byte Rect locals force the 0x30 frame, while the true-space
   definition recovers the non-state-0/1 jump as the shared local epilogue. A saved
   one-value plus short a0/a1/a2 ABI pins close the final call setup at cdk-G0. */
