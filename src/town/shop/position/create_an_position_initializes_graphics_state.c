#include "common.h"
#include "shared/object_node.h"

void *allocate_list_node();            /* extern */
s32 lookup_item_category_mapped_value();                          /* extern */
void configure_the_set_mode_n_4();   /* extern */
void initialize_optional_object_state(); /* extern */
void initialize_the_active_flag_install_handler(); /* extern */
extern s32 D_8006E240;
#include "town/menu/window.h"
#include "shared/dungeon_moving_views.h"
#include "shared/dungeon_projectile_views.h"
void dispatch_object_or_switch_alternate_state(func_800A075C_S_func_8009DEBC_0 *object, s32 source, s32 context);
extern u8 D_800D073C[];
extern u8 D_800D0754[];
extern u8 D_800D076C[];


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
} S_800A027C_5;   /* arg0 in create_an_position_initializes_graphics_state */

/* Creates an object at the supplied position and initializes its graphics and state. */
void *create_an_position_initializes_graphics_state(S_800A027C_5 *config, MovingPosition *position) {
    u8 type;
    S_800A027C_4 *state;
    S_800A027C_3 *render;
    MovingPosition *coords;
    void *object;

    object = allocate_list_node(0x136, ((s32 *)&D_80083498.next));
    if (object == 0) {
        return 0;
    }
    coords = ((ProjectileObject *)object)->unk_08;
    render = ((ProjectileObject *)object)->unk_0C;
    coords->unk_02 = (u16) position->unk_02;
    coords->unk_06 = (u16) position->unk_06;
    state = object + 0x20;
    coords->unk_0A = (u16) position->unk_0A;
    render->unk_1E = 0x1000;
    render->unk_1C = 0x1000;
    render->unk_0C = 0x808080;
    state->unk_48 = 0;
    state->unk_98 = 0;
    state->unk_93 = 0;
    state->unk_4C = (u8) config->unk_00;
    state->unk_4D = (u8) config->unk_01;
    state->unk_4E = (u8) config->unk_02;
    state->unk_4F = (u8) config->unk_03;
    configure_the_set_mode_n_4(state, coords, &D_800D073C);
    initialize_optional_object_state(state, coords, render, &D_800D076C);
    type = state->unk_4D;
    if (type == 0x12) {
        state->unk_0C = &D_800D0754;
    }
    if (type == 0x12 && type == state->unk_4D) {
        render->unk_08 = (s32) &D_8006E240;
    } else {
        render->unk_08 = lookup_item_category_mapped_value(state->unk_4D, state->unk_4C);
    }
    ((ProjectileObject *)object)->unk_10 = &dispatch_object_or_switch_alternate_state;
    initialize_the_active_flag_install_handler(state, state, coords, render);

    return object;
}
