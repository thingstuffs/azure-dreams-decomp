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
} S_800A48B0_0;   /* arg0 in func_800A48B0 */


/* Copy six fields from the source record to the destination. */
void func_800A48B0(S_800A48B0_0 *destination, EntityRec *source) {
    destination->unk_00 = (s32) source->x.v;
    destination->unk_04 = (s32) source->y.v;
    destination->unk_08 = (s32) source->z.v;
    destination->unk_0C = (s32) source->unk_0C;
    destination->unk_10 = (s32) source->unk_10;
    destination->unk_14 = (s32) source->flags14;
}
