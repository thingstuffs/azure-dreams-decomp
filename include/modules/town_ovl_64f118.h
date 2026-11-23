#ifndef TOWN_OVL_64F118_H
#define TOWN_OVL_64F118_H
#include "modules/town_ovl_64f0c0.h"

struct TownObjectSet;
extern s32 func_80017434(void);
extern char D_80017570[];
void select_count_cycled_response(struct TownObjectSet *forwardedValue, s32 unused, s32 forwardedData);
void *select_response_with_two_overrides(struct TownObjectSet *input, s32 unused_1, s32 input_code, s32 unused_3);
#endif
