#include "common.h"
#include "shared/object_index_slots.h"
#include "shared/entity_objects.h"

typedef struct {
    s32 unk0;
    void *object;
} ObjectEntry;

typedef struct {
    u8 pad0[0x10];
    void *current;
    u8 pad14[4];
    s32 object_index;
} TownState;

extern TownState town_actor_control;
extern s16 D_800D5078[];

#include "town/person/object_setup.h"

/* Return the current object's cached value or look it up at the town coordinates. */
s16 get_cached_or_coordinate_transform_value(void *object, void *lookup_mode)
{
    TownState *state = &town_actor_control;

    if (object == state->current &&
        object == (u8 *)object_index_slots[*(s32 *)((u8 *)object + 0x60)].object +
                    0x20) {
        return D_800D5078[state->object_index];
    }

    return clamp_transform_coordinate_deltas(view_reference_entity.x.w.i, view_reference_entity.y.w.i, lookup_mode);
}
