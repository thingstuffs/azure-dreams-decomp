#include "common.h"
#include "m2c_compat.h"

typedef struct S_8072A398_1 {
    void * unk_00;
} S_8072A398_1;   /* D_80016000 in func_8072A398 */

typedef struct S_8072A398_2 {
    u8 pad_00[0x1C];
    void * unk_1C;
    void * unk_20;
} S_8072A398_2;   /* ((S_8072A398_1 *)D_80016000)->unk_00 in func_8072A398 */

typedef struct S_8072A398_3 {
    u8 pad_00[0x208];
    M2C_UNK (*unk_208)(M2C_UNK);
    u8 pad_20C[0x18];
    M2C_UNK (*unk_224)(s32 *);
    u8 pad_228[0x30];
    M2C_UNK (*unk_258)(M2C_UNK);
} S_8072A398_3;   /* ((S_8072A398_2 *)(((S_8072A398_1 *)D_80016000)->unk_00))->unk_20 in func_8072A398 */

typedef struct S_8072A398_4 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_8072A398_4;   /* ((S_8072A398_2 *)(((S_8072A398_1 *)D_80016000)->unk_00))->unk_1C in func_8072A398 */

typedef struct S_8072A398_5 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_8072A398_5;   /* (*(void **)((u8 *)(((S_8072A398_1 *)D_80016000)->unk_00) + 0x1C)) in func_8072A398 */




extern s8 D_80016000[];
extern s32 D_80017B78;

typedef struct S_8072A398_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_8072A398_0;   /* temp_a0 in func_8072A398 */

/* Configures the active object with two 16.16 coordinates and a zero third component. */
void func_8072A398(void) {
    s32 *fixed_coords;

    ((S_8072A398_3 *)(((S_8072A398_2 *)(((S_8072A398_1 *)D_80016000)->unk_00))->unk_20))->unk_258(0xC);
    D_80017B78 = ((S_8072A398_4 *)(((S_8072A398_2 *)(((S_8072A398_1 *)D_80016000)->unk_00))->unk_1C))->unk_04 << 0x10;
    fixed_coords = &D_80017B78;
    ((S_8072A398_0 *)fixed_coords)->unk_04 = (s32) (((S_8072A398_5 *)((*(void **)((u8 *)(((S_8072A398_1 *)D_80016000)->unk_00) + 0x1C))))->unk_08 << 0x10);
    ((S_8072A398_0 *)fixed_coords)->unk_08 = 0;
    ((S_8072A398_3 *)(((S_8072A398_2 *)(((S_8072A398_1 *)D_80016000)->unk_00))->unk_20))->unk_224(fixed_coords);
    ((S_8072A398_3 *)(((S_8072A398_2 *)(((S_8072A398_1 *)D_80016000)->unk_00))->unk_20))->unk_208(0);
}

/* MECHANISM: Declaring D_80016000 as a wide array holds its 0x80010000 page in s0,
   producing the 0x18 frame with only s0/ra saved and repeated 0x6000 page loads.
   Storing the shifted +4 field before zeroing +8 lets a0 become the record pointer in retail order. */
