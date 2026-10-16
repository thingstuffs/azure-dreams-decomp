#include "modules/dungeon_ovl_1930844.h"

void dungeonUpdateTheFiveOrbitingPointsAdvanceEffectAnimation(ovl_1930844_81911BF4_Obj81911BF4 *effect, s32 *position)
{
    s32 point_index;
    s32 brightness;
    s32 fade;
    u16 angle_step;
    s16 angle_sum;
    s32 signed_angle;
    s32 angle_dividend;
    s32 state;

    effect->inner->field14++;
    effect->timer++;

    for (point_index = 0; point_index < 5; point_index++) {
        effect->x[point_index] = position[0] + (((func_800644B8(point_index * 0x333 + effect->angle) >> 4) * effect->scale) << 8);
        effect->y[point_index] = position[1] + (((func_80064584(point_index * 0x333 + effect->angle) >> 4) * effect->scale) << 8);
    }

    state = effect->state;
    if ((u32)state >= 7U) {
        return;
    }

    switch (state) {
    case 0:
        dungeonBuildAndDepthSortsFiveRadialLineSegmentsEffect(effect, position, effect->timer, effect->duration);
        if (effect->timer < effect->duration) {
            return;
        }
        position[2] = effect->field14 << 16;
        effect->timer = 0;
        effect->state++;
        return;

    case 1:
        dungeonBuildAndEnqueueFiveTranslucentQuadsBetweenInterpolatedPoints(effect, position, effect->timer, effect->duration);
        if (effect->timer < effect->duration) {
            return;
        }
        effect->timer = 0;
        effect->duration = 4;
        effect->state++;
        return;

    case 2:
        dungeonBuildAndEnqueueFiveTranslucentQuadsBetweenInterpolatedPoints(effect, position, 0, 0);
        dungeonBuildAndQueueInterpolatedVerticalQuadsAroundFivePerimeterPoints(effect, position, effect->timer, effect->duration);
        if (effect->timer < effect->duration) {
            return;
        }
        effect->field12 = 3;
        effect->timer = 0;
        effect->duration = 0x10;
        effect->state++;
        return;

    case 3:
        effect->angle_step += 0x10;
        effect->angle += effect->angle_step;
        signed_angle = effect->angle;
        effect->field10 += 0x10;
        effect->angle = signed_angle % 0x1000;
        dungeonBuildAndEnqueueFiveTranslucentQuadsBetweenInterpolatedPoints(effect, position, 0, 0);
        dungeonBuildAndQueueInterpolatedVerticalQuadsAroundFivePerimeterPoints(effect, position, 0, 0);
        if (effect->timer < effect->duration) {
            return;
        }
        effect->timer = 0;
        effect->state++;
        return;

    case 4:
        angle_step = effect->angle_step;
        angle_sum = (u16)effect->angle;
        brightness = effect->field42;
        angle_step += 0x10;
        angle_sum += angle_step;
        signed_angle = (s16)angle_sum;
        angle_dividend = signed_angle;
        brightness += 0x0C;
        effect->field42 = brightness;
        effect->field41 = brightness;
        effect->angle_step = angle_step;
        effect->angle = angle_sum;
        effect->scale = (u16)effect->scale - 4;
        if (angle_dividend < 0) {
            angle_dividend += 0xFFF;
        }
        effect->angle = signed_angle - ((angle_dividend >> 12) << 12);
        dungeonBuildAndEnqueueFiveTranslucentQuadsBetweenInterpolatedPoints(effect, position, 0, 0);
        dungeonBuildAndQueueInterpolatedVerticalQuadsAroundFivePerimeterPoints(effect, position, 0, 0);
        if (effect->timer < effect->duration) {
            return;
        }
        dungeonCreateObjectHex212InitializeDataPointerMode(effect);
        effect->timer = 0;
        effect->duration = 0x20;
        effect->state++;
        return;

    case 5:
        angle_step = effect->angle_step;
        angle_sum = (u16)effect->angle;
        fade = effect->field42;
        angle_step += 0x10;
        angle_sum += angle_step;
        signed_angle = (s16)angle_sum;
        angle_dividend = signed_angle;
        fade -= 6;
        effect->field42 = fade;
        effect->field41 = fade;
        effect->field40 = fade;
        effect->angle_step = angle_step;
        effect->angle = angle_sum;
        effect->scale = (u16)effect->scale + 0x0C;
        if (angle_dividend < 0) {
            angle_dividend += 0xFFF;
        }
        effect->angle = signed_angle - ((angle_dividend >> 12) << 12);
        dungeonBuildAndEnqueueFiveTranslucentQuadsBetweenInterpolatedPoints(effect, position, 0, 0);
        effect->scale = (u16)effect->scale * 2;

        for (point_index = 0; point_index < 5; point_index++) {
            effect->x[point_index] = position[0] + (((func_800644B8(point_index * 0x333 + effect->angle) >> 4) * effect->scale) << 9);
            effect->y[point_index] = position[1] + (((func_80064584(point_index * 0x333 + effect->angle) >> 4) * effect->scale) << 9);
        }

        dungeonBuildAndQueueInterpolatedVerticalQuadsAroundFivePerimeterPoints(effect, position, 0, 0);
        effect->scale = ((s32)(u16)effect->scale << 16) >> 17;
        if (effect->timer < effect->duration) {
            return;
        }

        effect->timer = 0;
        effect->state++;
        return;

    case 6:
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        return;
    }
}
