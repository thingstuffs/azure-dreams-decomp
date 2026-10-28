#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

#include "shared/entity.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"
#include "dungeon/actor/status.h"
#include "engine/node.h"






extern s32 generate_random_value(void);

extern u8 ifrit_object_callback_4[];
extern u8 D_8016E820[];
extern u8 D_8016E860[];
void func_8016AE84(ActorRecord *controller, ObjectPosition *context, SpriteFrameState *entity, ActorRecord *actor_state);

/* Creates an Ifrit actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *queue_projected_point_primitives_2(s16 mask, s16 value_24_input, s16 value_25_input, s16 value_0A_input)
{
    s32 kind;
    ObjectNodeHeader *object;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    ActorRecord *work;
    ActorRecord *actor;
    s32 value_14;
    s32 value_1C;
    s16 value_0A;

    work = 0;
    value_0A = value_0A_input;
    object = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (object != 0) {
        work = (ActorRecord *)(object + 1);
        object->update_callback = ifrit_object_callback_4;
        work->species = MONSTER_IFRIT;
        register_node(object, project_sprite_chain);

        part_a = object->position;
        part_a->z.w.i = value_0A;
        part_b = object->sprite;
        kind = mask & 3;
        part_b->tile_y = value_25_input;
        actor = work;
        part_b->frameTable = D_8016E820;
        part_b->tile_x = value_24_input;

        if (kind == 1) {
            value_14 = work->flags14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            value_1C = work->flags1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            work->flags14 = value_14;
            work->flags1C = value_1C;
        } else if (kind >= 2) {
            value_14 = work->flags14 | ACTOR_CLASS_ENABLED;
            value_1C = work->flags1C | ACTOR_PLAYER_SIDE;
            work->flags14 = value_14;
            work->flags1C = value_1C;
        } else if (((mask & ~3) << 16) == 0) {
            if (!(work->flags14 & ACTOR_RESIST_SLEEP)) {
                value_14 = generate_random_value();
                if (value_14 & 1) {
                    work->flags1C |= ACTOR_ASLEEP;
                    set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = D_8016E860;
                }
            }
        }
        initialize_actor_sprite_and_animation(((void *)(object)), part_a, part_b, mask);
        actor->action_id.u = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C.address = &func_8016AE84;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
