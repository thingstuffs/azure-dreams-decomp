#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene.h"

void process_history_entries_by_mode(void);
extern s32 D_8001691C;
extern s32 *D_80019BB8;
extern s32 D_80019BBC;

/* Call func_800182A8, then set the global pointer and base-derived value. */
void call_set_global_pointer(s32 first_input, s32 second_input, s32 third_input) {
    Rec_D_80016000 *base;

    process_history_entries_by_mode();
    base = town_scene_root;
    D_80019BB8 = &D_8001691C;
    D_80019BBC = ((s32)base->event_data) + 8;
}
