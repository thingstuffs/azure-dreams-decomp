#include "common.h"



typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void *func_8003FC64();
void func_8004491C(void *, void *);
s32 func_8004DA74();
M2C_UNK func_800A6BBC();
M2C_UNK func_800B1320();
M2C_UNK func_800B135C();
M2C_UNK func_800B13CC();
M2C_UNK func_800B1400();
extern M2C_UNK D_80089074;
extern M2C_UNK D_800A6B70;
extern M2C_UNK D_800B06F0;

typedef struct S_800A6C00_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
    u8 pad_24[0x9C];
    s32 unk_C0;
    u8 pad_C4[0x2C];
    s32 unk_F0;
    s32 unk_F4;
} S_800A6C00_0;   /* temp_v0 in func_800A6C00 */

typedef struct S_800A6C00_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800A6C00_1;   /* temp_v1 in func_800A6C00 */

typedef struct S_800A6C00_2 {
    u8 pad_00[0x4];
    void * unk_04;
    s16 unk_08;
} S_800A6C00_2;   /* temp_s1 in func_800A6C00 */

typedef struct S_800A6C00_3 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_800A6C00_3;   /* temp_a2 in func_800A6C00 */

typedef struct S_800A6C00_4 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800A6C00_4;   /* temp_s0 in func_800A6C00 */

void *func_800A6C00(void) {
    S_800A6C00_3 *temp_a2;
    S_800A6C00_4 *temp_s0;
    S_800A6C00_2 *temp_s1;
    void *temp_v0;
    S_800A6C00_1 *temp_v1;

    temp_v0 = func_8003FC64(0x12);
    if (temp_v0 != 0) {
        temp_v1 = ((S_800A6C00_0 *)temp_v0)->unk_08;
        temp_a2 = ((S_800A6C00_0 *)temp_v0)->unk_0C;
        temp_s1 = temp_v0 + 0x20;
        temp_v1->unk_02 = 0x3C;
        temp_v1->unk_06 = 0x40;
        temp_s1->unk_08 = 1;
        temp_a2->unk_1E = 0x1800;
        temp_a2->unk_1C = 0x1800;
        ((S_800A6C00_0 *)temp_v0)->unk_10 = &D_800A6B70;
        func_8004491C(temp_v0, &D_800B06F0);
        temp_s0 = temp_v0 + 0x30;
        ((S_800A6C00_0 *)temp_v0)->unk_20 = (void *)(temp_v0 + 0xF0);
        temp_s1->unk_04 = (void *)(temp_v0 + 0xC0);
        ((S_800A6C00_0 *)temp_v0)->unk_F0 = func_8004DA74(temp_s0, &D_80089074, 0) & 0x7FFFFFFF;
        func_800B1320(temp_s0, 0xA8, (s16)((0 - (s8)temp_s0->unk_03) + 8));
        func_800A6BBC(temp_s0, 4);
        func_800B135C(temp_s0, 8);
        func_800B13CC(temp_s0, 0x20);
        func_800B1400(temp_s0, 2);
        ((S_800A6C00_0 *)temp_v0)->unk_C0 = 0x808080;
        ((S_800A6C00_0 *)temp_v0)->unk_F4 = 0;
    }
    return temp_v0;
}
