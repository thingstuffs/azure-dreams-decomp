#include "town/minigame/initialize_source_and_initial_data.h"
#include "shared/sprite_frame_state.h"
#include "town/minigame/initialize_source_and_initial_data.h"

void initialize_source_and_initial_data(minigame_pickup_source *source_data, minigame_pickup_initial *initial_data)
{
    Object *object;
    Object *allocated;
    Payload88 *payload;
    SpriteFrameState *part;
    u8 *table;

    table = D_80020014;
    allocated = (Object *)allocate_flagged_object_node(0x136);
    object = allocated;
    if (object != 0) {
        payload = (Payload88 *)((u8 *)object + 0x20);
        *payload = *(Payload88 *)source_data;
        object->callback = update_bouncing_pickup;
        *object->initial = *(Initial24 *)initial_data;
        register_node((struct RegistrationNode *)object, (s32)project_sprite_chain);
        part = object->render;
        part->scale_y = 0x1000;
        part->scale_x = 0x1000;
        part->source = D_8002445C[*(s16 *)((u8 *)source_data + 0x54)];
        part->unk_04 = 0;
        part->unk_05 = 0;
        part->color.word = 0x808080;
        part->flags |= 0x80;
        *(void **)((u8 *)payload + 0x50) = table;
        configure_the_set_mode_n_1((u8 *)payload + 8, object->initial, D_80024420);
    }
}
