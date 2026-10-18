#ifndef SHARED_TYPES3A_TYPES_H
#define SHARED_TYPES3A_TYPES_H
#include "common.h"

/* Neighbor backlink at +8 used by the resident doubly linked list unlinker. */
typedef struct ListBacklinkView {
    u8 pad_00[0x8];
    void * unk_08;
} ListBacklinkView;

/* Signed key and bitmap-bit value in the resident zero-terminated mapping table. */
typedef struct ResidentBitmapEntry {
    s16 key;
    s16 value;
} ResidentBitmapEntry;

/* Unsigned countdown/state halfword at +A; preserves wrap and signed tests at each use. */
typedef struct UnsignedCountdownView {
    u8 pad_00[0xA];
    u16 unk_0A;
} UnsignedCountdownView;

/* Event-script counter at +0x1C; distinct from entity flags. */
typedef struct ScriptCounterView {
    u8 pad_00[0x1C];
    s32 unk_1C;
} ScriptCounterView;

/* Signed source word at +8 controlling a resident destination flag. */
typedef struct RuntimeSourceValueView {
    u8 pad_00[0x8];
    s32 unk_08;
} RuntimeSourceValueView;

/* Current, previous and newly pressed controller words rooted at GameWork.buttons. */
typedef struct ControllerButtonHistory {
    s32 cur;
    s32 old;
    s32 trg;
} ControllerButtonHistory;

/* Unsigned halfword access within the renderer scratchpad; two-byte extent. */
typedef struct ScratchUnsignedHalf { u16 v; } ScratchUnsignedHalf;

/* Leading unsigned frame value divided by the animation rate divisor. */
typedef struct AnimationFrameRate {
    /* 0x00 */ u16 value;
} AnimationFrameRate;

/* Category/index pair in the twenty-entry table shared by resource slot operations. */
typedef struct ResourceCategoryPair {
    s16 a;
    s16 b;
} ResourceCategoryPair;

/* Two signed screen components used for ellipse triangle vertices. */
typedef struct ScreenPoint16 {
    s16 vx;
    s16 vy;
} ScreenPoint16;

/* Three signed words supplying packed GPU vertex colors; not a position vector. */
typedef struct PacketColorWords {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} PacketColorWords;

/* Three-word display template rooted at D_8002E5E8 and its copied instances. */
typedef struct DisplayPositionWords {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} DisplayPositionWords;

/* Three-word translation passed by address to the GTE helpers; retains the local 12-byte extent. */
typedef struct GteTranslationVector {
    s32 vx;
    s32 vy;
    s32 vz;
} GteTranslationVector;

/* Unsigned high coordinate half at +A used by menu placement. */
typedef struct UnsignedWidgetYView {
    u8 pad_00[0xA];
    u16 unk_0A;
} UnsignedWidgetYView;

/* Menu widget projection exposing the +8 component pointer. */
typedef struct WidgetComponentView {
    u8 pad_00[0x8];
    void * unk_08;
} WidgetComponentView;

/* Signed lifetime word at +8 of the fading resident effect. */
typedef struct EffectCountdownView {
    u8 pad_00[0x8];
    s32 unk_08;
} EffectCountdownView;

/* Three signed coordinate/vector words; units remain defined by the caller. */
typedef struct IntVector3 {
    s32 x;
    s32 y;
    s32 z;
} IntVector3;

/* Three-word sound sequence list state rooted at D_80086CC0. */
typedef struct SoundSequenceListState {
    int unk0;
    int unk4;
    int unk8; /* Retains the original third word and twelve-byte extent. */
} SoundSequenceListState;

/* Signed integer halves at +2/+6/+A in a twelve-byte position projection. */
typedef struct SignedPositionView {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} SignedPositionView;

/* Unsigned flags at +0x14 in the town action dispatcher argument, with 0x16 extent. */
typedef struct SpriteFlagsView {
    u8 pad_00[0x14];
    u16 unk_14;
} SpriteFlagsView;

/* Signed position integer half at +A; never substituted with an unsigned height view. */
typedef struct SignedHeightView {
    u8 pad_00[0xA];
    s16 unk_0A;
} SignedHeightView;

/* Three signed motion words at +C/+10/+14, preserving the sparse 0x18 extent. */
typedef struct MotionDeltaView {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} MotionDeltaView;

