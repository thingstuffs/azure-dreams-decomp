#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

typedef struct S_8002241C_0 {
    u16 unk_00;
    s16 unk_02;
} S_8002241C_0;   /* arg0 in func_8002241C; pointer addresses record offset 0x2 */


/* Set record and global flags when the record value is zero. */
void func_8002241C(void *record) {
    if (((S_8002241C_0 *)((u8 *)record - 0x2))->unk_02 == 0) {
        ((S_8002241C_0 *)((u8 *)record - 0x2))->unk_00 = (u16) (((S_8002241C_0 *)((u8 *)record - 0x2))->unk_00
            | 0x8000);
        objectFlagBlock.flags = (s32) (objectFlagBlock.flags | 0x8000);
    }
}
