#include "common.h"
#include "shared/game_state.h"
#include "dungeon/system.h"
#include "dungeon/menu.h"
#include "sdk/libc.h"

typedef struct {
    u8 text[17];
    u8 value;
    u8 type;
} Record818105FC;

/* Stores a text record in the circular table unless it matches an existing entry. */
void store_unique_text_record(char *text, s32 type, s32 value) {
    Record818105FC *record;
    u8 *type_base;
    TextRecord *records_base;
    GameState *data_base;
    s32 cursor;
    s32 write_slot, *next_slot;

    if (type == 19) {
        for (cursor = 0; cursor < 5; cursor++) {
            if (strncmp(text, get_mapped_menu_table_entry(value, cursor), 18) == 0) {
                return;
            }
        }
    }

    cursor = 0;
    record = (Record818105FC *)0x800157C0;
    type_base = (u8 *)0x80010000;
    do {
        if ((type_base[0x57D2] == type) &&
            (strncmp(text, (char *)record, 18) == 0)) {
            return;
        }
        record++;
        cursor++;
        type_base += 19;
    } while (cursor < 64);
    next_slot = &GAME_STATE->text_record_next;
    write_slot = *next_slot;
    *next_slot = write_slot + 1;
    data_base = GAME_STATE;
    if (data_base->text_record_next == 64) {
        data_base->text_record_next = 0;
    }

    records_base = GAME_STATE->text_records;
    strncpy((char *)records_base[write_slot].text, text, 18);
    if (type == 19) {
        data_base->text_records[write_slot].text[17] = value;
    }
    data_base->text_records[write_slot].type = type;
}
