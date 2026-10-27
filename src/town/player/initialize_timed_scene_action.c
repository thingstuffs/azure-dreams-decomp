#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

short SD_Call(int flags);
#include "town/player/call_the_handler_selects_nonzero_entry_api.h"  /* extern */
extern void D_80091AF0(void *state, void *object, s32 context);
extern s32 timed_scene_handler_entries;


/* Initialize the record with its handler and a count of twelve. */
void initialize_timed_scene_action(Rec_func_80094268_arg0 *record, s32 unused, s32 setup_value) {
    SD_Call(0x510);
    call_the_handler_selects_nonzero_entry(&timed_scene_handler_entries, record, (void *)(setup_value));
    record->unk_00.as_pm = &D_80091AF0;
    record->unk_0A.as_s16 = 0xC;
}
