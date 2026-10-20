#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_effect_views.h"
void register_node_if_unregistered(void *block_data, s32 registration_id);           /* extern */
s32 lookup_item_category_mapped_value();                /* extern */
void *create_town_effect_object(); /* extern */
void update_linked_part_position(void *, s32, void *);         /* extern */


typedef struct S_800A7FD8_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    void * unk_0C;
} S_800A7FD8_0;

typedef struct S_800A7FD8_1 {
    u8 pad_00[0x60];
    s32 unk_60;
} S_800A7FD8_1;


/* present_flower_set: create a flower gift object and initialize its state and callback data. */
void present_flower_set(s32 initial_value) {
    s32 callback_arg;
    S_800A7FD8_1 *state;
    EffectStateWordView *callback_data;
    void *object;

    object = create_town_effect_object(0, 0, &update_linked_part_position, 0);
    if (object != 0) {
        callback_arg = ((S_800A7FD8_0 *)object)->unk_08;
        callback_data = ((S_800A7FD8_0 *)object)->unk_0C;
        state = object + 0x20;
        state->unk_60 = initial_value;
        callback_data->unk_08 = lookup_item_category_mapped_value(0xB, 2);
        register_node_if_unregistered(state, project_sprite_chain);
        update_linked_part_position(state, callback_arg, callback_data);
    }
}
