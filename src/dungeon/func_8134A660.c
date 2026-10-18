#include "common.h"
#include "shared/object_flags.h"

typedef struct DungeonFade {
    u8 r;
    u8 g;
    u8 b;
    u8 pad03;
    s8 scaled_r;
    s8 scaled_g;
    s8 scaled_b;
    u8 pad07;
    s32 value;
    u8 pad0C[0x26];
    s16 step;
    s16 divisor;
} DungeonFade;


/* Move the fade effect backward by two units while updating its scaled colors. */
void update_receding_scaled_rgb_fade(DungeonFade *fade, void *progress) {
    s16 steps_left;

    *(s32 *)((u8 *)progress + 8) -= 0x20000;
    fade->scaled_r = (fade->r * fade->step) / fade->divisor;
    fade->scaled_g = (fade->g * fade->step) / fade->divisor;
    fade->scaled_b = (fade->b * fade->step) / fade->divisor;
    steps_left = (u16)fade->step - 1;
    fade->step = steps_left;
    fade->value = *(s32 *)&fade->scaled_r;
    if ((steps_left << 16) <= 0) {
        *(u16 *)((u8 *)fade - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
