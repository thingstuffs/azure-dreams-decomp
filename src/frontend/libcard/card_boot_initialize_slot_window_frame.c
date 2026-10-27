#include "common.h"
#include "frontend/libcard/message.h"



extern CardDisplayBlock display_block_defaults;
extern DisplayPositionWords display_vector_defaults;





/* Initialize and link two template blocks, applying defaults and a slot-based offset. */
void card_boot_initialize_slot_window_frame(CardDisplayNode *entity, CardDisplayBlock *primary, DisplayPositionWords *secondary, s32 slot_index) {
    CardDisplayBlock *primary_template = &display_block_defaults;
    DisplayPositionWords *secondary_template = &display_vector_defaults;
    s32 *secondary_head;

    primary->words[0] = primary_template->words[0];
    secondary_head = &secondary_template->unk0;
    primary->words[1] = primary_template->words[1];
    primary->words[2] = primary_template->words[2];
    primary->words[3] = primary_template->words[3];

    secondary->unk0 = *secondary_head;
    secondary->unk4 = secondary_template->unk4;
    secondary->unk8 = secondary_template->unk8;

    entity->block = primary;
    entity->vector = secondary;
    entity->unk_00 = 0;

    entity->block->fields.x = -0xA0;
    entity->block->fields.y = (slot_index * 0x18) - 0x78;
    entity->block->fields.depth = 0x200;
    entity->block->fields.mode = 4;
}
