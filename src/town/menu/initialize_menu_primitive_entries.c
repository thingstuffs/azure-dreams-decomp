#include "frontend/card/slot_details.h"
#include "common.h"
#include "frontend/card/menu_defaults.h"

typedef struct { s32 value; } DefaultWord;
extern DefaultWord D_8002D6A4, D_8002D6A8;
/* Links menu entries to their primitive storage and copies the default primitive and shared settings. */
void initialize_menu_primitive_entries(CardDevSlotDetails *work, s32 count) {
    s32 i;
    for (i = 0; i < count; i++) {
        work->entries[i] = &work->nodes[i];
        work->blocks[i].words[0] = menu_primitive_defaults[0];
        work->blocks[i].words[1] = menu_primitive_defaults[1];
        work->blocks[i].words[2] = menu_primitive_defaults[2];
        work->blocks[i].words[3] = menu_primitive_defaults[3];
        work->nodes[i].display.block = &work->blocks[i];
        work->nodes[i].settings = work->settings;
    }
    work->settings[0] = menu_settings_defaults[0];
    work->settings[1] = D_8002D6A4.value;
    work->settings[2] = D_8002D6A8.value;
}
