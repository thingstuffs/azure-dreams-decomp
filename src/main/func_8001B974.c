#include "common.h"

typedef struct S_8001B974_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8001B974_3;   /* arg0 in func_8001B974 */

typedef struct S_8001B974_4 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x1];
    s8 unk_0F;
} S_8001B974_4;   /* ((S_8001B974_3 *)arg0)->unk_04 in func_8001B974 */




#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 D_8002D690[];
extern s32 D_8002D694[];
extern s32 D_8002D698[];
extern s32 D_8002D69C[];
extern s32 D_8002D6A0[];
extern s32 D_8002D6A4[];
extern s32 D_8002D6A8[];

typedef struct S_8001B974_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_8001B974_0;   /* arg1 in func_8001B974 */

typedef struct S_8001B974_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8001B974_1;   /* arg2 in func_8001B974 */

typedef struct S_8001B974_2 {
    s32 unk_00;
    void * unk_04;
    void * unk_08;
} S_8001B974_2;   /* arg0 in func_8001B974 */

void func_8001B974(S_8001B974_2 *arg0, S_8001B974_0 *arg1, S_8001B974_1 *arg2) {
    s32 t;
    arg1->unk_00 = D_8002D690[0];
    t = D_8002D6A0[0];
    arg1->unk_04 = D_8002D694[0];
    arg1->unk_08 = D_8002D698[0];
    arg1->unk_0C = D_8002D69C[0];
    arg2->unk_00 = t;
    arg2->unk_04 = D_8002D6A4[0];
    arg2->unk_08 = D_8002D6A8[0];
    arg0->unk_04 = arg1;
    arg0->unk_08 = arg2;
    arg0->unk_00 = 0;
    ((S_8001B974_4 *)(((S_8001B974_3 *)arg0)->unk_04))->unk_08 = -0xA0;
    ((S_8001B974_4 *)(((S_8001B974_3 *)arg0)->unk_04))->unk_0A = -0x48;
    ((S_8001B974_4 *)(((S_8001B974_3 *)arg0)->unk_04))->unk_0C = 0x200;
    ((S_8001B974_4 *)(((S_8001B974_3 *)arg0)->unk_04))->unk_0F = 4;
}
