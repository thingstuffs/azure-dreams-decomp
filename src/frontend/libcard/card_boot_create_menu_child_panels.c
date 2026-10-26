#include "common.h"

typedef struct S_80027A9C_0 {
    void (*unk_00)(void *);
    u8 pad_04[0x18];
    s32 unk_1C;
    u8 pad_20[0x10];
    void *unk_30;
    void *unk_34;
} S_80027A9C_0;   /* arg0 in card_boot_create_menu_child_panels; pointer addresses record offset 0x10 */


#include "modules/main_server_ship_interfaces.h"
#include "frontend/libcard/interfaces.h"
#include "engine/menu.h"
#include "frontend/libcard.h"

/* Initializes record values and installs its callback pointer. */
void card_boot_create_menu_child_panels(void *record) {
    s32 record_base;

    record_base = record - 0x20;
    ((S_80027A9C_0 *)((u8 *)record - 0x10))->unk_30 = create_or_reset_seven_entry_menu_backdrop(record_base, record + 0xC);
    ((S_80027A9C_0 *)((u8 *)record - 0x10))->unk_34 = create_visual_object(record_base, ((S_80027A9C_0 *)((u8 *)record
        - 0x10))->unk_1C);
    card_boot_toggle_channel();
    ((S_80027A9C_0 *)((u8 *)record - 0x10))->unk_00 = &card_boot_update_card_chooser_input;
}
