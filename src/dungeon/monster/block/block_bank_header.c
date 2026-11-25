#include "dungeon/monster/block.h"
#include "dungeon/monster/saber.h"

const struct {
    void *(*spawn)(s16, s16, s16, s32);
    void (*update)(ActorRecord *, ObjectPosition *, SpriteFrameState *);
} block_bank_header = {
    create_linked_object_position,
    update_entity_callbacks_and_floor_motion,
};
