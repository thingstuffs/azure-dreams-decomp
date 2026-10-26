#ifndef TOWN_OVL_6490C0_H
#define TOWN_OVL_6490C0_H
#include "common.h"

extern s32 get_flag_test_table_address(void *, void *, s32, s32);
extern u8 D_80017760[];
extern u8 D_800178C0[];

s32 process_value_with_fixed_tables(s32, s32, s32);
s32 dispatch_first(s32 dispatch_value, s32 unused, s32 dispatch_option);

#endif
