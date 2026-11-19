/* Complete resident-engine cohort contract. Review pending. */
#ifndef DUNGEON_ENGINE_SCREEN_EFFECTS_H
#define DUNGEON_ENGINE_SCREEN_EFFECTS_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/game_work.h"
#include "shared/gpu_packets.h"

/* The spark constructors set a 32 by 32 copy and a displacement of (1, 0).
 * The screen copy bounds both rectangles before queuing the move. */
typedef struct RectangleCopy {
    s16 width;
    s16 height;
    s16 delta_x;
    s16 delta_y;
} RectangleCopy;

typedef struct MotionRecord {
    RectangleCopy copy;
    u8 pad_08[0x28];
    s16 speed;          /* 0x30 */
    u8 pad_32[4];
    s16 direction;      /* 0x36 */
} MotionRecord;

struct ShadedModelQuad;
struct SVECTOR;
/* The first three words of a model source select its face, position and normal arrays. */
typedef struct ShadedModel {
    struct ShadedModelQuad *quads;
    struct SVECTOR *positions;
    struct SVECTOR *normals;
} ShadedModel;

struct ObjectPosition;
struct SpriteFrameState;
void transform_shade_and_queue_model_quads(void *parent_matrix, struct ObjectPosition *translation,
                                           struct SpriteFrameState *sprite, s16 depth_bias);

#endif
