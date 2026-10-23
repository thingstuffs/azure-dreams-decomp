#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"

extern s32 rsin(s32);
extern s32 rcos(s32);
extern void advance_sprite_animation_and_textures(void *);
extern void select_record_entry_and_value(void *, void *, s32);
extern u8 D_800DEAE0[];

#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

/* Advance an expanding spiral effect and update its sprite. */
void update_expanding_spiral_sprite(void *state, void *position, SpriteFrameState *sprite)
{
    s16 angle;
    GameWork *angle_table;
    void *owner;

    owner = *(void **)state;
    U16_AT(owner, 0x14) = U16_AT(owner, 0x14) + 1;
    sprite->color.word = sprite->color.word + 0xFFF7F7F8;

    angle = U16_AT(state, 0x1C) + U16_AT(state, 0x1E);
    angle_table = &g_game_work;
    U16_AT(state, 0x1C) = angle;
    U16_AT(state, 0x1C) = angle % 0x1000;
    U16_AT(state, 0x20) = U16_AT(state, 0x20) + 4;

    S16_AT(position, 2) = U16_AT(state, 6) +
        (((rsin(S16_AT(state, 0x1C)) >> 4) *
          S16_AT(state, 0x20)) >> 8);
    S16_AT(position, 6) = U16_AT(state, 0xA) +
        (((rcos(S16_AT(state, 0x1C)) >> 4) *
          S16_AT(state, 0x20)) >> 8);
    sprite->angle_z =
        (s32)(0 - ((rcos(S16_AT(state, 0x1C) - angle_table->view.camera_rotation.parts.viewAngle) >> 4) << 8)) >> 8;

    advance_sprite_animation_and_textures(sprite);
    if (sprite->flags & 0x6000) {
        select_record_entry_and_value(sprite, D_800DEAE0, 0);
    }
}
