#include "common.h"



#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

typedef struct S_800B0544_4 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800B0544_4;   /* obj in func_800B0544 */

typedef struct S_800B0544_5 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
} S_800B0544_5;   /* ((S_800B0544_4 *)obj)->unk_0C in func_800B0544 */

typedef struct S_800B0544_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800B0544_6;   /* ((S_800B0544_4 *)obj)->unk_08 in func_800B0544 */

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8003E1C4();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();

extern s32 D_80012090[];
extern s16 D_8008146C;
extern M2C_UNK D_800AFAD8;
extern M2C_UNK D_800AFBFC;
extern s8 D_800DCF4C;
extern M2C_UNK D_800DEF90;

typedef struct S_800B0544_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800B0544_0;   /* obj in func_800B0544 */

typedef struct S_800B0544_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_800B0544_1;   /* temp_v1 in func_800B0544 */

typedef struct S_800B0544_2 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_800B0544_2;   /* temp_v1_2 in func_800B0544 */

typedef struct S_800B0544_3 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_800B0544_3;   /* temp_a0 in func_800B0544 */

void func_800B0544(s16 arg0) {
    s8 *state;
    s32 mode;
    S_800B0544_3 *temp_a0;
    S_800B0544_1 *temp_v1;
    S_800B0544_2 *temp_v1_2;
    void *obj;

    state = &D_800DCF4C;
    if (*state != arg0) {
        func_8003E1C4(arg0);
        *state = (s8)arg0;
    }
    obj = func_8003FC64(0x12);
    if (obj != NULL) {
        ((S_800B0544_0 *)obj)->unk_10 = &D_800AFAD8;
        func_8004491C(obj, &D_800AFBFC);
        ((S_800B0544_5 *)(((S_800B0544_4 *)obj)->unk_0C))->unk_08 = &D_800DEF90;
        temp_v1 = ((S_800B0544_0 *)obj)->unk_0C;
        temp_v1->unk_0E = 0xE0;
        temp_v1->unk_0D = 0xE0;
        temp_v1->unk_0C = 0xE0;
        temp_v1_2 = ((S_800B0544_0 *)obj)->unk_0C;
        temp_v1_2->unk_1E = 0x1000;
        temp_v1_2->unk_1C = 0x1000;
        ((S_800B0544_6 *)(((S_800B0544_4 *)obj)->unk_08))->unk_02 = 0;
        ((S_800B0544_6 *)(((S_800B0544_4 *)obj)->unk_08))->unk_06 = 0;
        ((S_800B0544_6 *)(((S_800B0544_4 *)obj)->unk_08))->unk_0A = 0x4000;
        mode = *(s32 *)0x80012090;
        temp_a0 = obj + 0x20;
        if (mode == 0) {
            if (D_8008146C == 0x28) {
                temp_a0->unk_02 = 1;
                return;
            }
        } else if (mode == 2) {
            temp_a0->unk_02 = (s16)mode;
        }
    }
}

/* MECHANISM: A void CFG plus split object/mode live ranges removes seven return-merge words.
   Unsigned byte fields preserve li 0xE0; the raw mode read gives maspsx base==dest v1.
   The held state page in s1 and object in s0 produce the exact 0x20 frame/save contract. */
