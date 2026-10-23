#ifndef TOWN_SCENE_OBJECT_PREPEND_SCENE_LIST_NODE_G01118_H
#define TOWN_SCENE_OBJECT_PREPEND_SCENE_LIST_NODE_G01118_H
/* Shared declarations for prepend_scene_list_node_g01118 */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01118 - CL:town/func_80091840. */

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct Node {
    struct Node *prev;
    struct Node *next;
} Node;

/* Entry zero is the circular-list sentinel prefix of a larger control object.
 * The unsized view preserves its non-small-data addressing; no Node-array
 * extent or enclosing control-record size is asserted. */
extern Node town_actor_control[];

/* Functions defined in this translation unit. */
s32 prepend_scene_list_node(Node *node);
s32 append_scene_list_node(Node *node);
void handle_insert_initialize_two_values_status_flags(Rec_D_800CFCB4 *node, s32 value_08, s32 value_0c);

#endif
