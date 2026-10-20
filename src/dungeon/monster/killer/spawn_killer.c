#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_80FDB000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80FDB000_0;   /* created in spawn_killer */

typedef struct S_80FDB000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
} S_80FDB000_1;   /* result in spawn_killer */

typedef struct S_80FDB000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FDB000_2;   /* position in spawn_killer */

typedef struct S_80FDB000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80FDB000_4;   /* actor in spawn_killer */

extern void *allocate_list_node();
extern void register_node();
extern void set_or_clear_actor_status_slot();
extern s32 generate_random_value();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();

extern u8 D_80170A7C[];
extern u8 D_80170EA8[];
extern u8 D_80174038[];
extern u8 D_80174088[];
extern void *spawn_killer(s16, s32, s32, s32);
extern u8 D_801712B8[];
extern u8 D_801712E4[];
extern u8 D_80171264[];
extern u8 D_801711F4[];
extern u8 D_801711E4[];
extern u8 D_801712A8[];
extern u8 D_80172AC4[];
extern u8 D_80172ABC[];
extern u8 D_80172AB4[];
extern u8 D_80172ACC[];
extern u8 D_80172A74[];
extern u8 D_80172A6C[];
extern u8 D_80172A64[];

void *spawn_killer(s16 flags, s32 kind_id, s32 variant, s32 spawn_value)
;

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */
void *spawn_killer(s16 flags, s32 kind_id, s32 variant, s32 spawn_value)
{
    void *result = 0;
    void *created;
    void *position;
    SpriteFrameState *part_b;
    S_80FDB000_4 *actor;
    s32 left;
    s32 right;
    s16 saved_kind_id;
    s32 saved_spawn;
    s16 saved_variant;
    s16 original_flags;
    void *call_a0;
    void *call_a1;
    s32 kind;

    saved_kind_id = kind_id;
    saved_spawn = spawn_value;
    saved_variant = variant;
    created = allocate_list_node(0x112, ((u8 *)(&D_80083498)));
    original_flags = flags;
    if (created != 0) {
        result = (u8 *)created + 0x20;
        ((S_80FDB000_0 *)created)->unk_10 = D_80170A7C;
        ((S_80FDB000_1 *)result)->unk_13 = 0x28;
        register_node(created, project_sprite_chain);

        position = ((S_80FDB000_0 *)created)->unk_08;
        ((S_80FDB000_2 *)position)->unk_0A = saved_spawn;
        part_b = ((S_80FDB000_0 *)created)->unk_0C;
        kind = flags & 3;
        part_b->unk_25 = saved_variant;
        actor = result;
        part_b->frameTable = D_80174038;
        part_b->unk_24 = saved_kind_id;

        if (kind == 1) {
            ((S_80FDB000_1 *)result)->unk_14 |= 0x6000;
            ((S_80FDB000_1 *)result)->unk_1C |= 0x6000;
        } else if (kind >= 2) {
            ((S_80FDB000_1 *)result)->unk_14 |= 0x2000;
            ((S_80FDB000_1 *)result)->unk_1C |= 0x2000;
        } else {
            call_a0 = created;
            if (((flags & ~3) << 16) == 0) {
                if (!(((S_80FDB000_1 *)result)->unk_14 & 0x200)) {
                    call_a1 = position;
                    if (generate_random_value() & 1) {
                        ((S_80FDB000_1 *)result)->unk_1C |= 0x200;
                        set_or_clear_actor_status_slot(result, 1,
                            (generate_random_value() & 0x3F) | 0x20);
                        part_b->frameTable = D_80174088;
                    }
                }
            }
        }

        initialize_actor_sprite_and_animation(created, position, part_b,
            (s16)original_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = D_80170EA8;
        try_move_actor_to_valid_position(actor, position,
            part_b, result);
    }

    return result;
}
