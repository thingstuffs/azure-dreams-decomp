#include "common.h"





#ifndef NULL
#define NULL 0
#endif

typedef struct S_800A47A8_4 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_800A47A8_4;   /* temp_v0 in func_800A47A8 */

typedef struct S_800A47A8_5 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800A47A8_5;   /* ((S_800A47A8_4 *)temp_v0)->unk_0C in func_800A47A8 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void *func_8003FC64();
s32 func_8004491C();
extern s32 D_800A3918[];
extern s32 D_800A3B1C[];
extern s32 D_800D0C40[];
typedef struct {
    s16 value;
    u8 pad[10];
} LargeS16;
extern LargeS16 D_80100D88;
extern LargeS16 D_80100D8A;

typedef struct S_800A47A8_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_800A47A8_0;   /* temp_v0 in func_800A47A8 */

typedef struct S_800A47A8_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_800A47A8_1;   /* temp_v1 in func_800A47A8 */

typedef struct S_800A47A8_2 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_800A47A8_2;   /* temp_v1_2 in func_800A47A8 */

typedef struct S_800A47A8_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x8];
    s16 unk_0C;
    u8 pad_0E[0x4];
    s16 unk_12;
    s16 unk_14;
} S_800A47A8_3;   /* temp_v0_2 in func_800A47A8 */

void func_800A47A8(s16 arg0) {
    void *temp_v0;
    S_800A47A8_3 *temp_v0_2;
    S_800A47A8_1 *temp_v1;
    S_800A47A8_2 *temp_v1_2;
    s32 shifted;
    s32 *table;

    temp_v0 = func_8003FC64(0x12);
    if (temp_v0 != NULL) {
        ((S_800A47A8_0 *)temp_v0)->unk_10 = D_800A3918;
        func_8004491C(temp_v0, D_800A3B1C);
        shifted = arg0 << 0x10;
        table = D_800D0C40;
        ASM_USE(table);   /* MATCH pin: retail schedule: same instructions, different order without it */
        shifted >>= 0xE;
        ((S_800A47A8_5 *)(((S_800A47A8_4 *)temp_v0)->unk_0C))->unk_08 =
            *(s32 *)((s8 *)table + shifted);
        temp_v1 = ((S_800A47A8_0 *)temp_v0)->unk_0C;
        temp_v1->unk_0E = 0xE0;
        temp_v1->unk_0D = 0xE0;
        temp_v1->unk_0C = 0xE0;
        temp_v1_2 = ((S_800A47A8_0 *)temp_v0)->unk_0C;
        temp_v1_2->unk_1E = 0x1000;
        temp_v1_2->unk_1C = 0x1000;
        temp_v1 = ((S_800A47A8_0 *)temp_v0)->unk_08;
        D_80100D88.value = 0;
        temp_v1->unk_02 = 0;
        temp_v1 = ((S_800A47A8_0 *)temp_v0)->unk_08;
        D_80100D8A.value = 0;
        temp_v1->unk_06 = 0;
        temp_v1 = ((S_800A47A8_0 *)temp_v0)->unk_08;
        temp_v1->unk_0A = 0x4000;
        temp_v0_2 = temp_v0 + 0x20;
        temp_v0_2->unk_0C = arg0;
        temp_v0_2->unk_02 = 0;
        temp_v0_2->unk_12 = 0;
        temp_v0_2->unk_14 = 0x80;
    }
}
