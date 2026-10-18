#include "modules/dungeon_ovl_1830850.h"

void initialize_text_editor_context(void *object, s32 range_start, s32 initial_value, s32 text_addr)
{
    u8 *data = object;

    inventory_initialize_packet_and_set_flag(*(s32 *)(data + 0x74));
    initialize_inventory_packet(*(s32 *)(data + 0x74) + 0xC);
    *(s32 *)(data + 0x0C) = initial_value;
    *(s32 *)(data + 0x14) = range_start;
    *(s32 *)(data + 0x18) = range_start + 0x20;
    *(s32 *)(data + 0x88) = text_addr;
    strcpy(data + 0x78, text_addr);
    *(s32 **)(data - 0x10) = (void *)inventory_apply_step_and_reset_after_five;
}
