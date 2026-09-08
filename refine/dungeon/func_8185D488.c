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

typedef struct Child {
    u8 pad00[0x10];
    void (*update)(void);
    u8 pad14[0xA];
    u16 flags;
} Child;

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
    s16 pad16;
    Child *children[8];
    Motion saved;
    Fixed32 target[3];
    u8 pad5C[12];
    s16 cell_x;
    s16 cell_y;
} Controller;

typedef struct LargeFlag {
    u32 value;
    u32 pad[2];
} LargeFlag;

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

extern s16 D_8006CCD8[8];
extern s16 D_8006CCE8[8];
extern LargeFlag D_800814A0;
extern u32 D_8008346C[3];
extern s32 func_8003DE58();
extern s32 func_800A44E0();
extern s32 func_800BCB04();
extern void func_800247D4();
extern Child *func_80024628();
extern void func_800A56E0();
extern void func_80024060();
extern void func_800244D4(void);

/* Moves to a target cell, runs child effects, and retires the controller. */
void func_80024C88(Controller *controller, Motion *motion_arg, void *render_arg)
{
    register Controller *ctrl ASM_REG("$19") = controller;
    register Motion *motion ASM_REG("$22") = motion_arg;
    u8 *root;
    register void *render_data ASM_REG("$5");
    RootPrefix *prefix;
    Lookup *lookup;
    Motion *root_motion;
    register Motion *linked_motion ASM_REG("$16");
    Child *child;
    u8 *linked_root;
    s16 delta[3];
    u16 target_cell_x;
    u16 target_cell_y[1];
    s32 index;
    register s32 diff ASM_REG("$2");
    register void (*child_update)(void);
    s32 origin_coord;
    s32 floor_height;
    s32 cell_x;
    s32 cell_y;
    u16 origin_z;
    s32 state;
    u32 elapsed;
    Child **child_slot;

    elapsed = (u16)ctrl->timer;
    state = ctrl->state;
    root = ctrl->root;
    ctrl->timer = elapsed + 1;
    render_data = render_arg;
    switch (state) {
    case 0:
        ctrl->timer = 0;
        ctrl->state++;
        ctrl->angle = (*(u16 *)(root + 0x2A) >> 9) & 7;
        index = 7;
        child_slot = &ctrl->children[1];
        do {
            child_slot[6] = 0;
            index--;
            child_slot--;
        } while (index >= 0);
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
        origin_z = root_motion->z.h.hi;
        motion->z.h.hi = origin_z;
        if (!(prefix->lookup->flags & 0x8000)) {
            motion->x.h.hi += delta[0];
            motion->y.h.hi += delta[1];
            motion->z.h.hi += delta[2];
        } else {
            motion->z.h.hi = origin_z - 64;
        }
        if (!(*ctrl->flags & 0x80)) {
            goto finish;
        }

        ctrl->saved = *motion;
        linked_root = *(u8 **)(root + 0x60);
        if (linked_root != 0) {
            s32 div_magic = (s32)0x88880000;
            WideProduct product;

            ASM_KEEP_NV(div_magic);
            linked_motion = *(Motion **)(linked_root - 0x18);

            origin_coord = motion->x.h.hi;
            diff = linked_motion->x.h.hi - origin_coord;
            if (diff < 0) {
                diff = -diff;
            }
            delta[0] = diff;

            diff = linked_motion->y.h.hi;
            diff -= motion->y.h.hi;
            if (diff < 0) {
                diff = -diff;
            }
            delta[1] = diff;

            linked_root = *(u8 **)(root + 0x60);
            origin_coord = motion->z.h.hi;
            diff = *(s16 *)(linked_root + 0x88);
            diff -= origin_coord;
            if (diff < 0) {
                diff = -diff;
            }
            delta[2] = diff;

            linked_root = *(u8 **)(root + 0x60);
            lookup = *(Lookup **)(linked_root - 0x14);
            ctrl->cell_x = lookup->cell_x;
            ctrl->cell_y = lookup->cell_y;

            ctrl->target[0].val = linked_motion->x.val;
            ctrl->target[1].val = linked_motion->y.val;
            diff = *(volatile u16 *)(*(u8 **)(root + 0x60) + 0x88);
            *(volatile u16 *)&ctrl->target[2].h.lo = 0;
            *(volatile u16 *)&ctrl->target[2].h.hi = diff;

            div_magic |= 0x8889;
            diff = *(volatile s32 *)&ctrl->target[0].val;
            diff -= motion->x.val;
            product.value = (long long)diff * div_magic;
            motion->dx.val = ((s32)((u32)product.word.upper -
                                (0U - (u32)diff)) >> 3) - (diff >> 31);
            diff = *(volatile s32 *)&ctrl->target[1].val;
            diff -= motion->y.val;
            product.value = (long long)diff * div_magic;
            motion->dy.val = ((s32)((u32)product.word.upper -
                                (0U - (u32)diff)) >> 3) - (diff >> 31);
            diff = *(volatile s32 *)&ctrl->target[2].val;
            diff -= motion->z.val;
            product.value = (long long)diff * div_magic;
            motion->dz.val = ((s32)((u32)product.word.upper -
                                (0U - (u32)diff)) >> 3) - (diff >> 31);
            goto advance;
        }

        index = 0;
        lookup = prefix->lookup;
        ASM_USE_NV(lookup);
        diff = (s32)0x80070000;
        ASM_USE_NV(diff);
        cell_y = lookup->cell_y;
        cell_x = lookup->cell_x;
        target_cell_x = cell_x;
        target_cell_y[0] = cell_y;

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
                s32 height;
                s32 direction;
                u16 root_z;

                direction = (s16)ctrl->angle;
                root_z = *(u16 *)(root + 0x88);
                x_step = &D_8006CCD8[direction];
                ASM_SCHED_BARRIER();
                height = (s16)(root_z - 32);
                y_step = &D_8006CCE8[direction];
                floor_height = func_800BCB04((((s16)cell_x + *x_step) << 6) + 32 & 0xFFE0,
                                           (((s16)cell_y + *y_step) << 6) + 32 & 0xFFE0,
                                           height);
            }
            if ((s16)floor_height >= 513) {
                break;
            }
            if ((s16)(floor_height - *(u16 *)(root + 0x88)) < -63) {
                break;
            }

            {
                register s32 next_x ASM_REG("$4");
                register s32 next_y ASM_REG("$2");
                s16 *x_step;
                s16 *y_step;
                s32 direction;

                direction = (s16)ctrl->angle;
                x_step = &D_8006CCD8[direction];
                index++;
                y_step = &D_8006CCE8[direction];
                next_x = cell_x + (u16)*x_step;
                cell_x = next_x;
                next_y = cell_y + (u16)*y_step;
                cell_y = next_y;
                target_cell_x = next_x;
                target_cell_y[0] = next_y;
            }
        } while (index < 8);

        {
            Fixed32 *target;

            target = ctrl->target;
            target[2].val = 0;
            target[1].val = 0;
            ctrl->target[0].val = 0;
            target[0].h.hi = ((target_cell_x << 16) >> 10) + 32;
            target[1].h.hi = ((target_cell_y[0] << 16) >> 10) + 32;
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
        ctrl->cell_x = target_cell_x;
        ctrl->cell_y = target_cell_y[0];

advance:
        ctrl->timer = 0;
        ctrl->state++;
        goto finish;

    case 2:
        motion->x.val += motion->dx.val;
        motion->y.val += motion->dy.val;
        motion->z.val += motion->dz.val;
        func_800247D4(ctrl, render_data);
        ASM_KEEP(ctrl);
        if (ctrl->timer < 15) {
            goto finish;
        }
        ctrl->timer = 0;
        ctrl->state++;
        {
            Child **child_slot;

            index = 7;
            child_slot = &ctrl->children[1];
            do {
                child_slot[6] = func_80024628(ctrl, motion, (s16)index);
                index--;
                child_slot--;
            } while (index >= 0);
        }
        func_800A56E0(0x300);
        goto finish;

    case 3:
        index = 7;
        if (ctrl->timer < 33) {
            goto finish;
        }
        child_update = func_800244D4;
        ctrl->timer = 0;
        ctrl->state++;
        {
            Child **child_slot;

            child_slot = &ctrl->children[1];
            do {
                if (child_slot[6] != 0) {
                    child_slot[6]->update = child_update;
                }
                index--;
                child_slot--;
            } while (index >= 0);
        }
        goto finish;

    case 4:
        if (ctrl->timer < 17) {
            goto finish;
        }
        func_80024060(ctrl->cell_x, ctrl->cell_y, root, ctrl->kind);
        ctrl->timer = 0;
        ctrl->state++;
        {
            register Child **child_slot ASM_REG("$5");
            u8 *global_page;

            index = 7;
            global_page = (u8 *)0x80080000;
            child_slot = &ctrl->children[1];
            do {
                child = child_slot[6];
                if (child != 0) {
                    u16 child_flags;
                    register u32 global_flags ASM_REG("$3");

                    child_flags = child->flags;
                    ASM_KEEP(child_flags);
                    global_flags = *(u32 *)(global_page + 0x14A0);
                    child_flags |= 0x8000;
                    global_flags |= 0x8000;
                    ASM_KEEP(global_flags);
                    child->flags = child_flags;
                    *(u32 *)(global_page + 0x14A0) = global_flags;
                    child_slot[6] = 0;
                }
                index--;
                child_slot--;
            } while (index >= 0);
        }
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
