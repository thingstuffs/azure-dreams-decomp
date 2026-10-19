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
typedef struct PointRecord { u8 pad_00[8]; u32 color; /* r/g/b/code word copied into the tile */ u8 pad_0C[4]; s32 unk_10; s16 unk_14; u8 pad_16[0x1C]; s16 brightness; } PointRecord;
/* 1990800 renderer multiplies each color channel by scale / scale_max.
 * This is a larger record than the brightness-only PointRecord. */
typedef struct ScaledPointRecord { u8 pad_00[8]; u32 color; u8 pad_0C[0x26]; s16 scale; s16 scale_max; } ScaledPointRecord;
typedef struct PointPacket { u32 tag; u8 r; u8 g; u8 b; u8 code; u32 data; } PointPacket;


/* Exact access views shared across registered binary consumers. */
/* Signed lifetime word at +8 of the fading resident effect. */
typedef struct EffectCountdownView {
    unsigned char pad_00[0x8];
    int unk_08;
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
