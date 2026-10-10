#include "modules/dungeon_ovl_1918800.h"
#include "common.h"
#include "modules/dungeon_native_abi.h"
#include "shared/entity.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"


/* Raise the entity toward the queried ground height and set flags when the countdown expires. */
void func_8002515C(EntityRec *state, EntityRec *position)
{
    u16 countdown;

    D_800266BC = 1;
    if (position->z.w.i <
        (s16)func_800BCB04((u16)position->x.w.i, (u16)position->y.w.i,
                      (s16)(position->z.w.i + 2))) {
        position->z.v += 0x20000 + (rand() & 0xFFF);
    }

    countdown = state->unk_32 - 8;
    state->unk_32 = countdown;
    if ((s32)(countdown << 16) <= 0) {
        ((ObjectNodeHeader *)state - 1)->flags |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}

