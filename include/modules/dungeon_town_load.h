#ifndef DUNGEON_TOWN_LOAD_H
#define DUNGEON_TOWN_LOAD_H
#include "common.h"
#include "m2c_compat.h"
#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)
extern s32 D_800CF85C[];
extern u8 D_800CF828[16];
extern s32 D_800CF838[16];
extern u8 D_80080EA8[];
extern void file_load_com(s32);
s32 func_8008B2E4(s32 value);
s32 func_8008B328(void);
s32 func_8008B3AC(void);
void reserve_twch_load(s32 entry_id);
void func_8008B4B0(void);
#endif
