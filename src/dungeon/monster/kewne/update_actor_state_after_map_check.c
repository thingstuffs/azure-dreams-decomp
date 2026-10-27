#include "shared/entity.h"
#include "common.h"
#include "dungeon/actor.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"

typedef struct {
    s8 pad_00[0x8C];
    void *unk_8C;
} Actor;

typedef struct {
    u8 pad_00[0x2C];
    u8 *unk_2C;
} Entity;

typedef struct {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} MapObject;

extern s32 update_actor_transform_from_parent(Actor *, void *, void *, void *);

struct SpriteFrameState;
extern void select_sprite_entry(void *, s16, s16);

extern u8 kewne_action_resume_address[9];
extern u8 kewne_direction_frames[9];
extern u8 kewne_frame_set_1[9];

/* Update actor and entity state after checking the map object. */
void update_actor_state_after_map_check(Actor *actor, ObjectPosition *action, SpriteFrameState *entity, MapObject *map_object)
{
    if (update_actor_transform_from_parent(actor, action, entity, map_object) != 0) {
        if ((check_actor_floor_trap(entity, map_object) << 16) > 0) {
            actor->unk_8C = kewne_action_resume_address;
            return;
        }
    } else if (*(u8 **)&entity->frameTable == kewne_frame_set_1 &&
               !(map_object->unk_1C & 0x208)) {
        entity->frameTable = kewne_direction_frames;
        select_sprite_entry(entity,
                      kewne_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + map_object->unk_2A + 0x100) >> 9) & 7],
                      0);
    }
}
