#ifndef TOWN_PLAYER_SELECTION_OBJECT_ACTION_G00534_H
#define TOWN_PLAYER_SELECTION_OBJECT_ACTION_G00534_H
/* G00534: shared declarations for selection object action. */
/* Original-file evidence (G00534): inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_80096098. */

#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/object_node.h"
#include "shared/vector.h"

typedef struct {
    u8 pad[0x18];
    s16 field_18;
    s16 field_1A;
} TownState;

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
} Unk96134Bytes;

typedef struct {
    IntVector3 pos;
    u8 padC[0xC];
    Unk96134Bytes bytes;
} Unk96134Work;

typedef struct {
    u8 pad0[0x10];
    void *unk10;
    u8 pad14[4];
    s32 unk18;
} Unk96134State;

typedef struct S_80093894_1 {
    Unk96134Bytes * unk_00;
    u8 pad_04[0x4];
    s32 unk_08;
} S_80093894_1;

/* context in handle_selection_and_create_object */
/* arg1 in handle_selection_and_create_object */
typedef struct S_80093894_3 {
    void * unk_00;
} S_80093894_3;

/* &D_80110EB8 in handle_selection_and_create_object */
typedef struct S_80093894_4 {
    u8 pad_00[0x2C];
    void * unk_2C;
} S_80093894_4;

extern TownState map_runtime_state;
extern void write_resource_command(void *ptr, s32 value);
extern void initialize_actor_movement_interaction_action(void *object, void *position, void *callback_data);
extern void set_item_selection_data_pointer(void *object, void *position, void *callback_data);
extern void *create_configured_object(void *context, IntVector3 *position, s32 mode);
extern s32 get_first_free_four_byte_entry_index_n_1_none_available(void *ptr, s32 value);
extern s32 is_unk_18_n_12_unk_1_a_between_n_37_n_41(s32 state_index);
extern s32 count_type_n_4_links_whose_state_not_n_1(void);
extern s32 find_target_byte_index_in_list(void);
extern u8 D_80088C0C[];
extern u8 D_80088C48[];
extern u8 D_80088C8C[];
extern u8 D_80088CCC[];
extern u8 D_80088D04[];
extern s32 town_motion_action_address;
extern u8 town_actor_control[];
extern s32 town_target_height_offset;
extern s32 town_record_capacities[];
extern s32 town_interaction_pending;
extern void (*town_player_action_callback)(void *object, void *position, void *callback_data);
extern u8 item_menu_scene_state[];

#include "town/player/action_initializers.h"

/* Functions defined in this translation unit. */
s32 is_town_state_pair_accepted(void);
void initialize_town_context_action(void);
void handle_selection_and_create_object(void);

#endif
