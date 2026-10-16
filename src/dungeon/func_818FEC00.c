/* Relink of matched dungeon/func_818F995C; every changed retail word is a paired relocation. */
#define dungeonRaiseEntityToGround func_80024400
#define D_800266BC D_80025E80
#include "shared/dungeon_effect_views.h"
#include "modules/dungeon_ovl_1918800.h"
#include "common.h"
#include "modules/dungeon_native_abi.h"
#include "shared/entity.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
extern s32 rand(void);


/* Raise the entity toward the queried ground height and set flags when the countdown expires. */
void func_80024400(PointRecord *state, EntityRec *position)
{
    u16 countdown;

    D_80025E80 = 1;
    if (position->z.w.i <
        (s16)func_800BCB04((u16)position->x.w.i, (u16)position->y.w.i,
                      (s16)(position->z.w.i + 2))) {
        position->z.v += 0x20000 + (rand() & 0xFFF);
    }

    countdown = state->brightness - 8;
    state->brightness = countdown;
    if ((s32)(countdown << 16) <= 0) {
        ((ObjectNodeHeader *)state - 1)->flags |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}

