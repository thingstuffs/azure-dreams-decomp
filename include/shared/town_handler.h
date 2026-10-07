#ifndef SHARED_TOWN_HANDLER_H
#define SHARED_TOWN_HANDLER_H

#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_80082D58.h"

struct S_80094A60_0;

/* The third argument is the destination carried through the handler helpers. */
void func_80094984(s32 *entries, Rec_func_80094268_arg0 *record, void *ptr2);
void func_80094A60(s32 *values, struct S_80094A60_0 *selector, void *ptr2);
void func_80094A38(s32 value, Rec_D_80082D58 *record, void *ptr2);
void func_800949C4(u8 *sourceBytes, s32 selection, u8 *destination);

#endif
