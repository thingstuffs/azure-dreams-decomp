#include "common.h"

typedef struct {
    u8 pad00[0x7C];
    s32 unk7C;
    s32 unk80;
} S_80011A50;

extern u8 D_80083E98;
extern void card_boot_format_saved_slot_details(S_80011A50 *record);
extern void card_boot_format_empty_slot_guidance(S_80011A50 *context);
extern void build_a_trigonometric_table_processes_up_eight_height_offset_segments(S_80011A50 *context);

/* Dispatch to a handler based on the object's table entry and state. */
void card_boot_refresh_slot_details(S_80011A50 *object)
{
    u8 *entry_table;
    register s32 state;

    entry_table = &D_80083E98;
    if (*(s32 *)(entry_table + (object->unk7C << 7)) != 0) {
        card_boot_format_saved_slot_details(object);
        return;
    }
    state = object->unk80;
    if ((state != 0) && (state != 2)) {
        card_boot_format_empty_slot_guidance(object);
        return;
    }
    build_a_trigonometric_table_processes_up_eight_height_offset_segments(object);
}
