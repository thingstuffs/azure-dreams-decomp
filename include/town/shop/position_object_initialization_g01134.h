#ifndef TOWN_SHOP_POSITION_OBJECT_INITIALIZATION_G01134_H
#define TOWN_SHOP_POSITION_OBJECT_INITIALIZATION_G01134_H
/* position object initialization g01134. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01134 - CL:town/func_800A2ACC, CL:town/func_800A2B1C, CL:town/func_800A2CA4, CL:town/func_800A2D54, PD:town/engine:80100AA0. */

/* Position object initialization (G00563). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A2ACC. */
/* Position object initialization declarations (G00563). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A2ACC. */
#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "town/menu/window.h"
#include "shared/dungeon_moving_views.h"
#include "shared/dungeon_projectile_views.h"
#include "m2c_compat.h"

typedef struct S_800A022C_0 {
    u8 pad_00[0x15];
    s8 unk_15;
} S_800A022C_0;

/* arg1 in initialize_the_active_flag_install_handler */
typedef struct S_800A022C_2 {
    u8 pad_00[0x50];
    s32 * unk_50;
} S_800A022C_2;

/* arg1 in create_an_position_initializes_graphics_state */
typedef struct S_800A027C_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800A027C_3;

typedef struct S_800A027C_4 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0x38];
    s32 unk_48;
    u8 unk_4C;
    u8 unk_4D;
    u8 unk_4E;
    u8 unk_4F;
    u8 pad_50[0x43];
    s8 unk_93;
    u8 pad_94[0x4];
    s32 unk_98;
} S_800A027C_4;

typedef struct S_800A027C_5 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S_800A027C_5;

typedef union {
    struct {
        u8 unk0;
        u8 unk1;
        u8 unk2;
        u8 unk3;
    } bytes;
    u32 word;
} TownRecord;

/* extern */
typedef struct S_800A0504_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800A0504_0;

typedef struct TownLink TownLink;

struct TownLink {
    u8 pad_00[4];
    TownLink *next;
    u8 pad_08[0xC];
    u8 type;
    u8 pad_15[0x7F];
    s8 state;
    u8 pad_95[3];
    void *object;
};

void add_motion_deltas_to_position(ObjectPosition *motion);
/* extern */
extern void *D_8009BC44;
void *allocate_list_node();
/* extern */
s32 lookup_item_category_mapped_value(s32 category_index, s32 record_index);
/* extern */
void configure_the_set_mode_n_4();
/* extern */
void initialize_optional_object_state();
/* extern */
extern s32 item_effect_descriptor;
void dispatch_object_or_switch_alternate_state(func_800A075C_S_func_8009DEBC_0 *object, s32 source, s32 context);
extern u8 D_800D073C[];
extern u8 D_800D0754[];
extern u8 D_800D076C[];
extern TownRecord shop_record_queue[20];
extern s32 town_actor_control;
extern s32 is_unk_18_n_12_unk_1_a_between_n_37_n_41(void);

/* Functions defined in this translation unit. */
void initialize_the_active_flag_install_handler(S_800A022C_2 *object, S_800A022C_0 *state, ObjectPosition *record, void *unused_render);
void *create_an_position_initializes_graphics_state(S_800A027C_5 *config, MovingPosition *position);
void clear_entry_table(void);
void handle_inserts_first_free_slot_discarding_first_full(TownRecord *record);
s32 *get_address_global_80100_aa_0(void);
void handle_shift_entries_left_until_free_entry_limit_clear_tail(void);
void run_the_follow_up_action_has_eligible_type_passes_check(s32 check_value);
void process_unlinked_type_four_entries(void);

#endif
