#include "shared/record_ptrs.h"
#include "shared/town_root.h"
typedef signed char s8;
typedef short s16;
typedef int s32;

typedef void (*Callback)();

/* Invoke the callback and add two signed deltas to the current stats. */
void apply_signed_stat_deltas(void *stat_deltas)
{
    TownPositionState *first_stats;
    TownPositionState *second_stats;

    ((Callback)(town_scene_root->services->callback_258))(1);

    first_stats = town_scene_root->position;
    first_stats->x += *(s16 *)((s8 *)stat_deltas + 0);
    second_stats = town_scene_root->position;
    second_stats->y += *(s16 *)((s8 *)stat_deltas + 2);
}
