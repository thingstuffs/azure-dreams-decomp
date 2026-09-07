#include "common.h"

typedef struct S_8001640C_0 {
    void * unk_00;
} S_8001640C_0;   /* page in func_8001640C */

typedef struct S_8001640C_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x34];
    s32 unk_40;
} S_8001640C_1;   /* ((S_8001640C_0 *)page)->unk_00 in func_8001640C */

typedef struct S_8001640C_2 {
    u8 pad_00[0x4];
    u8 unk_04;
} S_8001640C_2;   /* (((S_8001640C_1 *)(((S_8001640C_0 *)page)->unk_00))->unk_08 * 8) +
            ((S_8001640C_1 *)(((S_8001640C_0 *)page)->unk_00))->unk_40 in func_8001640C */

typedef struct S_8001640C_3 {
    u8 pad_00[0x4];
    s8 unk_04;
} S_8001640C_3;   /* (((S_8001640C_1 *)(((S_8001640C_0 *)page)->unk_00))->unk_08 * 8) +
                ((S_8001640C_1 *)(((S_8001640C_0 *)page)->unk_00))->unk_40 in func_8001640C */



extern s8 D_80016000[];
extern s32 D_80019AFC;

s32 func_80018618(void);

s32 func_8001640C(void) {
    void **page;
    s32 result;

    page = (void **)D_80016000;
    D_80019AFC = ((S_8001640C_2 *)((((S_8001640C_1 *)(((S_8001640C_0 *)page)->unk_00))->unk_08 * 8) +
            ((S_8001640C_1 *)(((S_8001640C_0 *)page)->unk_00))->unk_40))->unk_04;
    result = func_80018618();
    if (result != 0) {
        ((S_8001640C_3 *)((((S_8001640C_1 *)(((S_8001640C_0 *)page)->unk_00))->unk_08 * 8) +
                ((S_8001640C_1 *)(((S_8001640C_0 *)page)->unk_00))->unk_40))->unk_04 = 0;
    }
    return result;
}

/* MECHANISM: A pointer to the D_80016000 pointer slot stays live in s0 across
   the call, giving the bare page lui and 0x6000 loads with no asm barrier;
   direct nested field expressions retain region-specific coloring. */
