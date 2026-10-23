#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"



typedef struct S_80F99000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80F99000_1;   /* work in spawn_zu_slot_d */

typedef struct S_80F99000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x3];
    s16 unk_A0;
} S_80F99000_4;   /* actor in spawn_zu_slot_d */

extern void *allocate_list_node();
extern void register_node();
extern s32 generate_random_value();
extern void set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();

extern u8 D_8015EA70[];
extern u8 D_80162AD4[];
extern u8 D_80162AFC[];
extern u8 D_8015F138[];

void *spawn_zu_slot_d(s16, s16, s16, s16)
#ifdef __mips__
#endif
;

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
/* Creates Zu with default frames at D_80162AD4, applies spawn flags, and attempts valid tile placement. */
void *spawn_zu_slot_d(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c)
{
    s32 kind;
    void *work = 0;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    S_80F99000_4 *actor;
    s32 left;
    s32 right;
    s8 held_a;
    s16 held_c;
    s8 held_b;

    held_a = attr_a;
    held_c = attr_c;
    held_b = attr_b;
    obj = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        obj->update_callback = D_8015EA70;
        ((S_80F99000_1 *)work)->unk_13 = MONSTER_ZU;
        register_node(obj, project_sprite_chain);

        part_a = *(void ** *)&obj->position;
        part_a->z.w.i = held_c;
        part_b = *(void ** *)&obj->sprite;
        kind = spawn_flags & 3;
        part_b->tile_y = held_b;
        actor = work;
        part_b->frameTable = D_80162AD4;
        part_b->tile_x = held_a;

        if (kind == 1) {
            left = ((S_80F99000_1 *)work)->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            right = ((S_80F99000_1 *)work)->unk_1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            ((S_80F99000_1 *)work)->unk_14 = left;
            ((S_80F99000_1 *)work)->unk_1C = right;
        } else if (kind >= 2) {
            left = ((S_80F99000_1 *)work)->unk_14 | ACTOR_CLASS_ENABLED;
            right = ((S_80F99000_1 *)work)->unk_1C | ACTOR_PLAYER_SIDE;
            ((S_80F99000_1 *)work)->unk_14 = left;
            ((S_80F99000_1 *)work)->unk_1C = right;
        } else {
            if (((spawn_flags & ~3) << 16) == 0) {
                if (!(((S_80F99000_1 *)work)->unk_14 & ACTOR_RESIST_SLEEP)) {
                    left = generate_random_value();
                    if (left & 1) {
                        ((S_80F99000_1 *)work)->unk_1C |= ACTOR_ASLEEP;
                        set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                      (generate_random_value() & 0x3F) | 0x20);
                        part_b->frameTable = D_80162AFC;
                    }
                }
            }
        }
        initialize_actor_sprite_and_animation(obj, part_a, part_b, spawn_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = D_8015F138;
        ((S_80F99000_1 *)work)->unk_1C |= 0x40000;
        actor->unk_A0 = 0;
        actor->unk_92 = -0x30;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
