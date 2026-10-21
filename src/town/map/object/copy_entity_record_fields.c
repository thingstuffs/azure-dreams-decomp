#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

typedef struct S_800A48B0_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800A48B0_0;   /* arg0 in copy_entity_record_fields */


/* Copy six fields from the source record to the destination. */
void copy_entity_record_fields(S_800A48B0_0 *destination, ObjectPosition *source) {
    destination->unk_00 = (s32) source->x.v;
    destination->unk_04 = (s32) source->y.v;
    destination->unk_08 = (s32) source->z.v;
    destination->unk_0C = (s32) source->velocity_x;
    destination->unk_10 = (s32) source->velocity_y;
    destination->unk_14 = (s32) source->velocity_z;
}
