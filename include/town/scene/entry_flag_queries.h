#ifndef INCLUDE_TOWN_SCENE_ENTRY_FLAG_QUERIES_H
#define INCLUDE_TOWN_SCENE_ENTRY_FLAG_QUERIES_H

#include "common.h"

struct TownObjectSet;

struct FlagTestRecord;
struct ScriptContext;
struct ScriptEntry8;

s32 set_entry_flag_if_viv_engei_ok(struct TownObjectSet *target, s32 value);
s32 set_sbs24_pad04_if_ready(void);
s32 set_taiin_if_ready(void);

#endif
