#include "shared/runtime_dispatch.h"
#include "common.h"



typedef struct S_8006CE80 {
    u16 unk0;
    u16 unk2;
    void *unk4;
    void *unk8;
} S_8006CE80;

extern S_8006CE80 dispatch_resource_records[100];

extern void play_selected_movie_and_restore_display(void);
extern void scene_save_previous_mode_and_reset_callbacks(void);
extern void load_dispatch_entry_files(u16 a0);
extern void invalidate_four_sprite_resource_slots(void);

/* Refreshes dispatch state and resets it unless the resulting entry has type 4. */
void play_scene_movie(void) {
    S_8006CE80 *dispatch_entry;

    dispatch_entry = &dispatch_resource_records[D_80082E60.field_B];
    play_selected_movie_and_restore_display();
    D_80082E60.unk_08 = dispatch_entry->unk2;
    scene_save_previous_mode_and_reset_callbacks();

    dispatch_entry = &dispatch_resource_records[D_80082E60.field_B];
    if (dispatch_entry->unk0 != 4) {
        load_dispatch_entry_files(0);
        invalidate_four_sprite_resource_slots();
    }
}
