#include "common.h"

#include "engine/window.h"

typedef struct S_800357B0_0 {
    u8 pad_00[0x50];
    u16 unk_50;
    u8 pad_52[0x16];
    void (*unk_68)(struct S_800357D0_0 *);
} S_800357B0_0;   /* arg0 in wait_both_window_flags */

/* Assigns advance_window_close_counter to objects with code 0x101. */
void wait_both_window_flags(S_800357B0_0 *object) {
    if (object->unk_50 == 0x101) {
        object->unk_68 = &advance_window_close_counter;
    }
}
