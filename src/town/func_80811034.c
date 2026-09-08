#include "common.h"
#include "m2c_compat.h"

typedef struct S_80811034_0_pre {
    u16 unk_00;
} S_80811034_0_pre;   /* the 0x2 bytes before arg0 in func_80811034, addressed as arg0[-1] */

typedef struct S_80811034_0 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80811034_0;   /* arg0 in func_80811034 */


extern s32 D_80084D5C;

/* Decrement the countdown and set record and global flags when it expires. */
void func_80811034(void *record) {
    u16 countdown;

    countdown = ((S_80811034_0 *)record)->unk_02 - 1;
    ((S_80811034_0 *)record)->unk_02 = countdown;
    if ((countdown << 0x10) <= 0) {
        (*(u16 *)((u8 *)record + -2)) = (u16) (((S_80811034_0_pre *)record)[-1].unk_00 | 0x8000);
        D_80084D5C |= 0x8000;
    }
}
