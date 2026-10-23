#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/object_links.h"

   /* the 0x2 bytes before arg0 in update_linked_four_column_number, addressed as arg0[-1] */

typedef struct S_80023FF8_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s16 * unk_08;
    s16 * unk_0C;
} S_80023FF8_0;   /* arg0 in update_linked_four_column_number */


void format_decimal_field_space_padded();           /* extern */

/* Process the entry and set its header and global flags when its status is zero. */
void update_linked_four_column_number(void *entry) {
    ObjectStatusPrefix16 *entry_view = entry;
    s16 *status;

    status = ((S_80023FF8_0 *)entry)->unk_0C;
    format_decimal_field_space_padded(*((S_80023FF8_0 *)entry)->unk_08, 4, ((S_80023FF8_0 *)entry)->unk_04 + 7);
    if (*status == 0) {
        entry_view[-1].flags = (u16) (entry_view[-1].flags | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
