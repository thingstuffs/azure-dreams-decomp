#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "slus.h"
#include "sdk/libc.h"
#include "town/map/motion.h"
#include "town/map/short_lived_particle.h"
#include "shared/object_node.h"

/* Updates the effect's motion and fade state, then refreshes its display. */
void update_effect_motion_and_fade(void *effect, ObjectPosition *motion_data, void *display_data) {
    s16 ticks_left;
    s16 phase_value;
    s32 random_drop;
    s32 x_velocity;
    s32 height;
    ShortLivedParticleBody *body;
    ObjectPosition *motion;
    s32 x_decay;
    void *fade_step;
    register SpriteFrameState *display;

    body = effect;
    motion = motion_data;
    display = display_data;
    phase_value = body->phase;
    switch (phase_value) {
    case 0:
        motion->x.v += (motion->velocity_x / (s16) body->remaining_ticks);
        motion->y.v += (motion->velocity_y / (s16) body->remaining_ticks);
        ticks_left = (u16) body->remaining_ticks - 1;
        body->remaining_ticks = ticks_left;
        phase_value = 0x60;
        if ((ticks_left << 0x10) <= 0) {
            display->tpage_abr = phase_value;
            display->flags |= 0xC;
            body->phase += 1;
        }
        break;
    case 1:
        motion->x.v += motion->velocity_x;
        motion->y.v += motion->velocity_y;
        x_velocity = motion->velocity_x;
        x_decay = x_velocity >> 1;
        motion->velocity_x = x_velocity - x_decay;
        motion->velocity_y -= (motion->velocity_y >> 1);
        fade_step = (void *)0xFFEFEFF0;
        display->color.word += (s32)fade_step;
        if ((u8) display->color.word < 0x11U) {
            NODE_HEADER(body)->flags |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }
    random_drop = (rand() & 7) << 0xF;
    height = motion->z.v;
    height -= random_drop;
    motion->z.v = height;
    advance_sprite_animation_and_textures(display);
}
