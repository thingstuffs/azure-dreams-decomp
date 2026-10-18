#include "common.h"
#include "m2c_compat.h"

typedef struct S_80027A9C_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x18];
    s32 unk_1C;
    u8 pad_20[0x10];
    s32 unk_30;
    s32 unk_34;
} S_80027A9C_0;   /* arg0 in card_boot_create_menu_child_panels; pointer addresses record offset 0x10 */


void card_boot_toggle_channel();                            /* extern */
s32 create_visual_object();                        /* extern */
s32 create_or_reset_seven_entry_menu_backdrop();                        /* extern */
extern M2C_UNK D_8002789C;

/* Initializes record values and installs its callback pointer. */
void card_boot_create_menu_child_panels(void *record) {
    s32 record_base;

    record_base = record - 0x20;
    ((S_80027A9C_0 *)((u8 *)record - 0x10))->unk_30 = create_or_reset_seven_entry_menu_backdrop(record_base, record + 0xC);
    ((S_80027A9C_0 *)((u8 *)record - 0x10))->unk_34 = create_visual_object(record_base, ((S_80027A9C_0 *)((u8 *)record
        - 0x10))->unk_1C);
    card_boot_toggle_channel();
    ((S_80027A9C_0 *)((u8 *)record - 0x10))->unk_00 = &D_8002789C;
}
