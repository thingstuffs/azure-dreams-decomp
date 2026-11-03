#include "town/scene.h"
#include "town/devkit.h"
#include "town/scene/hooks.h"

typedef struct FlagPageState {
    u8 pad_00[0xE];
    u8 unk_0E;
} FlagPageState;   /* page_state in update_flag_page_2_value */
extern void func_807002D4(s32 index);

/* Devkit flag page 2: pass the value through when idle, else mark dirty and rescan. */
s32 update_flag_page_2_value(s32 carry_value)
{
    FlagPageState *page_state;
    s32 result;

    if (check_devkit_secondary_condition_8070021c(2) == 0) {
        func_807002D4(2);
        result = carry_value;
    }
    else {
        forward_indexed_table_value(2);
        page_state = *(void **)0xA0700F40;
        page_state->unk_0E = page_state->unk_0E;
        result = dispatch_first_failed_entry_b();
    }
    return result;
}
