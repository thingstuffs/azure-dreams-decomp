#ifndef TOWN_OVL_6490C0_H
#define TOWN_OVL_6490C0_H
#include "common.h"

struct TownObjectSet;

extern u8 D_80017760[];
extern u8 D_800178C0[];

s32 apply_selected_scene_entry(struct TownObjectSet *, s32, s32);
s32 dispatch_first(struct TownObjectSet *dispatch_value, s32 unused, s32 dispatch_option);

#endif
