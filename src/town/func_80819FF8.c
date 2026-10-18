#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

typedef struct S_80023FF8_0_pre {
    u16 unk_00;
} S_80023FF8_0_pre;   /* the 0x2 bytes before arg0 in update_linked_four_column_number, addressed as arg0[-1] */

typedef struct S_80023FF8_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s16 * unk_08;
    s16 * unk_0C;
} S_80023FF8_0;   /* arg0 in update_linked_four_column_number */


void format_decimal_field_space_padded();           /* extern */

/* Process the entry and set its header and global flags when its status is zero. */
void update_linked_four_column_number(void *entry) {
    s16 *status;

    status = ((S_80023FF8_0 *)entry)->unk_0C;
    format_decimal_field_space_padded(*((S_80023FF8_0 *)entry)->unk_08, 4, ((S_80023FF8_0 *)entry)->unk_04 + 7);
    if (*status == 0) {
        ((S_80023FF8_0_pre *)entry)[-1].unk_00 = (u16) (((S_80023FF8_0_pre *)entry)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    }
}
