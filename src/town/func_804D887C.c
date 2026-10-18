#include "common.h"

extern s32 check_town_event_flags_clear(s32, s32);
s32 check_town_event_flags_clear_result(s32 arg0, s32 arg1) { return (check_town_event_flags_clear(arg0, arg1) != -1); }
