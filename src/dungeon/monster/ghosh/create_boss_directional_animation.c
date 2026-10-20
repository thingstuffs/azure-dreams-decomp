#include "common.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/entity.h"

typedef struct S_func_8132B8AC_0 S_func_8132B8AC_0;
typedef struct S_func_8132B8AC_1 S_func_8132B8AC_1;
typedef struct S_func_8132B8AC_2 S_func_8132B8AC_2;


typedef struct S_80173F6C_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173F6C_5;   /* ((Rec_D_800E3D7C *)D_80083498)->unk_08.at00_pv.v in create_boss_directional_animation */


extern u8 D_80174C84[];
extern void *D_80174CE0[];
void *allocate_list_node();
s32 register_node(); /* extern */
void unlink_entity_node(); /* extern */
void update_map_cell_flags_with_item_limit(); /* extern */
s32 retain_spawn_resource(); /* extern */
void initialize_actor_sprite_and_animation(); /* extern */
void select_sprite_entry(); /* extern */
void create_boss_linked_effect(); /* extern */
void func_801730AC(S_func_8132B8AC_0 *actor, S_func_8132B8AC_1 *motion, S_func_8132B8AC_2 *sprite);

typedef struct S_80173F6C_0 {
    u8 pad_00[0x13];
    s8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x6A];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    u8 pad_9B[0x1B];
    s8 unk_B6;
} S_80173F6C_0;

typedef struct S_80173F6C_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80173F6C_1;

typedef struct S_80173F6C_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173F6C_2;

typedef struct S_80173F6C_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80173F6C_3;

/* Create and initialize an object with offset coordinates and directional animation. */
void create_boss_directional_animation(void) {
    s32 unused;
    S_80173F6C_3 *sprite;
    S_80173F6C_0 *object_state;
    S_80173F6C_2 *model;
    void *object;
    u16 sprite_flags;

    object = allocate_list_node(0x112, ((u8 *)(&D_80083498)));
    if (object != 0) {
        object_state = object + 0x20;
        object_state->unk_13 = 0x18;
        object_state->unk_9A = 0;
        object_state->unk_96 = 0;
        ((S_80173F6C_1 *)object)->unk_10 = &func_801730AC;
        register_node(object, project_sprite_chain);
        model = ((S_80173F6C_1 *)object)->unk_08;
        model->unk_0A = (u16) ((S_80173F6C_5 *)((*(void * *)&((EntityRec *)((u8 *)(&D_80083498)))->z)))->unk_0A;
        sprite = ((S_80173F6C_1 *)object)->unk_0C;
        sprite->unk_24 = (u8) (D_80082E80.tileX + 9);
        sprite->unk_25 = (u8) (D_80082E80.tileY - 9);
        sprite->unk_2C = D_80174C84;
        initialize_actor_sprite_and_animation(object, model, sprite, 0);
        object_state->unk_B6 = 1;
        object_state->unk_2A = 0x800;
        select_sprite_entry(sprite, sprite->unk_2C[((s32) (g_game_work.view.viewAngle + 0x900) >> 9) & 7], 0);
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        update_map_cell_flags_with_item_limit(sprite->unk_24, sprite->unk_25,
                      (object_state->unk_1C & 0x2000) ? 0x300 : 0x3000);
        unlink_entity_node(object_state);
        ((S_80173F6C_1 *)object)->unk_10 = (s32 *) ((s32) ((S_80173F6C_1 *)object)->unk_10 | 0x80000000);
        create_boss_linked_effect(object_state, model, sprite);
        sprite_flags = sprite->unk_14;
        *D_80174CE0 = object;
        sprite->unk_14 = (u16) (sprite_flags | 0x80);
        retain_spawn_resource(0x18, 1);
    }
}
