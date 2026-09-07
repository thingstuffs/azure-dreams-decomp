#include "common.h"



#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct Copy24 {
    s32 words[6];
} Copy24;

extern s32 func_8003DB94();
extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 D_8002420C;
extern s32 D_80045340;
extern s32 D_800E2178;

typedef struct S_81892AF0_0 {
    u8 pad_00[0x8];
    Copy24 * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_81892AF0_0;   /* temp_v0 in func_81892AF0 */

typedef struct S_81892AF0_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
} S_81892AF0_1;   /* temp_v0_2 in func_81892AF0 */

typedef struct S_81892AF0_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_81892AF0_2;   /* temp_s0 in func_81892AF0 */

typedef struct S_81892AF0_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_81892AF0_3;   /* temp_a1 in func_81892AF0 */

void *func_81892AF0(s32 arg0, Copy24 *arg1, s16 arg2) {
    Copy24 *temp_a1;
    S_81892AF0_2 *temp_s0;
    void *temp_v0;
    S_81892AF0_1 *temp_v0_2;
    register void *var_v0 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    temp_v0 = func_8003FC64(0x212);
    var_v0 = NULL;
    if (temp_v0 != NULL) {
        ((S_81892AF0_0 *)temp_v0)->unk_10 = &D_8002420C;
        temp_v0_2 = temp_v0 + 0x20;
        ((S_81892AF0_0 *)temp_v0)->unk_20 = arg0;
        temp_v0_2->unk_04 = 0;
        temp_v0_2->unk_06 = arg2;
        temp_s0 = ((S_81892AF0_0 *)temp_v0)->unk_0C;
        temp_s0->unk_0E = 0x80;
        temp_s0->unk_0D = 0x80;
        temp_s0->unk_0C = 0x80;
        func_8003DB94(temp_s0, &D_800E2178, 0);
        temp_s0->unk_1E = 0x1800;
        temp_s0->unk_1C = 0x1800;
        func_8004491C(temp_v0, &D_80045340);
        temp_a1 = ((S_81892AF0_0 *)temp_v0)->unk_08;
        var_v0 = temp_v0;
        *temp_a1 = *arg1;
        ((S_81892AF0_3 *)temp_a1)->unk_14 = 0x10000;
        ((S_81892AF0_3 *)temp_a1)->unk_08 += 0xFD010000;
    }
    return var_v0;
}
