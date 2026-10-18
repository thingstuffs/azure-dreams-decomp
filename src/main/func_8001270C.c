#include "common.h"

extern void update_spark_effect(void *menu, s32 entry_id);
extern void card_boot_show_no_saved_game_notice(void *object, s32 entry_id);

extern u8 D_8002593C[];
extern u8 D_80024FAC[];
extern u8 D_80025584[];

/* Select an entry handler and update the owning object's callback. */
void card_boot_select_copy_source_slot(void *state) {
    extern s32 D_80083E98[];
    s32 entry_id = *(s32 *)((u8 *)state + 0x28);

    if (D_80083E98[entry_id * 32] != 0) {
        *(s32 *)((u8 *)state + 0x2C) = entry_id;
        update_spark_effect(state, entry_id);
        *(s32 **)((u8 *)state - 0x10) = (s32 *)D_80025584;
    } else {
        *(s32 **)((u8 *)state + 0x34) = (s32 *)D_8002593C;
        card_boot_show_no_saved_game_notice((u8 *)state - 0x20, entry_id);
        *(s32 **)((u8 *)state - 0x10) = (s32 *)D_80024FAC;
    }
}
