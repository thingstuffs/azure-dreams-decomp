#include "common.h"
#include "frontend/card/menu_defaults.h"
#include "frontend/card.h"



extern s32 D_8002D6A4[3];
extern s32 D_8002D6A8[3];

/* Initialize entry pointers, per-entry defaults, and shared data. */
void card_background_init_entry_tables(CardBackgroundBody *object, s32 entry_count) {
    s32 entry_index;
    s32 *defaults;
    s32 pad[2];

    entry_index = 0;
    if (entry_count > 0) {
        defaults = menu_primitive_defaults;
        do {
            object->entry_table[entry_index] = &object->entries[entry_index];
            object->primitives[entry_index].words[0] = defaults[0];
            object->primitives[entry_index].words[1] = defaults[1];
            object->primitives[entry_index].words[2] = defaults[2];
            object->primitives[entry_index].words[3] = defaults[3];
            object->entries[entry_index].display.block = &object->primitives[entry_index];
            object->entries[entry_index].settings = object->settings;
            entry_index++;
        } while (entry_index < entry_count);
    }
    object->settings[0] = menu_settings_defaults[0];
    object->settings[1] = D_8002D6A4[0];
    object->settings[2] = D_8002D6A8[0];
}
