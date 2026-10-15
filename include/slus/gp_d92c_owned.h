#ifndef SLUS_GP_D92C_OWNED_H
#define SLUS_GP_D92C_OWNED_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "shared/runtime_dispatch.h"
#include "common.h"
#include "shared/game_work.h"

extern u8 D_80080A84;
extern short D_80080ABC;
extern short D_80080ABE;
extern short D_80080A94;
extern short D_80080A98;
extern short D_80080A9C;
extern u8 D_80080A8A;
extern u8 D_80080A88;
extern u8 D_80080AA0;

extern void func_8003F320(void);
extern int func_80053EF0(int);
extern void func_8003E758(void);
extern void func_80044618(int);
extern short SD_Call(int a0);
extern void func_80040AA0(int);
extern void func_80053DCC(short saved_setting);
extern void func_80053DF0(short);
extern void func_80053E14(short a0);
extern void func_8003D468(void);

/* Handles a held button combination and restores saved settings when it triggers. */

int func_8003D92C(void);

#endif
