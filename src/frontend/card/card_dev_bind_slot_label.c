#include "frontend/card/server_menu.h"
#include "common.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"


/* Passes the object's data at offset 0x7C to func_80051B50 with D_80408D6C. */
void card_dev_bind_slot_label(CardDevMenu4 *panel) {
    func_80051B50(panel->label_payload, &D_80408D6C, 1);
}
