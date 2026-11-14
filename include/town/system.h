#ifndef TOWN_SYSTEM_H
#define TOWN_SYSTEM_H
/* Prototypes of the functions defined in src/town/system/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/town_object.h"
#include "records/Rec_func_800AD7F8_arg0.h"

struct KeimaState;

/* create_paletted_position_object.c */
void create_paletted_position_object(s32 signed_position, s32 palette_index, struct KeimaState *settings, s32 field_28_value);

/* create_user_data_object.c */
void create_user_data_object(s32 user_data);

/* flag_test_conditions.c */
s32 check_all_flags_set(s16 *flag_ids);

/* flag_test_pair_actions.c */
s32 process_flag_test_record(u32 records, s32 condition_arg, u32 context, s32 record_selector);

/* person_idle_dispatch.c */
void advance_object_animation_when_idle(TownObjectRecord *object, void *callback_arg, s32 unused_a, s32 unused_b);
void clear_object_status_and_dispatch_target(void *object, void *target, int value, s16 flags);

/* person_timers.c */
void run_setup_on_timer_expiry(TownObjectRecord *object, void *callback_arg_1, void *callback_arg_2);
void func_800C3B7C(TownObjectRecord *object, void *callback_arg_1, void *callback_arg_2);
void install_handler_on_timer_expiry(TownObjectRecord *object);
void func_800C3BB8(TownObjectRecord *object);

/* randomize_keima_payout_factors.c */
s32 randomize_keima_payout_factors(void);

/* play_overlay_height_sound.c */
void play_overlay_height_sound(void);

/* shop_entry_flags.c */
void toggle_selected_entry_flag(Rec_func_800AD7F8_arg0 *state);
s32 sum_flagged_entry_prices(u8 *entry, s32 mode);

/* shop_value_dispatch.c */
void buy_flagged_entries(void *value);
void sell_flagged_entries(u8 *base_value);

#endif
