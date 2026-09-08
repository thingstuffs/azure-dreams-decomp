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
    u8 ready;
    u8 pad17;
    Motion saved;
    Fixed32 target[3];
    u8 pad3C[12];
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
extern void func_800248C8();
extern void func_800247DC();
extern void func_800A56E0();
extern void func_80024684();
extern void func_80024060();

/* Moves toward a linked object or forward cell over 15 ticks, then completes the action. */
void func_80024CD4(Controller *input_ctrl, Motion *input_motion, void *input_render_data)
{
    register Controller *ctrl ASM_REG("$18") = input_ctrl;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register Motion *motion ASM_REG("$21") = input_motion;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *root;
    register void *render_data ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
    RootPrefix *root_prefix;
    Lookup *lookup;
    Motion *source_motion;
    register Motion *linked_motion ASM_REG("$16");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    u8 *linked_root;
    s16 offsets[3];
    u16 end_x;
    u16 end_y;
    s32 steps;
    register s32 coord_diff ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 origin_coord;
    s32 floor_height;
    s32 cell_x;
    s32 cell_y;
    u16 source_z;
    s32 state;
    u32 elapsed;

    elapsed = (u16)ctrl->timer;
    state = ctrl->state;
    root = ctrl->root;
    ctrl->timer = elapsed + 1;
    render_data = input_render_data;
    switch (state) {
    case 0:
        ctrl->timer = 0;
        ctrl->state++;
        ctrl->angle = (*(u16 *)(root + 0x2A) >> 9) & 7;
        ctrl->ready = 0;
        ((s32 *)render_data)[3] = 0x00808080;

    case 1:
        root_prefix = (RootPrefix *)(root - 0x20);
        if (func_8003DE58(root_prefix->lookup->key, root_prefix->lookup, offsets, 0) == 0) {
            if (!(root_prefix->lookup->flags & 0x8000)) {
                goto finish;
            }
        }

        source_motion = root_prefix->motion;
        motion->x.h.hi = source_motion->x.h.hi;
        motion->y.h.hi = source_motion->y.h.hi;
        source_z = source_motion->z.h.hi;
        motion->z.h.hi = source_z;
        if (!(root_prefix->lookup->flags & 0x8000)) {
            motion->x.h.hi += offsets[0];
            motion->y.h.hi += offsets[1];
            motion->z.h.hi += offsets[2];
        } else {
            motion->z.h.hi = source_z - 64;
        }
        if (!(*ctrl->flags & 0x80)) {
            goto finish;
        }

        ctrl->saved = *motion;
        linked_root = *(u8 **)(root + 0x60);
        if (linked_root != 0) {
            s32 div_magic = (s32)0x88880000;
            WideProduct product;

            ASM_KEEP_NV(div_magic);   /* MATCH pin: keeps a statement from moving across a call/branch */
            linked_motion = *(Motion **)(linked_root - 0x18);

            origin_coord = motion->x.h.hi;
            coord_diff = linked_motion->x.h.hi - origin_coord;
            if (coord_diff < 0) {
                coord_diff = -coord_diff;
            }
            offsets[0] = coord_diff;

            coord_diff = linked_motion->y.h.hi;
            coord_diff -= motion->y.h.hi;
            if (coord_diff < 0) {
                coord_diff = -coord_diff;
            }
            offsets[1] = coord_diff;

            linked_root = *(u8 **)(root + 0x60);
            origin_coord = motion->z.h.hi;
            coord_diff = *(s16 *)(linked_root + 0x88);
            coord_diff -= origin_coord;
            if (coord_diff < 0) {
                coord_diff = -coord_diff;
            }
            offsets[2] = coord_diff;

            linked_root = *(u8 **)(root + 0x60);
            lookup = *(Lookup **)(linked_root - 0x14);
            ctrl->cell_x = lookup->cell_x;
            ctrl->cell_y = lookup->cell_y;

            ctrl->target[0].val = linked_motion->x.val;
            ctrl->target[1].val = linked_motion->y.val;
            coord_diff = *(volatile u16 *)(*(u8 **)(root + 0x60) + 0x88);
            *(volatile u16 *)&ctrl->target[2].h.lo = 0;
            *(volatile u16 *)&ctrl->target[2].h.hi = coord_diff;

            div_magic |= 0x8889;
            coord_diff = *(volatile s32 *)&ctrl->target[0].val;
            coord_diff -= motion->x.val;
            product.value = (long long)coord_diff * div_magic;
            motion->dx.val = ((s32)((u32)product.word.upper -
                (0U - (u32)coord_diff)) >> 3) - (coord_diff >> 31);
            coord_diff = *(volatile s32 *)&ctrl->target[1].val;
            coord_diff -= motion->y.val;
            product.value = (long long)coord_diff * div_magic;
            motion->dy.val = ((s32)((u32)product.word.upper -
                (0U - (u32)coord_diff)) >> 3) - (coord_diff >> 31);
            coord_diff = *(volatile s32 *)&ctrl->target[2].val;
            coord_diff -= motion->z.val;
            product.value = (long long)coord_diff * div_magic;
            motion->dz.val = ((s32)((u32)product.word.upper -
                (0U - (u32)coord_diff)) >> 3) - (coord_diff >> 31);
            goto advance;
        }

        steps = 0;
        lookup = root_prefix->lookup;
        ASM_USE_NV(lookup);   /* MATCH pin: retail basic-block layout depends on it */
        coord_diff = (s32)0x80070000;
        ASM_USE_NV(coord_diff);   /* MATCH pin: load-bearing for the whole function shape */
        cell_y = lookup->cell_y;
        cell_x = lookup->cell_x;
        end_x = cell_x;
        end_y = cell_y;

        do {
            if ((s16)func_800A44E0(((s16)cell_x << 6) & 0xFFC0,
                ((s16)cell_y << 6) & 0xFFC0,
                *(s16 *)(root + 0x88),
                (s16)(ctrl->angle << 9)) != 0) {
                break;
            }

            {
                s16 *step_x;
                s16 *step_y;
                s32 height;
                s32 direction;
                u16 root_z;

                direction = (s16)ctrl->angle;
                root_z = *(u16 *)(root + 0x88);
                step_x = &D_8006CCD8[direction];
                ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
                height = (s16)(root_z - 32);
                step_y = &D_8006CCE8[direction];
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
                register s32 next_x ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
                register s32 next_y ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
                s16 *step_x;
                s16 *step_y;
                s32 direction;

                direction = (s16)ctrl->angle;
                step_x = &D_8006CCD8[direction];
                steps++;
                step_y = &D_8006CCE8[direction];
                next_x = cell_x + (u16)*step_x;
                cell_x = next_x;
                next_y = cell_y + (u16)*step_y;
                cell_y = next_y;
                end_x = next_x;
                end_y = next_y;
            }
        } while (steps < 8);

        {
            Fixed32 *target;

            target = ctrl->target;
            target[2].val = 0;
            target[1].val = 0;
            ctrl->target[0].val = 0;
            target[0].h.hi = ((end_x << 16) >> 10) + 32;
            target[1].h.hi = ((end_y << 16) >> 10) + 32;
            target[2].h.hi = -1024;
            target[2].h.hi = func_800BCB04((u16)target[0].h.hi,
                (u16)target[1].h.hi, -1024);
            if ((s16)target[2].h.hi >= 513) {
                target[2].h.hi = motion->z.h.hi + 32;
            }
        }

        motion->dx.val = (ctrl->target[0].val - motion->x.val) / 15;
        motion->dy.val = (ctrl->target[1].val - motion->y.val) / 15;
        motion->dz.val = (ctrl->target[2].val - motion->z.val) / 15;
        ctrl->cell_x = end_x;
        ctrl->cell_y = end_y;
        goto advance;

    case 2:
        motion->x.val += motion->dx.val;
        motion->y.val += motion->dy.val;
        motion->z.val += motion->dz.val;
        func_800248C8(ctrl, render_data);
        ASM_KEEP(ctrl);   /* MATCH pin: retail schedule: same instructions, different order without it */
        if (ctrl->timer < 15) {
            goto finish;
        }
        ctrl->timer = 0;
        ctrl->state++;
        func_800247DC(ctrl, motion);
        func_800A56E0(0x300);
        goto finish;

    case 3:
        if (ctrl->ready == 0) {
            goto finish;
        }
        ctrl->timer = 0;
        ctrl->ready = 0;
        ctrl->state++;
        func_80024684(ctrl, motion);
        goto finish;

    case 4:
        if (ctrl->ready == 0) {
            goto finish;
        }
        func_80024060(ctrl->cell_x, ctrl->cell_y, root, ctrl->kind);

    advance:
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
