#include "common.h"

typedef struct S_808B2F58_0 {
    u8 pad_00[0x8];
    s32 * unk_08;
} S_808B2F58_0;   /* *(void **)0xA0700F5C in func_808B2F58 */

typedef struct S_808B2F58_1 {
    u8 pad_00[0xE];
    u8 unk_0E;
} S_808B2F58_1;   /* temp_v1 in func_808B2F58 */



extern s32 func_8070021C();
extern s32 func_807002A4();
extern s32 func_807002D4();
extern void func_807007D0(void) __attribute__((noreturn));
extern s32 func_8070090C();

s32 func_808B2F58(s32 arg0)
{
    S_808B2F58_1 *temp_v1;

    if ((func_8070021C(1) != 0) &&
        (*((S_808B2F58_0 *)(*(void **)0xA0700F5C))->unk_08 > 0)) {
        func_807002A4(1);
        temp_v1 = *(void **)0xA0700F40;
        temp_v1->unk_0E = temp_v1->unk_0E;
        func_8070090C();
        func_807007D0();
    }
    func_807002D4(1);
    return arg0;
}
