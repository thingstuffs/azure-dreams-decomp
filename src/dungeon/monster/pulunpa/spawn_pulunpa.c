#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_80CBD000_0 {
    u8 pad_00[0x13];
    s8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0x6C];
    void * unk_8C;
} S_80CBD000_0;   /* work in create_actor_grid_object */

typedef struct S_80CBD000_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80CBD000_1;   /* part in create_actor_grid_object */

typedef struct S_80CBD000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80CBD000_2;   /* coord in create_actor_grid_object */

typedef struct S_80CBD000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0xA];
    s8 unk_A7;
    s8 unk_A8;
} S_80CBD000_4;   /* actor in create_actor_grid_object */

extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern void set_or_clear_actor_status_slot(void *, s32, s32);
extern s32 generate_random_value(void);
extern void initialize_actor_sprite_and_animation(void *, void *, void *, s16);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);

extern u8 entity_spawn_variant_code;
extern u8 D_80170AE0[];
extern u8 D_80170F20[];
extern u8 D_80173B98[];
extern u8 D_801762C0[];
extern u8 D_80176300[];
extern u8 D_80176320[];

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */
/* Creates Pulunpa, selecting its normal or alternate callback and sprite table from the global spawn
 * variant. */
void *create_actor_grid_object(s16 flags, s16 unused_kind_id, s16 variant, s16 unused_spawn)
{
    s8 kind_id;
    s16 spawn_value;
    s32 kind;
    s32 random;
    s16 arg0_copy;
    s32 alloc_id;
    ObjectNodeHeader *alloc_base;
    void *part;
    void *work;
    S_80CBD000_2 *coord;
    SpriteFrameState *state;
    void *actor;

    work = 0;
    alloc_id = 0x112;
    kind_id = unused_kind_id;
    alloc_base = &scene_object_list_anchor;
    spawn_value = unused_spawn;
    part = allocate_list_node(alloc_id, alloc_base);
    arg0_copy = flags;
    if (part != 0) {
        work = (u8 *)part + 0x20;
        ((S_80CBD000_0 *)work)->unk_13 = 0x15;
        register_node(part, project_sprite_chain);
        coord = ((S_80CBD000_1 *)part)->unk_08;
        kind = flags & 3;
        coord->unk_0A = spawn_value;
        state = ((S_80CBD000_1 *)part)->unk_0C;
        state->unk_25 = variant;
        actor = work;
        state->unk_24 = kind_id;

        if (kind == 1) {
            ((S_80CBD000_0 *)work)->unk_8C = D_80170F20;
            ((S_80CBD000_0 *)work)->unk_14 |= 0x6000;
            ((S_80CBD000_0 *)work)->unk_1C |= 0x6000;
            state->frameTable = D_801762C0;
        } else if (kind >= 2) {
            ((S_80CBD000_0 *)work)->unk_8C = D_80170F20;
            ((S_80CBD000_0 *)work)->unk_14 |= 0x2000;
            ((S_80CBD000_0 *)work)->unk_1C |= 0x2000;
            state->frameTable = D_801762C0;
        } else if (((flags & -4) << 16) == 0) {
            if (!(((S_80CBD000_0 *)work)->unk_14 & 0x200)) {
                random = generate_random_value();
                if (random & 1) {
                    random = generate_random_value();
                    set_or_clear_actor_status_slot(work, 1, (random & 0x3F) | 0x20);
                    state->frameTable = D_80176300;
                }
            }
            if (entity_spawn_variant_code < 10) {
                ((S_80CBD000_4 *)actor)->unk_8C = D_80170F20;
                state->frameTable = D_801762C0;
            } else {
                ((S_80CBD000_4 *)actor)->unk_A7 = 1;
                ((S_80CBD000_4 *)actor)->unk_8C = D_80173B98;
                state->frameTable = D_80176320;
            }
        } else {
            ((S_80CBD000_0 *)work)->unk_8C = D_80170F20;
            state->frameTable = D_801762C0;
        }

        ((S_80CBD000_1 *)part)->unk_10 = D_80170AE0;
        initialize_actor_sprite_and_animation(part, coord, state, arg0_copy);
        ((S_80CBD000_4 *)actor)->unk_9A = 0xFF;
        ((S_80CBD000_4 *)actor)->unk_9C = -1;
        ((S_80CBD000_4 *)actor)->unk_A8 = 0;
        try_move_actor_to_valid_position(actor, coord, state, work);
    }
    return work;
}
