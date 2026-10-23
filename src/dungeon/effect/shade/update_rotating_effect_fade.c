#include "common.h"
#include "dungeon/effect/rotating_quad.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_links.h"



/* Callback work: four world vertices and the two colors faded each update. */
typedef struct RotatingFadeWork {
    u8 pad_00[0x1A];
    s16 frames_left;
    u8 pad_1C[0x18];
    RotatingQuadVertex vertices[4];
    RotatingQuadColor colors[2];
} RotatingFadeWork;

#include "shared/object_flags.h"


extern void PushMatrix(s32);
extern void PopMatrix(void);
extern void SetRotMatrix(void *);
extern void SetTransMatrix(void *);
extern void func_80065320(void *, void *, void *);
extern void RotMatrix(void *, void *);

/* Rotate and move four effect vertices, fade their colors, and mark the effect expired when its lifetime ends. */
void update_rotating_effect_fade(RotatingFadeWork *effect, ObjectPosition *motion, SpriteFrameState *rotation)
{
    u16 angles[3];
    s32 matrix[8];
    RotatingQuadScratch *scratch = (RotatingQuadScratch *)0x1F800000;
    ObjectPosition *motion_state = motion;
    u16 *counter_page;
    s32 center_z;
    u16 vertex_z;
    u16 update_count;
    u16 relative_z;
    s32 red_a;
    s32 green_a;
    s32 blue_a;
    s32 red_b;
    s32 green_b;
    s32 blue_b;
    s32 red_step_a;
    s32 green_step_a;
    s32 blue_step_a;
    s32 red_step_b;
    s32 green_step_b;
    s32 blue_step_b;
    s16 frames_left;
    s32 frames_test;

    scratch->relative[0].x = effect->vertices[0].x - (u16)motion_state->x.w.i;
    scratch->relative[1].x = effect->vertices[1].x - (u16)motion_state->x.w.i;
    scratch->relative[2].x = effect->vertices[2].x - (u16)motion_state->x.w.i;
    scratch->relative[3].x = effect->vertices[3].x - (u16)motion_state->x.w.i;
    scratch->relative[0].y = effect->vertices[0].y - (u16)motion_state->y.w.i;
    scratch->relative[1].y = effect->vertices[1].y - (u16)motion_state->y.w.i;
    scratch->relative[2].y = effect->vertices[2].y - (u16)motion_state->y.w.i;
    scratch->relative[3].y = effect->vertices[3].y - (u16)motion_state->y.w.i;
    scratch->relative[0].z = effect->vertices[0].z - (u16)motion_state->z.w.i;
    scratch->relative[1].z = effect->vertices[1].z - (u16)motion_state->z.w.i;
    counter_page = (u16 *)0x80020000;

    update_count = counter_page[0x6472 / 2];
    vertex_z = effect->vertices[2].z;
    center_z = (u16)motion_state->z.w.i;
    update_count++;
    relative_z = vertex_z - center_z;
    counter_page[0x6472 / 2] = update_count;
    scratch->relative[2].z = relative_z;
    scratch->relative[3].z = effect->vertices[3].z - (u16)motion_state->z.w.i;
    PushMatrix(center_z);

    angles[0] = rotation->angle_x;
    angles[1] = rotation->angle_y;
    angles[2] = 0;
    matrix[7] = 0;
    matrix[6] = 0;
    matrix[5] = 0;
    RotMatrix(angles, matrix);
    SetTransMatrix(matrix);
    SetRotMatrix(matrix);

    func_80065320(&scratch->relative[0], &scratch->rotated[0],
                  &scratch->transform_flags);
    func_80065320(&scratch->relative[1], &scratch->rotated[1],
                  &scratch->transform_flags);
    func_80065320(&scratch->relative[2], &scratch->rotated[2],
                  &scratch->transform_flags);
    func_80065320(&scratch->relative[3], &scratch->rotated[3],
                  &scratch->transform_flags);
    PopMatrix();

    motion_state->x.v = motion_state->x.v + motion_state->velocity_x;
    motion_state->y.v = motion_state->y.v + motion_state->velocity_y;
    motion_state->z.v = motion_state->z.v + motion_state->velocity_z;

    effect->vertices[0].x = scratch->rotated[0].x + (u16)motion_state->x.w.i;
    effect->vertices[1].x = scratch->rotated[1].x + (u16)motion_state->x.w.i;
    effect->vertices[2].x = scratch->rotated[2].x + (u16)motion_state->x.w.i;
    effect->vertices[3].x = scratch->rotated[3].x + (u16)motion_state->x.w.i;
    effect->vertices[0].y = scratch->rotated[0].y + (u16)motion_state->y.w.i;
    effect->vertices[1].y = scratch->rotated[1].y + (u16)motion_state->y.w.i;
    effect->vertices[2].y = scratch->rotated[2].y + (u16)motion_state->y.w.i;
    effect->vertices[3].y = scratch->rotated[3].y + (u16)motion_state->y.w.i;
    effect->vertices[0].z = scratch->rotated[0].z + (u16)motion_state->z.w.i;

    effect->vertices[1].z = scratch->rotated[1].z + (u16)motion_state->z.w.i;
    effect->vertices[2].z = scratch->rotated[2].z + (u16)motion_state->z.w.i;
    effect->vertices[3].z = scratch->rotated[3].z + (u16)motion_state->z.w.i;
    effect->colors[0].r -= effect->colors[0].r / effect->frames_left;
    effect->colors[0].g -= effect->colors[0].g / effect->frames_left;
    effect->colors[0].b -= effect->colors[0].b / effect->frames_left;
    effect->colors[1].r -= effect->colors[1].r / effect->frames_left;
    effect->colors[1].g -= effect->colors[1].g / effect->frames_left;
    effect->colors[1].b -= effect->colors[1].b / effect->frames_left;
    frames_left = (u16)effect->frames_left - 1;
    effect->frames_left = frames_left;
    frames_test = frames_left << 16;


    if (frames_test <= 0) {
        ((ObjectStatusPrefix16 *)effect)[-1].unk_00 |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
