#ifndef ENGINE_EFFECT_SINE_MOTION_H
#define ENGINE_EFFECT_SINE_MOTION_H
#include "common.h"
#include "shared/object_node.h"
#include "slus/jtbl_800517CC.h"
struct Controller;
typedef struct SineMotionEffectNode {
    ObjectNodeHeader header;
    EffectState800517CC body;
} SineMotionEffectNode;
/* Imported descriptor selector, with its established resident signature. */
void select_record_entry_and_value(void *record, void *source, s16 slot);
void init_orbit_motion_sprite(SineMotionEffectNode *object, struct Controller *owner);
#endif
