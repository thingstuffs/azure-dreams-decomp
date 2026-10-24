#include "shared/runtime_dispatch.h"
#include "common.h"
#include "engine/resource.h"
#include "engine/scene.h"
#include "slus.h"



typedef struct S_8006CE80 {
    u16 unk0;
    u16 unk2;
    void *unk4;
    void *unk8;
} S_8006CE80;

extern S_8006CE80 dispatch_resource_records[35];

extern void play_selected_movie_and_restore_display(void);

/* Refreshes dispatch state and resets it unless the resulting entry has type 4. */
void play_scene_movie(void) {
    S_8006CE80 *dispatch_entry;

    dispatch_entry = &dispatch_resource_records[runtime_dispatch_state.field_B];
    play_selected_movie_and_restore_display();
    runtime_dispatch_state.unk_08 = dispatch_entry->unk2;
    scene_save_previous_mode_and_reset_callbacks();

    dispatch_entry = &dispatch_resource_records[runtime_dispatch_state.field_B];
    if (dispatch_entry->unk0 != 4) {
        load_dispatch_entry_files(0);
        invalidate_four_sprite_resource_slots();
    }
}
