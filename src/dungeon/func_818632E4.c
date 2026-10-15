#include "modules/dungeon_ovl_188298c.h"

void func_80024AE4(ovl_188298c_818632E4_Controller *ctrl, ovl_188298c_818632E4_Motion *motion, void *render_data)
{
    u8 *root;
    ovl_188298c_818632E4_RootPrefix *prefix;
    ovl_188298c_818632E4_Lookup *lookup;
    ovl_188298c_818632E4_Lookup *lookup_2;
    ovl_188298c_818632E4_Motion *root_motion;

    u8 *linked_root;
    u8 *slot;
    s16 delta[3];
    u16 final_x;
    u16 final_y;
    s32 step;
    s32 diff;
    s32 start_coord;
    s32 floor_height;
    u16 cell_x;
    u16 cell_y;
    u16 start_z;
    s32 state;
    u32 elapsed;

    elapsed = (u16)ctrl->timer;
    state = ctrl->state;
    root = ctrl->root;
    ctrl->timer = elapsed + 1;
    switch (state) {
    case 0:
        ctrl->timer = 0;
        ctrl->state++;
        ctrl->angle = (*(u16 *)(root + 0x2A) >> 9) & 7;
        step = 7;
        slot = (u8 *)ctrl + 7;
        do {
            slot[22] = 0;
            step--;
            slot--;
        } while (step >= 0);
        ((s32 *)render_data)[3] = 0x00808080;

    case 1:
        prefix = (ovl_188298c_818632E4_RootPrefix *)(root - 0x20);
        if (func_8003DE58(prefix->lookup->key, prefix->lookup, delta, 0) == 0) {
            if (!(prefix->lookup->flags & 0x8000)) {
                break;
            }
        }

        root_motion = prefix->motion;
        motion->x.h.hi = root_motion->x.h.hi;
        motion->y.h.hi = root_motion->y.h.hi;
        start_z = root_motion->z.h.hi;
        motion->z.h.hi = start_z;
        if (!(prefix->lookup->flags & 0x8000)) {
            motion->x.h.hi += delta[0];
            motion->y.h.hi += delta[1];
            motion->z.h.hi += delta[2];
        } else {
            motion->z.h.hi = start_z - 64;
        }
        if (!(*ctrl->flags & 0x80)) {
            break;
        }

        ctrl->saved = *motion;
        linked_root = *(u8 **)(root + 0x60);
        if (linked_root != 0) {
            prefix = (ovl_188298c_818632E4_RootPrefix *)*(ovl_188298c_818632E4_Motion **)(linked_root - 0x18);

            start_coord = motion->x.h.hi;
            delta[0] = __builtin_abs(((ovl_188298c_818632E4_Motion *)prefix)->x.h.hi - start_coord);

            delta[1] = __builtin_abs(((ovl_188298c_818632E4_Motion *)prefix)->y.h.hi - motion->y.h.hi);

            linked_root = *(u8 **)(root + 0x60);
            start_coord = motion->z.h.hi;
            delta[2] = __builtin_abs(*(s16 *)(linked_root + 0x88) - start_coord);

            linked_root = *(u8 **)(root + 0x60);
            lookup = *(ovl_188298c_818632E4_Lookup **)(linked_root - 0x14);
            ctrl->cell_x = lookup->cell_x;
            ctrl->cell_y = lookup->cell_y;

            ctrl->target[0].val = ((ovl_188298c_818632E4_Motion *)prefix)->x.val;
            ctrl->target[1].val = ((ovl_188298c_818632E4_Motion *)prefix)->y.val;
            diff = *(u16 *)(*(u8 **)(root + 0x60) + 0x88);
            ctrl->target[2].h.lo = 0;
            ctrl->target[2].h.hi = diff;

            motion->dx.val = (ctrl->target[0].val - motion->x.val) / 15;
            motion->dy.val = (ctrl->target[1].val - motion->y.val) / 15;
            motion->dz.val = (ctrl->target[2].val - motion->z.val) / 15;
        } else {
            step = 0;
            lookup_2 = prefix->lookup;
            cell_x = lookup_2->cell_x;
            cell_y = lookup_2->cell_y;
            final_x = cell_x;
            final_y = cell_y;

            do {
                if ((s16)func_800A44E0(((s16)cell_x << 6) & 0xFFC0,
                                       ((s16)cell_y << 6) & 0xFFC0,
                                       *(s16 *)(root + 0x88),
                                       (s16)(ctrl->angle << 9)) != 0) {
                    break;
                }

                {
                    s16 *x_step;
                    s16 *y_step;
                    s32 probe_z;
                    s32 direction;
                    u16 root_z;

                    direction = (s16)ctrl->angle;
                    root_z = *(u16 *)(root + 0x88);
                    lookup = &dirStepX[direction];
                    x_step = lookup;
                    probe_z = (s16)(root_z - 32);
                    y_step = &dirStepY[direction];
                    floor_height = func_800BCB04((((s16)cell_x + *x_step) << 6) + 32 & 0xFFE0,
                                                 (((s16)cell_y + *y_step) << 6) + 32 & 0xFFE0,
                                                 probe_z);
                }
                if ((s16)floor_height >= 513) {
                    break;
                }
                if ((s16)(floor_height - *(u16 *)(root + 0x88)) < -63) {
                    break;
                }

                {
                    s32 direction;

                    direction = (s16)ctrl->angle;
                    step++;
                    cell_x += dirStepX[direction];
                    cell_y += dirStepY[direction];
                    final_x = cell_x;
                    final_y = cell_y;
                }
            } while (step < 8);

            {


                prefix = (ovl_188298c_818632E4_RootPrefix *)ctrl->target;
                ((ovl_188298c_818632E4_Fixed32 *)prefix)[2].val = 0;
                ((ovl_188298c_818632E4_Fixed32 *)prefix)[1].val = 0;
                ctrl->target[0].val = 0;
                ((ovl_188298c_818632E4_Fixed32 *)prefix)[0].h.hi = ((final_x << 16) >> 10) + 32;
                ((ovl_188298c_818632E4_Fixed32 *)prefix)[1].h.hi = ((final_y << 16) >> 10) + 32;
                ((ovl_188298c_818632E4_Fixed32 *)prefix)[2].h.hi = -1024;
                ((ovl_188298c_818632E4_Fixed32 *)prefix)[2].h.hi = func_800BCB04((u16)((ovl_188298c_818632E4_Fixed32 *)prefix)[0].h.hi,
                                               (u16)((ovl_188298c_818632E4_Fixed32 *)prefix)[1].h.hi, -1024);
                if ((s16)((ovl_188298c_818632E4_Fixed32 *)prefix)[2].h.hi >= 513) {
                    ((ovl_188298c_818632E4_Fixed32 *)prefix)[2].h.hi = motion->z.h.hi + 32;
                }
            }

            motion->dx.val = (ctrl->target[0].val - motion->x.val) / 15;
            motion->dy.val = (ctrl->target[1].val - motion->y.val) / 15;
            motion->dz.val = (ctrl->target[2].val - motion->z.val) / 15;
            ctrl->cell_x = final_x;
            ctrl->cell_y = final_y;
        }
        ctrl->timer = 0;
        ctrl->state++;
        func_800A56E0(0x300);
        break;

    case 2:
        motion->x.val += motion->dx.val;
        motion->y.val += motion->dy.val;
        motion->z.val += motion->dz.val;
        func_800246D8(ctrl, render_data);
        if (ctrl->timer < 15) {
            break;
        }
        ctrl->timer = 0;
        ctrl->state++;
        func_80024428(ctrl, motion, 0, &ctrl->slots[0]);
        break;

    case 3:
    {
        u32 effect_tick;

        effect_tick = (u16)ctrl->timer;
        if ((effect_tick & 7) == 0) {
            func_80024428(ctrl, motion, (s16)effect_tick >> 3, &ctrl->slots[0]);
        }
    }
        if (ctrl->timer < 24) {
            break;
        }
        ctrl->timer = 0;
        ctrl->state++;
        break;

    case 4:
        if (ctrl->timer < 36) {
            break;
        }
        func_80024060(ctrl->cell_x, ctrl->cell_y, root, ctrl->kind);
        ctrl->timer = 0;
        ctrl->state++;
        break;

    case 5:
        if (ctrl->active == 0) {
            dungeonStatus.unk_0C = 0;
            *(u16 *)((u8 *)ctrl - 2) |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }

    default:
        break;
    }

    ctrl->active = 0;
}
