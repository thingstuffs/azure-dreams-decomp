#include "common.h"

extern void card_boot_layout_empty_slot_window(s32 *object);
extern void func_80023BE4(void *, s32, s32);
extern void card_boot_format_occupied_slot_window(s32 *slot_owner);
extern void card_boot_layout_alternate_slot_window(s32 *context);

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad4[4];
    /* 0x08 */ s16 unk8;
    /* 0x0A */ u8 pad10[0x80 - 0x0A];
} EntryS80083E98; // size 0x80

extern EntryS80083E98 D_80083E98[];

/* Processes two buffers and selects handlers using the state's indexed entry. */
void card_boot_populate_slot_window_display(s32 *state) {
    func_80023BE4((u8 *)state + 0x134, 0x80, 0x18);
    func_80023BE4((u8 *)state + 0x1AC, 0x2A, 0x14);
    if (D_80083E98[*state].unk0 != 0) {
        card_boot_format_occupied_slot_window(state);
        if (D_80083E98[*state].unk8 != 0) {
            card_boot_layout_alternate_slot_window(state);
            return;
        }
    } else {
        card_boot_layout_empty_slot_window(state);
    }
}
