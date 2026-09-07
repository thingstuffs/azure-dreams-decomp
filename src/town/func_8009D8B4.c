#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_8009B014_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_8009B014_0;   /* arg1 in func_8009B014 */

typedef struct S_8009B014_1 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
    u8 pad_08[0x2];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x20];
    s16 unk_32;
} S_8009B014_1;   /* arg0 in func_8009B014 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80094984(void *arg0, void *arg1, s32 arg2);
extern void func_80099754(void *arg0);
extern M2C_UNK D_8009AFF4[3];
extern M2C_UNK D_800D0078[3];
extern s32 D_800D0620;
extern M2C_UNK D_800D0640[3];

void func_8009B014(void *arg0, void *arg1, M2C_UNK arg2) {
    u16 temp_v0;
    s32 temp_index;
    s32 *temp_base;
    s32 *temp_a2;

    temp_index = D_800D0620;
    temp_base = D_800D0640;
    temp_a2 = temp_base + temp_index;
    ((S_8009B014_0 *)arg1)->unk_10 = (s32) ((u32) (((S_8009B014_1 *)arg0)->unk_32 * 0x10000) + (u32) *temp_a2 - (u32) ((S_8009B014_0 *)arg1)->unk_04) / ((S_8009B014_1 *)arg0)->unk_0A.s;
    temp_v0 = (u16) ((S_8009B014_1 *)arg0)->unk_0A.s - 1;
    ((S_8009B014_1 *)arg0)->unk_0A.u = temp_v0;
    if (((s16) temp_v0 * 0x10000) <= 0) {
        ((S_8009B014_0 *)arg1)->unk_04 = (s32) ((u32) (((S_8009B014_1 *)arg0)->unk_32 * 0x10000) + (u32) *temp_a2);
        func_80099754(arg1);
        ((S_8009B014_1 *)arg0)->unk_10 = 0x400;
        ((S_8009B014_1 *)arg0)->unk_0A.u = 0xA;
        func_80094984(D_800D0078, arg0, arg2);
        ((S_8009B014_1 *)arg0)->unk_04 = D_8009AFF4;
    }
}
