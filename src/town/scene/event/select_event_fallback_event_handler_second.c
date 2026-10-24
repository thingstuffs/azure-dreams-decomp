#include "common.h"
#include "town/scene/milestone_rewards.h"

extern char scene_string_fallback[];
extern s32 scene_event_results[];
extern char D_8001B9E0[];
extern char event_string_fallback[];
extern char D_80020E44[];

extern s32 select_address_based_input(long long);
extern s32 get_local_global_table(void);


/* Select event data, using fallback data when an event handler returns null. */
char *select_event_fallback_event_handler(long long forwarded_arg, s32 event_id)
{
    s32 result_addr;

    switch (event_id - 12) {
    case 7:
        result_addr = select_address_based_input(forwarded_arg);
        scene_event_results[0] = result_addr;
        if (result_addr == 0) {
            return D_8001B9E0;
        }
        return (char *)result_addr;
    case 6:
        result_addr = get_local_global_table();
        scene_event_results[0] = result_addr;
        if (result_addr != 0) {
            return (char *)result_addr;
        }
        return D_80020E44;
    case 40:
    case 41:
    case 42:
        return award_next_unearned_milestone(event_id);
    case 0:
        return event_string_fallback;
    default:
        return scene_string_fallback;
    }
}
