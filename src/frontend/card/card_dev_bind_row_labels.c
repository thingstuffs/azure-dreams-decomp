#include "common.h"
#include "frontend/card.h"
#include "frontend/card/command_panel.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"


// Process four entries spaced 0x3C bytes apart using consecutive table values.
void card_dev_bind_row_labels(CardDevCommandPanel *panel) {
    s32 *tableValue;
    s32 entryIndex;

    entryIndex = 0;
    tableValue = &D_80408C8C;
    do {
        func_80051B50(panel->labels[entryIndex], *tableValue, 1);
        tableValue++;
        entryIndex++;
    } while (entryIndex < 4);
}
