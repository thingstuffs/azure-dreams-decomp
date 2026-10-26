#include "common.h"
#include "m2c_compat.h"

void select_record_entry_and_value(void *state, void *entries, short index);
struct Rec_D_800CFCB4; void handle_insert_initialize_two_values_status_flags(struct Rec_D_800CFCB4 *, s32, s32);     /* extern */
struct Rec_D_80082E80; void initialize_optional_object_state(void *, s32, struct Rec_D_80082E80 *, s32); /* extern */
extern M2C_UNK D_800D0690;
#include "shared/sprite_source.h"
extern SpriteSourceEntry emote_sprite_entries[];
extern M2C_UNK D_800D6A58;

/* Initialize the object's sprite, scene data, and behavior. */
void initialize_emote_sprite_and_scene(s32 object, s32 scene, s32 sprite) {
    select_record_entry_and_value(sprite, &emote_sprite_entries, 0);
    handle_insert_initialize_two_values_status_flags((struct Rec_D_800CFCB4 *)(object), scene, (s32)(&D_800D6A58));
    initialize_optional_object_state((void *)(object), scene, (struct Rec_D_80082E80 *)(sprite), (s32)(&D_800D0690));
}
