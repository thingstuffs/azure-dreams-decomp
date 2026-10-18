#include "common.h"

extern void mark_sprite_resources_for_purge(void);
extern void clear_marked_slot_entries(void);
extern void *prepare_uncached_sprite_resource(s16 a0);
extern s32 Control_CD(s32 a0, void *a1, void *a2);
extern int func_800499DC(int *a0);

/* Gets the code's slot, refreshing for code 0x38, and initializes callback state on success. */
void *begin_sprite_resource_load_with_completion_flag(s32 packed_code, s32 *callback_state)
{
    s16 code = (s16)packed_code;
    void *slot;

    if (code == 0x38) {
        mark_sprite_resources_for_purge();
        clear_marked_slot_entries();
    }
    slot = prepare_uncached_sprite_resource(code);
    if (slot != 0) {
        *callback_state = 0;
        Control_CD(0xFF, (void *)func_800499DC, callback_state);
    }
    return slot;
}
