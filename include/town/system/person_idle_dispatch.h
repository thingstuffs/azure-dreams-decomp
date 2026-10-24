#ifndef TOWN_SYSTEM_PERSON_IDLE_DISPATCH_H
#define TOWN_SYSTEM_PERSON_IDLE_DISPATCH_H

#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

/* The mode selects either a source-table value or a numeric sprite-table index.
 * That third input retains its existing word representation pending a shared
 * source/index storage review. Both branches consume the target as a pointer. */
void clear_object_status_and_dispatch_target(void *object, void *target, int value, s16 flags);
void dispatch_object_when_idle(Rec_func_80094268_arg0 *object, void *callback_arg, s32 unused_a, s32 unused_b);

#endif
