#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800244C4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0x14];
    s32 unk_28;
} S_800244C4_0;   /* object in func_800244C4 */

typedef struct S_800244C4_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800244C4_1;   /* part in func_800244C4 */

typedef struct S_800244C4_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800244C4_2;   /* arg0 in func_800244C4 */

typedef struct S_800244C4_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x10];
    s16 unk_1C;
    s16 unk_1E;
} S_800244C4_3;   /* effect in func_800244C4 */


extern void *func_8003FC64();
extern void func_800B835C();
extern void func_80024328(void *, void *, void *);
extern u8 D_80027460[9];
extern u8 D_8002746C[9];

/* Allocate and initialize an effect object from the supplied part data. */
void *func_800244C4(S_800244C4_2 *source_part, s32 offset_base) {
    s32 init_data[2];
    void *object;
    S_800244C4_1 *part;
    S_800244C4_3 *effect;
    void *result;

    object = func_8003FC64(0x12);
    if (object != NULL) {
        init_data[0] = 0x01000340;
        init_data[1] = 0x00200020;
        func_800B835C(D_8002746C, init_data, 1, 0);

        part = ((S_800244C4_0 *)object)->unk_08;
        ((S_800244C4_0 *)object)->unk_10 = func_80024328;
        part->unk_02 = source_part->unk_02;
        part->unk_06 = source_part->unk_06;
        part->unk_0A = source_part->unk_0A;

        effect = ((S_800244C4_0 *)object)->unk_0C;
        effect->unk_08 = D_80027460;
        effect->unk_1E = 0xC00;
        effect->unk_1C = 0xC00;
        ((S_800244C4_0 *)object)->unk_28 = offset_base - 0x20;
    }

    result = NULL;
    if (object != NULL) {
        result = (u8 *)object + 0x20;
    }
    return result;
}
