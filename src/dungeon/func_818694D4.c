#include "modules/dungeon_ovl_188898c.h"

void func_80024CD4(ovl_188898c_818694D4_Controller *input_ctrl, ovl_188898c_818694D4_Motion *input_motion, void *input_render_data)
{
    u8 *root;
    void *render_data;
    ovl_188898c_818694D4_RootPrefix *root_prefix;
    ovl_188898c_818694D4_Lookup *lookup;
    ovl_188898c_818694D4_Lookup *lookup_2;
    ovl_188898c_818694D4_Motion *source_motion;
    ovl_188898c_818694D4_Motion *linked_motion;
    u8 *linked_root;
    u8 *linked_root_2;
    u8 *linked_root_3;
    s16 offsets[3];
    u16 end_x;
    u16 end_y;
    s32 steps;
    s32 coord_diff;
    s32 origin_coord;
    s32 floor_height;
    u16 cell_x;
    u16 cell_y;
    u16 source_z;
    s32 state;
    u32 elapsed;

    elapsed = (u16)input_ctrl->timer;
    state = input_ctrl->state;
    root = input_ctrl->root;
    input_ctrl->timer = elapsed + 1;
    render_data = input_render_data;
    switch (state) {
    case 0:
        input_ctrl->timer = 0;
        input_ctrl->state++;
        input_ctrl->angle = (*(u16 *)(root + 0x2A) >> 9) & 7;
        input_ctrl->ready = 0;
        ((s32 *)render_data)[3] = 0x00808080;

    case 1:
        root_prefix = (ovl_188898c_818694D4_RootPrefix *)(root - 0x20);
        if (resolveRecordOrientationOrFallback(root_prefix->lookup->key, root_prefix->lookup, offsets, 0) == 0) {
            if (!(root_prefix->lookup->flags & 0x8000)) {
                break;
            }
        }

        source_motion = root_prefix->motion;
        input_motion->x.h.hi = source_motion->x.h.hi;
        input_motion->y.h.hi = source_motion->y.h.hi;
        source_z = source_motion->z.h.hi;
        input_motion->z.h.hi = source_z;
        if (!(root_prefix->lookup->flags & 0x8000)) {
            input_motion->x.h.hi += offsets[0];
            input_motion->y.h.hi += offsets[1];
            input_motion->z.h.hi += offsets[2];
        } else {
            input_motion->z.h.hi = source_z - 64;
        }
        if (!(*input_ctrl->flags & 0x80)) {
            break;
        }

        input_ctrl->saved = *input_motion;
        linked_root = *(u8 **)(root + 0x60);
        if (linked_root != 0) {
            linked_motion = *(ovl_188898c_818694D4_Motion **)(linked_root - 0x18);

            origin_coord = input_motion->x.h.hi;
            offsets[0] = abs(linked_motion->x.h.hi - origin_coord);

            offsets[1] = abs(linked_motion->y.h.hi - input_motion->y.h.hi);

            linked_root_2 = *(u8 **)(root + 0x60);
            origin_coord = input_motion->z.h.hi;
            offsets[2] = abs(*(s16 *)(linked_root_2 + 0x88) - origin_coord);

            linked_root_3 = *(u8 **)(root + 0x60);
            lookup = *(ovl_188898c_818694D4_Lookup **)(linked_root_3 - 0x14);
            input_ctrl->cell_x = lookup->cell_x;
            input_ctrl->cell_y = lookup->cell_y;

            input_ctrl->target[0].val = linked_motion->x.val;
            input_ctrl->target[1].val = linked_motion->y.val;
            coord_diff = *(u16 *)(*(u8 **)(root + 0x60) + 0x88);
            input_ctrl->target[2].h.lo = 0;
            input_ctrl->target[2].h.hi = coord_diff;

            input_motion->dx.val = (input_ctrl->target[0].val - input_motion->x.val) / 15;
            input_motion->dy.val = (input_ctrl->target[1].val - input_motion->y.val) / 15;
            input_motion->dz.val = (input_ctrl->target[2].val - input_motion->z.val) / 15;
            input_ctrl->timer = 0;
            input_ctrl->state++;
            break;
        }

        steps = 0;
        lookup_2 = root_prefix->lookup;
        cell_x = lookup_2->cell_x;
        cell_y = lookup_2->cell_y;
        end_x = cell_x;
        end_y = cell_y;

        do {
            if ((s16)dungeonCheckLayerOffsetHeight(((s16)cell_x << 6) & 0xFFC0,
                ((s16)cell_y << 6) & 0xFFC0,
                *(s16 *)(root + 0x88),
                (s16)(input_ctrl->angle << 9)) != 0) {
                break;
            }

            {
                s16 *step_x;
                s16 *step_y;
                s32 height;
                s32 direction;
                u16 root_z;

                direction = (s16)input_ctrl->angle;
                root_z = *(u16 *)(root + 0x88);
                lookup = &dirStepX[direction];
                step_x = lookup;
                height = (s16)(root_z - 32);
                step_y = &dirStepY[direction];
                floor_height = func_800BCB04((((s16)cell_x + *step_x) << 6) + 32 & 0xFFE0,
                    (((s16)cell_y + *step_y) << 6) + 32 & 0xFFE0,
                    height);
            }
            if ((s16)floor_height >= 513) {
                break;
            }
            if ((s16)(floor_height - *(u16 *)(root + 0x88)) < -63) {
                break;
            }

            {
                s32 direction;

                direction = (s16)input_ctrl->angle;
                steps++;
                cell_x += dirStepX[direction];
                cell_y += dirStepY[direction];
                end_x = cell_x;
                end_y = cell_y;
            }
        } while (steps < 8);

        {

            linked_motion = (ovl_188898c_818694D4_Motion *)input_ctrl->target;
            ((ovl_188898c_818694D4_Fixed32 *)linked_motion)[2].val = 0;
            ((ovl_188898c_818694D4_Fixed32 *)linked_motion)[1].val = 0;
            input_ctrl->target[0].val = 0;
            ((ovl_188898c_818694D4_Fixed32 *)linked_motion)[0].h.hi = ((end_x << 16) >> 10) + 32;
            ((ovl_188898c_818694D4_Fixed32 *)linked_motion)[1].h.hi = ((end_y << 16) >> 10) + 32;
            ((ovl_188898c_818694D4_Fixed32 *)linked_motion)[2].h.hi = -1024;
            ((ovl_188898c_818694D4_Fixed32 *)linked_motion)[2].h.hi = func_800BCB04((u16)((ovl_188898c_818694D4_Fixed32 *)linked_motion)[0].h.hi,
                (u16)((ovl_188898c_818694D4_Fixed32 *)linked_motion)[1].h.hi, -1024);
            if ((s16)((ovl_188898c_818694D4_Fixed32 *)linked_motion)[2].h.hi >= 513) {
                ((ovl_188898c_818694D4_Fixed32 *)linked_motion)[2].h.hi = input_motion->z.h.hi + 32;
            }
        }

        input_motion->dx.val = (input_ctrl->target[0].val - input_motion->x.val) / 15;
        input_motion->dy.val = (input_ctrl->target[1].val - input_motion->y.val) / 15;
        input_motion->dz.val = (input_ctrl->target[2].val - input_motion->z.val) / 15;
        input_ctrl->cell_x = end_x;
        input_ctrl->cell_y = end_y;
        goto advance;

    case 2:
        input_motion->x.val += input_motion->dx.val;
        input_motion->y.val += input_motion->dy.val;
        input_motion->z.val += input_motion->dz.val;
        interpolateShadeAndQueueLine(input_ctrl, render_data);
        if (input_ctrl->timer < 15) {
            break;
        }
        input_ctrl->timer = 0;
        input_ctrl->state++;
        dungeonDelayAndFadeParticle(input_ctrl, input_motion);
        func_800A56E0(0x300);
        break;

    case 3:
        if (input_ctrl->ready == 0) {
            break;
        }
        input_ctrl->timer = 0;
        input_ctrl->ready = 0;
        input_ctrl->state++;
        createCoordinateSpriteObject(input_ctrl, input_motion);
        break;

    case 4:
        if (input_ctrl->ready == 0) {
            break;
        }
        func_80024060(input_ctrl->cell_x, input_ctrl->cell_y, root, input_ctrl->kind);

advance:
        input_ctrl->timer = 0;
        input_ctrl->state++;
        break;

    case 5:
        if (input_ctrl->active == 0) {
            dungeonStatus.unk_0C = 0;
            *(u16 *)((u8 *)input_ctrl - 2) |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }

    default:
        break;
    }

    input_ctrl->active = 0;
}
