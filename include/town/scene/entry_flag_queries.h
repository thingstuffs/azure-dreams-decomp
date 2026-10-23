#ifndef INCLUDE_TOWN_SCENE_ENTRY_FLAG_QUERIES_H
#define INCLUDE_TOWN_SCENE_ENTRY_FLAG_QUERIES_H

#include "common.h"

struct FlagTestRecord;
struct ScriptContext;
struct ScriptEntry8;

s32 dispatch_entry_flag_query_if_ready(s32 target, s32 value);
s32 set_sbs24_pad04_if_ready(void);
s32 set_taiin_if_ready(void);
s32 test_alternate_record_flag_when_enabled(struct FlagTestRecord *record);
s32 test_record_flag_when_enabled(struct FlagTestRecord *record);
void query_scene_entry_flag_a(struct ScriptEntry8 *entries, struct ScriptContext *context, s32 entry_key);
void query_scene_entry_flag_b(struct ScriptEntry8 *entries, struct ScriptContext *context, s32 entry_key);
void query_scene_entry_flag_c(struct ScriptEntry8 *entries, struct ScriptContext *context, s32 entry_key);
void query_scene_entry_flag_d(struct ScriptEntry8 *entries, struct ScriptContext *context, s32 entry_key);
void query_scene_entry_flag_e(struct ScriptEntry8 *entries, struct ScriptContext *context, s32 entry_key);
void query_scene_entry_flag_f(struct ScriptEntry8 *entries, struct ScriptContext *context, s32 entry_key);
void query_scene_entry_flag_g(struct ScriptEntry8 *entries, struct ScriptContext *context, s32 entry_key);
void query_scene_entry_flag_h(struct ScriptEntry8 *entries, struct ScriptContext *context, s32 entry_key);
void query_scene_entry_flag_i(struct ScriptEntry8 *entries, struct ScriptContext *context, s32 entry_key);
void query_scene_entry_flag_j(struct ScriptEntry8 *entries, struct ScriptContext *context, s32 entry_key);
void query_scene_entry_flag_k(struct ScriptEntry8 *entries, struct ScriptContext *context, s32 entry_key);

#endif
