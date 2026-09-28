#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"


/* Adds each of the three motion increments to its corresponding position component. */
void func_8009539C(EntityRec *motion) {
    motion->x.v = (s32) (motion->x.v + motion->unk_0C);
    motion->y.v = (s32) (motion->y.v + motion->unk_10);
    motion->z.v = (s32) (motion->z.v + motion->flags14);
}
