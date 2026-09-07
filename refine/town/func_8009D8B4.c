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

/* Updates motion toward the target and advances the state when the countdown expires. */
void func_8009B014(void *state, void *motion, M2C_UNK context) {
    u16 ticks_left;
    s32 target_index;
    s32 *target_bases;
    s32 *target_base;

    target_index = D_800D0620;
    target_bases = D_800D0640;
    target_base = target_bases + target_index;
    ((S_8009B014_0 *)motion)->unk_10 = (s32) ((u32) (((S_8009B014_1 *)state)->unk_32 * 0x10000) + (u32) *target_base - (u32) ((S_8009B014_0 *)motion)->unk_04) / ((S_8009B014_1 *)state)->unk_0A.s;
    ticks_left = (u16) ((S_8009B014_1 *)state)->unk_0A.s - 1;
    ((S_8009B014_1 *)state)->unk_0A.u = ticks_left;
    if (((s16) ticks_left * 0x10000) <= 0) {
        ((S_8009B014_0 *)motion)->unk_04 = (s32) ((u32) (((S_8009B014_1 *)state)->unk_32 * 0x10000) + (u32) *target_base);
        func_80099754(motion);
        ((S_8009B014_1 *)state)->unk_10 = 0x400;
        ((S_8009B014_1 *)state)->unk_0A.u = 0xA;
        func_80094984(D_800D0078, state, context);
        ((S_8009B014_1 *)state)->unk_04 = D_8009AFF4;
    }
}
