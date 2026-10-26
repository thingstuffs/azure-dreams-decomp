#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"

typedef s32 M2C_UNK;

typedef struct S_80FAB000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80FAB000_1;   /* work in create_actor_kind_object */

typedef struct S_80FAB000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FAB000_2;   /* part_a in create_actor_kind_object */

typedef struct S_80FAB000_4 {
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
} S_80FAB000_4;   /* actor in create_actor_kind_object */

extern void register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 generate_random_value(void);
extern void set_or_clear_actor_status_slot();
extern u8 D_8014CA70[];
extern M2C_UNK D_8014D138;
extern u8 zu_frame_set_3[];
extern u8 D_80150AFC[];

void *create_actor_kind_object(s16 flags, s16 field24_input, s16 field25_input, s16 field0A_input)
;
/* Creates a Zu actor at the supplied tile and height, then initializes mode flags, status, and callbacks. */
void *create_actor_kind_object(s16 flags, s16 field24_input, s16 field25_input, s16 field0A_input)
{
    s32 kind;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    S_80FAB000_1 *work;
    S_80FAB000_4 *actor;
    s32 left;
    s32 right;
    s8 field24_value;
    s16 field0A_value;
    s8 field25_value;

    work = 0;
    field24_value = field24_input;
    field0A_value = field0A_input;
    field25_value = field25_input;
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        obj->update_callback = D_8014CA70;
        work->unk_13 = MONSTER_ZU;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = field0A_value;
        part_b = obj->sprite;
        kind = flags & 3;
        part_b->tile_y = field25_value;
        actor = work;
        actor = work;
        part_b->frameTable = zu_frame_set_3;
        part_b->tile_x = field24_value;

        if (kind == 1) {
            left = work->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            right = work->unk_1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            work->unk_14 = left;
            work->unk_1C = right;
        } else if (kind >= 2) {
            left = work->unk_14 | ACTOR_CLASS_ENABLED;
            right = work->unk_1C | ACTOR_PLAYER_SIDE;
            work->unk_14 = left;
            work->unk_1C = right;
        } else {
            if (((flags & ~3) << 16) == 0) {
                if (!(work->unk_14 & ACTOR_RESIST_SLEEP)) {
                    left = generate_random_value();
                    if (left & 1) {
                        work->unk_1C |= ACTOR_ASLEEP;
                        set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                      (generate_random_value() & 0x3F) | 0x20);
                        part_b->frameTable = D_80150AFC;
                    }
                }
            }
        }
        initialize_actor_sprite_and_animation(((void *)(obj)), part_a, part_b, flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8014D138;
        work->unk_1C |= 0x40000;
        actor->unk_A0 = 0;
        actor->unk_92 = -0x30;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
