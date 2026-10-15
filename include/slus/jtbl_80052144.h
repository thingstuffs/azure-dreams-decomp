#ifndef SLUS_JTBL_80052144_H
#define SLUS_JTBL_80052144_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "shared/runtime_dispatch.h"
#include "common.h"
#include "shared/game_work.h"

typedef struct Child {
    u8 pad00[0x1E];
    u16 flags;
} Child;

typedef struct Controller {
    s16 state;
    s16 timer;
    s16 attached;
    s16 finished;
    s16 *script;
    Child *child0;
    Child *child1;
    Child *child2;
    Child *child3;
    void *group;
} Controller;

typedef struct Shared83160 {
    u8 pad00[0x10];
    s32 flags10;
} Shared83160;

extern Shared83160 D_80083160;

extern s32 D_800814A0;


extern void func_800530C4(void *);
extern s16 SD_Call(s32);
extern s32 func_80053EF0(s32);
extern void func_80051528(void *);
extern void func_800517AC(void *);
extern void func_800530A4(void *);
extern void func_80051CA4(void *);
extern void func_80051F38(void *);
extern void func_80041094(s32, s32, s32, s32, s32);

/* Advances the timed child sequence and retires the controller when all children finish. */

void func_80052144(Controller *controller);

#endif
