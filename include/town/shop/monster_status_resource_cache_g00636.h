#ifndef TOWN_SHOP_MONSTER_STATUS_RESOURCE_CACHE_G00636_H
#define TOWN_SHOP_MONSTER_STATUS_RESOURCE_CACHE_G00636_H
/* Initialize and refresh monster status resource cache (G00636): shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B956C, CL:town/func_800B958C, CL:town/func_800B95F4, CL:town/func_800B9634, CL:town/func_800B97F4. */

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B683C_arg0.h"
#include "shared/resident_resources.h"

typedef struct S_800B6CCC_0 {
    s32 unk_00;
    s32 unk_04;
} S_800B6CCC_0;

struct Rec_func_800B683C_arg0;

typedef struct S_800B6E3C_2 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_800B6E3C_2;

extern s32 get_entity_effect_value(void *, s8);
extern s32 normalize_monster_status_species_code(s32);
extern s32 select_mapped_object_status_code(void *);
extern void *alloc_gpu_scratch_ring(s32 size);
extern void bzero(void *dst, s32 size);
extern void func_80067014(s32 sync_mode);
extern void func_800672D8(s16 *rect, void *data);
extern s32 Control_CD();
extern s32 get_enabled_record_flag_priority();
s32 release_monster_status_request_handles(struct Rec_func_800B683C_arg0 *);
extern s16 display_resource_cache_keys[8];
extern u8 D_800B5B20[16];

/* Functions defined in this translation unit. */
void initialize_mode_offset_entry(s32 mode, s32 value_base, S_800B6CCC_0 *entry, s32 data_base);
s32 get_mapped_object_code(void *object);
void initialize_coordinate_entry(void *object);
void clear_monster_status_texture(void *texture);
s32 invalidate_cached_state_and_queue_read(void *state);

#endif
