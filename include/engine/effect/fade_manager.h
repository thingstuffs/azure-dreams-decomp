#ifndef ENGINE_EFFECT_FADE_MANAGER_H
#define ENGINE_EFFECT_FADE_MANAGER_H

#include "common.h"
#include "shared/object_node.h"

struct ObjectPosition;
struct SpriteFrameState;
struct SpriteSourceEntry;

/* Body of the static fade-manager node. create_marked_callback_node initializes callback_node_storage (flags 0x15,
 * 0x49 words) as the node header, so this body follows it at +0x20 and the fade's position and sprite records are
 * reached through NODE_HEADER(&fade_manager_state). The node's update callback, run_node_callback_and_set_marker,
 * calls step with the body, position and sprite each frame; the begin and ramp steps install the next step and a
 * finished fade clears it. */
typedef struct FadeManagerBody {
    /* 0x00 */ void (*step)(struct FadeManagerBody *manager, struct ObjectPosition *position, struct SpriteFrameState *sprite); /* current fade step; null when idle */
    /* 0x04 */ s8 has_source; /* set to 1 by runtime_set_destination_flag_from_source when the sprite has a source; cleared when the fade ends */
    /* 0x05 */ u8 pad_05[3];
    /* 0x08 */ struct SpriteSourceEntry *source; /* sprite source the shared fade display selects; activate_indexed_resource_and_upload_images stores the selected entry's value here */
} FadeManagerBody;

extern FadeManagerBody fade_manager_state;

#endif
