#ifndef TOWN_SHOP_POSITION_H
#define TOWN_SHOP_POSITION_H
/* Prototypes of the functions defined in src/town/shop/position/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_D_800CFCB4.h"
#include "shared/town_object.h"
#include "records/Rec_func_8009EE9C_arg0.h"
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
struct ShopWindow;
void position_shop_child_elements(struct ShopWindow *window);

/* position_shop_row_widgets.c */
void position_shop_row_widgets(struct ShopWindow *menu);

/* set_display_entry_text_and_position.c */
void set_display_entry_text_and_position(struct S_800B5264_0 *entry, s32 text, s32 text_style, s16 x, s32 y);

/* set_monster_status_display_position.c */
void set_monster_status_display_position(struct S_800B6C94_0 *object, s16 x, s16 y);

/* update_item_menu_page_bounds.c */
void update_item_menu_page_bounds(ItemMenuObject *obj);

/* update_position_displacement_dispatch_active_entity_handler_g01131.c */
void bob_entity_and_dispatch_handler(Rec_func_8009EE9C_arg0 *entity, s32 entity_id, struct S_8009EE9C_0 *motion, struct SpriteFrameState *context);
void move_entity_toward_view_reference(void *entity, s32 context, ObjectPosition *motion, s32 mode);
void start_entity_bob(void *entity, void *state, void *transform, s32 unused);
void start_slot_entity_move_toward_view(Rec_func_8009EE9C_arg0 *entity, struct S_8009F1C0_0 *action, void *unused_motion, struct SpriteFrameState *unused_context);
s32 get_target_itemp(void);
void bob_entity_and_wait_for_event(void *state, s32 event_id, DelayMotionZ *target, struct SpriteFrameState *context);
void jitter_and_pulse_entity_scale(Rec_D_800CFCB4 *state, s32 context, EntityRec *position, struct S_8009F374_2 *scale);
void unlink_entity_and_set_bob_handler(Rec_func_8009EE9C_arg0 *record, s32 value, void *unused_motion, struct SpriteFrameState *unused_context);
void snapshot_entity_slot_and_start_jitter(TownObjectRecord *entity, s32 unused_arg1, s32 unused_arg2, void *context);

#endif
