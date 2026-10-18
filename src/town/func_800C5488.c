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

extern TownState D_800CFCB4;
extern s16 D_800D5078[];

extern s16 clamp_transform_coordinate_deltas(s16 x, s16 z, s32 origin);

/* Return the current object's cached value or look it up at the town coordinates. */
s16 get_cached_or_coordinate_transform_value(void *object, s32 lookup_mode)
{
    TownState *state = &D_800CFCB4;

    if (object == state->current &&
        object == (u8 *)D_80082660[*(s32 *)((u8 *)object + 0x60)].object +
                    0x20) {
        return D_800D5078[state->object_index];
    }

    return clamp_transform_coordinate_deltas(D_80083780.x.w.i, D_80083780.y.w.i, lookup_mode);
}
