#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "town/minigame/effect.h"

typedef struct S_8002241C_0 {
    u16 unk_00;
    s16 unk_02;
} S_8002241C_0;   /* arg0 in retire_transient_line_effect; pointer addresses record offset 0x2 */


/* Set record and global flags when the record value is zero. */
void retire_transient_line_effect(void *record) {
    if (((S_8002241C_0 *)((u8 *)record - 0x2))->unk_02 == 0) {
        ((S_8002241C_0 *)((u8 *)record - 0x2))->unk_00 = (u16) (((S_8002241C_0 *)((u8 *)record - 0x2))->unk_00
            | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
