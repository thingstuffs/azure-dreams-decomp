#ifndef TOWN_MINIGAME_KEIMA_H
#define TOWN_MINIGAME_KEIMA_H

#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"

/* Shared controller body: initialize_keima_interface gives each path actor
 * a backlink to it; update_keima_minigame owns these pointer/slot arrays. */
typedef struct KeimaState {
    ObjectPosition *rec[4];              /* 0x00 */
    s16 *angle[4];                  /* 0x10: angle[0] = base record + 0x10, angle[i] = the node record's facing */
    ObjectNodeHeader *node[3];      /* 0x20: the node of ball i+1 (rec[i + 1]); angle[3] ends at 0x20 */
    union { s16 s; u16 u; u16 p; } stage;   /* 0x2C (accessed as both) */
    union { u16 s; s16 u; } timer;  /* 0x2E (accessed as both) */
    s16 flag[4];                    /* 0x30 */
    u8 pad_38[0x2];
    u16 flags;                      /* 0x3A */
    s16 slot[4];                    /* 0x3C */
    s16 unk_44;
    s16 unk_46;
    u16 unk_48;
    union { u16 s; s16 u; } unk_4A; /* (accessed as both) */
} KeimaState;

typedef union KeimaHalf { s16 s; u16 u; } KeimaHalf;

/* The table cursor advances eight bytes. The former +0E flag access is
 * the following waypoint's +6, not a sixteen-byte waypoint. */
typedef struct KeimaPathPoint {
    s16 x;
    s16 y;
    s16 heading;
    u16 flags;
} KeimaPathPoint;

typedef struct KeimaPath {
    KeimaPathPoint *points;
    s16 unk_04;
    u16 effect_period;
    s16 turn_limit;
    s16 pad_0A;
} KeimaPath;

/* Body installed with D_80023260 at node+20 by the interface initializer.
 * +14/+16 are the cycle count/index passed to advance_bounded_entry_index. */
typedef struct KeimaPathActor {
    KeimaState *owner;
    s32 speed;
    s32 flags;
    s32 impulse_x;
    s32 impulse_y;
    u16 cycles;
    s16 zone_index;
    KeimaHalf state;
    u16 path_ticks;
    s16 waypoint_index;
    u16 turn_bias;
    s16 sprite_direction;
    s16 path_index;
    s16 lane;
    u8 pad_26[4];
    KeimaHalf facing;
} KeimaPathActor;

extern KeimaPath town_minigame_path_records[];
s32 initialize_keima_interface(void);
void update_keima_minigame(KeimaState *game);
void update_path_following_actor(KeimaPathActor *actor, ObjectPosition *motion, SpriteFrameState *sprite);

#endif
