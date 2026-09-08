#include "common.h"
#include "m2c_compat.h"

typedef struct S_8080DD50_0_pre {
    u16 unk_00;
} S_8080DD50_0_pre;   /* the 0x2 bytes before arg0 in func_8080DD50, addressed as arg0[-1] */

typedef struct S_8080DD50_0 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8080DD50_0;   /* arg0 in func_8080DD50 */

typedef struct S_8080DD50_1 {
    u8 pad_00[0x36];
    s16 unk_36;
} S_8080DD50_1;   /* ((S_8080DD50_0 *)arg0)->unk_04 in func_8080DD50 */


extern s32 D_80084D5C;

/* Set record and global flags when the linked object has state 7. */
void func_8080DD50(void *record) {
    if (((S_8080DD50_1 *)(((S_8080DD50_0 *)record)->unk_04))->unk_36 == 7) {
        (*(u16 *)((u8 *)record + -2)) = (u16) (((S_8080DD50_0_pre *)record)[-1].unk_00 | 0x8000);
        D_80084D5C |= 0x8000;
    }
}
