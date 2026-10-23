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

extern s32 update_actor_transform_from_parent(Actor *, s32, Entity *, MapObject *);

extern void select_sprite_entry(Entity *, s16, s16);

extern u8 D_801710EC[9];
extern u8 D_80175E40[9];
extern u8 D_80175EA0[9];

/* Update actor and entity state after checking the map object. */
void update_actor_state_after_map_check(Actor *actor, s32 action, SpriteFrameState *entity, MapObject *map_object)
{
    if (update_actor_transform_from_parent(actor, action, entity, map_object) != 0) {
        if ((check_actor_floor_trap(entity, map_object) << 16) > 0) {
            actor->unk_8C = D_801710EC;
            return;
        }
    } else if (*(u8 **)&entity->frameTable == D_80175EA0 &&
               !(map_object->unk_1C & 0x208)) {
        entity->frameTable = D_80175E40;
        select_sprite_entry(entity,
                      D_80175E40[((g_game_work.view.camera_rotation.parts.viewAngle + map_object->unk_2A + 0x100) >> 9) & 7],
                      0);
    }
}
