#include "script_symbols.h"
#include "common.h"

extern s32 get_referenced_object_active_flag(void);
extern void *apply_entry_position(void *entries, void *object, s32 context, s32 selection);
extern s32 get_script_flag_mask(s32 flagIndex);

extern s32 D_8001BB3C;
extern s32 scene_dispatch_context;
extern s32 D_8001E3B0;
extern s32 D_8001E59B;

// Returns the lookup result or an alternate pointer selected by the current state.
void *dispatch_or_select_state_data(s32 lookupValue, s32 unused, s32 lookupOption) {
    void *lookupResult;

    lookupResult = apply_entry_position(&D_8001BB3C, &scene_dispatch_context, lookupValue, lookupOption);
    if (get_referenced_object_active_flag() != 0) {
        if (get_script_flag_mask(Ftt_pad34) == 0) {
            return &D_8001E3B0;
        }
        return &D_8001E59B;
    }
    return lookupResult;
}
