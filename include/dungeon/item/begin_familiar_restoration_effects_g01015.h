#include "shared/dungeon_item_entries.h"

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
#include "engine/node/allocation.h"
#include "engine/node.h"

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



typedef struct S_800C1A44_3 {
    u8 pad_00[0x48];
    s16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
} S_800C1A44_3;

extern u8 D_800C152C[];
extern u8 D_800DF514[];
extern u8 D_800E14A6[];
struct DungeonItemEntry;
s32 process_record_and_update_linked_state(struct DungeonItemEntry *, s32); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
void begin_mode_selected_item_action(void *object,void *unused_1,void *unused_2,void *mode);
void display_actor_item_status_message(void *, struct DungeonItemEntry *);
void display_formatted_context_message(void *);
void clear_slot_and_update_linked_state(DungeonItemEntry *slot);
extern void clear_slots_of_type(void *obj, s8 index);
extern void apply_entity_effects(void *entity);
/* extern */
/* extern */
extern s32 clipped_sprite_renderer_address(u8 *first_data, s32 link_value, struct SpriteFrameState *value_record);
extern s32 D_800C1718[4];
extern s32 familiar_restore_sprite_data[4];

/* Shared import declarations; data casts preserve each measured view. */


/* Functions defined in this translation unit. */
s32 begin_familiar_restoration_effects(void);
s32 use_item_to_draw_full_recovery_circle(void *target, struct DungeonItemEntry *action_id, s16 action_type, s32 action_arg);
void update_familiar_restoration_effect(DungeonState *state, RenderSource *render_source, u8 *effect_data);
void *create_familiar_restoration_effect(s32 tile_x, s32 tile_y, s32 z);

#endif
