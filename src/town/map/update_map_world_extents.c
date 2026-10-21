#include "common.h"
#include "shared/game_work.h"

typedef struct {
    s8 pad[0x14];
    s16 unk14;
    s16 unk16;
} TownViewState;

extern s32 town_map_column_extent[];
extern s32 town_map_row_extent[];

/* Set the two view scales from the stored shift counts. */
void update_map_world_extents(void)
{
    TownViewState *state;

    state = (TownViewState *)((u8 *)(&g_game_work));

    state = (TownViewState *)((u8 *)state + 0x1DC);

    town_map_column_extent[0] = 0x40 << state->unk14;
    town_map_row_extent[0] = 0x40 << state->unk16;
}
