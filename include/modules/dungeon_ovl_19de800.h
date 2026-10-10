#ifndef DUNGEON_OVL_19DE800_H
#define DUNGEON_OVL_19DE800_H
#include "common.h"
typedef struct {
    s16 x;
    u16 y;
} OffsetPair;
typedef struct {
    OffsetPair entries[8];
} OffsetTable;
extern const OffsetTable D_80024028;
struct S_80024AE8_3;
struct S_80024BF4_1;
struct S_80024BF4_2;
struct S_80024BF4_4;
struct S_80025FB0_0;
struct S_80025FB0_1;
struct Bank19de800_19e092c_EntryCursor;
struct S_func_80026418_0;
void *func_80024064(s32, s32, s16);
s32 func_8002458C(s32);
void func_80024AE8(s32, struct S_80024AE8_3 *);
void func_80024BF4(struct S_80024BF4_4 *, struct S_80024BF4_1 *, struct S_80024BF4_2 *, s16);
void func_800251F4(s32, s32, s16, s16);
/* Retail callers pass promoted scalar words; the callee reads their low halves. */
s32 func_80025CE8(s32, s32, s32, s32);
void func_80025FB0(struct S_80025FB0_1 *, struct S_80025FB0_0 *);
void func_80026060(void *, s16 *, s32, s32);
void func_8002612C(struct Bank19de800_19e092c_EntryCursor *, s16);
void func_8002626C(s32,s32,s32,s32,s32,s32,s32,s32,s32,s32);
void func_80026418(struct S_func_80026418_0 *);
s32 func_8004491C(void *, s32, ...);
s32 func_8003DB94(void *, void *, s32);
void func_80064BC0(void *, void *);
s32 func_800A56E0(s32);
extern s16 D_8002992E;
extern void *D_80028630;
void func_80024398(void *);
void func_800246B0(void *, void *, void *);
void func_800247C0(void *, void *);
s32 func_80025034(void *, void *, void *);
void func_80025088(void *, void *, void *);
void func_80025800(void *, void *, void *);
void func_8002615C(void *, void *, void *);
#endif
