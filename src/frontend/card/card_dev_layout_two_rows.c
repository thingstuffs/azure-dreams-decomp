#include "frontend/card/choice_panel.h"
#include "common.h"
#include "frontend/card.h"
#include "main/data.h"

extern void func_8004DDBC(void *base, void *data, void *entry);

/* Configures two object entries and initializes them with shared data. */
void card_dev_layout_two_rows(void *object) {
    CardMenuDisplayNode *entry;
    CardDevChoicePanelPrefix *panel;
    void *shared_data;

    panel = object;
    shared_data = D_80408A30;
    entry = panel->children[2];
    entry->block->fields.x = 0x40;
    entry->block->fields.y = 0x20;
    func_8004DDBC((u8 *)object + 4, shared_data, entry);

    entry = panel->children[3];
    entry->block->fields.x = 0xC0;
    entry->block->fields.y = 0x20;
    func_8004DDBC((u8 *)object + 0x10, shared_data, entry);
}
