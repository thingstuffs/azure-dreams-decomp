#include "common.h"
#include "engine/resource.h"
#include "engine/texture.h"
#include "engine/util.h"
#include "town/shop/object.h"
#include "town/person/four_slot_object_owner_g00628.h"

extern s32 display_vector_defaults[];

/* Initializes object resources and defaults, returning whether the auxiliary allocation succeeds. */
s32 initialize_storage_menu_resources(void *object, s32 resource_id) {
    StorageDisplayBody *state = object;
    s32 *default_values;
    void *buffer;
    s32 success = 0;

    if ((state->parts = (ItemMenuPart **)rebuild_pointer_pool(&state->unk60, resource_id, 0xC)) != 0) {
        default_values = display_vector_defaults;
        state->vector.unk0 = display_vector_defaults[0];
        state->vector.unk4 = default_values[1];
        state->vector.unk8 = default_values[2];
        set_menu_part_vectors(state->parts, &state->vector, 0x29);
        buffer = allocate_node_body(0x48);
        success = buffer != 0;
        state->unk20 = buffer;
    }
    return success;
}
