#ifndef TOWN_MINIGAME_TAKO_CHILD_BODY_H
#define TOWN_MINIGAME_TAKO_CHILD_BODY_H

#include "common.h"

/* Body of a Tako target: initialize_tako_minigame allocates three and installs update_tako_target, which throws the
 * projectiles (TakoProjectileBody) that keep the target in their first word. */
typedef struct TakoChildBody {
    /* 0x00 */ struct TakoMinigameState *parent; /* the minigame state */
    /* 0x04 */ u8 pad_04[0x48];
    /* 0x4C */ void *resource;
    /* 0x50 */ s16 state;
    /* 0x52 */ u16 timer;
    /* 0x54 */ s16 deflect_count; /* deflections of this target's projectiles; while it reads 9 the projectile in
                                 * flight shows a per-column effect, and the tenth deflection adds 10 points */
    /* 0x56 */ s16 column_index;
    /* 0x58 */ u16 flags; /* 0x1: set on each update of its live projectile or hit sparks, cleared when they are
                         * removed; 0x2: set on each update of a deflected projectile, cleared by update_tako_target;
                         * 0x4: set while the projectile's wind-up timer reads 0x10, cleared on its other wind-up updates */
} TakoChildBody;

#endif
