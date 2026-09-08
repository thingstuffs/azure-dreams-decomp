#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800CA75C(void *);                            /* extern */
extern u8 D_80083498[];


typedef struct S_800CA134_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_800CA134_0;   /* arg0 in func_800CA134 */

typedef struct S_800CA134_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    union { s16 n; volatile u16 v; } unk_0A;   /* accessed as both */
} S_800CA134_1;   /* arg1 in func_800CA134 */

typedef struct S_800CA134_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800CA134_2;   /* target in func_800CA134 */

typedef struct S_800CA134_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800CA134_3;   /* (*(void * volatile *)((u8 *)base + (8))) in func_800CA134 */

/* Decrement the lifetime and ease the position toward the target with a vertical offset. */
void func_800CA134(void *state, void *position) {
    u8 *target_table;
    s32 x_delta;
    s32 y_delta;
    u16 ticks_left;

    ticks_left = ((S_800CA134_0 *)state)->unk_6C - 1;
    ((S_800CA134_0 *)state)->unk_6C = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        func_800CA75C(state);
        return;
    }
    target_table = D_80083498;
    x_delta = ((S_800CA134_3 *)((*(void * volatile *)((u8 *)target_table + (8)))))->unk_02 - ((S_800CA134_1 *)position)->unk_02;
    if (x_delta < 0) {
        x_delta += 3;
    }
    (*(s16 *)((u8 *)position + (2))) = (s16) ((u16) ((S_800CA134_1 *)position)->unk_02 + (x_delta >> 2));
    y_delta = ((S_800CA134_3 *)((*(void * volatile *)((u8 *)target_table + (8)))))->unk_06 - ((S_800CA134_1 *)position)->unk_06;
    if (y_delta < 0) {
        y_delta += 3;
    }
    (*(s16 *)((u8 *)position + (6))) = (s16) ((u16) ((S_800CA134_1 *)position)->unk_06 + (y_delta >> 2));
    {
        void *target;
        register s32 z_step ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 target_z;
        register u32 z_value ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */

        target = (*(void * volatile *)((u8 *)target_table + (8)));
        z_step = ((S_800CA134_1 *)position)->unk_0A.n;
        target_z = ((S_800CA134_2 *)target)->unk_0A;
        z_step += 0xD0;
        z_step = target_z - z_step;
        ASM_KEEP(z_step);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        z_value = ((S_800CA134_1 *)position)->unk_0A.v;
        if (z_step < 0) {
            z_step += 3;
        }
        z_step = z_value + (z_step >> 2);
        ((S_800CA134_1 *)position)->unk_0A.n = (s16) z_step;
    }
}
