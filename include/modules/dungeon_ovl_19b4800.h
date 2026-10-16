#ifndef DUNGEON_OVL_19B4800_H
#define DUNGEON_OVL_19B4800_H
#include "common.h"
#include "modules/dungeon_native_abi.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
struct TransitionState;
typedef struct { u16 x, y, w, h; } Rect16;
typedef struct { Rect16 rect[8]; } RectTable;
typedef struct { u32 word[3]; } __attribute__((packed)) PackedVec3;
void func_8002405C(void *, void *, void *);
void func_80024104(void *);
void dungeonCreateAnLinkedParentInitializePositionPartData(void *, void *, void *);
void dungeonFadeThePrimitiveFlagEffectCountdownExpires(void *, void *, u8 *);
void func_8002458C(struct TransitionState *, void *, void *);
extern const RectTable D_80024004;
extern PackedVec3 D_8002533C;
extern s16 D_80025384;
void func_800B8FC8(s32, void *, void *, s32, s16);
#endif
