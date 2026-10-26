#include "town/minigame/initialize_source_and_initial_data.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "town/minigame/initialize_source_and_initial_data.h"

/* Creates a bouncing pickup from copied source and motion data and initializes its sprite. */
void initialize_source_and_initial_data(minigame_pickup_source *source_data, minigame_pickup_initial *initial_data)
{
    ObjectNodeHeader *object;
    Object *allocated;
    Payload88 *payload;
    SpriteFrameState *part;
    u8 *table;

    table = D_80020014;
    allocated = allocate_flagged_object_node(0x136);
    object = allocated;
    if (object != 0) {
        payload = (Payload88 *)((u8 *)object + 0x20);
        *payload = *(Payload88 *)source_data;
        object->update_callback = update_bouncing_pickup;
        **(Initial24 * *)&object->position = *(Initial24 *)initial_data;
        register_node(object, project_sprite_chain);
        part = object->sprite;
        part->scale_y = 0x1000;
        part->scale_x = 0x1000;
        part->source = minigame_pickup_sprite_sources[source_data->x];
        part->unk_04 = 0;
        part->frame_ticks = 0;
        part->color.word = 0x808080;
        part->flags |= 0x80;
        *(void **)((u8 *)payload + 0x50) = table;
        configure_the_set_mode_n_1((u8 *)payload + 8, object->position, minigame_source_bounds);
    }
}
