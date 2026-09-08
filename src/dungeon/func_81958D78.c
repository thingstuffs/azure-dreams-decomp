#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80024578_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0x14];
    s32 unk_28;
} S_80024578_0;   /* object in func_80024578 */

typedef struct S_80024578_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024578_1;   /* part in func_80024578 */

typedef struct S_80024578_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024578_2;   /* arg0 in func_80024578 */

typedef struct S_80024578_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x10];
    s16 unk_1C;
    s16 unk_1E;
} S_80024578_3;   /* effect in func_80024578 */



extern void *func_8003FC64();
extern s32 func_800B835C();
extern u8 D_800243C4[9];
extern u8 D_80028208[9];
extern u8 D_800DF334[9];

/* Allocate and initialize an effect object from the supplied part data. */
void *func_80024578(S_80024578_2 *source_part, s32 offset_base) {
    s32 init_data[2];
    void *object;
    S_80024578_1 *part;
    S_80024578_3 *effect;
    void *result;

    object = func_8003FC64(0x12);
    if (object != NULL) {
        init_data[0] = 0x01000340;
        init_data[1] = 0x00200020;
        func_800B835C(D_800DF334, init_data, 1, 0);

        part = ((S_80024578_0 *)object)->unk_08;
        ((S_80024578_0 *)object)->unk_10 = D_800243C4;
        part->unk_02 = source_part->unk_02;
        part->unk_06 = source_part->unk_06;
        part->unk_0A = source_part->unk_0A;

        effect = ((S_80024578_0 *)object)->unk_0C;
        effect->unk_08 = D_80028208;
        effect->unk_1E = 0xC00;
        effect->unk_1C = 0xC00;
        ((S_80024578_0 *)object)->unk_28 = offset_base - 0x20;
    }

    result = NULL;
    if (object != NULL) {
        result = (u8 *)object + 0x20;
    }
    return result;
}
