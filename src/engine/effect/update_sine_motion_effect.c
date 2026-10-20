#include "slus/jtbl_800517CC.h"

#include "common.h"

/* Rodata owner: the row's switch emits its jump table(s) into this object's .rodata,
 * placed at the retail address by config/slus_modules.json (assets/800.bin carve). */

#include "slus/jtbl_800517CC.h"

void update_sine_motion_effect(
    EffectState800517CC *effect,
    VecState800517CC *motion,
    ColorState800517CC *color)
{
    u32 state_index;

    effect->timer++;
    func_800478B8(color);

    state_index = effect->state;
    switch (state_index) {
    case 0:
        if (effect->trigger != 0) {
            effect->trigger = 0;
            effect->timer = 0;
            effect->state = (u16)effect->state + 1;
        }
        return;
    case 1:
        if ((s16)effect->timer >= 0x60) {
            effect->timer = 0;
            effect->state = (u16)effect->state + 1;
        }
        return;
    case 2:
        motion->x = 0x01A00000 - ((rsin((s16)effect->timer << 4) >> 4) << 16);
        motion->y = ((rcos((s16)effect->timer << 4) >> 4) << 14) + 0x00200000;
        if ((s16)effect->timer >= 0x40) {
            effect->timer = 0;
            effect->state = (u16)effect->state + 1;
        }
        return;
    case 3:
        motion->x = 0x00C00000 - ((rcos((s16)effect->timer << 5) >> 4) << 13);
        motion->y = ((rsin((s16)effect->timer << 5) >> 4) << 12) + 0x00200000;
        if ((s16)effect->timer >= 0x20) {
            motion->z = 0x00800000;
            effect->wait = (rand() % 64) + 0x20;
            effect->timer = 0;
            effect->state = (u16)effect->state + 1;
        }
        return;
    case 4:
        if ((s16)effect->timer >= effect->wait) {
            s32 next_state = (u16)effect->state + 1;
            effect->timer = 0;
            effect->state = next_state;
        }
        if (effect->trigger != 0) {
            effect->trigger = 0;
            effect->timer = 0;
            effect->state = 7;
        }
        return;
    case 5:
    {
        s32 cos_value;
        s32 accel;
        s32 displacement;
        s32 center_offset;
        s32 round_bias;
        s32 next_vx;
        s32 next_x;

        cos_value = rcos(((s16)effect->timer + 0x100) << 3) >> 4;
        accel = (cos_value * 3) << 11;
        displacement = motion->x;
        center_offset = (s32)0xFF280000;
        displacement += center_offset;
        accel -= displacement;
        round_bias = (s32)((u32)accel >> 31);
        accel += round_bias;
        accel >>= 1;
        next_vx = motion->vx + accel;
        next_x = motion->x + next_vx;
        motion->vx = next_vx;
        motion->x = next_x;
    }

        {
            s32 accel;
            s32 displacement;
            s32 center_offset;
            s32 round_bias;
            s32 next_vy;
            s32 next_y;

            accel = rcos((s16)effect->timer << 3) >> 4;
            accel <<= 10;
            displacement = motion->y;
            center_offset = (s32)0xFFD40000;
            displacement += center_offset;
            accel -= displacement;
            round_bias = (s32)((u32)accel >> 31);
            accel += round_bias;
            accel >>= 1;
            next_vy = motion->vy + accel;
            next_y = motion->y + next_vy;
            motion->vy = next_vy;
            motion->y = next_y;
        }

        if ((s16)effect->timer >= 0x100) {
            s32 next_state = (u16)effect->state + 1;
            effect->timer = 0;
            effect->state = next_state;
        }
        if (effect->trigger != 0) {
            effect->trigger = 0;
            effect->timer = 0;
            effect->state = 7;
        }
        return;
    case 6:
    {
        s32 cos_value;
        s32 accel;
        s32 displacement;
        s32 center_offset;
        s32 round_bias;
        s32 next_vx;
        s32 next_x;

        cos_value = rcos((s16)effect->timer << 4) >> 4;
        accel = (cos_value * 3) << 11;
        displacement = motion->x;
        center_offset = (s32)0xFF280000;
        displacement += center_offset;
        accel -= displacement;
        round_bias = (s32)((u32)accel >> 31);
        accel += round_bias;
        accel >>= 1;
        next_vx = motion->vx + accel;
        next_x = motion->x + next_vx;
        motion->vx = next_vx;
        motion->x = next_x;
    }

        {
            s32 accel;
            s32 displacement;
            s32 center_offset;
            s32 round_bias;
            s32 next_vy;
            s32 next_y;

            accel = rcos(((s16)effect->timer + 0x80) << 4) >> 4;
            accel <<= 10;
            displacement = motion->y;
            center_offset = (s32)0xFFD40000;
            displacement += center_offset;
            accel -= displacement;
            round_bias = (s32)((u32)accel >> 31);
            accel += round_bias;
            accel >>= 1;
            next_vy = motion->vy + accel;
            next_y = motion->y + next_vy;
            motion->vy = next_vy;
            motion->y = next_y;
        }

        if ((s16)effect->timer >= 0x80) {
            effect->wait = (rand() % 64) + 0x20;
            effect->timer = 0;
            effect->state = 4;
        }

        if (effect->trigger != 0) {
            effect->trigger = 0;
            effect->timer = 0;
            effect->state = 7;
        }
        return;
    case 7:
        motion->x += (s32)0xFFF40000;
        motion->y += 0x00020000;
        if ((s16)effect->timer < 0x40) {
            return;
        }
        break;
    default:
        color->b = 0;
        color->g = 0;
        color->r = 0;
    }

    ((ParentState800517CC *)effect->parent)->child10 = 0;
    ((ParentState800517CC *)effect->parent)->timer++;
    *(u16 *)((u8 *)effect - 2) |= 0x8000;
    D_800814A0 |= 0x8000;
}
