#ifndef TOWN_MINIGAME_EFFECT_H
#define TOWN_MINIGAME_EFFECT_H
/* Prototypes of the functions defined in src/town/minigame/effect/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/entity.h"

/* State carried by the casino betting effect callback. */
typedef struct TownEffect {
    /* 0x00 */ u8 *child;
    /* 0x04 */ u8 pad_04[0xC];
    /* 0x10 */ s32 payout_scale;
    /* 0x14 */ s32 amount;
    /* 0x18 */ s16 state;
    /* 0x1A */ s16 timer;
    /* 0x1C */ s16 count;
    /* 0x1E */ s16 ticks;
    /* 0x20 */ u16 flags;
    /* 0x22 */ s16 phase;
    /* 0x24 */ s16 phase2;
} TownEffect;

typedef struct CopyRecord {
    s32 words[6];
} CopyRecord;

/* Body shared by the snowball scene effect creator and copy callback. */
typedef struct SceneEffectCopyObject {
    /* 0x00 */ u8 pad_00[0x2];
    /* 0x02 */ union { u16 u; s16 s; } timer;
    /* 0x04 */ void *source;
} SceneEffectCopyObject;

struct S_80026978_1;

/* create_brief_randomized_particle.c */
void create_brief_randomized_particle(struct S_80026978_1 *origin);

/* create_randomized_trail_particle.c */
void create_randomized_trail_particle(ObjectPosition *source);

/* create_tinted_animated_particle.c */
void create_tinted_animated_particle(s32 color, s32 x, s32 y, s32 z);

/* retire_transient_line_effect.c */
void retire_transient_line_effect(void *record);

/* copy_scene_effect_until_timer_expires.c */
void copy_scene_effect_until_timer_expires(SceneEffectCopyObject *entry, CopyRecord *out_record, void *update_arg);

#endif
