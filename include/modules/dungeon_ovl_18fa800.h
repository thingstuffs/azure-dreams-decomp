#ifndef DUNGEON_OVL_18FA800_H
#define DUNGEON_OVL_18FA800_H
#include "modules/dungeon_native_abi.h"
struct Unk818DAD38Owner;
struct Unk818DAD38Target;
void func_80024538(struct Unk818DAD38Owner *, s32, struct Unk818DAD38Target *);
void func_80024684(void *);
/* Retail callback 80024714 receives its entry in a0; a1/a2/a3 are overwritten before use. */
void func_80024714(void *entry);
#endif
