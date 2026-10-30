#ifndef TOWN_MENU_OBJECT_H
#define TOWN_MENU_OBJECT_H
/* Prototypes of the functions defined in src/town/menu/object/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_D_80082D58.h"
#include "shared/dungeon_effect_views.h"
#include "shared/dungeon_moving_views.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_source.h"
#include "shared/vector.h"

struct Func800A4A20Object;
struct Func800A4B70Object;
struct Func800A4B70Output;
struct S_800A21EC_0;
struct S_800A21EC_1;
struct EmoteCallbackObject;
struct S_800A7360_1;
struct S_800A7B98_2;
struct S_func_800A9F90;
struct SpriteFrameState;
struct TownObject;

/* Body finalized when its bounds check or countdown expires. */
typedef struct BoundsExpiryObject {
    /* 0x00 */ u8 pad_00[0x6C];
    /* 0x6C */ u16 timer;
    /* 0x6E */ u8 pad_6E[0x2A];
    /* 0x98 */ u8 *linked_flag;
} BoundsExpiryObject;

/* allocate_and_initialize_display_object_g01137.c */
void *allocate_and_initialize_display_object(s32 object_key, s32 payload_value, s32 payload_param, s32 payload_halfword, s32 object_param, s32 object_value);
s32 create_objects_descending_by_count(s32 object_key, s32 payload_value, s32 payload_param, s32 count);
void update_menu_node_or_retire_on_zero_state(struct Func800A4A20Object *object, s32 context, void *output);
void initialize_directional_object_state(void *object, struct S_800A21EC_1 *placement, struct S_800A21EC_0 *state);
void copy_signed_inner_value_by_flag(struct Func800A4B70Object *object, s32 unused, struct Func800A4B70Output *out);
void *create_object_with_shared_data(s32 input_first, s32 input_second, s32 input_third, s32 input_fourth);

/* create_display_object_with_callbacks.c */
void *create_display_object_with_callbacks(s32 payload_word, s32 payload_halfword);

/* create_positioned_sprite_object_g01142.c */
ObjectNodeHeader *create_positioned_sprite_object(IntVector3 *position, s32 state_value, SpriteSourceEntry *graphic_id);
void copy_indexed_motion_value_and_advance(Rec_D_80082D58 *object, EntityRec *output, s32 unused);
void invoke_emote_object_callback(struct EmoteCallbackObject *object, void *motion, s32 context);
void advance_emote_motion(struct S_800A7360_1 *object, EntityRec *motion);
void advance_position_and_handle_ground_contact(void *entity, void *motion, s32 context);

/* create_preset_sprite_object.c */
ObjectNodeHeader *create_preset_sprite_object(IntVector3 *position);

/* create_timed_effect_object.c */
void create_timed_effect_object(s32 ownerDataAddress, s32 creationParam, struct S_800A7B98_2 *sourceData);

/* decrement_callback_object_timer.c */
void decrement_callback_object_timer(struct S_func_800A9F90 *self, s32 expiry_arg);

/* finalize_object_after_check_or_expiry.c */
void finalize_object_after_check_or_expiry(BoundsExpiryObject *object, s32 check_value);

/* initialize_effect_object.c */
void initialize_effect_object(void *object, void *unused, struct SpriteFrameState *context);

/* initialize_object_items_in_reverse.c */
s32 initialize_object_items_in_reverse(struct TownObject *object, void *item_data, s32 item_count);

/* initialize_timed_scale_object.c */
void initialize_timed_scale_object(void *object, ScaleStateHalfView *state, void *context);

/* render_shaded_object_primitive.c */
void render_shaded_object_primitive(void *object, MovingPosition *coords, void *primitive);

/* swap_paired_entry_values_and_node_halfwords.c */
void swap_paired_entry_values_and_node_halfwords(u8 *state);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "shared/sprite_frame_state.h"

#endif
