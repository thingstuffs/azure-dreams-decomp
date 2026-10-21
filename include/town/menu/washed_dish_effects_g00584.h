#ifndef TOWN_MENU_WASHED_DISH_EFFECTS_G00584_H
#define TOWN_MENU_WASHED_DISH_EFFECTS_G00584_H
/* inferred-strong G00584: washed_dish_effects_g00584; shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D0E44, PD:town/engine:800F8A70. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/object_flags.h"

typedef struct {
    s32 words[3];
} TownRecord;

typedef struct {
    s32 value;
    s32 pad[2];
} D800D0E44;

void register_node_if_unregistered(void *, s32);
extern void project_sprite_chain();
extern s32 classify_object_against_bounds(void *object, void *position_data);
extern void unlink_node_if_registered(void *object);
extern s32 D_800D0E40[3];

extern s32 dish_counter;
extern TownRecord D_800F8A70[];

/* Functions defined in this translation unit. */
void initialize_timed_resource_object(void *object, s32 unused, void *context);
void finalize_object_or_select_town_record(void *object, void *check_context, void *record_holder);
s32 washed_dish_suu_set(s32 new_count);
s32 washed_dish_suu_inc(void);

#endif
