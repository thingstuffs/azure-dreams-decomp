#include "common.h"
#include "m2c_compat.h"

#include "common.h"

s32 DrawSync(s32);
s32 SetDispMask(s32);
s32 VSync(s32);
void town_movie_exe();            /* extern */
void load_alternate_sprite_bundle_and_clear_textures();                            /* extern */
void init_town_runtime_objects();                            /* extern */
s32 find_or_load_runtime_resource_key();                   /* extern */
void file_load_com();                   /* extern */
short SD_Call(int flags);
void drain_audio_commands_and_service_channels();                            /* extern */
s32 reserve_twch_load(s32);
void reserve_tw_mon_load(s32 reservation_value);
void plt_init_sleep_set(void);
extern M2C_UNK D_80080E28;
extern u32 town_scene_resource;
extern M2C_UNK town_scene_setup_resource;
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
    file_load_com(&D_80080E28);
    file_load_com(&D_800D1D54);
    file_load_com(&D_800D1E7C);
    load_alternate_sprite_bundle_and_clear_textures();
    init_town_runtime_objects();
    find_or_load_runtime_resource_key(&town_scene_setup_resource);
    reserve_twch_load(1);
    reserve_tw_mon_load(1);
    plt_init_sleep_set();
}
