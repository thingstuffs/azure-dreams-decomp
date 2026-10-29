#include "common.h"
#include "town/player.h"
#include "town/player/position.h"

typedef struct {
    u8 unk0[0xC];
    s32 unkC;
    s32 unk10;
} TownObject;

extern void update_state_limits(TownObject *);

/* Update the object and clear fields selected by the combined status flags. */
s32 update_object_and_clear_status_fields(TownObject *object) {
    void *object_data;
    s32 status_flags;

    update_state_limits(object);
    object_data = (u8 *)object + 4;
    status_flags = clamp_coordinates_to_bounds(object, object_data);
    status_flags |= push_point_to_containing_edges(object, object_data);
    if (status_flags & 0x11) {
        object->unkC = 0;
    }
    if (status_flags & 0x1100) {
        object->unk10 = 0;
    }
    return status_flags;
}
