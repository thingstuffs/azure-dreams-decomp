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
#include "dungeon/actor/status.h"

typedef s32 M2C_UNK;




extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 generate_random_value(void);
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
    ActorRecord *work;
    ActorRecord *actor;
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
        work = (ActorRecord *)(obj + 1);
        obj->update_callback = D_8014CA70;
        work->species = MONSTER_ZU;
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
            left = work->flags14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            right = work->flags1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            work->flags14 = left;
            work->flags1C = right;
        } else if (kind >= 2) {
            left = work->flags14 | ACTOR_CLASS_ENABLED;
            right = work->flags1C | ACTOR_PLAYER_SIDE;
            work->flags14 = left;
            work->flags1C = right;
        } else {
            if (((flags & ~3) << 16) == 0) {
                if (!(work->flags14 & ACTOR_RESIST_SLEEP)) {
                    left = generate_random_value();
                    if (left & 1) {
                        work->flags1C |= ACTOR_ASLEEP;
                        set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                      (generate_random_value() & 0x3F) | 0x20);
                        part_b->frameTable = D_80150AFC;
                    }
                }
            }
        }
        initialize_actor_sprite_and_animation(((void *)(obj)), part_a, part_b, flags);
        actor->action_id.u = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C.address = &D_8014D138;
        work->flags1C |= 0x40000;
        actor->unk_A0.parts.low = 0;
        actor->unk_90.parts.high.s = -0x30;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
