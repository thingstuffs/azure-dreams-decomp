#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
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

extern u8 ghosh_frame_set_1[];
extern void *ghosh_scripted_actor[];
void *allocate_list_node();
s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */ /* extern */
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

typedef struct S_80173F6C_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173F6C_2;

/* Create and initialize an object with offset coordinates and directional animation. */
void create_boss_directional_animation(void) {
    s32 unused;
    SpriteFrameState *sprite;
    S_80173F6C_0 *object_state;
    ObjectPosition *model;
    ObjectNodeHeader *object;
    u16 sprite_flags;

    object = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (object != 0) {
        object_state = ((void *)object) + 0x20;
        object_state->unk_13 = MONSTER_U_BOAT;
        object_state->unk_9A = 0;
        object_state->unk_96 = 0;
        object->update_callback = &func_801730AC;
        register_node(object, project_sprite_chain);
        model = object->position;
        model->z.w.i = (u16) ((S_80173F6C_5 *)((*(void * *)&((EntityRec *)((u8 *)(&scene_object_list_anchor)))->z)))->unk_0A;
        sprite = object->sprite;
        sprite->tile_x = (u8) (reference_tile_object.tile_position.parts.tile_x + 9);
        sprite->tile_y = (u8) (reference_tile_object.tile_position.parts.tile_y - 9);
        sprite->frameTable = ghosh_frame_set_1;
        initialize_actor_sprite_and_animation(object, model, sprite, 0);
        object_state->unk_B6 = 1;
        object_state->unk_2A = 0x800;
        select_sprite_entry(sprite, (*(u8 * *)&sprite->frameTable)[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + 0x900) >> 9) & 7], 0);
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        update_map_cell_flags_with_item_limit(sprite->tile_x, sprite->tile_y,
                      (object_state->unk_1C & 0x2000) ? 0x300 : 0x3000);
        unlink_entity_node(object_state);
        object->update_callback = (s32 *) ((s32) object->update_callback | 0x80000000);
        create_boss_linked_effect(object_state, model, sprite);
        sprite_flags = sprite->flags;
        *ghosh_scripted_actor = object;
        sprite->flags = (u16) (sprite_flags | 0x80);
        retain_spawn_resource(0x18, 1);
    }
}
