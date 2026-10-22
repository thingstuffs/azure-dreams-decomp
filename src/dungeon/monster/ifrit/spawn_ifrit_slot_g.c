#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef s32 M2C_UNK;

typedef struct S_80170884_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80170884_0;   /* object in build_projected_tile_packets */

typedef struct S_80170884_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80170884_1;   /* work in build_projected_tile_packets */

typedef struct S_80170884_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80170884_2;   /* part_a in build_projected_tile_packets */

typedef struct S_80170884_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80170884_4;   /* actor in build_projected_tile_packets */

extern void *allocate_list_node();
extern void register_node();
extern s32 generate_random_value(void);
extern void set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();
extern u8 D_80170A58[];
extern u8 D_80174820[];
extern u8 D_80174860[];
extern M2C_UNK D_80170E84;

extern void *build_projected_tile_packets(s16, s16, s16, s16);
/* Creates a Ifrit actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *build_projected_tile_packets(s16 mask, s16 value_24_input, s16 value_25_input, s16 value_0A_input)
{
    s32 kind;
    void *object;
    S_80170884_2 *part_a;
    SpriteFrameState *part_b;
    S_80170884_1 *work;
    S_80170884_4 *actor;
    s32 value_14;
    s32 value_1C;
    s8 value_24;
    s16 value_0A;
    s8 value_25;

    work = 0;
    value_24 = value_24_input;
    value_0A = value_0A_input;
    value_25 = value_25_input;
    object = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (object != 0) {
        work = (u8 *)object + 0x20;
        ((S_80170884_0 *)object)->unk_10 = D_80170A58;
        work->unk_13 = 5;
        register_node(object, project_sprite_chain);

        part_a = ((S_80170884_0 *)object)->unk_08;
        part_a->unk_0A = value_0A;
        part_b = ((S_80170884_0 *)object)->unk_0C;
        kind = mask & 3;
        part_b->unk_25 = value_25;
        actor = work;
        part_b->frameTable = D_80174820;
        part_b->unk_24 = value_24;

        if (kind == 1) {
            value_14 = work->unk_14 | 0x6000;
            value_1C = work->unk_1C | 0x6000;
            work->unk_14 = value_14;
            work->unk_1C = value_1C;
        } else if (kind >= 2) {
            value_14 = work->unk_14 | 0x2000;
            value_1C = work->unk_1C | 0x2000;
            work->unk_14 = value_14;
            work->unk_1C = value_1C;
        } else if (((mask & ~3) << 16) == 0) {
            if (!(work->unk_14 & 0x200)) {
                value_14 = generate_random_value();
                if (value_14 & 1) {
                    work->unk_1C |= 0x200;
                    set_or_clear_actor_status_slot(work, 1,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = D_80174860;
                }
            }
        }
        initialize_actor_sprite_and_animation(((void *)(object)), part_a, part_b, mask);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_80170E84;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
