#include "dungeon/monster/golem/spawn_api.h"
#include "shared/monster_ids.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"



typedef struct S_801708BC_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_801708BC_1;   /* result in func_801708BC */

typedef struct S_801708BC_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_801708BC_4;   /* result_copy in func_801708BC */

extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern s32 generate_random_value(void);
extern void set_or_clear_actor_status_slot(void *, s32, s32);
extern void initialize_actor_sprite_and_animation(void *, void *, void *, s16);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);

extern u8 golem_particle_update_address[];
extern s32 golem_action_continuation_address;
extern u8 golem_direction_frames[];
extern u8 golem_alt_direction_frames[];

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
/* Creates Golem with default frames at D_80175F10, applies spawn flags, and attempts valid tile placement. */
void *create_golem_actor(s16 spawn_flags, s32 tile_x, s32 tile_y, s32 spawn_height)
{
    void *result = 0;
    ObjectNodeHeader *object;
    ObjectPosition *part0;
    SpriteFrameState *part1;
    S_801708BC_4 *result_copy;
    s16 saved_tile_x;
    s32 saved_height;
    s16 saved_tile_y;
    s16 flags_copy;
    s32 kind;

    saved_tile_x = tile_x;
    saved_height = spawn_height;
    saved_tile_y = tile_y;
    object = allocate_list_node(0x112, ((s32 *)&scene_object_list_anchor.next));
    flags_copy = spawn_flags;
    if (object != 0) {
        result = (u8 *)object + 0x20;
        object->update_callback = golem_particle_update_address;
        ((S_801708BC_1 *)result)->unk_13 = MONSTER_GOLEM;
        register_node(object, project_sprite_chain);

        part0 = object->position;
        part0->z.w.i = saved_height;
        part1 = object->sprite;
        kind = spawn_flags & 3;
        part1->tile_y = saved_tile_y;
        result_copy = result;
        part1->frameTable = golem_direction_frames;
        part1->tile_x = saved_tile_x;

        if (kind == 1) {
            ((S_801708BC_1 *)result)->unk_14 |= 0x6000;
            ((S_801708BC_1 *)result)->unk_1C |= 0x6000;
        } else if (kind >= 2) {
            ((S_801708BC_1 *)result)->unk_14 |= 0x2000;
            ((S_801708BC_1 *)result)->unk_1C |= 0x2000;
        } else if (((spawn_flags & -4) << 16) == 0 &&
                   (((S_801708BC_1 *)result)->unk_14 & 0x200) == 0) {
            if ((generate_random_value() & 1) != 0) {
                set_or_clear_actor_status_slot(result, 1, (generate_random_value() & 0x3F) | 0x20);
                part1->frameTable = golem_alt_direction_frames;
            }
        }

        initialize_actor_sprite_and_animation(object, part0, part1, (s16)flags_copy);
        result_copy->unk_9A = 0xFF;
        result_copy->unk_9C = -1;
        result_copy->unk_8C = &golem_action_continuation_address;
        try_move_actor_to_valid_position(result_copy, part0, part1, result);
    }
    return result;
}
