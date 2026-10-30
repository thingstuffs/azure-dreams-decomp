#ifndef MODULES_TOWN_OVL_3FE0D0_P00_H
#define MODULES_TOWN_OVL_3FE0D0_P00_H
#include "common.h"
#include "town/scene/service.h"
#include "shared/record_ptrs.h"
#include "shared/town_event_state.h"
#include "shared/town_pointees.h"
#include "shared/town_root.h"

typedef void (*SceneCallType2)(void);
typedef struct {
    SceneCallType2 callback;
    s32 unused;
} CallbackEntry;
typedef struct {
    u8 pad0[8];
    s32 callbackIndex;
    u8 padC[0x34];
    CallbackEntry *callbacks;
} Runtime;
typedef struct {
    s32 _0;
    s32 _4;
} EntryWords;
typedef struct {
    void *_0;
    s32 _4;
    s32 _8;
} PointerRecord;
typedef struct S_8047E130_2 {
    EntryWords * unk_00;
} S_8047E130_2;
typedef struct S_8047E178_2 {
    EntryWords * unk_00;
} S_8047E178_2;
typedef void (*TownCall)(s32, s32);
typedef struct S_func_8047E1C0_3 {
    u8 pad_00[0x2EC];
    TownCall unk_2EC;
} S_func_8047E1C0_3;
typedef struct { unsigned char pad_000[0x2a4]; int (*service)(int); } SceneService2A4;
typedef union { PointerRecord record; s32 *pointers[3]; s32 *pointer; } ScenePointerStorage;
extern u8 D_80016178[3];
extern s32 D_80017720[3];
extern ScenePointerStorage D_8001794C;
extern s32 D_80017B88[3];
extern u8 D_800161C0[3];
extern s32 scene_mode_event_data[3];
extern s32 D_80017E66[3];
extern s32 D_8001624C;
extern s32 D_800177C8;
extern s32 D_8001802A;
extern u8 D_80010000[];
extern s32 D_8001781C;
extern s32 D_8001857C;
extern s32 scene_event_data;
extern s32 D_80017870;
/* Placed copy of clear_script_flag_bit. */
void func_800175E0(s32 bit_index);
s32 dispatch_town_callback_or_fallback(void);
void dispatch_town_callback_or_default(s32 value0, s32 value1);
void initialize_context_entry_tables_variant_1(s32 unused_a, s32 unused_b);
void initialize_context_entry_tables_variant_2(void);
void play_town_sound_b1(void);
void advance_floor_event_counter(void);
void set_active_position_state_record(void);

void func_80016278(void);
void run_scene_service_224(void);
void func_800162B8(void);
void call_first_handler_if_flag_0x3ec_set(void);
void call_scene_service_280_1705(void);
void func_80016328(void);
void call_scene_service_280_1706(void);
void func_80016360(void);
void play_town_sound_1700(void);
void select_table_result_with_override(void);
void invoke_system_callback_29(void);
void func_80016408(void);

#endif
