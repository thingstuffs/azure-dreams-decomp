#ifndef TOWN_SHOP_POSITION_OBJECT_INITIALIZATION_G00563_H
#define TOWN_SHOP_POSITION_OBJECT_INITIALIZATION_G00563_H
/* Position object initialization declarations (G00563). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A2ACC. */

#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "town/menu/window.h"
#include "shared/dungeon_moving_views.h"
#include "shared/dungeon_projectile_views.h"
#include "engine/menu.h"

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

void add_motion_deltas_to_position();
/* extern */
extern void *D_8009BC44;
void *allocate_list_node();
/* extern */
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

/* Functions defined in this translation unit. */
void initialize_the_active_flag_install_handler(S_800A022C_2 *object, S_800A022C_0 *state, ObjectPosition *record, void *unused_render);
void *create_an_position_initializes_graphics_state(S_800A027C_5 *config, MovingPosition *position);

#endif
