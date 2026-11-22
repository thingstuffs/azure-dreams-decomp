#ifndef INCLUDE_SLUS_RESOURCE_TRANSITION_TASK_H
#define INCLUDE_SLUS_RESOURCE_TRANSITION_TASK_H
struct ObjectNodeHeader;

#include "common.h"

void *create_resource_transition_task(void *owner);
void *create_resource_transition_for_descriptor_check(struct ObjectNodeHeader *object);
void *create_resource_transition_card(struct ObjectNodeHeader *object);

#endif
