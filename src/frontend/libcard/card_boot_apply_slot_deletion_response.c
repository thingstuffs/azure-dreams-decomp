#include "common.h"

typedef struct S_80025788_0_pre {
    void * unk_00;
    u8 pad_04[0xC];
} S_80025788_0_pre;   /* the 0x10 bytes before arg0 in card_boot_apply_slot_deletion_response, addressed as arg0[-1] */

typedef struct S_80025788_0 {
    u8 pad_00[0x28];
    s32 unk_28;
    u8 pad_2C[0x8];
    void * unk_34;
    s32 unk_38;
    u8 pad_3C[0x4];
    s32 unk_40;
} S_80025788_0;   /* arg0 in card_boot_apply_slot_deletion_response */

typedef struct S_80025788_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80025788_1;   /* cursor in card_boot_apply_slot_deletion_response */


#include "modules/main_server_ship_interfaces.h"
extern void card_boot_show_delete_failure_notice(void *command_arg);
extern void card_boot_refresh_slot_window(s32 object_addr);
extern u8 D_80024F7C[];
extern u8 D_8002593C[];

/* Updates object pointers and processes five entries when its status check succeeds. */
void card_boot_apply_slot_deletion_response(void *object) {
    u8 *entry_cursor;
    s32 entry_index;

    if (((S_80025788_0 *)object)->unk_38 != 0) {
        ((S_80025788_0_pre *)object)[-1].unk_00 = D_8002593C;
        return;
    }

    if (card_boot_erase_slot_file(((S_80025788_0 *)object)->unk_28) != 0) {
        ((S_80025788_0_pre *)object)[-1].unk_00 = D_8002593C;
        entry_index = 0;
        entry_cursor = object;
        do {
            card_boot_refresh_slot_window(((S_80025788_1 *)entry_cursor)->unk_04);
            entry_cursor += 4;
            entry_index++;
        } while (entry_index < 5);
    } else {
        ((S_80025788_0 *)object)->unk_34 = D_8002593C;
        card_boot_show_delete_failure_notice((u8 *)object - 0x20);
        ((S_80025788_0_pre *)object)[-1].unk_00 = D_80024F7C;
    }

    card_boot_recheck_selected_channel();
    ((S_80025788_0 *)object)->unk_40 = 0;
}
