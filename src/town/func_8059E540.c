/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;

#ifndef NULL
#define NULL 0
#endif

typedef u32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

typedef struct S_8059E540_2 {
    u8 pad_00[0x6000];
    void * unk_6000;
} S_8059E540_2;   /* page in func_8059E540 */

typedef struct S_8059E540_3 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_8059E540_3;   /* state in func_8059E540 */

typedef struct S_8059E540_4 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8059E540_4;   /* ((S_8059E540_2 *)page)->unk_6000 in func_8059E540 */

typedef struct S_8059E540_5 {
    u8 pad_00[0x40];
    M2C_UNK * unk_40;
} S_8059E540_5;   /* ((S_8059E540_3 *)state)->unk_1C in func_8059E540 */

typedef struct S_8059E540_6 {
    u8 pad_00[0x27C];
    M2C_UNK (*unk_27C)(M2C_UNK);
    u8 pad_280[0x74];
    M2C_UNK (*unk_2F4)(M2C_UNK, M2C_UNK);
} S_8059E540_6;   /* ((S_8059E540_4 *)(((S_8059E540_2 *)page)->unk_6000))->unk_20 in func_8059E540 */

M2C_UNK func_800168E0();
s32 func_80018964();
extern u8 D_80010000[];
extern M2C_UNK D_80018EE4;
extern M2C_UNK D_80019148[3];
extern M2C_UNK D_8001D07C;

typedef struct S_8059E540_0 {
    u8 pad_00[0x6000];
    void * unk_6000;
} S_8059E540_0;   /* page in func_8059E540 */

typedef struct S_8059E540_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x34];
    s8 * unk_40;
} S_8059E540_1;   /* state in func_8059E540 */

void func_8059E540(void) {
    M2C_UNK *temp_v1;
    M2C_UNK *new_value;
    S_8059E540_1 *state;

    if (func_80018964(0x11FC) == 0) {
        u8 *page = (u8 *)0x80010000;
        ((S_8059E540_6 *)(((S_8059E540_4 *)(((S_8059E540_2 *)page)->unk_6000))->unk_20))->unk_27C(0);
        ((S_8059E540_6 *)(((S_8059E540_4 *)(((S_8059E540_2 *)page)->unk_6000))->unk_20))->unk_2F4(-1, -5);
    }
    func_800168E0();
    state = ((S_8059E540_0 *)D_80010000)->unk_6000;
    new_value = (M2C_UNK *)&D_80010000[0xD07C];
    ((S_8059E540_5 *)(((S_8059E540_3 *)state)->unk_1C))->unk_40 = new_value;
    temp_v1 = *(M2C_UNK **)((s8 *)state->unk_40 + (state->unk_08 * 8));
    if (temp_v1 != NULL) {
        ((S_8059E540_5 *)(((S_8059E540_3 *)state)->unk_1C))->unk_40 = temp_v1;
        *(M2C_UNK **)((s8 *)state->unk_40 + (state->unk_08 * 8)) = 0;
    }
    *(M2C_UNK **)&D_80019148[0] = &D_80018EE4;
}
