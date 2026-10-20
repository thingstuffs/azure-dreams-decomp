#include "common.h"

typedef struct {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;
extern s32 interpolate_actor_to_terrain_tile(void);
extern u8 D_800D8C64[];

void run_terrain_tile_interpolation(CallbackOwner *owner) {
    if (interpolate_actor_to_terrain_tile() != 0) {
        owner->callback = D_800D8C64;
    }
}
