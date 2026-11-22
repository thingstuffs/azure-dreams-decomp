#ifndef TOWN_MENU_ANIMATION_H
#define TOWN_MENU_ANIMATION_H
/* Prototypes of the functions defined in src/town/menu/animation/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_func_801237A4_arg0.h"
#include "shared/entity.h"
#include "shared/position_views.h"
#include "shared/town_object.h"

struct MenuAnimationPhaseObject;
struct SpriteFrameState;
struct DoorTransitionEffect;

s32 animate_spinning_shrinking_object(struct DoorTransitionEffect *object, const struct ObjectPosition *point, struct SpriteFrameState *unused_sprite);

/* layout_catalog_frame.c */
void layout_catalog_frame(void);

#endif
