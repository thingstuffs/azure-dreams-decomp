#include "shared/entity.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/monster/ghosh.h"
#include "engine/graphics.h"

typedef struct S_80172B00_0 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x68];
    u16 unk_94;
    s16 unk_96;
    u8 pad_98[0x14];
    s32 unk_AC;
} S_80172B00_0;

typedef struct S_80172B00_2 {
    u8 pad_00[0x2A];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x84];
    u8 unk_B0;
} S_80172B00_2;   /* arg0 in create_boss_child_effect */

   /* arg1 in create_boss_child_effect */

typedef struct S_80172B00_7 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_80172B00_7;   /* arg2 in create_boss_child_effect */

void *allocate_list_node();                  /* extern */
s32 register_node(ObjectNodeHeader *entry, void *registration_id); /* extern */
void * create_tracked_effect(); /* extern */
extern s8 view_direction_depth_biases[];
void D_80172610(void *actor_data, void *output_data, void *context_data);
extern u8 ghosh_frame_set_10[];

typedef struct {
    s32 words[4];
} CopyBlock;

typedef struct {
    u32 words[12];
} Copy48;

/* Creates a child effect with copied position and sprite data and direction-dependent appearance. */
void create_boss_child_effect(void *parent_data, MovingPosition *source_pos, void *sprite_template) {
    s32 parent_object;
    SpriteFrameState *sprite;
    void *effect_data;
    ObjectNodeHeader *effect_object;
    ObjectPosition *effect_pos;
    CopyBlock *copy_dst;
    CopyBlock *copy_src;
    u16 template_1c;
    s32 direction_index;
    s32 parent_angle;
    s16 setup_mode;

    parent_object = parent_data - 0x20;
    effect_object = allocate_list_node(0x112, parent_object);
    effect_data = ((void *)effect_object) + 0x20;
    if (effect_object != NULL) {
        ((S_80172B00_0 *)effect_data)->unk_96 = 0x78;
        effect_object->update_callback = &D_80172610;
        ((S_80172B00_0 *)effect_data)->unk_AC = parent_object;
        ((S_80172B00_0 *)effect_data)->unk_94 = (u16) ((S_80172B00_2 *)parent_data)->unk_2A.s;
        copy_src = (CopyBlock *) sprite_template;
        ((S_80172B00_0 *)effect_data)->unk_2A = (u16) ((S_80172B00_2 *)parent_data)->unk_2A.s;
        sprite = effect_object->sprite;
        copy_dst = (CopyBlock *) sprite;
        *(Copy48 *)copy_dst = *(Copy48 *)copy_src;
        register_node(effect_object, project_sprite_chain);
        sprite->frameTable = ghosh_frame_set_10;
        select_sprite_entry(sprite, ghosh_frame_set_10[((s32) (g_game_work.view.camera_rotation.parts.viewAngle
            + (s16) ((S_80172B00_2 *)parent_data)->unk_2A.s + 0x100) >> 9) & 7], 0);
        effect_pos = effect_object->position;
        effect_pos->x.w.i = (u16) source_pos->x;
        effect_pos->y.w.i = (u16) source_pos->y;
        effect_pos->z.w.i = (u16) source_pos->z;
        template_1c = ((S_80172B00_7 *)sprite_template)->unk_1C;
        sprite->scale_x = template_1c;
        sprite->scale_y = (u16) ((S_80172B00_7 *)sprite_template)->unk_1E;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        direction_index = g_game_work.view.camera_rotation.parts.viewAngle;
        parent_angle = ((S_80172B00_2 *)parent_data)->unk_2A.u;
        setup_mode = 0;
        direction_index += parent_angle;
        direction_index += 0x100;
        direction_index >>= 9;
        direction_index &= 7;
        sprite->depth_bias = (s16) (view_direction_depth_biases[direction_index] * 4);
        ((S_80172B00_2 *)parent_data)->unk_B0 = (u8) (((S_80172B00_2 *)parent_data)->unk_B0 + 1);
        create_tracked_effect(effect_object, setup_mode, ((void *)sprite) + 0x2C, effect_data + 0x2A);
    }
}
