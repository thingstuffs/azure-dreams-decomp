#include "common.h"

typedef struct S_80016F40_0 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_80016F40_0;   /* D_80016000 in func_80016F40 */

typedef struct S_80016F40_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_80016F40_1;   /* ((S_80016F40_0 *)D_80016000)->unk_1C in func_80016F40 */




#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern S_80016F40_0 *D_80016000;


void func_80016F40(void) {
    ((S_80016F40_1 *)(D_80016000->unk_1C))->unk_04 = 0x560;
    ((S_80016F40_1 *)(D_80016000->unk_1C))->unk_08 = 0x3E0;
}
