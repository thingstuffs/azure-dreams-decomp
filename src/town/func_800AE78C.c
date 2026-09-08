#include "common.h"

/* func_800ABEEC (TOWN overlay copy: func_800AE78C) -- flood/visit step over the
 * collision grid.  Two walkers start at (start_x, start_y): one steps forward
 * along direction `dir`, one steps backward (dir rotated by 4, i.e. -2..+2 & 7).
 * Each iteration (10 max) a walker still in bounds probes its cell; if the cell
 * has bit 15 set it is marked visited (bit 14), func_800ABE60 is called on it,
 * and the walker advances by the per-direction step table entry.  Returns the
 * total number of cells visited by both walkers.
 *
 * D_8006CCD8: per-direction x-step table (8 x u16)
 * D_8006CCE8: per-direction y-step table (== D_8006CCD8 + 0x10)
 *
 * MATCHING NOTES (gcc 2.7.2-cdk -O2 -G0, no extra flags):
 * The six function-scope scalars below deliberately outnumber the callee-saved
 * registers, so global-alloc denies them and reload homes them on the stack
 * (frame 0x10..0x34) and services every access through the spill registers --
 * that reproduces retail's whole $t0/$a3 register stream.  Three guarded
 * scaffold lines force choices the optimizers otherwise make differently; each
 * is a no-op in the port build and is documented where it appears.
 */

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

