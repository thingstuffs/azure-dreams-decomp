#include "common.h"

extern void func_800ABE60(u32 x, u32 y, u32 cell);
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;

typedef struct {
    s32 map_base;
    u8 pad04[0x10];
    s16 x_shift;
    s16 y_shift;
} GridInfo;

extern GridInfo D_8008333C[];

/* Visit and count flagged grid cells along two opposite directions for up to ten steps. */
s32 func_800ABEEC(s32 dir, s32 start_x, s32 start_y) {
    /* The six spilled locals. Declaration order == stack slot order:
       0x10, 0x18, 0x20, 0x28, 0x30, 0x34($sp). */
    s32 map_base;
    u16 reverse_dir;
    u16 fwd_count;
    u16 rev_count;
    s32 fwd_step_offset;
    u16 *fwd_x_step;

    s32 fwd_dir_offset;
    register s32 fwd_check_x;
    s32 fwd_check_y;
    s32 rev_check_x;
    s32 rev_check_y;
    register s32 fwd_y;
    register s32 rev_y;
    register s32 fwd_x;
    register s32 fwd_blocked;
    register s32 rev_blocked;
    register GridInfo *grid;
    register s32 step_count;
    s32 one;
    register s32 fwd_x_test;
    s32 fwd_y_high;
    s32 fwd_stopped;
    s32 rev_x_high;
    s32 rev_y_high;
    s32 rev_stopped;
    u16 *fwd_cell;
    u16 *rev_cell;
    register u32 fwd_cell_flags;
    register u32 rev_cell_flags;
    s32 rev_x;
    u8 *x_steps;
    s32 fwd_map_y;
    s32 fwd_dx;
    s32 rev_map_y;
    s32 rev_dx;
    s32 visit_count;
    s32 fwd_dy;
    s32 rev_step_offset;
    s32 rev_dy;
    s32 fwd_map_x;
    s32 fwd_map_base;
    s32 rev_map_base;
    s32 fwd_row_shift;
    s32 rev_row_shift;
    s32 rev_map_x;
    s32 y_steps_addr;
    u16 *rev_y_step;
    s32 rev_step_dir;
    /* $0 read as the constant zero.  Spelling `step_count = 0` with a literal
       lets reload's find_equiv_reg re-source the 0 from $s4/$s5 (which hold 0
       here); reading the zero register keeps retail's `move $s7,$zero`. */
    register s32 zero ASM_REG("$0");   /* MATCH pin: retail register colouring depends on it */

#ifdef NON_MATCHING
    zero = 0;
#endif
    grid = D_8008333C;
    rev_blocked = 0;
    fwd_blocked = rev_blocked;
    rev_x = start_x;
    /* Copy-propagation pin: this empty asm writes the parameter pseudo, which
       stops local-alloc's optimize_reg_copy_1 from re-sourcing the second copy
       below from the first (would give `move $s2,$s3` instead of retail's two
       direct `move $sN,$a1`). */
    ASM_KEEP_NV(start_x);   /* MATCH pin: load-bearing for the whole function shape */
    fwd_x = start_x;
    rev_y = start_y;
    ASM_KEEP_NV(start_y); /* same pin for the $a2 pair */
    fwd_y = start_y;
    step_count = zero;
    one = 1;
    map_base = D_8008333C[0].map_base;
    x_steps = (u8 *)&D_8006CCD8;
    rev_count = 0;
    fwd_count = 0;
    reverse_dir = (dir - 2) & 7;
    fwd_dir_offset = ((dir + 2) & 7) << 1;
    fwd_step_offset = fwd_dir_offset;
    fwd_x_step = (u16 *)(x_steps + fwd_dir_offset);
    /* Dead pre-set (removed by flow): gives `rev_step_dir`'s real definition a
       non-first regno_first_uid so loop.c refuses to hoist the invariant
       reverse_dir read+shift out of the loop, as retail keeps it in-loop. */
    rev_step_dir = dir;
    do {
        fwd_x_test = fwd_x << 0x10;
        fwd_check_x = fwd_x_test >> 0x10;
        if (fwd_check_x >= 0) {
            fwd_x_test = fwd_check_x < (one << grid->x_shift);
            if (fwd_x_test != 0) {
                fwd_y_high = fwd_y << 0x10;
                goto check_fwd_y;
            }
        }
        fwd_blocked = 1;
        fwd_y_high = fwd_y << 0x10;
    check_fwd_y:
        fwd_check_y = fwd_y_high >> 0x10;
        if ((fwd_check_y < 0) ||
            ((fwd_check_y < (one << grid->y_shift)) == 0)) {
            fwd_blocked = 1;
            fwd_stopped = fwd_blocked;
        } else {
            fwd_stopped = fwd_blocked;
        }
        if (fwd_stopped != 0) {
            goto second_walker;
        }
        fwd_map_x = (fwd_x << 0x10) >> 0x10;
        fwd_map_y = (fwd_y << 0x10) >> 0x10;
        fwd_row_shift = grid->x_shift;
        fwd_map_base = map_base;
        fwd_cell = (u16 *)(fwd_map_base +
            ((fwd_map_x + (fwd_map_y << fwd_row_shift)) << 1));
        fwd_cell_flags = *fwd_cell;
        if (fwd_cell_flags & 0x8000) {
            *fwd_cell = fwd_cell_flags | 0x4000;
            func_800ABE60(fwd_x & 0xFFFF, fwd_y & 0xFFFF, fwd_cell_flags);
            {
                u16 *fwd_y_step;
                u16 *fwd_x_step_ptr;

                fwd_count += 1;
                y_steps_addr = (s32)&D_8006CCD8 + 0x10;
                fwd_y_step = (u16 *)(fwd_step_offset + y_steps_addr);
                fwd_x_step_ptr = fwd_x_step;
                fwd_dy = *fwd_y_step;
                fwd_dx = *fwd_x_step_ptr;
                fwd_y += fwd_dy;
                fwd_x += fwd_dx;
            }
            goto second_walker;
        }
        fwd_blocked = 1;
    second_walker:
        rev_x_high = rev_x << 0x10;
        rev_check_x = rev_x_high >> 0x10;
        if ((rev_check_x < 0) ||
            ((rev_check_x < (one << grid->x_shift)) == 0)) {
            rev_blocked = 1;
        }
        rev_y_high = rev_y << 0x10;
        rev_check_y = rev_y_high >> 0x10;
        if ((rev_check_y < 0) ||
            ((rev_check_y < (one << grid->y_shift)) == 0)) {
            rev_blocked = 1;
            rev_stopped = rev_blocked;
        } else {
            rev_stopped = rev_blocked;
        }
        if (rev_stopped == 0) {
            rev_map_x = (rev_x << 0x10) >> 0x10;
            rev_map_y = (rev_y << 0x10) >> 0x10;
            rev_row_shift = grid->x_shift;
            rev_map_base = map_base;
            rev_cell = (u16 *)(rev_map_base +
                ((rev_map_x + (rev_map_y << rev_row_shift)) << 1));
            rev_cell_flags = *rev_cell;
            if (rev_cell_flags & 0x8000) {
                *rev_cell = rev_cell_flags | 0x4000;
                func_800ABE60(rev_x & 0xFFFF, rev_y & 0xFFFF, rev_cell_flags);
                {
                    register u16 *rev_x_step;

                    rev_count += 1;
                    rev_step_dir = reverse_dir;
                    rev_step_offset = rev_step_dir << 1;
                    rev_x_step = (u16 *)(rev_step_offset + (s32)x_steps);
                    rev_y_step = (u16 *)(rev_step_offset + (s32)&D_8006CCE8);
                    rev_dx = *rev_x_step;
                    rev_dy = *rev_y_step;
                    rev_x += rev_dx;
                    rev_y += rev_dy;
                }
                goto next_step;
            }
            rev_blocked = 1;
        }
    next_step:
        step_count += 1;
        visit_count = fwd_x << 0x10; /* loop-bottom reference; keeps the s2/s3
                                       walker birth order (do not remove) */
    } while (step_count < 10);
    /* Two dead stores (removed by flow): they keep the parameter pseudos
       cse-canonical for their whole lifetime, so cse leaves both prologue
       copies of each parameter reading the argument register directly. */
    visit_count = start_x;
    visit_count = start_y;
    visit_count = (s16)(fwd_count + rev_count);
    return visit_count;
}
