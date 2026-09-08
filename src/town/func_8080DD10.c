#include "common.h"
#include "m2c_compat.h"

typedef struct S_8080DD10_0_pre {
    u16 unk_00;
} S_8080DD10_0_pre;   /* the 0x2 bytes before arg0 in func_8080DD10, addressed as arg0[-1] */

typedef struct S_8080DD10_0 {
    s16 unk_00;
} S_8080DD10_0;   /* arg0 in func_8080DD10 */


extern s32 D_80084D5C;

/* Set bit 0x8000 in the preceding flags and global flags when the value is zero. */
void func_8080DD10(void *value_ptr) {
    if (((S_8080DD10_0 *)value_ptr)->unk_00 == 0) {
        (*(u16 *)((u8 *)value_ptr + -2)) = (u16) (((S_8080DD10_0_pre *)value_ptr)[-1].unk_00 | 0x8000);
        D_80084D5C |= 0x8000;
    }
}
