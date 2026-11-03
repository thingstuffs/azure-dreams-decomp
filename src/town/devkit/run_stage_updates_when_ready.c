#include "common.h"
#include "town/shop/state.h"
#include "town/scene.h"
#include "town/devkit.h"
#include "town/devkit/flag_test_imports.h"
extern void set_indexed_flag_bit_unless(s32);
extern void clear_indexed_flag_bit_unless(s32);

extern u8 D_807009BA[];
extern u16 D_807009DC[];

/* When the two queries and the entry check pass, run the stage updates and return the handler's result. */
s32 run_stage_updates_when_ready(s32 entry) {
    if (!test_linked_flag_80701134(*(u16 *)D_807009BA) &&
        test_linked_flag_80701134(0x152) &&
        is_next_entry_zero_after_skipping_80700ce8(entry)) {
        set_indexed_flag_bit_unless(D_807009DC[entry * 2]);
        clear_indexed_flag_bit_unless(0x152);
        return func_80700E3C();
    }

    func_80700D58(entry, 0);
    return entry;
}
