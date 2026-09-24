#include "common.h"

typedef union Fixed32 {
    s32 val;
    struct {
        u16 lo;
        s16 hi;
    } h;
} Fixed32;

typedef struct Motion {
    Fixed32 x;
    Fixed32 y;
    Fixed32 z;
    Fixed32 dx;
    Fixed32 dy;
    Fixed32 dz;
} Motion;

typedef struct Lookup {
    u8 pad00[8];
    void *key;
    u8 pad0C[8];
    u16 flags;
    u8 pad16[14];
    u8 cell_x;
    u8 cell_y;
} Lookup;

typedef struct RootPrefix {
    u8 pad00[8];
    Motion *motion;
    Lookup *lookup;
} RootPrefix;

typedef struct Controller {
    u8 *root;
    u16 *flags;
    u8 pad08;
    u8 kind;
    s16 state;
    s16 pad0C;
    u16 angle;
    s16 timer;
    s16 pad12;
    s16 active;
    u8 slots[8];
    u8 pad1E[2];
    Motion saved;
    Fixed32 target[3];
    u8 pad44[12];
    s16 cell_x;
    s16 cell_y;
} Controller;

typedef union WideProduct {
    long long value;
    struct {
#ifdef NON_MATCHING
        s32 lower;
        s32 upper;
#else
        s32 upper;
        s32 lower;
#endif
    } word;
} WideProduct;

typedef struct LargeFlag {
    u32 value;
    u32 pad[2];
} LargeFlag;

extern LargeFlag D_800814A0;
extern u32 D_8008346C[3];
extern s16 D_8006CCD8[8];
extern s16 D_8006CCE8[8];
extern s32 func_8003DE58();
extern s32 func_800A44E0();
extern s32 func_800BCB04();
extern void func_800A56E0();
extern void func_800246D8();
extern void func_80024428();
extern void func_80024060();

/* Moves toward a linked object or a reachable cell, then runs the arrival effects. */
void func_80024AE4(Controller *ctrl, Motion *motion, void *render_data)
{
    u8 *root;
    RootPrefix *prefix;
    Lookup *lookup;
    Lookup *lookup_2;
    Motion *root_motion;

    u8 *linked_root;
    u8 *slot;
    s16 delta[3];
    u16 final_x;
    u16 final_y;
    s32 step;
    s32 diff;
    s32 start_coord;
    s32 floor_height;
    s32 cell_x;
    s16 cell_y;
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
        prefix = (RootPrefix *)(root - 0x20);
        if (func_8003DE58(prefix->lookup->key, prefix->lookup, delta, 0) == 0) {
            if (!(prefix->lookup->flags & 0x8000)) {
                goto finish;
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
            goto finish;
        }

        ctrl->saved = *motion;
        linked_root = *(u8 **)(root + 0x60);
        if (linked_root != 0) {
            prefix = (RootPrefix *)*(Motion **)(linked_root - 0x18);

            start_coord = motion->x.h.hi;
            delta[0] = __builtin_abs(((Motion *)prefix)->x.h.hi - start_coord);

            delta[1] = __builtin_abs(((Motion *)prefix)->y.h.hi - motion->y.h.hi);

            linked_root = *(u8 **)(root + 0x60);
            start_coord = motion->z.h.hi;
            delta[2] = __builtin_abs(*(s16 *)(linked_root + 0x88) - start_coord);

            linked_root = *(u8 **)(root + 0x60);
            lookup = *(Lookup **)(linked_root - 0x14);
            ctrl->cell_x = lookup->cell_x;
            ctrl->cell_y = lookup->cell_y;

            ctrl->target[0].val = ((Motion *)prefix)->x.val;
            ctrl->target[1].val = ((Motion *)prefix)->y.val;
            diff = *(u16 *)(*(u8 **)(root + 0x60) + 0x88);
            ctrl->target[2].h.lo = 0;
            ctrl->target[2].h.hi = diff;

            motion->dx.val = (ctrl->target[0].val - motion->x.val) / 15;
            motion->dy.val = (ctrl->target[1].val - motion->y.val) / 15;
            motion->dz.val = (ctrl->target[2].val - motion->z.val) / 15;
            goto advance;
        }

        step = 0;
        lookup_2 = prefix->lookup;
        cell_y = lookup_2->cell_y;
        cell_x = lookup_2->cell_x;
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
                lookup = &D_8006CCD8[direction];
                x_step = lookup;
                probe_z = (s16)(root_z - 32);
                y_step = &D_8006CCE8[direction];
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
                register s32 next_x ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                s16 next_y;
                s16 *x_step;
                s16 *y_step;
                s32 direction;

                direction = (s16)ctrl->angle;
                x_step = &D_8006CCD8[direction];
                step++;
                y_step = &D_8006CCE8[direction];
                next_x = cell_x + (u16)*x_step;
                cell_x = next_x;
                next_y = cell_y + (u16)*y_step;
                cell_y = next_y;
                final_x = next_x;
                final_y = next_y;
            }
        } while (step < 8);

        {
            

            prefix = (RootPrefix *)ctrl->target;
            ((Fixed32 *)prefix)[2].val = 0;
            ((Fixed32 *)prefix)[1].val = 0;
            ctrl->target[0].val = 0;
            ((Fixed32 *)prefix)[0].h.hi = ((final_x << 16) >> 10) + 32;
            ((Fixed32 *)prefix)[1].h.hi = ((final_y << 16) >> 10) + 32;
            ((Fixed32 *)prefix)[2].h.hi = -1024;
            ((Fixed32 *)prefix)[2].h.hi = func_800BCB04((u16)((Fixed32 *)prefix)[0].h.hi,
                                           (u16)((Fixed32 *)prefix)[1].h.hi, -1024);
            if ((s16)((Fixed32 *)prefix)[2].h.hi >= 513) {
                ((Fixed32 *)prefix)[2].h.hi = motion->z.h.hi + 32;
            }
        }

        motion->dx.val = (ctrl->target[0].val - motion->x.val) / 15;
        motion->dy.val = (ctrl->target[1].val - motion->y.val) / 15;
        motion->dz.val = (ctrl->target[2].val - motion->z.val) / 15;
        ctrl->cell_x = final_x;
        ctrl->cell_y = final_y;

advance:
        ctrl->timer = 0;
        ctrl->state++;
        func_800A56E0(0x300);
        goto finish;

    case 2:
        motion->x.val += motion->dx.val;
        motion->y.val += motion->dy.val;
        motion->z.val += motion->dz.val;
        func_800246D8(ctrl, render_data);
        if (ctrl->timer < 15) {
            goto finish;
        }
        ctrl->timer = 0;
        ctrl->state++;
        func_80024428(ctrl, motion, 0, &ctrl->slots[0]);
        goto finish;

    case 3:
        {
            u32 effect_tick;

            effect_tick = (u16)ctrl->timer;
            if ((effect_tick & 7) == 0) {
                func_80024428(ctrl, motion, (s16)effect_tick >> 3, &ctrl->slots[0]);
            }
        }
        if (ctrl->timer < 24) {
            goto finish;
        }
        goto advance2;

    case 4:
        if (ctrl->timer < 36) {
            goto finish;
        }
        func_80024060(ctrl->cell_x, ctrl->cell_y, root, ctrl->kind);

advance2:
        ctrl->timer = 0;
        ctrl->state++;
        goto finish;

    case 5:
        if (ctrl->active == 0) {
            D_8008346C[0] = 0;
            *(u16 *)((u8 *)ctrl - 2) |= 0x8000;
            D_800814A0.value |= 0x8000;
        }

    default:
        break;
    }

finish:
    ctrl->active = 0;
}
