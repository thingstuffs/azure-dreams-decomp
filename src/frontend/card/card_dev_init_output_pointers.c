#include "frontend/card/server_menu.h"
#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "main/data.h"

/* Populate the indirect output pointers with shared data and embedded records. */
void card_dev_init_output_pointers(CardDevMenu4 *panel) {
    panel->entries[0]->display.payload.data = &D_80083060;
    panel->entries[1]->display.payload.data = &D_8008306C;
    panel->entries[2]->display.payload.data = panel->first_payload;
    panel->entries[3]->display.payload.data = panel->label_payload;
}
