#include "shared/entity.h"
#include "engine/node.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"

typedef struct S_80F2D000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80F2D000_1;   /* work in spawn_effect_object */

typedef struct S_80F2D000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80F2D000_2;   /* part_a in spawn_effect_object */

typedef struct S_80F2D000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x7];
    s16 unk_A4;
    s16 unk_A6;
} S_80F2D000_4;   /* work_copy in spawn_effect_object */

/* cfail-repair: tf7-phase1-cache-v3 */
s16 set_or_clear_actor_status_slot();        /* extern */
s32 generate_random_value(void);                          /* extern */
void retire_tracked_effect_by_id();                      /* extern */
extern M2C_UNK D_8014CA8C;
extern M2C_UNK D_8014CF74;
extern M2C_UNK D_8014FD30;
extern M2C_UNK D_8014FD78;

void *spawn_effect_object(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c);
/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
/* Creates Stealth with frames at D_8014FD30; a random display variant changes sprite flags and unlinks the
 * node. */
void *spawn_effect_object(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c) {
    s32 unksp20;
    s32 kind;
    s32 variant;
    void *obj_alt;
    SpriteFrameState *part_b;
    ObjectPosition *part_a;
    void *work_copy;
    ObjectNodeHeader *object;
    S_80F2D000_1 *work;

    unksp20 = (s32) *(s8 *)-0x149C;
    work = NULL;
    variant = 1;
    object = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (object != NULL) {
        work = ((void *)object) + 0x20;
        object->update_callback = &D_8014CA8C;
        work->unk_13 = MONSTER_STEALTH;
        register_node(object, project_sprite_chain);
        part_a = object->position;
        part_a->z.w.i = attr_c;
        part_b = object->sprite;
        part_b->tile_y = attr_b;
        work_copy = work;
        part_b->frameTable = &D_8014FD30;
        kind = spawn_flags & 3;
        part_b->tile_x = attr_a;
        if (kind == 1) {
            work->unk_14 = (s32) (work->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER));
            work->unk_1C = (s32) (work->unk_1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER));
        } else if (kind >= 2) {
            work->unk_14 = (s32) (work->unk_14 | ACTOR_CLASS_ENABLED);
            work->unk_1C = (s32) (work->unk_1C | ACTOR_PLAYER_SIDE);
        } else if (((spawn_flags & ~3) << 0x10) == 0) {
            if (!(work->unk_14 & ACTOR_RESIST_SLEEP)) {
                if (generate_random_value() & 1) {
                    work->unk_1C = (s32) (work->unk_1C | ACTOR_ASLEEP);
                    set_or_clear_actor_status_slot(work, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = &D_8014FD78;
                }
            }
            variant = generate_random_value() & 3;
        }
        initialize_actor_sprite_and_animation(object, part_a, part_b, spawn_flags);
        ((S_80F2D000_4 *)work_copy)->unk_9A = 0xFF;
        ((S_80F2D000_4 *)work_copy)->unk_9C = -1;
        ((S_80F2D000_4 *)work_copy)->unk_8C = &D_8014CF74;
        ((S_80F2D000_4 *)work_copy)->unk_A4 = -1;
        if (variant != 0) {
            ((S_80F2D000_4 *)work_copy)->unk_A6 = 0;
        } else {
            obj_alt = work_copy - 0x20;
            ((S_80F2D000_4 *)work_copy)->unk_A6 = 1;
            part_b->tpage_abr = 0x60;
            part_b->flags = (u16) (part_b->flags | 0xC);
            part_b->clut = (u16) (part_b->clut - 0x80);
            unlink_node(obj_alt);
            retire_tracked_effect_by_id(obj_alt);
        }
        try_move_actor_to_valid_position(work_copy, part_a, part_b, work);
    }
    return work;
}
