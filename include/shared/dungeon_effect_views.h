#ifndef SHARED_DUNGEON_EFFECT_VIEWS_H
#define SHARED_DUNGEON_EFFECT_VIEWS_H
#include "common.h"
#include "shared/entity.h"
/* Position consumers use EntityRec x/y/z directly. Retail lhu readers cast
 * the signed Fixed1616 integer half to u16 at the access site. */
/* Point payload at node +0x20, initialized by the point spawners and passed
 * to their registered PointRecord renderers. Color +08 is copied into the
 * packet; +32 is a signed brightness/movement/fade counter. The spawn
 * parameter +14 is a signed halfword (a direction index in the 183a800
 * movement callback). Its meaning is independent of EntityRec.flags14.
 * Position comes through node->unk_08; flags 0x211 place that cursor at
 * node +0xDC, separate from this payload. */
/* Colored point-effect payload at pooled node +0x20; point spawners allocate it with flags 0x211.
 * func_80024758 and create_random_jitter_child seed its color and motion/fade parameters. */
typedef struct PointRecord { u8 pad_00[8]; u32 color; /* packed RGB/command word copied to the point tile before channel scaling */ u8 pad_0C[4]; s32 unk_10; s16 unk_14; /* spawner parameter; used as the direction-table index by advance_scattered_directional_particle */ u8 pad_16[0x1C]; s16 brightness; /* brightness/motion/lifetime parameter; point renderers scale by /128 or /256 depending on the callback */ } PointRecord;
/* 1990800 renderer multiplies each color channel by scale / scale_max.
 * This is a larger record than the brightness-only PointRecord. */
/* Colored point payload reached through pooled node +0x20 by project_scaled_colored_point.
 * The renderer borrows this view; its spawning initializer remains untraced. */
typedef struct ScaledPointRecord { u8 pad_00[8]; u32 color; /* packed RGB/command word copied into the point tile */ u8 pad_0C[0x26]; s16 scale; /* brightness numerator applied independently to each RGB channel */ s16 scale_max; /* brightness denominator; rendered channel = source channel * scale / scale_max */ } ScaledPointRecord;
/* Twelve-byte point tile/draw-mode packet view allocated at the frame packet cursor.
 * Point renderers fill the tile form and append a draw-mode packet at the next cursor position. */
typedef struct PointPacket { u32 tag; /* DMA chain address/count word; point tiles contain two command words */ u8 r; /* tile red modulation byte after brightness scaling */ u8 g; /* tile green modulation byte after brightness scaling */ u8 b; /* tile blue modulation byte after brightness scaling */ u8 code; /* tile GPU command byte; point renderers set 0x6A */ u32 data; /* packed projected screen X/Y for tiles; draw-mode form uses this word as command data */ } PointPacket;


/* Exact access views shared across registered binary consumers. */
/* Signed lifetime word at +8 of the fading resident effect. */
/* Lifetime slice borrowed from the resident fading effect work.
 * fade_effect_parts decrements it and releases the linked parts on expiry. */
typedef struct EffectCountdownView {
    unsigned char pad_00[0x8];
    int unk_08; /* remaining fade updates; decrementing to -1 triggers part release and object retirement */
} EffectCountdownView;

/* Signed word at +8 containing a primitive resource or style selection. */
typedef struct EffectPrimitiveValueView {
    unsigned char pad_00[0x8];
    int unk_08;
} EffectPrimitiveValueView;

/* Signed state/default word at +8 used by effect setup and callback contexts. */
typedef struct EffectStateWordView {
    unsigned char pad_00[0x8];
    int unk_08;
} EffectStateWordView;

/* Three copied initialization words in the menu/effect allocation payload. */
typedef struct EffectInitialState {
    int unk_00;
    int unk_04;
    int unk_08;
} EffectInitialState;

/* Signed +A halfword in timed-scale setup; keeps its original 0xC view. */
typedef struct ScaleStateHalfView {
    unsigned char pad_00[0xA];
    short unk_0A;
} ScaleStateHalfView;

/* Effect state number and timer; these two halves are not a coordinate pair. */
typedef struct EffectPhaseTimer16 {
    short state;
    short timer;
} EffectPhaseTimer16;

/* Effect object payload pointer at +0x08; extent 0x0C. */
typedef struct EffectObjectPayloadView {
    unsigned char pad_00[0x8];
    void * unk_08;
} EffectObjectPayloadView;

#endif
