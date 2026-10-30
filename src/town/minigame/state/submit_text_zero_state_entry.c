#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/object_links.h"
#include "sdk/libc.h"
#include "engine/text.h"
#include "town/minigame/state.h"

   /* the 0x2 bytes before arg0 in submit_text_zero_state_entry, addressed as arg0[-1] */


typedef struct S_80026BC4_1 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_80026BC4_1;



/* Submits text for a zero-state entry and sets flags when requested by its configuration. */
void submit_text_zero_state_entry(TextEntryObject *text_entry) {
    ObjectStatusPrefix16 *text_entry_view = (ObjectStatusPrefix16 *)text_entry;
    S_80026BC4_1 *text_config;

    text_config = text_entry->configuration;
    if (text_entry->state == 0) {
        format_decimal_field_space_padded(*text_entry->value, strlen(text_entry->text),
            text_entry->text);
        if (text_config->unk_1A & 8) {
            text_entry_view[-1].flags = (u16) (text_entry_view[-1].flags | 0x8000);
            object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
        }
    }
}
