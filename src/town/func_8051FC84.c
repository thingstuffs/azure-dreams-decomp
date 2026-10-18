#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"


typedef struct S_8051FC84_1 {
    u8 pad_00[0x1];
    s8 unk_01;
} S_8051FC84_1;   /* ((D_80016000->unk_08 * 8) + ((s32)D_80016000->unk_40)) in func_8051FC84 */


s32 func_80018A64(s32);
extern void *D_800190E0;

/* Calls func_80018A64, sets the indexed entry's state to 2, and invokes the context callback. */
void func_8051FC84(void) {
    func_80018A64(0x5C8);
    ((S_8051FC84_1 *)(((D_80016000->unk_08 * 8)
        + ((s32)D_80016000->unk_40))))->unk_01 = 2;
    ((s32 (*)(s32 *))D_80016000->unk_20->callback_218)(&D_800190E0);
}
