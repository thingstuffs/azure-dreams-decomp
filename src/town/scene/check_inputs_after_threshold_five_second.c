#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/player/state.h"
#include "town.h"

typedef struct CallbackTable {
    u8 pad_00[0x2C8];
    s32 (*callback)(s32);
} CallbackTable;

extern s32 D_80017908;
extern s32 *D_800179D8;

/* Initialize callback data, invoke the owner callback, and dispatch conditional updates. */
void check_inputs_after_threshold_five(void)
{
    s32 zero = 0;
    s32 (*callback)(s32);
    Rec_D_80016000 *owner;
    CallbackTable *table;

    owner = town_scene_root;
    table = ((CallbackTable *)owner->services);
    callback = table->callback;
    D_800179D8 = &D_80017908;
    callback(zero);

    if (get_script_flag_mask(F_sbs32_pad24) != 0) {
        if (town_table_contains_first_byte_b(0xB) != 0) {
            set_script_flag_bit(F_sbs43_pad12);
            if (get_script_flag_mask(F_sbs43_pad13) == 0) {
                set_script_flag_bit(F_sbs43_pad11);
                return;
            }
        } else {
            clear_script_flag_bit(F_sbs43_pad12);
            set_script_flag_bit(F_sbs43_pad11);
            return;
        }
    }
    clear_script_flag_bit(F_sbs43_pad11);
}
