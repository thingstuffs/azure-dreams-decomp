#ifndef DUNGEON_ITEM_BEGIN_FAMILIAR_RESTORATION_EFFECTS_G01015_H
#define DUNGEON_ITEM_BEGIN_FAMILIAR_RESTORATION_EFFECTS_G01015_H
/* Begin familiar restoration effects. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01015 - CL:dungeon/func_800BC2E4. */

#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/entity_action_selectors.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/dungeon_status.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    u8 pad00[0x1c];
    s32 flags;
    u8 pad20[4];
    s8 byte24;
    u8 byte25;
    u8 byte26;
    u8 byte27;
    u8 pad28[0x20];
    s16 field48;
    s16 mode;
    s16 count;
    u16 field4e;
    s16 field50;
    u8 pad52[6];
    s16 field58;
    u8 pad5a[0xa];
    s16 field64;
    u8 byte66;
    u8 pad67;
    u8 byte68;
    u8 byte69;
} DungeonState;

typedef struct {
    u8 pad00[2];
    s16 x;
    u8 pad04[2];
    s16 y;
    u8 pad08[2];
    s16 z;
} RenderSource;

typedef struct S_800C1A44_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_800C1A44_0;

typedef struct S_800C1A44_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800C1A44_1;

typedef struct S_800C1A44_3 {
    u8 pad_00[0x48];
    s16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
} S_800C1A44_3;

extern s32 has_enough_available_runtime_nodes(u32);
extern u8 D_800C152C[];
extern u8 D_800DF514[];
extern u8 D_800E14A6[];
s32 process_record_and_update_linked_state(s32, s32);
void begin_mode_selected_item_action(s8 *object, s32 unused_1, s32 unused_2, s32 mode);
void display_actor_item_status_message(void *, s32);
s32 feed_actor_restore_mp(void *, s32, s32);
void place_actor_item(void *, s32);
s32 create_five_point_effect(s16 tile_x, s16 tile_y, s16 pos_z, void *transform_data, s16 scale, s32 setup_word_5c, s32 setup_word_60);
void display_formatted_context_message(void *);
void clear_slot_and_update_linked_state(s32);
extern void clear_slots_of_type(void *obj, s8 index);
extern void apply_entity_effects(void *obj);
extern void cap_pending_actor_value_delta(void *obj);
extern void create_orbiting_color_particle(s16 x, s16 y, s16 z, s16 angle,
                          s16 height, s16 depth, s32 color, s16 offset);
void *allocate_list_node();
/* extern */
s32 register_node();
/* extern */
extern s32 D_80045C34[4];
extern s32 D_800C1718[4];
extern s32 D_800DF3C0[4];

/* Shared import declarations; data casts preserve each measured view. */


/* Functions defined in this translation unit. */
s32 begin_familiar_restoration_effects(void);
s32 use_item_to_draw_full_recovery_circle(void *target, s32 action_id, s16 action_type, s32 action_arg);
void update_familiar_restoration_effect(DungeonState *state, RenderSource *render_source, u8 *effect_data);
void *create_familiar_restoration_effect(s32 tile_x, s32 tile_y, s32 z);

#endif
