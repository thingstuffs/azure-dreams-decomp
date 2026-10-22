#include "common.h"
#include "shared/monster_ids.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"



typedef struct S_80FE7000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
} S_80FE7000_1;   /* result in spawn_killer_slot_e */

typedef struct S_80FE7000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80FE7000_4;   /* actor in spawn_killer_slot_e */

#if 0 /* rowbase_rename_reverify precondition marker: dead declaration, never
         seen by the real compiler; satisfies the tool's textual defines()
         check for the proven-region rename of func_80164800. */
void func_80164800(void);
#endif

extern void *allocate_list_node();
extern void register_node();
extern void set_or_clear_actor_status_slot();
extern s32 generate_random_value();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();

extern u8 D_80164A7C[];
extern u8 D_80164EA8[];
extern u8 D_80168038[];
extern u8 D_80168088[];
extern void *spawn_killer_slot_e(s16, s32, s32, s32);
extern u8 D_801652B8[];
extern u8 D_801652E4[];
extern u8 D_80165264[];
extern u8 D_801651F4[];
extern u8 D_801651E4[];
extern u8 D_801652A8[];
extern u8 D_80166AC4[];
extern u8 D_80166ABC[];
extern u8 D_80166AB4[];
extern u8 D_80166ACC[];
extern u8 D_80166A74[];
extern u8 D_80166A6C[];
extern u8 D_80166A64[];

void *spawn_killer_slot_e(s16 spawn_flags, s32 attr_a, s32 attr_b, s32 attr_c)
#ifdef __mips__
    #endif
    ;

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
/* Creates Killer with default frames at D_80168038, applies spawn flags, and attempts valid tile
 * placement. */
void *spawn_killer_slot_e(s16 spawn_flags, s32 attr_a, s32 attr_b, s32 attr_c)
{
    void *result = 0;
    ObjectNodeHeader *created;
    ObjectPosition *position;
    SpriteFrameState *part_b;
    S_80FE7000_4 *actor;
    s32 left;
    s32 right;
    s16 held_a;
    s32 held_c;
    s16 held_b;
    s16 flags_copy;
    void *call_a0;
    void *call_a1;
    s32 kind;

    held_a = attr_a;
    held_c = attr_c;
    held_b = attr_b;
    created = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    flags_copy = spawn_flags;
    if (created != 0) {
        result = (u8 *)created + 0x20;
        created->unk_10 = D_80164A7C;
        ((S_80FE7000_1 *)result)->unk_13 = MONSTER_KILLER;
        register_node(created, project_sprite_chain);

        position = created->position;
        position->z.w.i = held_c;
        part_b = created->sprite;
        kind = spawn_flags & 3;
        part_b->unk_25 = held_b;
        actor = result;
        part_b->frameTable = D_80168038;
        part_b->unk_24 = held_a;

        if (kind == 1) {
            ((S_80FE7000_1 *)result)->unk_14 |= 0x6000;
            ((S_80FE7000_1 *)result)->unk_1C |= 0x6000;
        } else if (kind >= 2) {
            ((S_80FE7000_1 *)result)->unk_14 |= 0x2000;
            ((S_80FE7000_1 *)result)->unk_1C |= 0x2000;
        } else {
            call_a0 = created;
            if (((spawn_flags & ~3) << 16) == 0) {
                if (!(((S_80FE7000_1 *)result)->unk_14 & 0x200)) {
                    call_a1 = position;
                    if (generate_random_value() & 1) {
                        ((S_80FE7000_1 *)result)->unk_1C |= 0x200;
                        set_or_clear_actor_status_slot(result, 1,
                            (generate_random_value() & 0x3F) | 0x20);
                        part_b->frameTable = D_80168088;
                    }
                }
            }
        }

        initialize_actor_sprite_and_animation(created, position, part_b,
            (s16)flags_copy);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = D_80164EA8;
        try_move_actor_to_valid_position(actor, position,
            part_b, result);
    }
    return result;
}
