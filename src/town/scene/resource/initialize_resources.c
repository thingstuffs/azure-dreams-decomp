#include "shared/game_work.h"

#include "common.h"
#include "slus.h"
#include "engine/movie.h"
#include "engine/scene.h"
#include "sdk/libgpu.h"
#include "town/map/resource.h"

extern void reserve_twch_load(s32 a0);
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
