#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "dungeon/actor.h"
#include "engine/node/allocation.h"
#include "engine/node.h"

typedef struct S_80FF9000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80FF9000_1;   /* work in spawn_killer_slot_b */

typedef struct S_80FF9000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FF9000_2;   /* part_a in spawn_killer_slot_b */

typedef struct S_80FF9000_4 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80FF9000_4;   /* actor in spawn_killer_slot_b */

#if 0 /* rowbase_rename_reverify precondition marker: dead declaration, never
seen by the real compiler;
satisfies the tool's textual defines()
check for the proven-region rename of func_80152800. */
    void func_80152800(void);
#endif

s16 set_or_clear_actor_status_slot();
s32 generate_random_value(void);
void initialize_actor_sprite_and_animation();
extern u8 D_80152A7C[];
extern M2C_UNK D_80152EA8;
extern M2C_UNK D_80156038;
extern M2C_UNK D_80156088;

void *spawn_killer_slot_b(s16 spawn_flags, s32 grid_x, s32 grid_y, s16 part_value) ;

/* Allocates an actor and initializes its parts, position, and spawn flags. */
/* Creates Killer with default frames at D_80156038, applies spawn flags, and attempts valid tile
 * placement. */
void *spawn_killer_slot_b(s16 spawn_flags, s32 grid_x, s32 grid_y, s16 part_value) {
    s16 saved_x;
    s16 saved_y;
    s16 init_flags;
    S_80FF9000_1 *work;
    s32 alloc_kind;
    void *alloc_desc;
    s32 random_bits;
    s32 extra_flags;
    s32 kind;
    s32 flags_14;
    s32 flags_1c;
    SpriteFrameState *part_b;
    ObjectPosition *part_a;
    ObjectNodeHeader *obj;
    S_80FF9000_4 *actor;

    work = NULL;
    alloc_kind = 0x112;
    saved_x = grid_x;
    alloc_desc = ((s32 *)&scene_object_list_anchor.next);
    saved_y = grid_y;
    random_bits = (s32) *(s8 *)0x4A64;
    obj = allocate_list_node(alloc_kind, alloc_desc);
    init_flags = spawn_flags;
    if (obj != NULL) {
        work = ((void *)obj) + 0x20;
        obj->update_callback = &D_80152A7C;
        work->unk_13 = MONSTER_KILLER;
        register_node(obj, project_sprite_chain);
        part_a = obj->position;
        part_a->z.w.i = part_value;
        part_b = obj->sprite;
        kind = spawn_flags & 3;
        part_b->tile_y = saved_y;
        actor = work;
        part_b->frameTable = &D_80156038;
        part_b->tile_x = saved_x;

        if (kind == 1) {
            flags_14 = work->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            flags_1c = work->unk_1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            work->unk_14 = flags_14;
            work->unk_1C = flags_1c;
        } else if (kind >= 2) {
            flags_14 = work->unk_14 | ACTOR_CLASS_ENABLED;
            flags_1c = work->unk_1C | ACTOR_PLAYER_SIDE;
            work->unk_14 = flags_14;
            work->unk_1C = flags_1c;
        } else {
            extra_flags = (spawn_flags & ~3) << 0x10;
            if (extra_flags == 0) {
                if (!(work->unk_14 & ACTOR_RESIST_SLEEP)) {
                    random_bits = generate_random_value();
                    if (random_bits & 1) {
                        work->unk_1C = (s32) (work->unk_1C | ACTOR_ASLEEP);
                        set_or_clear_actor_status_slot(work, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                        part_b->frameTable = &D_80156088;
                    }
                }
            }
        }

        initialize_actor_sprite_and_animation((s32)obj, part_a, part_b, init_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_80152EA8;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
