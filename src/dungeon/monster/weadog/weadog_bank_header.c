#include "dungeon/monster/weadog.h"
#include "dungeon/monster/saber.h"

const struct {
    void *(*spawn)(s16, s16, s16, s32);
    void (*update)(ActorRecord *, ObjectPosition *, SpriteFrameState *);
} weadog_bank_header = {
    spawn_weadog_actor,
    update_entity_callbacks_and_floor_motion,
};
