#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern void set_or_clear_actor_status_slot(void *, s32, s32);
extern s32 generate_random_value();
extern void initialize_actor_sprite_and_animation(void *, void *, void *, s16);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);
extern void update_actor_callbacks_and_ground(void);
extern void update_actor_animation_and_behavior(void);

extern u8 D_80175E40[];
extern u8 D_80175EA0[];

typedef struct S_801708B4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_801708B4_0;   /* entity in create_grid_position_entity */

typedef struct S_801708B4_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
} S_801708B4_1;   /* inner in create_grid_position_entity */

typedef struct S_801708B4_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_801708B4_2;   /* part_a in create_grid_position_entity */

typedef struct S_801708B4_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_801708B4_4;   /* result in create_grid_position_entity */

/* Create an entity at the given grid position and initialize its behavior and spawn flags. */
/* Creates Kewne with default frames at D_80175E40, applies spawn flags, and attempts valid tile placement. */
void *create_grid_position_entity(s16 spawn_flags, s16 grid_x, s16 grid_y, s16 height)
{
    void *entity;
    S_801708B4_2 *position;
    SpriteFrameState *placement;
    S_801708B4_4 *actor;
    s32 spawn_mode;
    s16 saved_flags;
    u8 *entity_data;
    s8 saved_x;
    register s16 saved_height;
    s8 saved_y;

    saved_flags = spawn_flags;
    entity_data = 0;
    saved_x = grid_x;
    saved_height = height;
    saved_y = grid_y;
    entity = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (entity != 0) {
        entity_data = (u8 *)entity + 0x20;
        ((S_801708B4_0 *)entity)->unk_10 = update_actor_callbacks_and_ground;
        ((S_801708B4_1 *)entity_data)->unk_13 = MONSTER_KEWNE;
        register_node(entity, project_sprite_chain);

        position = ((S_801708B4_0 *)entity)->unk_08;
        position->unk_0A = saved_height;
        placement = ((S_801708B4_0 *)entity)->unk_0C;
        spawn_mode = spawn_flags & 3;
        placement->unk_25 = saved_y;
        actor = entity_data;
        placement->frameTable = D_80175E40;
        placement->unk_24 = saved_x;

        if (spawn_mode == 1) {
            ((S_801708B4_1 *)entity_data)->unk_14 |= 0x6000;
            ((S_801708B4_1 *)entity_data)->unk_1C |= 0x6000;
        } else if (spawn_mode >= 2) {
            ((S_801708B4_1 *)entity_data)->unk_14 |= 0x2000;
            ((S_801708B4_1 *)entity_data)->unk_1C |= 0x2000;
        } else if (((spawn_flags & -4) << 16) == 0) {
            if (!(((S_801708B4_1 *)entity_data)->unk_14 & 0x200)) {
                void *call_entity = entity;
                void *call_position = position;

                if (generate_random_value() & 1) {
                    s32 random_value;
                    void *second_entity = entity;

                    random_value = generate_random_value();

                    set_or_clear_actor_status_slot(entity_data, 1, (random_value & 0x3F) | 0x20);
                    placement->frameTable = D_80175EA0;
                }
            }
        }

        initialize_actor_sprite_and_animation(entity, position, placement, saved_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = update_actor_animation_and_behavior;
        ((S_801708B4_1 *)entity_data)->unk_1C |= 0x40000;
        actor->unk_92 = -0x20;
        try_move_actor_to_valid_position(actor, position, placement, entity_data);
    }
    return entity_data;
}
