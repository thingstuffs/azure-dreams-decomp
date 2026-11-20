#ifndef TOWN_PERSON_CURRENT_TRANSFORM_OBJECT_DATA_H
#define TOWN_PERSON_CURRENT_TRANSFORM_OBJECT_DATA_H

#include "common.h"

struct Box;

/* One bounds pointer per transform state, indexed by the object byte at +0x94. */
extern struct Box *person_transform_defaults[6];

/* Current town object selected for transform callbacks (0x800FE4A0). */
extern void *current_transform_object;

#endif
