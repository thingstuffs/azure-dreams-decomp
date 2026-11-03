#ifndef TOWN_EVENT_MOTION_CALLBACKS_API_H
#define TOWN_EVENT_MOTION_CALLBACKS_API_H

struct Actor;
struct Subject;
struct Motion;
struct TownMovementOutput;

void update_actor_with_controlled_motion(struct Actor *actor, struct Subject *subject, struct Motion *motion, struct TownMovementOutput *context);

#endif
