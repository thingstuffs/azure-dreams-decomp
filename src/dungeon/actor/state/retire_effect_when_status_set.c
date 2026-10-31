#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

typedef struct S_800ADB8C_0_pre {
    u16 unk_00;
} S_800ADB8C_0_pre;   /* the 0x2 bytes before arg0 in retire_effect_when_status_set, addressed as arg0[-1] */

typedef struct S_800ADB8C_0 {
    u8 * unk_00;
} S_800ADB8C_0;   /* arg0 in retire_effect_when_status_set */


/* Sets the record and global 0x8000 flags when the referenced byte is nonzero. */
void retire_effect_when_status_set(void *record_arg) {
    S_800ADB8C_0_pre *record = record_arg;

    if (*((S_800ADB8C_0 *)record)->unk_00 != 0) {
        record[-1].unk_00 = (u16) (record[-1].unk_00 | 0x8000);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
