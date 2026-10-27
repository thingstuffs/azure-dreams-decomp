#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
extern void play_movie_with_fixed_display_flag(s32 a0, s32 a1);
extern void SetDispMask(s32 a0);
extern void file_load_com(void *arg);
extern void find_or_load_runtime_resource_key(void *arg);
extern void reserve_twch_load(s32 a0);
extern void town_seq_reserve(s16 sequence_effect, s16 sequence_id);
extern u8 town_scene_resource_descriptor;
extern u8 D_800D1D54;
extern u8 D_80080F48;
extern u8 D_80080F98;
/* Initialize town resources and configure the scene. */
void initialize_resources(void)
{
    u8 *resource_data;
    play_movie_with_fixed_display_flag(1, 0x73);
    SetDispMask(1);
    file_load_com(&town_scene_resource_descriptor);
    resource_data = &D_800D1D54;
    file_load_com(resource_data);
    find_or_load_runtime_resource_key(&D_80080F48);
    find_or_load_runtime_resource_key(&D_80080F98);
    reserve_twch_load(6);
    reserve_twch_load(3);
    town_seq_reserve(0x27, 0x200);
}
