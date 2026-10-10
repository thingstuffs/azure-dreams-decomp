#ifndef DUNGEON_OVL_1894800_H
#define DUNGEON_OVL_1894800_H
#include "common.h"
#include "modules/dungeon_native_abi.h"
typedef struct LinkedRenderNode {
    u8 pad0[8];
    void *context;
    void *data;
} LinkedRenderNode;
void func_80024188(void *, void *, void *, s16);
void func_80024758(void *, void *, void *, u16);
s32 func_80024704(void *, void *, void *);
s32 func_80024FD4(void *, void *, void *);
s32 func_80025028(u8 *, u8 *);
void func_80025278(void *, s16 *);
void func_80025814(void *, void *, void *);
void func_80025470(u8 *, void *, u8 *);
void func_80024098(void *, s32, void *);
/* Signed two-byte view of the first counter; indexed reads use its address. */
extern s16 D_80026664;
#endif
