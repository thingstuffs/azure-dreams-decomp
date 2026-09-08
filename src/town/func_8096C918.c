#include "common.h"

typedef struct S_80124DB0_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x2];
    u8 unk_0A;
    u8 unk_0B;
    u8 pad_0C[0x1];
    u8 unk_0D;
    u8 pad_0E[0x5];
    u8 unk_13;
    u8 pad_14[0x2];
    u8 unk_16;
} S_80124DB0_0;   /* arg0 in func_80124DB0 */

typedef struct S_80124DB0_1 {
    u8 pad_00[0x17];
    u8 unk_17;
} S_80124DB0_1;   /* (u8 *)arg0 + ((S_80124DB0_0 *)arg0)->unk_16 in func_80124DB0 */



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
    Rect *out;
    u8 *pixels;
    s32 size;
    s32 one;
    u8 state;

    state = ((S_80124DB0_0 *)arg0)->unk_0B;
    if (state != 0) {
        if (state != 1) {
            return;
        }
        goto active;
    }

    func_8003F6D4(8, D_8012A998, D_80133198,
                  D_80126D44[((S_80124DB0_0 *)arg0)->unk_13][1]);
    func_8003E4FC(6, D_80133198, 0);
    ((S_80124DB0_0 *)arg0)->unk_0D = 0;
    func_8003E4FC(0xFF, D_8003E140, (u8 *)arg0 + 0xD);
    ((S_80124DB0_0 *)arg0)->unk_0B++;

active:
    if (((S_80124DB0_0 *)arg0)->unk_0D == 0) {
        return;
    }

    rect1.x = 0;
    rect1.y = ((S_80124DB0_0 *)arg0)->unk_16 + 0x1CA;
    rect1.w = 0x100;
    one = 1;
    rect1.h = one;
    func_800672D8(&rect1, D_8012A998);

    func_8004068C(D_8012A998 + 0x200, D_8012E998);

    out = &rect0;
    pixels = D_8012E998;
    ASM_KEEP(pixels);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    size = 0x80;
    ASM_KEEP(size);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    rect0.x = (((S_80124DB0_0 *)arg0)->unk_16 << 6) + 0x240;
    rect0.y = size;
    rect0.w = 0x40;
    rect0.h = size;
    func_800672D8(out, pixels, size);

    ((S_80124DB0_1 *)((u8 *)arg0 + ((S_80124DB0_0 *)arg0)->unk_16))->unk_17 =
        ((S_80124DB0_0 *)arg0)->unk_13;
    ((S_80124DB0_0 *)arg0)->unk_0A = 6;
    ((S_80124DB0_0 *)arg0)->unk_0B = 0;
    ((S_80124DB0_0 *)arg0)->unk_04 = one;
    ((S_80124DB0_0 *)arg0)->unk_06 = 0x19;
}

/* MECHANISM: Sibling 8-byte Rect locals force the 0x30 frame, while the true-space
   definition recovers the non-state-0/1 jump as the shared local epilogue. A saved
   one-value plus short a0/a1/a2 ABI pins close the final call setup at cdk-G0. */
