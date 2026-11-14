#ifndef TOWN_SHOP_MONSTER_STATUS_RESOURCE_CACHE_G00636_H
#define TOWN_SHOP_MONSTER_STATUS_RESOURCE_CACHE_G00636_H
/* Initialize and refresh monster status resource cache: shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B956C, CL:town/func_800B958C, CL:town/func_800B95F4, CL:town/func_800B9634, CL:town/func_800B97F4. */

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B683C_arg0.h"
#include "shared/resident_resources.h"
#include "engine/entity.h"
#include "sdk/libgpu.h"

typedef struct S_800B6CCC_0 {
    s32 unk_00;
    s32 unk_04;
} S_800B6CCC_0;

struct Rec_func_800B683C_arg0;

typedef struct S_800B6E3C_2 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_800B6E3C_2;

extern s32 normalize_monster_status_species_code(s32);
extern s32 select_mapped_object_status_code(void *);
extern void *alloc_gpu_scratch_ring(s32 size);
extern void bzero(void *dst, s32 size);
extern s32 Control_CD();
extern s32 get_enabled_record_flag_priority();
extern s16 display_resource_cache_keys[8];


/* Functions defined in this translation unit. */
void fill_cd_read_descriptor(s32 mode, s32 value_base, S_800B6CCC_0 *entry, s32 data_base);
s32 get_monster_status_species_code(void *object);
void set_monster_status_cd_read_target(void *object);
void clear_monster_status_texture(void *texture);
s32 queue_monster_status_reload(Rec_func_800B683C_arg0 *state);

#endif
