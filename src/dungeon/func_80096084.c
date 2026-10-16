#include "modules/dungeon_engine_tile_map_fragment_b5d50.h"
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef union { s16 coordinate; struct { u8 low; u8 high; } bytes; } CoordinateOutput;
typedef struct { CoordinateOutput first; CoordinateOutput second; } LocalBytes;

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80042900();             /* extern */


/* Updates the object's coordinates when a target passes the checks and new coordinates are found. */
s32 dungeonUpdateObjectCoordinatesIfValid(Rec_D_80082E80 *object, EntityRec *context) {
    LocalBytes next_coords;
    s32 target;

    target = findEligibleActorAtTileAndHeight(context, object->unk_24, object->unk_25, context->unk_88);
    if (target != 0) {
        if ((func_80042900(target, 0x1B) << 0x10) == 0) {
            if ((dungeonFindValidNearbyPosition(context, object->unk_24, object->unk_25, &next_coords.first.coordinate, &next_coords.second.coordinate)
                << 0x10) != 0) {
                object->unk_24 = next_coords.first.bytes.low;
                object->unk_25 = next_coords.second.bytes.low;
                return 1;
            }
            return 2;
        }
    }
    return 0;
}
