#ifndef TOWN_SCENE_OBJECT_PREPEND_SCENE_LIST_NODE_G01118_H
#define TOWN_SCENE_OBJECT_PREPEND_SCENE_LIST_NODE_G01118_H
/* Shared declarations for prepend_scene_list_node_g01118 */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01118 - CL:town/func_80091840. */

#include "common.h"
#include "m2c_compat.h"
#include "town/scene/list_setup.h"

#ifndef NULL
#define NULL 0
#endif

/* Entry zero is the circular-list sentinel prefix of a larger control object.
 * The unsized view preserves its non-small-data addressing; no Node-array
 * extent or enclosing control-record size is asserted. */
extern TownSceneListNode town_actor_control[];

/* Functions defined in this translation unit. */


#endif
