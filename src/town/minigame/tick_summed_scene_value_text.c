#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/object_links.h"
#include "sdk/libc.h"
#include "engine/text.h"
#include "town/minigame.h"

   /* the 0x2 bytes before arg0 in tick_summed_scene_value_text, addressed as arg0[-1] */


typedef struct S_80020510_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80020510_1;


extern s16 D_800272A0[];

/* Advances a text entry's delay, processes its string, and propagates the linked object's flag. */
void tick_summed_scene_value_text(TerminalSceneTextObject *entry) {
    u16 *flags;
    s16 state;
    s32 value_index;
    s32 value_sum;
    u16 ticks_left;
    S_80020510_1 *linked_object;

    value_sum = 0;
    value_index = 7;
    linked_object = entry->owner;
    do {
        value_sum += D_800272A0[value_index];
        value_index -= 1;
    } while (value_index >= 0);
    state = entry->state.s;
    switch (state) {
    case 0:
        ticks_left = entry->delay - 1;
        entry->delay = ticks_left;
        if ((ticks_left << 0x10) > 0) {
            return;
        }
        entry->flags =
            (u16) (entry->flags & 0xFFFD);
        entry->state.u =
            (u16) (entry->state.u + 1);
        break;
    case 1:
        format_decimal_field_space_padded(value_sum, strlen(entry->text),
                      entry->text);
        if (linked_object->unk_2A & 1) {
            flags = &((ObjectNodeHeader *)entry - 1)->flags;
            *flags =
                (u16) (*flags | NODE_REMOVE);
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }
}
