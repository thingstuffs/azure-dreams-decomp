#ifndef TOWN_PLAYER_INITIALIZE_SCENE_FOR_MODE_API_H
#define TOWN_PLAYER_INITIALIZE_SCENE_FOR_MODE_API_H

struct TownPlayerRecord;
struct ObjectPosition;
struct SpriteFrameState;

void process_scene_record_update(struct TownPlayerRecord *context, struct ObjectPosition *input, struct SpriteFrameState *sprite);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct ObjectPosition;
struct SpriteFrameState;
struct TownPlayerRecord;
void rebuild_menu_node_list(struct TownPlayerRecord *owner, struct ObjectPosition *node_in, struct SpriteFrameState *sprite);

#endif
