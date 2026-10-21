#include "common.h"
#include "frontend/libcard/menu_callbacks.h"
#include "frontend/libcard.h"
#include "main/data.h"

extern s32 card_save_slot_metadata[][32];
extern s32 D_8002593C;
extern s32 D_80024FAC;


/* Sets up the object from its indexed table entry and assigns its state data. */
void card_boot_confirm_selected_slot_deletion(void *state) {
    void *object = (u8 *)state - 0x20;
    s32 table_index = *(s32 *)((u8 *)state + 0x28);

    if (card_save_slot_metadata[table_index][0] != 0) {
        s32 *state_data = &D_80025788;
        void *update_data = (u8 *)state + 0x38;
        *(s32 **)((u8 *)state + 0x34) = state_data;
        card_boot_show_delete_confirmation(object, update_data);
        *(s32 **)((u8 *)state - 0x10) = &D_80024FAC;
    } else {
        *(s32 **)((u8 *)state + 0x34) = &D_8002593C;
        card_boot_show_no_saved_game_notice(object);
        *(s32 **)((u8 *)state - 0x10) = &D_80024FAC;
    }

}
