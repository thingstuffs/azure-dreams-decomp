#ifndef SHARED_DUNGEON_MOVING_VIEWS_H
#define SHARED_DUNGEON_MOVING_VIEWS_H
#include "common.h"
/* Partial moving-effect views; signed/unsigned counter operations share two bytes. */
typedef struct BankEffectCounter { union { s16 s; u16 u; } value; } BankEffectCounter;
typedef struct MovingEffectState_pre {
    u16 unk_00;
} MovingEffectState_pre;   /* the 0x2 bytes before self in func_80024050, addressed as self[-1] */

typedef struct MovingEffectState {
    u8 * unk_00;
    void * unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u16 unk_0C;
    u16 unk_0E;
    union { u16 u; s16 s; } unk_10;   /* accessed as both */
    u8 unk_12;
    u8 pad_13[0x1];
    u16 unk_14;
    union { u16 u; s16 s; } unk_16;   /* accessed as both */
    union { s16 s; u16 u; } unk_18;   /* accessed as both */
    u8 pad_1A[0x2];
    union {
        struct { u32 v; } at00;
        struct { u8 pad[0x2]; u8 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
        struct { u8 pad[0x2]; s8 v; } at02p;
        struct { u8 pad[0x3]; u8 v; } at03;
        struct { u8 pad[0x3]; s8 v; } at03u;
    } unk_1C;   /* overlapping accesses */
    union {
        struct { u8 v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_20;   /* overlapping accesses */
    u8 pad_22[0xA];
    union { s32 i; void * p; } unk_2C;   /* accessed as both */
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_30;   /* overlapping accesses */
} MovingEffectState;   /* self in func_80024050 */

typedef struct MovingObject {
    u8 pad_00[0x8];
    u8 * unk_08;
    void * unk_0C;
} MovingObject;   /* base in func_80024050 */

typedef struct MovingSprite {
    u8 pad_00[0x8];
    void * unk_08;
    union {
        struct { u32 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
    } unk_0C;   /* overlapping accesses */
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} MovingSprite;   /* part in func_80024050 */

typedef struct SignedWordView {
    u16 unk_00;
} SignedWordView;   /* D_80026470 in func_80024050 */

typedef struct SignedHalfView {
    u16 unk_00;
} SignedHalfView;   /* D_80026474 in func_80024050 */

typedef struct UnsignedWordView {
    u16 unk_00;
} UnsignedWordView;   /* D_80026476 in func_80024050 */

typedef struct UnsignedHalfView {
    u32 unk_00;
} UnsignedHalfView;   /* D_800265C0 in func_80024050 */

typedef struct UnsignedByteView {
    u32 unk_00;
} UnsignedByteView;   /* D_800265C4 in func_80024050 */

typedef struct MovingActor_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} MovingActor_pre;   /* the 0x14 bytes before owner in func_80024050, addressed as owner[-1] */

typedef struct MovingActor {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    union { u8 * p; void * p2; } unk_60;   /* accessed as both */
    u8 pad_64[0xC];
    union {
        struct { u32 v; } at00;
        struct { u8 pad[0x2]; s8 v; } at02;
        struct { u8 pad[0x3]; s8 v; } at03;
    } unk_70;   /* overlapping accesses */
    u8 pad_74[0x14];
    u16 unk_88;
} MovingActor;   /* owner in func_80024050 */

typedef struct UnusedBankPageView {
    u8 pad_00[0x6484];
    u16 unk_6484;
} UnusedBankPageView;   /* page in func_80024050 */

typedef struct MovingParameter {
    u8 pad_00[0x8];
    u32 unk_08;
} MovingParameter;   /* addr in func_80024050 */

typedef struct MovingMotion {
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_00;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_08;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_0C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_10;   /* overlapping accesses */
} MovingMotion;   /* motion in func_80024050 */

typedef struct MovingPosition {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} MovingPosition;   /* record in func_80024050 */

typedef struct OriginOffsetView {
    u8 pad_00[0x4];
    u16 unk_04;
} OriginOffsetView;   /* scratch in func_80024050 */

typedef struct MovingTarget_pre {
    u8 * unk_00;
    u8 pad_04[0x14];
} MovingTarget_pre;   /* the 0x18 bytes before target in func_80024050, addressed as target[-1] */

typedef struct MovingTarget {
    u8 pad_00[0x88];
    u16 unk_88;
} MovingTarget;   /* target in func_80024050 */

typedef struct MovingTargetPosition {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} MovingTargetPosition;   /* target_part in func_80024050 */

typedef struct MovingTile {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} MovingTile;   /* target_record in func_80024050 */

typedef struct MovingHeight {
    u16 unk_00;
} MovingHeight;   /* D_800269C8 in func_80024050 */



typedef struct RuntimeStatusPage {
    u8 pad_00[0x346C];
    u32 unk_346C;
} RuntimeStatusPage;   /* tail_page0 in func_80024050 */

typedef struct RuntimeFlagsPage {
    u8 pad_00[0x14A0];
    u32 unk_14A0;
} RuntimeFlagsPage;   /* tail_page1 in func_80024050 */

typedef struct MovingSpriteFlags {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} MovingSpriteFlags;   /* ((MovingObject *)base)->unk_0C in func_80024050 */

typedef struct MovingAnimationFlags {
    u16 unk_00;
} MovingAnimationFlags;   /* ((MovingEffectState *)self)->unk_04 in func_80024050 */

typedef struct MovingSpawnFlags {
    u8 pad_00[0x1E];
    u16 unk_1E;
} MovingSpawnFlags;   /* ((MovingEffectState *)self)->unk_2C.p in func_80024050 */

#endif
