#ifndef SHARED_TYPES3B_TYPES_H
#define SHARED_TYPES3B_TYPES_H

#include "common.h"

/* Two-byte object completion flags immediately before an effect payload.
 * This is an interior prefix view; [-1] must retain its two-byte stride. */
typedef struct ObjectStatusPrefix16 {
    u16 unk_00;
} ObjectStatusPrefix16;

/* Signed coordinate words; no fixed-point unit or allocation extent is implied. */
typedef struct IntVector3 {
    s32 x;
    s32 y;
    s32 z;
} IntVector3;

/* Signed two-coordinate value used by interpolation and grid callers. */
typedef struct SignedPair16 {
    s16 unk_00;
    s16 unk_02;
} SignedPair16;

/* Signed integer height half of a motion position, retaining the 0xC extent. */
typedef struct SignedHeightView {
    u8 pad_00[0xA];
    s16 unk_0A;
} SignedHeightView;

/* Signed integer halves of a three-coordinate position. */
typedef struct SignedPositionView {
    u8 pad_00[2];
    s16 unk_02;
    u8 pad_04[2];
    s16 unk_06;
    u8 pad_08[2];
    s16 unk_0A;
} SignedPositionView;

/* Unsigned X/Z position halves with an opaque middle coordinate. */
typedef struct UnsignedPositionXZView {
    u8 pad_00[2];
    u16 unk_02;
    u8 pad_04[6];
    u16 unk_0A;
} UnsignedPositionXZView;

/* The unsigned sprite flag halfword; distinct from an entity's word at +0x14. */
typedef struct SpriteFlagsView {
    u8 pad_00[0x14];
    u16 unk_14;
} SpriteFlagsView;

/* Sprite tile bytes and byte-addressed animation table, preserving pointer type. */
typedef struct SpriteTableView {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[6];
    u8 *unk_2C;
} SpriteTableView;

/* Payload returned through the object factory's pointer at +8. */
typedef struct ObjectPayloadView {
    u8 pad_00[8];
    void *unk_08;
} ObjectPayloadView;

/* Bank actor status with unsigned flags and signed facing/status fields.
 * This exact 0x70-byte view does not widen to EntityRec. */
typedef struct ActorUnsignedFlagsView {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[5];
    u8 unk_25;
    u8 pad_26[4];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[7];
    s8 unk_6D;
} ActorUnsignedFlagsView;

/* Town event entries expose a signed result at +8; their callers supply stride. */
typedef struct TownEventEntryValueView {
    u8 pad_00[8];
    s32 unk_08;
} TownEventEntryValueView;

/* Item-panel callback's selected value, separate from motion and event entries. */
typedef struct TownPanelSelectionView {
    u8 pad_00[8];
    s32 unk_08;
} TownPanelSelectionView;

/* Format callback's kind value, separate from coordinate Z. */
typedef struct TownFormatKindView {
    u8 pad_00[8];
    s32 unk_08;
} TownFormatKindView;

/* Town resource group selector at +0xA, separate from signed motion height. */
typedef struct TownResourceGroupView {
    u8 pad_00[0xA];
    s16 unk_0A;
} TownResourceGroupView;

/* Effect state number and timer; these two halves are not a coordinate pair. */
typedef struct EffectPhaseTimer16 {
    s16 state;
    s16 timer;
} EffectPhaseTimer16;

/* Minigame progress stage and elapsed time, retained as two signed halves. */
typedef struct MinigameProgressPair16 {
    s16 unk_00;
    s16 unk_02;
} MinigameProgressPair16;

/* Paired town-event arguments returned by select_event_data_table. */
typedef struct TownEventArgumentPair16 {
    s16 unk_00;
    s16 unk_02;
} TownEventArgumentPair16;

/* Source/target identifiers passed to update_flag_test_target. */
typedef struct FlagTestTargetPair16 {
    s16 unk_00;
    s16 unk_02;
} FlagTestTargetPair16;

/* Indexed value records rooted at D_80016470; the two tail words stay opaque. */
typedef struct TownIndexedValueEntry {
    s32 value;
    s32 unk4;
    s32 unk8;
} TownIndexedValueEntry;

/* Town scene mode and its two independently adjusted counters. */
typedef struct TownSceneModeState {
    s32 mode;
    s32 value4;
    s32 value8;
} TownSceneModeState;

/* Three reward/choice values copied by value from town tables.
 * The inherited x/y/z field names do not imply spatial coordinates. */
typedef struct TownRewardValues {
    s32 x;
    s32 y;
    s32 z;
} TownRewardValues;

/* Town search work reads the pointer and its signed high half in distinct paths.
 * Preserve both live alternatives; this view cannot become ObjectPayloadView. */
typedef struct TownSearchWorkView {
    u8 pad_00[8];
    union {
        struct { void *v; } at00;
        struct { u8 pad[2]; s16 v; } at02;
    } unk_08;
} TownSearchWorkView;

/* Score/collection total rooted at the rising-effect controller's first pointer.
 * It shares an offset with sprite flags but is updated as a counter. */
typedef struct TownScoreCounterView {
    u8 pad_00[0x14];
    u16 unk_14;
} TownScoreCounterView;

/* Resource holder reached through TownResourceLinks, without allocator proof. */
typedef struct TownNestedPayloadView {
    u8 pad_00[8];
    void *unk_08;
} TownNestedPayloadView;

/* Signed nested resource value; its +0xA offset alone does not establish height. */
typedef struct TownNestedRecordValueView {
    u8 pad_00[0xA];
    s16 unk_0A;
} TownNestedRecordValueView;

/* Grid-output callback word selected from the controller's two source values.
 * Its pointer is a callback output, not proven to be a delayed motion record. */
typedef struct TownGridOutputView {
    u8 pad_00[8];
    s32 unk_08;
} TownGridOutputView;

/* Destination Y word rooted at the town context's +0x1C position state.
 * Keep this separate from the delayed effect's Z coordinate. */
typedef struct TownDestinationYView {
    u8 pad_00[8];
    s32 unk_08;
} TownDestinationYView;

#endif
