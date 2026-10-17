#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
extern s16 dungeonGetTileChebyshevDistance(void *, void *);

/* Updates and returns the state flag using a source index and two thresholds. */
s32 dungeonUpdateActorProximityFlag(void *source, void *state, s32 lower_limit, s32 upper_limit, s8 *result) {
    u32 flags = (*(u32 *)&((EntityRec *)state)->flags1C);
    s8 source_index;

    if (flags & 0x20000) {
        if (flags & 0x10) {
            (*(u32 *)&((EntityRec *)state)->flags1C) = flags & ~0x20000;
            ((EntityRec *)state)->unk_73 = 0;
            ((EntityRec *)state)->unk_72 = 0;
            *result = -1;
            return ((*(u32 *)&((EntityRec *)state)->flags1C) >> 17) & 1;
        }
        source_index = ((TileObject *)source)->unk_026;
        if (source_index >= 0) {
            if (source_index == D_80082E80.unk_026)
                goto done;
        }
        if ((dungeonGetTileChebyshevDistance(((u8 *)(&D_80082E80)), source) << 16) >= (upper_limit << 16)) {
            ((EntityRec *)state)->unk_73 = 0;
            ((EntityRec *)state)->unk_72 = 0;
            (*(u32 *)&((EntityRec *)state)->flags1C) &= ~0x20000;
            *result = -1;
            return ((*(u32 *)&((EntityRec *)state)->flags1C) >> 17) & 1;
        }
        return ((*(u32 *)&((EntityRec *)state)->flags1C) >> 17) & 1;
    }
    if (!(flags & 0x10)) {
        source_index = ((TileObject *)source)->unk_026;
        if (source_index >= 0) {
            if (source_index == D_80082E80.unk_026)
                goto set_flag;
        }
        if ((dungeonGetTileChebyshevDistance(((u8 *)(&D_80082E80)), source) << 16) >= (lower_limit << 16))
            return ((*(u32 *)&((EntityRec *)state)->flags1C) >> 17) & 1;
set_flag:
        (*(u32 *)&((EntityRec *)state)->flags1C) |= 0x20000;
    }
done:
    return ((*(u32 *)&((EntityRec *)state)->flags1C) >> 17) & 1;
}
