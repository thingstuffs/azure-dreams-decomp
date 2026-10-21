#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/audio.h"
#include "engine/graphics.h"
#include "engine/movie.h"
#include "engine/scene.h"
#include "engine/town.h"
#include "sdk/libetc.h"
#include "sdk/libgpu.h"
#include "slus.h"
#include "slus/data.h"

s32 reserve_twch_load(s32);
void reserve_tw_mon_load(s32 reservation_value);
void plt_init_sleep_set(void);
extern M2C_UNK town_scene_resource_descriptor;
extern M2C_UNK D_800D1D54;
extern M2C_UNK D_800D1E7C;

/* Synchronize rendering, enable display output, and run runtime setup. */
void setup_town_scene(void) {
    VSync(0);
    VSync(0);
    DrawSync(0);
    SD_Call(0x7F);
    drain_audio_commands_and_service_channels();
    VSync(0);
    town_movie_exe(0x16, 0x5DB);
    SetDispMask(1);
    file_load_com(&town_scene_resource);
    file_load_com(&town_scene_resource_descriptor);
    file_load_com(&D_800D1D54);
    file_load_com(&D_800D1E7C);
    load_alternate_sprite_bundle_and_clear_textures();
    init_town_runtime_objects();
    find_or_load_runtime_resource_key(&town_scene_setup_resource);
    reserve_twch_load(1);
    reserve_tw_mon_load(1);
    plt_init_sleep_set();
}
