#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/object_links.h"

   /* the 0x2 bytes before arg0 in submit_text_zero_state_entry, addressed as arg0[-1] */

typedef struct S_80026BC4_0 {
    s16 unk_00;
    u8 pad_02[0x2];
    s32 unk_04;
    s16 * unk_08;
    void * unk_0C;
} S_80026BC4_0;   /* arg0 in submit_text_zero_state_entry */

typedef struct S_80026BC4_1 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_80026BC4_1;


void format_decimal_field_space_padded();               /* extern */
s32 strlen();                             /* extern */

/* Submits text for a zero-state entry and sets flags when requested by its configuration. */
void submit_text_zero_state_entry(void *text_entry) {
    ObjectStatusPrefix16 *text_entry_view = text_entry;
    S_80026BC4_1 *text_config;

    text_config = ((S_80026BC4_0 *)text_entry)->unk_0C;
    if (((S_80026BC4_0 *)text_entry)->unk_00 == 0) {
        format_decimal_field_space_padded(*((S_80026BC4_0 *)text_entry)->unk_08, strlen(((S_80026BC4_0 *)text_entry)->unk_04),
            ((S_80026BC4_0 *)text_entry)->unk_04);
        if (text_config->unk_1A & 8) {
            text_entry_view[-1].flags = (u16) (text_entry_view[-1].flags | 0x8000);
            object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
        }
    }
}
