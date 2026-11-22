#include "shared/sprite_frame_state.h"
#ifndef TOWN_MENU_H
#define TOWN_MENU_H
struct SpriteFrameState;
struct Rec_D_80100B70;

#include "common.h"
struct DoorTransitionEffect;


/* draw_vram_glyph_text.c */
void draw_vram_glyph_text(u8 *text, s16 start_x, s16 y);


/* draw_cached_catalog_text.c */
void draw_cached_catalog_text(u8 *text, s16 x, s16 y);

struct ItemMenuObject;
struct ItemMenuStateNode;
void initialize_item_menu_state(struct ItemMenuObject *object, struct ItemMenuStateNode *owner);

struct MenuResourceOwner;
s32 load_menu_display_resource(struct MenuResourceOwner *, s32);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct func_8009F880_S_8009CFE0_0;
struct ObjectPosition;
s32 classify_object_against_bounds(struct func_8009F880_S_8009CFE0_0 *object, struct ObjectPosition *position);

void initialize_sprite_defaults(void *body, SpriteFrameState *sprite, s32 mesh_index);

void create_item_category_effect(s32 index, s32 kind);

struct MenuDisplay;
void func_800B47BC(struct MenuDisplay *object);

#include "town/shop/storage_menu.h"
void update_paged_menu_record(AlternateStorageOwner *record);

struct ObjectPosition;
struct S_800A2A18_1;
s32 test_three_axis_box_overlap(struct S_800A2A18_1 *box, struct ObjectPosition *offset);

void create_entry_builder_controller(void);
struct TownRectangle;
extern struct TownRectangle *town_script_state_slots[];
struct TownRectangle **reset_script_rect_list(void);
struct TownRectangle **append_scaled_rect_to_script_list(s32 x, s32 y, s32 width, s32 height,
                                                        struct TownRectangle *rectangle);

#include "records/Rec_D_80082D58.h"
s32 classify_record_by_state_and_position(Rec_D_80082D58 *record, struct ObjectPosition *position);

#include "shared/town_object.h"
#include "shared/entity.h"
struct DungeonItemEntry;
struct ObjectNodeHeader *create_selection_entry_object(struct DungeonItemEntry *entry, Fixed1616 source_position[3], s32 alternate_callback);
s16 *get_cached_catalog_glyph(s16 char_code);
struct CardDevSlotDetails;
struct ObjectNodeHeader;
void initialize_menu_overlay_objects(struct CardDevSlotDetails *panel, struct ObjectNodeHeader *owner);
void initialize_randomized_scale_timer(TownObjectRecord *object, ObjectPosition *unused_position, SpriteFrameState *unused_sprite);
void update_opposing_scale_effect(TownObjectRecord *state, ObjectPosition *position, SpriteFrameState *scale, s32 unused_3);
u8 is_catalog_entry_available(s32 index);
void no_op_callback_a(struct DoorTransitionEffect *unused_effect, struct ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);
s32 store_target_record_value_and_kind(void *unused_arg0, void *unused_arg1, void *unused_arg2, void *unused_arg3);

void advance_effect_ramp_and_spawn_pair(void *updateState, s32 unused1, s32 unused2, void *accumulatorState);
void draw_random_tinted_quad_pair(struct DoorTransitionEffect *effect);
void draw_segmented_menu_ring(struct ObjectPosition *center_source, s32 radius_a, s32 radius_b, s16 segment_arg);
void initialize_catalog_entry_packets(void);
void initialize_catalog_glyph_cache(void);
void layout_catalog_entry_grid(void);
void reset_linked_value_records(void);
void store_cached_value_at_pointer(void);

struct CatalogDisplay;
void register_sprite_when_timer_expires(TownObjectRecord *record);
void initialize_catalog_slot_records(void);
void run_record_handler_if_active(TownObjectRecord *record, ObjectPosition *position, SpriteFrameState *sprite);
void update_catalog_scroll_availability(struct CatalogDisplay *entry);
void update_scale_effect_and_advance(TownObjectRecord *state, ObjectPosition *position, SpriteFrameState *scale);

#endif
