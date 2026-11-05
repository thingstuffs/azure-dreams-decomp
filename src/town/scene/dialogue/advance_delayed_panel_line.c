#include "common.h"
#include "m2c_compat.h"
#include "town/scene/dialogue.h"
#include "town/data.h"

typedef struct S_8080BCD4_0 {
    u16 unk_00;
    u16 unk_02;
    void * unk_04;
    u8 pad_08[0xE];
    u16 unk_16;
} S_8080BCD4_0;   /* ptr in advance_delayed_panel_line */

typedef struct S_8080BCD4_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_8080BCD4_1;   /* context in advance_delayed_panel_line */

/* Clears panel flag 2 after a delay, then marks the panel for removal when the linked flag is set. */
void advance_delayed_panel_line(void *ptr_arg) {
    S_8080BCD4_0 *ptr = ptr_arg;
    s16 state;
    u16 remaining;
    u16 next_state;
    u16 flags;
    S_8080BCD4_1 *context;

    state = ((s16)ptr->unk_00);
    context = ptr->unk_04;
    switch (state) {
    case 0:
        remaining = ptr->unk_02 - 1;
        ptr->unk_02 = remaining;
        if ((remaining << 0x10) <= 0) {
            next_state = ptr->unk_00;
            flags = ptr->unk_16;
            next_state++;
            flags &= 0xFFFD;
            ptr->unk_16 = flags;
            ptr->unk_00 = next_state;
            return;
        }
        return;
    case 1:
        if (context->unk_2A & 1) {
            *(u16 *)((u8 *)ptr - 2) |= 0x8000;
            scene_object_flags |= 0x8000;
        }
    default:
        return;
    }
}
