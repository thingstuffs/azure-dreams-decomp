#include "common.h"
#include "m2c_compat.h"

typedef struct S_8181B1A0_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8181B1A0_4;   /* arg0 in func_8181B1A0 */

typedef struct S_8181B1A0_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8181B1A0_5;   /* ((S_8181B1A0_4 *)arg0)->unk_08 in func_8181B1A0 */




void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_80024878;
extern M2C_UNK D_80025908[];
extern M2C_UNK D_80045340;

typedef struct S_8181B1A0_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x5C];
    s32 unk_60;
} S_8181B1A0_0;   /* temp_s0 in func_8181B1A0 */

typedef struct S_8181B1A0_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_8181B1A0_1;   /* temp_v0 in func_8181B1A0 */

typedef struct S_8181B1A0_2 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8181B1A0_2;   /* temp_a3 in func_8181B1A0 */

typedef struct S_8181B1A0_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8181B1A0_3;   /* temp_v1 in func_8181B1A0 */

/* Creates an effect at an offset from the source and initializes its state and appearance. */
void func_8181B1A0(void *source, s32 offset_x, s32 offset_y, s32 offset_z, s32 effect_value) {
    s32 saved_value = effect_value;
    S_8181B1A0_2 *render;
    S_8181B1A0_0 *state;
    void *effect;
    S_8181B1A0_3 *position;

    effect = func_8003FC64(0x212);
    do {
        state = effect + 0x20;
    } while (0);
    if (effect != NULL) {
        state->unk_02 = (s16) saved_value;
        state->unk_60 = (s32) ((rand() & 0x1FFFF) + 0x10000);
        ((S_8181B1A0_1 *)effect)->unk_10 = &D_80024878;
        func_8004491C(effect, &D_80045340);
        render = ((S_8181B1A0_1 *)effect)->unk_0C;
        render->unk_14 = (u16) (render->unk_14 | 0xC);
        position = ((S_8181B1A0_1 *)effect)->unk_08;
        position->unk_02 = (s16) (((S_8181B1A0_5 *)(((S_8181B1A0_4 *)source)->unk_08))->unk_02 + offset_x);
        position->unk_06 = (s16) (((S_8181B1A0_5 *)(((S_8181B1A0_4 *)source)->unk_08))->unk_06 + offset_y);
        position->unk_0A = (s16) (((S_8181B1A0_5 *)(((S_8181B1A0_4 *)source)->unk_08))->unk_0A + offset_z);
        render = ((S_8181B1A0_1 *)effect)->unk_0C;
        render->unk_1E = 0x1000;
        render->unk_1C = 0x1000;
        render->unk_0E = 0x80;
        render->unk_0D = 0x80;
        render->unk_0C = 0x80;
        memcpy((u8 *) effect + 0x40, &D_80025908, 12);
        render->unk_08 = (void *) (effect + 0x40);
    }
}

/* MECHANISM: The 48-byte frame holds arg0-arg3 in s3-s6, stack arg4 in pinned s2,
   the allocation result in s1, and a pinned +0x20 base in s0 with an entry-block fence.
   One pinned a3 name spans the two record-pointer live ranges; u8 fields preserve li 0x80.
   Fixed-size memcpy plus 2.7.2-cdk-G0 selects retail's 12-byte unaligned-copy temp colors. */
