#ifndef TOWN_PLAYER_SELECTION_OBJECT_ACTION_G00534_H
#define TOWN_PLAYER_SELECTION_OBJECT_ACTION_G00534_H
/* shared declarations for selection object action. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_80096098. */

#include "common.h"
#include "shared/town_object.h"
#include "shared/object_node.h"
#include "shared/dungeon_item_entries.h"
#include "town/shop/item_menu_scene_state_data.h"

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
} Unk96134Bytes;

typedef struct {
    Fixed1616 pos[3];
    u8 padC[0xC];
    Unk96134Bytes bytes;
} Unk96134Work;

typedef struct {
    u8 pad0[0x10];
    void *unk10;
    u8 pad14[4];
    s32 unk18;
} Unk96134State;

extern void write_resource_command(void *ptr, s32 value);
extern void initialize_actor_movement_interaction_action(void *object, void *position, void *callback_data);
#include "town/player/action_initializers.h"
extern s32 find_free_entry_index(void *ptr, s32 value);
s32 is_map_state_in_special_range(void);
extern s32 count_live_item_links(void);
extern s32 find_target_index_in_list(void);
extern u8 item_suffix_strings_ball_fruit_seed[];
extern u8 item_suffix_strings_herb[];
extern u8 D_80088C8C[];
extern u8 D_80088CCC[];
extern u8 D_80088D04[];
extern s32 town_motion_action_address;
extern u8 town_actor_control[];
extern s32 town_target_height_offset;
extern s32 town_record_capacities[];
extern s32 town_interaction_pending;
extern void (*town_player_action_callback)(void *object, void *position, void *callback_data);


/* Functions defined in this translation unit. */
s32 is_town_state_pair_accepted(void);
void initialize_town_context_action(void);
void create_selected_town_object(void);

#endif
