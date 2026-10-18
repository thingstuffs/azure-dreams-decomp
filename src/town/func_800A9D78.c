#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94(); /* extern */
void handle_insert_initialize_two_values_status_flags();     /* extern */
void initialize_optional_object_state(); /* extern */
extern M2C_UNK D_800D0690;
extern M2C_UNK D_800D0E04;
extern M2C_UNK D_800D6A58;

/* Initialize the object's sprite, scene data, and behavior. */
void initialize_emote_sprite_and_scene(s32 object, s32 scene, s32 sprite) {
    func_8003DB94(sprite, &D_800D0E04, 0);
    handle_insert_initialize_two_values_status_flags(object, scene, &D_800D6A58);
    initialize_optional_object_state(object, scene, sprite, &D_800D0690);
}
