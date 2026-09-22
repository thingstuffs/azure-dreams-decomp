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
    u8 *root;
    void *render_data;
    RootPrefix *root_prefix;
    Lookup *lookup;
    Lookup *lookup_2;
    Motion *source_motion;
    Motion *linked_motion;
    u8 *linked_root;
    u8 *linked_root_2;
    u8 *linked_root_3;
    s16 offsets[3];
    u16 end_x;
    u16 end_y;
    s32 steps;
    register s32 coord_diff ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 origin_coord;
    s32 floor_height;
    s32 cell_x;
    s16 cell_y;
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
        root_prefix = (RootPrefix *)(root - 0x20);
        if (func_8003DE58(root_prefix->lookup->key, root_prefix->lookup, offsets, 0) == 0) {
            if (!(root_prefix->lookup->flags & 0x8000)) {
                goto finish;
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
            goto finish;
        }

        input_ctrl->saved = *input_motion;
        linked_root = *(u8 **)(root + 0x60);
        if (linked_root != 0) {
            s32 div_magic = (s32)0x88880000;
            WideProduct product;

            ASM_KEEP_NV(div_magic);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            linked_motion = *(Motion **)(linked_root - 0x18);

            origin_coord = input_motion->x.h.hi;
            coord_diff = linked_motion->x.h.hi - origin_coord;
            if (coord_diff < 0) {
                coord_diff = -coord_diff;
            }
            offsets[0] = coord_diff;

            coord_diff = linked_motion->y.h.hi;
            coord_diff -= input_motion->y.h.hi;
            if (coord_diff < 0) {
                coord_diff = -coord_diff;
            }
            offsets[1] = coord_diff;

            linked_root_2 = *(u8 **)(root + 0x60);
            origin_coord = input_motion->z.h.hi;
            coord_diff = *(s16 *)(linked_root_2 + 0x88);
            coord_diff -= origin_coord;
            if (coord_diff < 0) {
                coord_diff = -coord_diff;
            }
            offsets[2] = coord_diff;

            linked_root_3 = *(u8 **)(root + 0x60);
            lookup = *(Lookup **)(linked_root_3 - 0x14);
            input_ctrl->cell_x = lookup->cell_x;
            input_ctrl->cell_y = lookup->cell_y;

            input_ctrl->target[0].val = linked_motion->x.val;
            input_ctrl->target[1].val = linked_motion->y.val;
            coord_diff = *(volatile u16 *)(*(u8 **)(root + 0x60) + 0x88);
            *(volatile u16 *)&input_ctrl->target[2].h.lo = 0;
            *(volatile u16 *)&input_ctrl->target[2].h.hi = coord_diff;

            div_magic |= 0x8889;
            coord_diff = *(volatile s32 *)&input_ctrl->target[0].val;
            coord_diff -= input_motion->x.val;
            product.value = (long long)coord_diff * div_magic;
            input_motion->dx.val = ((s32)((u32)product.word.upper -
                (0U - (u32)coord_diff)) >> 3) - (coord_diff >> 31);
            coord_diff = *(volatile s32 *)&input_ctrl->target[1].val;
            coord_diff -= input_motion->y.val;
            product.value = (long long)coord_diff * div_magic;
            input_motion->dy.val = ((s32)((u32)product.word.upper -
                (0U - (u32)coord_diff)) >> 3) - (coord_diff >> 31);
            coord_diff = *(volatile s32 *)&input_ctrl->target[2].val;
            coord_diff -= input_motion->z.val;
            product.value = (long long)coord_diff * div_magic;
            input_motion->dz.val = ((s32)((u32)product.word.upper -
                (0U - (u32)coord_diff)) >> 3) - (coord_diff >> 31);
            goto advance;
        }

        steps = 0;
        lookup_2 = root_prefix->lookup;
        coord_diff = (s32)0x80070000;
        cell_y = lookup_2->cell_y;
        cell_x = lookup_2->cell_x;
        end_x = cell_x;
        end_y = cell_y;

        do {
            if ((s16)func_800A44E0(((s16)cell_x << 6) & 0xFFC0,
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
                step_x = &D_8006CCD8[direction];
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
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
                register s32 next_x ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                s16 next_y;
                s16 *step_x;
                s16 *step_y;
                s32 direction;

                direction = (s16)input_ctrl->angle;
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

            linked_motion = (Motion *)input_ctrl->target;
            ((Fixed32 *)linked_motion)[2].val = 0;
            ((Fixed32 *)linked_motion)[1].val = 0;
            input_ctrl->target[0].val = 0;
            ((Fixed32 *)linked_motion)[0].h.hi = ((end_x << 16) >> 10) + 32;
            ((Fixed32 *)linked_motion)[1].h.hi = ((end_y << 16) >> 10) + 32;
            ((Fixed32 *)linked_motion)[2].h.hi = -1024;
            ((Fixed32 *)linked_motion)[2].h.hi = func_800BCB04((u16)((Fixed32 *)linked_motion)[0].h.hi,
                (u16)((Fixed32 *)linked_motion)[1].h.hi, -1024);
            if ((s16)((Fixed32 *)linked_motion)[2].h.hi >= 513) {
                ((Fixed32 *)linked_motion)[2].h.hi = input_motion->z.h.hi + 32;
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
        func_800248C8(input_ctrl, render_data);
        if (input_ctrl->timer < 15) {
            goto finish;
        }
        input_ctrl->timer = 0;
        input_ctrl->state++;
        func_800247DC(input_ctrl, input_motion);
        func_800A56E0(0x300);
        goto finish;

    case 3:
        if (input_ctrl->ready == 0) {
            goto finish;
        }
        input_ctrl->timer = 0;
        input_ctrl->ready = 0;
        input_ctrl->state++;
        func_80024684(input_ctrl, input_motion);
        goto finish;

    case 4:
        if (input_ctrl->ready == 0) {
            goto finish;
        }
        func_80024060(input_ctrl->cell_x, input_ctrl->cell_y, root, input_ctrl->kind);

    advance:
        input_ctrl->timer = 0;
        input_ctrl->state++;
        goto finish;

    case 5:
        if (input_ctrl->active == 0) {
            D_8008346C[0] = 0;
            *(u16 *)((u8 *)input_ctrl - 2) |= 0x8000;
            D_800814A0.value |= 0x8000;
        }

    default:
        break;
    }

finish:
    input_ctrl->active = 0;
}
