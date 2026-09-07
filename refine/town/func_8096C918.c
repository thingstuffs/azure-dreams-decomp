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

/* Load a texture and its palette, then advance the loader after upload. */
void func_80124DB0(void *loader)
{
    Rect texture_rect;
    Rect palette_rect;
    Rect *upload_rect;
    u8 *texture_pixels;
    s32 texture_height;
    s32 palette_rows;
    u8 load_state;

    load_state = ((S_80124DB0_0 *)loader)->unk_0B;
    if (load_state != 0) {
        if (load_state != 1) {
            return;
        }
        goto active;
    }

    func_8003F6D4(8, D_8012A998, D_80133198,
                  D_80126D44[((S_80124DB0_0 *)loader)->unk_13][1]);
    func_8003E4FC(6, D_80133198, 0);
    ((S_80124DB0_0 *)loader)->unk_0D = 0;
    func_8003E4FC(0xFF, D_8003E140, (u8 *)loader + 0xD);
    ((S_80124DB0_0 *)loader)->unk_0B++;

active:
    if (((S_80124DB0_0 *)loader)->unk_0D == 0) {
        return;
    }

    palette_rect.x = 0;
    palette_rect.y = ((S_80124DB0_0 *)loader)->unk_16 + 0x1CA;
    palette_rect.w = 0x100;
    palette_rows = 1;
    palette_rect.h = palette_rows;
    func_800672D8(&palette_rect, D_8012A998);

    func_8004068C(D_8012A998 + 0x200, D_8012E998);

    upload_rect = &texture_rect;
    texture_pixels = D_8012E998;
    ASM_KEEP(texture_pixels);   /* MATCH pin: retail schedule: same instructions, different order without it */
    texture_height = 0x80;
    ASM_KEEP(texture_height);   /* MATCH pin: load-bearing for the whole function shape */
    texture_rect.x = (((S_80124DB0_0 *)loader)->unk_16 << 6) + 0x240;
    texture_rect.y = texture_height;
    texture_rect.w = 0x40;
    texture_rect.h = texture_height;
    func_800672D8(upload_rect, texture_pixels, texture_height);

    ((S_80124DB0_1 *)((u8 *)loader + ((S_80124DB0_0 *)loader)->unk_16))->unk_17 =
        ((S_80124DB0_0 *)loader)->unk_13;
    ((S_80124DB0_0 *)loader)->unk_0A = 6;
    ((S_80124DB0_0 *)loader)->unk_0B = 0;
    ((S_80124DB0_0 *)loader)->unk_04 = palette_rows;
    ((S_80124DB0_0 *)loader)->unk_06 = 0x19;
}

/* MECHANISM: Sibling 8-byte Rect locals force the 0x30 frame, while the true-space
   definition recovers the non-state-0/1 jump as the shared local epilogue. A saved
   one-value plus short a0/a1/a2 ABI pins close the final call setup at cdk-G0. */
