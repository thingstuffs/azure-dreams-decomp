#ifndef MODULES_TOWN_OVL_5FF1D0_H
#define MODULES_TOWN_OVL_5FF1D0_H
#include "common.h"
s32 func_80017978(s32 value, s32 data);
s32 func_80018604(void);
s32 func_80017A54(s32 *table, s32 key, s32 index);
s32 *func_80017B0C(s32 *table, s32 *state, s32 key, s32 index);
extern s32 D_80018770;
extern s32 D_80018790;
extern s32 D_800188BC;
extern s32 D_8001A714;
extern s32 D_8001A854;
s32 check_inputs_after_threshold_five(s32 check_value, s32 check_data);
s32 *lookup_entry_with_special_override(s32 lookup_key, s32 unused, s32 entry_id);
s32 check_inputs_after_threshold_ten(s32 check_value, s32 check_data);
s32 *func_80016320(s32 lookup_key, s32 unused, s32 entry_id);
s32 check_inputs_after_threshold_twenty(s32 check_value, s32 check_data);

#endif
