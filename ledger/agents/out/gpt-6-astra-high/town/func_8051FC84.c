#include "common.h"

typedef struct S_8051FC84_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x34];
    s32 unk_40;
} S_8051FC84_0;   /* D_80016000 in func_8051FC84 */


typedef s32 M2C_UNK;

typedef struct S_8051FC84_1 {
    u8 pad_00[0x1];
    s8 unk_01;
} S_8051FC84_1;   /* ((D_80016000->unk_08 * 8) + D_80016000->unk_40) in func_8051FC84 */

typedef struct S_8051FC84_2 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8051FC84_2;   /* D_80016000 in func_8051FC84 */

typedef struct S_8051FC84_3 {
    u8 pad_00[0x218];
    void * unk_218;
} S_8051FC84_3;   /* ((S_8051FC84_2 *)D_80016000)->unk_20 in func_8051FC84 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80018A64();
extern S_8051FC84_0 *D_80016000;
extern void *D_800190E0;

/* Calls func_80018A64, sets the indexed entry's state to 2, and invokes the context callback. */
void func_8051FC84(void) {
    func_80018A64(0x5C8);
    ((S_8051FC84_1 *)(((D_80016000->unk_08 * 8) + D_80016000->unk_40)))->unk_01 = 2;
    (*(M2C_UNK (*)(M2C_UNK *))((u8 *)(((S_8051FC84_3 *)(((S_8051FC84_2 *)D_80016000)->unk_20))->unk_218) + 0))(&D_800190E0);
}
