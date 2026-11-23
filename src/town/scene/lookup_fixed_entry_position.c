#include "town/scene/position_entries.h"

extern ScenePositionEntry D_8001770C[];
extern s16 D_80017850[];

/* Applies the Jacof house position table and checks its required flags. */
void lookup_fixed_entry_position(struct TownObjectSet *context, s32 unused, s32 selection)
{
    (void)unused;
    apply_entry_position(D_8001770C, D_80017850, context, selection);
}
