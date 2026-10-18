#include "common.h"

extern char D_8001B14C[];
extern s32 D_8001B16C[];
extern char D_8001B9E0[];
extern char D_8001C6D0[];
extern char D_80020E44[];

extern s32 select_address_based_input(long long);
extern s32 get_local_global_table(void);
extern char *award_next_unearned_milestone(s32);

/* Select event data, using fallback data when an event handler returns null. */
char *select_event_fallback_event_handler(long long forwarded_arg, s32 event_id)
{
    s32 result_addr;

    switch (event_id - 12) {
    case 7:
        result_addr = select_address_based_input(forwarded_arg);
        D_8001B16C[0] = result_addr;
        if (result_addr == 0) {
            return D_8001B9E0;
        }
        return (char *)result_addr;
    case 6:
        result_addr = get_local_global_table();
        D_8001B16C[0] = result_addr;
        if (result_addr != 0) {
            return (char *)result_addr;
        }
        return D_80020E44;
    case 40:
    case 41:
    case 42:
        return award_next_unearned_milestone(event_id);
    case 0:
        return D_8001C6D0;
    default:
        return D_8001B14C;
    }
}
