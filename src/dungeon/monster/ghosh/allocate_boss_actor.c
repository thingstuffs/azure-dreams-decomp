#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef s32 M2C_UNK;

extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern void initialize_actor_sprite_and_animation(void *, void *, void *, s16);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);

extern void ghosh_motion_resume_address();
#include "dungeon/monster/ghosh.h"
extern void *ghosh_boss_node;



typedef struct S_8016F160_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 unk_9B;
    s8 unk_9C;
    u8 pad_9D[0x13];
    s16 unk_B0;
} S_8016F160_4;   /* tail_ptr in allocate_boss_actor */

/* Allocate an actor, initialize its parts and mode flags, and return its work area. */
/* Creates the Ghosh boss node with frames at D_80174A2C, applies spawn flags, and initializes its hidden
 * sprite. */
void *allocate_boss_actor(s16 mode, s16 config_24, s16 config_25, s16 config_0a)
{
    s16 mode_kind;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    ActorRecord *work;
    s16 saved_mode;
    s8 saved_config_24;
    s16 saved_config_0a;
    s8 saved_config_25;
    void *actor;
    void *actor_state;

    work = 0;
    saved_config_24 = config_24;
    saved_config_0a = config_0a;
    saved_config_25 = config_25;
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    saved_mode = mode;
    if (obj != 0) {
        work = (ActorRecord *)(obj + 1);
        ghosh_boss_node = obj;
        obj->update_callback = update_boss_actor_movement;
        work->species = MONSTER_SELFI;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = saved_config_0a;
        part_b = obj->sprite;
        mode_kind = mode & 3;
        part_b->frameTable = ghosh_direction_frames;
        part_b->tile_y = saved_config_25;
        actor = work;
        part_b->tile_x = saved_config_24;

        if (mode_kind == 1) {
            work->flags14 |= (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            work->flags1C |= (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
        } else if (mode_kind >= 2) {
            work->flags14 |= ACTOR_CLASS_ENABLED;
            work->flags1C |= ACTOR_PLAYER_SIDE;
        }

        initialize_actor_sprite_and_animation(obj, part_a, part_b, saved_mode);
        actor_state = actor;
        ((S_8016F160_4 *)actor_state)->unk_9A = 0xFF;
        ((S_8016F160_4 *)actor_state)->unk_9C = -1;
        ((S_8016F160_4 *)actor_state)->unk_8C = &ghosh_motion_resume_address;
        ((S_8016F160_4 *)actor_state)->unk_9B = 0;
        ((S_8016F160_4 *)actor_state)->unk_B0 = 0;
        part_b->flags |= 0x80;
        try_move_actor_to_valid_position(actor_state, part_a, part_b, work);
    }
    return work;
}
