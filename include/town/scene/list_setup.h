#ifndef TOWN_SCENE_LIST_SETUP_H
#define TOWN_SCENE_LIST_SETUP_H

#include "common.h"

struct ObjectPosition;
struct Box;

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
s32 append_scene_list_node(TownSceneListNode *node);
void handle_insert_initialize_two_values_status_flags(void *record, void *position, void *bounds);
void configure_the_set_mode_n_1(void *record, void *position, void *bounds);
void configure_the_set_mode_n_2(void *record, void *position, void *bounds);

#endif
