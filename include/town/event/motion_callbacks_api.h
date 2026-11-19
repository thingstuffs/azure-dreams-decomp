#ifndef TOWN_EVENT_MOTION_CALLBACKS_API_H
#define TOWN_EVENT_MOTION_CALLBACKS_API_H

struct TownObjectRecord;
struct ColliderView;
struct ObjectPosition;
struct SpriteFrameState;

void update_actor_with_controlled_motion(struct TownObjectRecord *actor, struct ColliderView *subject, struct ObjectPosition *motion, struct SpriteFrameState *context);

#endif