s32 func_800ABEEC(s32 dir, s32 start_x, s32 start_y) {
    /* The six spilled locals. Declaration order == stack slot order:
       0x10, 0x18, 0x20, 0x28, 0x30, 0x34($sp). */
    s32 map_base;
    u16 reverse_dir;
    u16 first_count;
    u16 second_count;
    s32 dir_offset;
    u16 *x_step_ptr;

    s32 fwd_off;
    register s32 check;
    s32 check_y1;
    s32 check_x2;
    s32 check_y2;
    register s32 fwd_y;
    register s32 rev_y;
    register s32 fwd_x;
    register s32 fwd_blocked;
    register s32 rev_blocked;
    register GridInfo *grid;
    register s32 step_no;
    s32 one;
    register s32 tmp;
    s32 tmp_y1;
    s32 tmp2;
    s32 tmp_x2;
    s32 tmp_y2;
    s32 tmp_tail;
    u16 *fwd_cell;
    u16 *rev_cell;
    register u32 fwd_val;
    register u32 rev_val;
    s32 rev_x;
    u8 *step_base;
    s32 fwd_map_y;
    s32 fwd_dx;
    s32 rev_map_y;
    s32 rev_dx;
    s32 tail_value;
    s32 fwd_dy;
    s32 rev_off;
    s32 rev_dy;
    s32 fwd_map_x;
    s32 fwd_mb;
    s32 rev_mb;
    s32 fwd_shift;
    s32 rev_shift;
    s32 rev_map_x;
    s32 fwd_ybase;
    u16 *rev_y_ptr;
    s32 rev_dir2;
    /* $0 read as the constant zero.  Spelling `step_no = 0` with a literal
       lets reload's find_equiv_reg re-source the 0 from $s4/$s5 (which hold 0
       here); reading the zero register keeps retail's `move $s7,$zero`. */
    register s32 zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

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
    ASM_KEEP_NV(start_x);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    fwd_x = start_x;
    rev_y = start_y;
    ASM_KEEP_NV(start_y); /* same pin for the $a2 pair */
    fwd_y = start_y;
    step_no = zero;
    one = 1;
    map_base = D_8008333C[0].map_base;
    step_base = (u8 *)&D_8006CCD8;
    second_count = 0;
    first_count = 0;
    reverse_dir = (dir - 2) & 7;
    fwd_off = ((dir + 2) & 7) << 1;
    dir_offset = fwd_off;
    x_step_ptr = (u16 *)(step_base + fwd_off);
    /* Dead pre-set (removed by flow): gives `rev_dir2`'s real definition a
       non-first regno_first_uid so loop.c refuses to hoist the invariant
       reverse_dir read+shift out of the loop, as retail keeps it in-loop. */
    rev_dir2 = dir;
    do {
    tmp = fwd_x << 0x10;
    check = tmp >> 0x10;
    if (check >= 0) {
        tmp = check < (one << grid->x_shift);
        if (tmp != 0) {
            tmp_y1 = fwd_y << 0x10;
            goto check_fwd_y;
        }
    }
    fwd_blocked = 1;
    tmp_y1 = fwd_y << 0x10;
check_fwd_y:
    check_y1 = tmp_y1 >> 0x10;
    if ((check_y1 < 0) ||
        ((check_y1 < (one << grid->y_shift)) == 0)) {
        fwd_blocked = 1;
        tmp2 = fwd_blocked;
    } else {
        tmp2 = fwd_blocked;
    }
    if (tmp2 != 0) {
        goto second_walker;
    }
    fwd_map_x = (fwd_x << 0x10) >> 0x10;
    fwd_map_y = (fwd_y << 0x10) >> 0x10;
    fwd_shift = grid->x_shift;
    fwd_mb = map_base;
    fwd_cell = (u16 *)(fwd_mb +
        ((fwd_map_x + (fwd_map_y << fwd_shift)) << 1));
    fwd_val = *fwd_cell;
    if (fwd_val & 0x8000) {
        *fwd_cell = fwd_val | 0x4000;
        func_800ABE60(fwd_x & 0xFFFF, fwd_y & 0xFFFF, fwd_val);
        {
            u16 *y_step;
            u16 *x_step;

            first_count += 1;
            fwd_ybase = (s32)&D_8006CCD8 + 0x10;
            y_step = (u16 *)(dir_offset + fwd_ybase);
            x_step = x_step_ptr;
            fwd_dy = *y_step;
            fwd_dx = *x_step;
            fwd_y += fwd_dy;
            fwd_x += fwd_dx;
        }
        goto second_walker;
    }
    fwd_blocked = 1;
second_walker:
    tmp_x2 = rev_x << 0x10;
    check_x2 = tmp_x2 >> 0x10;
    if ((check_x2 < 0) ||
        ((check_x2 < (one << grid->x_shift)) == 0)) {
        rev_blocked = 1;
    }
    tmp_y2 = rev_y << 0x10;
    check_y2 = tmp_y2 >> 0x10;
    if ((check_y2 < 0) ||
        ((check_y2 < (one << grid->y_shift)) == 0)) {
        rev_blocked = 1;
        tmp_tail = rev_blocked;
    } else {
        tmp_tail = rev_blocked;
    }
    if (tmp_tail == 0) {
        rev_map_x = (rev_x << 0x10) >> 0x10;
        rev_map_y = (rev_y << 0x10) >> 0x10;
        rev_shift = grid->x_shift;
        rev_mb = map_base;
        rev_cell = (u16 *)(rev_mb +
            ((rev_map_x + (rev_map_y << rev_shift)) << 1));
        rev_val = *rev_cell;
        if (rev_val & 0x8000) {
            *rev_cell = rev_val | 0x4000;
            func_800ABE60(rev_x & 0xFFFF, rev_y & 0xFFFF, rev_val);
            {
                register u16 *rev_x_ptr;

                second_count += 1;
                rev_dir2 = reverse_dir;
                rev_off = rev_dir2 << 1;
                rev_x_ptr = (u16 *)(rev_off + (s32)step_base);
                rev_y_ptr = (u16 *)(rev_off + (s32)&D_8006CCE8);
                rev_dx = *rev_x_ptr;
                rev_dy = *rev_y_ptr;
                rev_x += rev_dx;
                rev_y += rev_dy;
            }
            goto next_step;
        }
        rev_blocked = 1;
    }
next_step:
    step_no += 1;
    tail_value = fwd_x << 0x10; /* loop-bottom reference; keeps the s2/s3
                                   walker birth order (do not remove) */
    } while (step_no < 10);
    /* Two dead stores (removed by flow): they keep the parameter pseudos
       cse-canonical for their whole lifetime, so cse leaves both prologue
       copies of each parameter reading the argument register directly. */
    tail_value = start_x;
    tail_value = start_y;
    tail_value = (s16)(first_count + second_count);
    return tail_value;
}
