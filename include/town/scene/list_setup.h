#ifndef TOWN_SCENE_LIST_SETUP_H
#define TOWN_SCENE_LIST_SETUP_H

#include "common.h"

struct ObjectPosition;
struct Box;
extern struct Box D_800D0678;
extern struct Box D_800D6A58;

typedef struct TownSceneListNode {
    struct TownSceneListNode *prev;
    struct TownSceneListNode *next;
    struct ObjectPosition *position;
    struct Box *bounds;
    u8 pad_10[4];
    s8 mode;
    s8 active;
} TownSceneListNode;

s32 prepend_scene_list_node(TownSceneListNode *node);
void init_scene_list_node(void *record, struct ObjectPosition *position, struct Box *bounds);
void init_scene_node_mode_1(void *record, struct ObjectPosition *position, void *bounds);
void init_scene_node_mode_2(void *record, struct ObjectPosition *position, struct Box *bounds);

#endif
