#ifndef TOWN_SHOP_POSITION_H
#define TOWN_SHOP_POSITION_H
/* Prototypes of the functions defined in src/town/shop/position/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_D_800CFCB4.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_func_8009EE9C_arg0.h"
#include "records/Rec_func_800B0C68_arg0.h"
#include "shared/dungeon_delay_views.h"
#include "shared/entity.h"
#include "shared/item_menu.h"

struct S_8009EE9C_0;
struct S_8009F1C0_0;
struct S_8009F374_2;
struct S_800B5264_0;
struct S_800B6C94_0;
struct ShopWindow;
struct SpriteFrameState;

/* position_item_menu_side_indicators.c */
void position_item_menu_side_indicators(ItemMenuPart **parts);

/* position_shop_child_elements.c */
void position_shop_child_elements(Rec_func_800B0C68_arg0 *parentObject);

/* position_shop_row_widgets.c */
void position_shop_row_widgets(struct ShopWindow *menu);

/* set_display_entry_text_and_position.c */
void set_display_entry_text_and_position(struct S_800B5264_0 *entry, s32 text, s32 text_style, s16 x, s32 y);

/* set_monster_status_display_position.c */
void set_monster_status_display_position(struct S_800B6C94_0 *object, s16 x, s16 y);

/* update_item_menu_page_bounds.c */
void update_item_menu_page_bounds(ItemMenuObject *obj);

/* update_position_displacement_dispatch_active_entity_handler_g01131.c */
void update_position_displacement_dispatch_active_entity_handler(Rec_func_8009EE9C_arg0 *entity, s32 entity_id, struct S_8009EE9C_0 *motion, struct SpriteFrameState *context);
void update_motion_toward_target_resolves_entity_countdown_expires(void *entity, s32 context, ObjectPosition *motion, s32 mode);
void initialize_entity_flags_transform_type_dependent_variant(void *entity, void *state, void *transform, s32 unused);
void initialize_the_entity_s_action_copy_selected_state_hex_13(Rec_func_8009EE9C_arg0 *entity, struct S_8009F1C0_0 *action, void *unused_motion, struct SpriteFrameState *unused_context);
s32 get_target_itemp(void);
void update_the_target_offset_advance_phase_handle_active_event(void *state, s32 event_id, DelayMotionZ *target, struct SpriteFrameState *context);
void handle_jitter_position_pulse_scale_until_countdown_expires(Rec_D_800CFCB4 *state, s32 context, EntityRec *position, struct S_8009F374_2 *scale);
void call_callee_80033_d_08_set_handler(Rec_func_8009EE9C_arg0 *record, s32 value, void *unused_motion, struct SpriteFrameState *unused_context);
void initialize_the_town_entity_synchronize_slot_state(Rec_func_80094268_arg0 *entity, s32 unused_arg1, s32 unused_arg2, void *context);

#endif
