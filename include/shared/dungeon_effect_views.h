#ifndef SHARED_DUNGEON_EFFECT_VIEWS_H
#define SHARED_DUNGEON_EFFECT_VIEWS_H
#include "common.h"
/* Views of the EntityRec leading Fixed1616 x/y/z triple. Projection reads
 * unsigned high halves; spawn reads signed high halves. Retail halfword
 * readers use +2,+6,+10; the raise view also updates the z word at +8.
 * Folding these views onto Fixed1616/EntityRec is a follow-up. */
typedef struct PointPosition { u16 pad_00; u16 x; u16 pad_04; u16 y; u16 pad_08; u16 z; } PointPosition;
typedef struct SignedEffectPosition { u16 pad_00; s16 x; u16 pad_04; s16 y; u16 pad_08; s16 z; } SignedEffectPosition;
typedef struct EffectPosition { u16 pad_00; u16 x; u16 pad_04; u16 y; u16 pad_08; u16 z; } EffectPosition;
/* Height-raise view also reads/writes the z word. */
typedef struct RaisedEffectPosition { u16 pad_00; u16 x; u16 pad_04; u16 y; union { s32 word; struct { u16 pad_08; u16 z; } half; } z_slot; } RaisedEffectPosition;
typedef union EffectPositionViews { RaisedEffectPosition raise; SignedEffectPosition spawn; } EffectPositionViews;
typedef union FixedCoord { s32 fixed; struct { u16 frac; s16 whole; } part; } FixedCoord;
typedef struct FixedEffectPosition { FixedCoord x; FixedCoord y; FixedCoord z; } FixedEffectPosition;
/* +8 is copied to the packet; +0x32 is the signed brightness multiplier.
 * The 7/8-bit normalization belongs to each renderer, not the record. */
typedef struct PointRecord { u8 pad_00[8]; u32 color; /* r/g/b/code word copied into the tile */ u8 pad_0C[0x26]; s16 brightness; } PointRecord;
typedef struct PointPacket { u32 tag; u8 r; u8 g; u8 b; u8 code; u32 data; } PointPacket;
/* Observed spawn stores: word +8, signed halfwords +0x14 and +0x32. */
typedef struct SpawnedRecord { u8 pad_00[8]; u32 unk_08; u8 pad_0C[4]; s32 unk_10; s16 unk_14; u8 pad_16[0x1C]; s16 unk_32; } SpawnedRecord;
#endif
