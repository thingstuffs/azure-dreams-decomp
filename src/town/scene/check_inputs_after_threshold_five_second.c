#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef struct CallbackTable {
    u8 pad_00[0x2C8];
    s32 (*callback)(s32);
} CallbackTable;

extern s32 D_80017908;
extern s32 *D_800179D8;

extern void func_800175FC(s32);
extern void func_80017674(s32);
extern s32 func_800176F4(s32);
extern s32 contains_value_in_table(s32);

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

    if (func_800176F4(F_sbs32_pad24) != 0) {
        if (contains_value_in_table(0xB) != 0) {
            func_800175FC(F_sbs43_pad12);
            if (func_800176F4(F_sbs43_pad13) == 0) {
                func_800175FC(F_sbs43_pad11);
                return;
            }
        } else {
            func_80017674(F_sbs43_pad12);
            func_800175FC(F_sbs43_pad11);
            return;
        }
    }
    func_80017674(F_sbs43_pad11);
}
