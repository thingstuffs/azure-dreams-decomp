#include "common.h"
#include "m2c_compat.h"

typedef struct S_800AE630_2 {
    u8 pad_00[0xD0];
    void * unk_D0;
} S_800AE630_2;   /* obj in func_800AE630 */

typedef struct S_800AE630_3 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_800AE630_3;   /* ((S_800AE630_2 *)obj)->unk_D0 in func_800AE630 */




typedef struct S_800AE630_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
    M2C_UNK (*unk_10)(void);
    u8 pad_14[0x8];
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u8 pad_22[0x2];
    s16 unk_24;
    s16 unk_26;
    s16 unk_28;
    u8 pad_2A[0xA];
    s32 unk_34;
    u8 pad_38[0xA4];
    void * unk_DC;
} S_800AE630_0;   /* obj in func_800AE630; pointer addresses record offset 0x10 */

typedef struct S_800AE630_1 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
} S_800AE630_1;   /* temp_a1 in func_800AE630 */


extern M2C_UNK D_800AE600;

/* Advance the object position and transition step, then invoke its callback. */
void func_800AE630(void *object) {
    register M2C_UNK (*callback)(void) ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 next_step;
    s32 scaled_x;
    s32 scaled_y;
    s32 scaled_z;
    S_800AE630_1 *position;
    void *obj;

    obj = object;
    ASM_KEEP(obj);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    position = ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_DC;
    scaled_x = ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_24 * ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_34;
    if (scaled_x < 0) {
        scaled_x += 3;
    }
    position->unk_08 = (s16) (((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_1C + (scaled_x >> 2));
    position = ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_DC;
    scaled_y = ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_26 * ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_34;
    if (scaled_y < 0) {
        scaled_y += 3;
    }
    position->unk_0A = (s16) (((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_1E + (scaled_y >> 2));
    position = ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_DC;
    scaled_z = ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_28 * ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_34;
    if (scaled_z < 0) {
        scaled_z += 3;
    }
    position->unk_0C = (s16) (((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_20 + (scaled_z >> 2));
    ((S_800AE630_3 *)(((S_800AE630_2 *)obj)->unk_D0))->unk_02 = (s16) ((((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_34 << 8) - 0x400);
    next_step = ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_34 + 1;
    ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_34 = next_step;
    if (next_step >= 5) {
        register u8 *page;

        page = (u8 *)0x800B0000;
        ASM_KEEP_NV(page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_00 = (M2C_UNK *)(page - 0x1A00);
    }
    callback = ((S_800AE630_0 *)((u8 *)obj - 0x10))->unk_10;
    if (callback != NULL) {
        callback();
    }
}

/* MECHANISM: The true-space function keeps the runtime object in $a0 and reloads
   a block-lived destination pointer before each multiply to occupy the latency slot.
   A kept page/offset split fills the conditional delay slot; the callback stays in $v0. */