/* Unsigned angle value read from the town overlay rotation global. */
typedef struct AngleHalfView {
    u16 unk_00;
} AngleHalfView;

/* Unsigned display coordinate read from the overlay drawing global. */
typedef struct DisplayXHalfView {
    u16 unk_00;
} DisplayXHalfView;

/* Object constructor result projection exposing its +8 payload pointer. */
typedef struct ObjectPayloadView {
    u8 pad_00[0x8];
    void * unk_08;
} ObjectPayloadView;

/* Signed word at +8 carrying a handler-table address; retained as an integer. */
typedef struct HandlerAddressWordView {
    u8 pad_00[0x8];
    s32 unk_08;
} HandlerAddressWordView;

/* Signed word at +0x1C holding a handler-table address; pointer representation is unchanged. */
typedef struct HandlerTableWordView {
    u8 pad_00[0x1C];
    s32 unk_08;
} HandlerTableWordView;

/* Two bytes immediately before an object; bit 0x8000 marks retirement, preserving [-1] stride. */
typedef struct ObjectRetirementFlags {
    u16 unk_00;
} ObjectRetirementFlags;

/* Three signed alternatives selected from the actor height-band value record. */
typedef struct HeightBandValues {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} HeightBandValues;

/* Signed word at +8 containing a primitive resource or style selection. */
typedef struct EffectPrimitiveValueView {
    u8 pad_00[0x8];
    s32 unk_08;
} EffectPrimitiveValueView;

/* Signed state/default word at +8 used by effect setup and callback contexts. */
typedef struct EffectStateWordView {
    u8 pad_00[0x8];
    s32 unk_08;
} EffectStateWordView;

/* Three copied initialization words in the menu/effect allocation payload. */
typedef struct EffectInitialState {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} EffectInitialState;

/* Signed +A halfword in timed-scale setup; keeps its original 0xC view. */
typedef struct ScaleStateHalfView {
    u8 pad_00[0xA];
    s16 unk_0A;
} ScaleStateHalfView;

/* Two signed words in the angle record rooted at D_80100D60. */
typedef struct PositionRotationPair { s16 field_0; s16 angle; } PositionRotationPair;

/* Unsigned map tile identifier and flag bits read with two-byte element stride. */
typedef struct MapTileHalfView {
    u16 unk_00;
} MapTileHalfView;

/* Three signed parameters passed to the item-menu lifecycle handlers. */
typedef struct ItemMenuParameters {
    s32 field0;
    s32 field4;
    s32 field8;
} ItemMenuParameters;

/* Three-word item-menu scene state rooted at D_80110EB8. */
typedef struct ItemMenuSceneState {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} ItemMenuSceneState;

/* Item-menu selection delay status, limit and counter words. */
typedef struct ItemMenuDelayState {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} ItemMenuDelayState;

/* Signed high coordinate half at +A used by menu row and icon placement. */
typedef struct SignedWidgetYView {
    u8 pad_00[0xA];
    s16 unk_0A;
} SignedWidgetYView;

/* Signed enable word at +0x1C of the item-menu referenced state. */
typedef struct ItemMenuEnabledView {
    u8 pad_00[0x1C];
    s32 unk_1C;
} ItemMenuEnabledView;

/* Signed flag word at +0x1C of the shop record. */
typedef struct ItemMenuFlagsView {
    u8 pad_00[0x1C];
    s32 unk_1C;
} ItemMenuFlagsView;

/* Signed cached object code and state selector in D_80083D78. */
typedef struct CachedObjectCodePair {
    s16 unk_00;
    s16 unk_02;
} CachedObjectCodePair;

/* Signed halfword at +A used to initialize a resource-slot state. */
typedef struct ResourceSlotStateView {
    u8 pad_00[0xA];
    s16 unk_0A;
} ResourceSlotStateView;

/* Twelve-byte resource-read state with one active word and two opaque signed words. */
typedef struct ResourceReadState {
    s32 field0;
    s32 pad4;
    s32 pad8;
} ResourceReadState;

/* Signed output word at +8 of the town movement context. */
typedef struct TownMovementOutput {
    u8 pad_00[8];
    s32 value;
} TownMovementOutput;

#endif
