#include "slus/data.h"
#include "slus/event_string_fallback_data.h"
#include "common.h"
#include "town/scene/milestone_rewards.h"
#include "town/scene.h"

extern u8 scene_choice_text[];
extern u8 D_800227FB[];


/* Selects a data pointer by ID, using default data for unhandled IDs. */
void *select_scene_text_by_id(s32 unused_0, s32 unused_1, s32 data_id)
{
    switch (data_id - 12) {
    case 7:
        return scene_choice_text;
    case 6:
        return D_800227FB;
    case 0:
        return event_string_fallback;
    case 40:
    case 41:
    case 42:
        return award_next_unearned_milestone(data_id);
    default:
        return scene_string_fallback;
    }
}
