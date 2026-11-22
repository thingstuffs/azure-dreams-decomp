#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/town_object.h"

struct SpriteFrameState;
extern void func_800CE9EC(TownObjectRecord *, ObjectPosition *, struct SpriteFrameState *);

/* Counts down to a transition and moves halfway toward the target with a Y offset. */
void move_halfway_toward_transition_target(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *sprite)
{
    s32 adjusted_y;
    s16 timer;

    timer = (u16)object->timer - 1;
    object->timer = timer;
    if (timer <= 0) {
        object->unk_90 = 1;
        func_800CE9EC(object, position, sprite);
    }

    position->x.w.i += (-position->x.w.i + scene_object_list_anchor.position->x.w.i) / 2;
    adjusted_y = position->y.w.i;
    adjusted_y -= 0x10;
    position->y.w.i += (scene_object_list_anchor.position->y.w.i - adjusted_y) / 2;
    position->z.w.i += (-position->z.w.i + scene_object_list_anchor.position->z.w.i) / 2;
}
