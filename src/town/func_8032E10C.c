#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001890C_0 {
    void * unk_00;
} S_8001890C_0;   /* D_80016000 in func_8001890C */

typedef struct S_8001890C_1 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0x1C];
    void * unk_40;
} S_8001890C_1;   /* ((S_8001890C_0 *)D_80016000)->unk_00 in func_8001890C */

typedef struct S_8001890C_2 {
    u8 pad_00[0x110];
    u32 unk_110;
} S_8001890C_2;   /* ((S_8001890C_1 *)(((S_8001890C_0 *)D_80016000)->unk_00))->unk_40 in func_8001890C */

typedef struct S_8001890C_3 {
    u8 pad_00[0x50];
    u32 (*unk_50)(s8 *);
} S_8001890C_3;   /* ((S_8001890C_1 *)(((S_8001890C_0 *)D_80016000)->unk_00))->unk_20 in func_8001890C */




extern u8 D_80016000[0x10];


s32 func_8001890C(void) {
    s8 sp10[2];

    sp10[1] = 0x17;
    sp10[0] = 5;
    return (s32) ((S_8001890C_2 *)(((S_8001890C_1 *)(((S_8001890C_0 *)D_80016000)->unk_00))->unk_40))->unk_110 >= ((S_8001890C_3 *)(((S_8001890C_1 *)(((S_8001890C_0 *)D_80016000)->unk_00))->unk_20))->unk_50(sp10);
}
