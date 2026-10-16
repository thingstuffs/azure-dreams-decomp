#ifndef R108_BANK42_H
#define R108_BANK42_H
#include "common.h"
#include "modules/dungeon_native_abi.h"
typedef struct { u16 x,y,w,h; } __attribute__((packed)) Rect;
typedef struct { s16 x,y; } Point;
typedef struct { s16 x; u16 y; } Coord;
typedef struct { Coord value[8]; } __attribute__((packed)) CoordTable;
typedef struct { u32 word[3]; } __attribute__((packed)) Packed12;
extern const Rect D_80024038, D_80024040;
extern const CoordTable D_80024064;
extern s16 D_80025630;
void func_800240AC(void *,s32,void *);
struct PointRecord; struct EntityRec;
s32 func_80024154(struct PointRecord *,struct EntityRec *);
struct EffectRecord; struct EntityRec;
void dungeonHandleRaisePositionTowardQueriedHeightSetFlagsCountdownExpires(struct EffectRecord *,struct EntityRec *);
void dungeonHandleRetailN8190AC70Callee80024470SpawnEffectUnderParentNodePlacedParent(ObjectNodeHeader *,s16,s32,s16,s16,s16,s16);
s32 dungeonGetARandomInN0LimitZeroLimitZeroRejectionSampling(s32);
void dungeonAdvanceTheAnimationDrawsRectanglesInRandomizedOrder(void *,s32 *,void *);
struct S_func_8190B2D0_0;
void dungeonUpdateAMovingEffectTargetAnimationCleanupState(struct S_func_8190B2D0_0 *,void *,void *);
void func_800B8FC8(void *,void *,void *,s32,s32);
#endif
