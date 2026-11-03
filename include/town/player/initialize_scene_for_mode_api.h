#ifndef TOWN_PLAYER_INITIALIZE_SCENE_FOR_MODE_API_H
#define TOWN_PLAYER_INITIALIZE_SCENE_FOR_MODE_API_H

struct TownPlayerRecord;
struct ObjectPosition;
struct SpriteFrameState;

void process_scene_record_update(struct TownPlayerRecord *context, struct ObjectPosition *input, struct SpriteFrameState *sprite);

#endif
