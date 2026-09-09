#include "common.h"

typedef struct S_801254D8_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x2];
    s8 unk_0A;
    u8 unk_0B;
    u8 pad_0C[0x1];
    u8 unk_0D;
    u8 pad_0E[0x5];
    u8 unk_13;
    u8 unk_14;
    u8 pad_15[0x1];
    u8 unk_16;
} S_801254D8_0;   /* arg0 in func_801254D8 */

typedef struct S_801254D8_1 {
    u8 pad_00[0x17];
    u8 unk_17;
} S_801254D8_1;   /* (u8 *)arg0 + ((S_801254D8_0 *)arg0)->unk_16 in func_801254D8 */


typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect;

extern s32 Control_CD();
extern s32 func_8003F6D4();
extern s32 func_8004068C();
extern s32 func_800672D8();

extern s32 D_8003E140[];
extern s32 *D_80126D44[];
extern u8 D_8012A998[];
extern u8 D_8012E998[];
extern u8 D_80133198[];


/* Loads an image and palette into VRAM, then updates the loading state. */
void func_801254D8(void *context) {
    Rect image_rect;
    Rect palette_rect;
    u8 load_phase;

    load_phase = ((S_801254D8_0 *)context)->unk_0B;
    if (load_phase != 0) {
        if (load_phase != 1) {
            return;
        }
        goto state_ready;
    }

    func_8003F6D4(8, D_8012A998, D_80133198,
                  D_80126D44[((S_801254D8_0 *)context)->unk_13][1]);
    Control_CD(6, D_80133198, 0);
    ((S_801254D8_0 *)context)->unk_0D = 0;
    Control_CD(0xFF, D_8003E140, (u8 *)context + 0xD);
    ((S_801254D8_0 *)context)->unk_0B++;

state_ready:
    if (((S_801254D8_0 *)context)->unk_0D == 0) {
        return;
    }

    palette_rect.x = 0;
    palette_rect.y = ((S_801254D8_0 *)context)->unk_16 + 0x1CA;
    palette_rect.w = 0x100;
    palette_rect.h = 1;
    func_800672D8(&palette_rect, D_8012A998);

    func_8004068C(D_8012A998 + 0x200, D_8012E998);

    image_rect.x = (((S_801254D8_0 *)context)->unk_16 << 6) + 0x240;
    image_rect.y = 0x80;
    image_rect.w = 0x40;
    image_rect.h = 0x80;
    func_800672D8(&image_rect, D_8012E998);

    ((S_801254D8_1 *)((u8 *)context + ((S_801254D8_0 *)context)->unk_16))->unk_17 =
        ((S_801254D8_0 *)context)->unk_13;

    {
        u32 state_value = ((S_801254D8_0 *)context)->unk_13;
        register u32 index_limit ASM_REG("$3") = ((S_801254D8_0 *)context)->unk_14;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        state_value = state_value < index_limit;
        if (state_value == 0) {
            state_value = 0xB;
        } else {
            state_value = 0xA;
        }
        ((S_801254D8_0 *)context)->unk_0A = state_value;
        state_value = 1;
        ((S_801254D8_0 *)context)->unk_04 = state_value;
    }
    ((S_801254D8_0 *)context)->unk_0B = 0;
    ((S_801254D8_0 *)context)->unk_06 = 0x19;
}
