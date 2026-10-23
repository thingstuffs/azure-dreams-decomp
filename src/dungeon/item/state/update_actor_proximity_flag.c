#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
extern s16 get_tile_chebyshev_distance(void *, void *);

/* Updates and returns the state flag using a source index and two thresholds. */
s32 update_actor_proximity_flag(void *source, void *state, s32 lower_limit, s32 upper_limit, s8 *result) {
    u32 flags = (*(u32 *)&((EntityRec *)state)->flags1C);
    s8 source_index;

    if (flags & ACTOR_PLAYER_AWARE) {
        if (flags & ACTOR_BLIND) {
            (*(u32 *)&((EntityRec *)state)->flags1C) = flags & ~ACTOR_PLAYER_AWARE;
            ((EntityRec *)state)->unk_73 = 0;
            ((EntityRec *)state)->unk_72 = 0;
            *result = -1;
            return ((*(u32 *)&((EntityRec *)state)->flags1C) >> 17) & 1;
        }
        source_index = ((TileObject *)source)->room_index;
        if (source_index < 0 || source_index != reference_tile_object.room_index) {
            if ((get_tile_chebyshev_distance(((u8 *)(&reference_tile_object)), source) << 16) >= (upper_limit << 16)) {
                ((EntityRec *)state)->unk_73 = 0;
                ((EntityRec *)state)->unk_72 = 0;
                (*(u32 *)&((EntityRec *)state)->flags1C) &= ~ACTOR_PLAYER_AWARE;
                *result = -1;
                return ((*(u32 *)&((EntityRec *)state)->flags1C) >> 17) & 1;
            }
        }
        return ((*(u32 *)&((EntityRec *)state)->flags1C) >> 17) & 1;
    }
    if (!(flags & ACTOR_BLIND)) {
        source_index = ((TileObject *)source)->room_index;
        if ((source_index >= 0 && source_index == reference_tile_object.room_index)
            || (get_tile_chebyshev_distance(((u8 *)(&reference_tile_object)), source) << 16) < (lower_limit << 16))
            (*(u32 *)&((EntityRec *)state)->flags1C) |= ACTOR_PLAYER_AWARE;
    }
    return ((*(u32 *)&((EntityRec *)state)->flags1C) >> 17) & 1;
}
