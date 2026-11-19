#include "common.h"
#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"
#include "frontend/libcard/paired_choice.h"
#include "main/data.h"
#include "slus.h"

/* Updates two selected records and writes their table values to paired destinations. */
void card_boot_refresh_paired_choice_labels(CardChoiceOwner *state)
{
    s32 slot;
    u8 *id_table;
    s32 *value_table;

    slot = 0;
    id_table = D_80028068;
    value_table = D_8002806C;
    do {
        unsigned long id_address;
        unsigned long second_id_address;
        CardChoiceDisplayNode *first_link;
        CardChoiceDisplayNode *second_link;
        u8 id;
        u8 second_id;
        s32 table_offset;
        s32 second_table_offset;
        s32 *first_dest;
        s32 *second_dest;
        CardChoiceDisplayNode *entry;
        s32 first_value;
        s32 second_value;

        /* Retail adds the selected row offset to the table address before the slot. */
        table_offset = state->selection * 2;
        id_address = table_offset;
        id_address += (unsigned long)id_table;
        id_address += slot;
        id = *(u8 *)id_address;
        entry = state->pointers[id + 2];
        if (entry->payload.word != 0) {
            initialize_scaled_entry_cursor(&state->choice_cursors[id], D_80028074[slot], &entry->payload.word);
        }

        table_offset = state->selection * 2;
        first_link = state->pointers[slot];
        id_address = table_offset;
        id_address += (unsigned long)id_table;
        id_address += slot;
        id = *(u8 *)id_address;
        first_dest = &first_link->block->fields.unk_00;
        first_value = value_table[id];
        *first_dest = first_value;

        second_table_offset = state->selection * 2;
        second_link = state->pointers[slot + 2];
        second_id_address = second_table_offset;
        second_id_address += (unsigned long)id_table;
        second_id_address += slot;
        second_id = *(u8 *)second_id_address;
        second_dest = &second_link->block->fields.unk_00;
        second_value = value_table[second_id];
        slot++;
        *second_dest = second_value;
    } while (slot < 2);
}
