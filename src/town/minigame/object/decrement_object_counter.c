#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/object_links.h"
#include "sdk/libc.h"

   /* the 0x2 bytes before arg0 in decrement_object_counter, addressed as arg0[-1] */

typedef struct S_800249A0_0 {
    s16 unk_00;
    u8 pad_02[0x2];
    char *unk_04;
    s16 * unk_08;
    void * unk_0C;
} S_800249A0_0;   /* arg0 in decrement_object_counter */

typedef struct S_800249A0_1 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_800249A0_1;


void format_decimal_field_space_padded();               /* extern */

/* Process the entry text when its state is zero and propagate the linked flags. */
void decrement_object_counter(void *entry) {
    ObjectStatusPrefix16 *entry_view = entry;
    S_800249A0_1 *text_info;

    text_info = ((S_800249A0_0 *)entry)->unk_0C;
    if (((S_800249A0_0 *)entry)->unk_00 == 0) {
        format_decimal_field_space_padded(*((S_800249A0_0 *)entry)->unk_08, strlen(((S_800249A0_0 *)entry)->unk_04),
            ((S_800249A0_0 *)entry)->unk_04);
        if (text_info->unk_0C & 2) {
            entry_view[-1].flags = (u16) (entry_view[-1].flags | 0x8000);
            object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
        }
    }
}
