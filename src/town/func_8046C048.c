#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"

typedef struct S_8001D048_3 {
    u8 pad_00[0x2D0];
    M2C_UNK (*unk_2D0)(s32, u8, s32);
} S_8001D048_3;   /* callback_base in func_8001D048 */



typedef struct S_8001D048_1 {
    u8 pad_00[0x3640];
    u8 unk_3640;
} S_8001D048_1;   /* row + work_s0 in func_8001D048 */

typedef struct S_8001D048_2 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8001D048_2;   /* global_base in func_8001D048 */


s32 func_8001D280();                   /* extern */
s32 func_8001E7E4();                         /* extern */
extern Rec_D_80016000 *D_80016000;
extern s16 D_8001902C[];

/* Invoke the callback for nonzero row entries using the selected mode and bounds. */
void func_8001D048(void) {
    s32 mode_check;
    s32 entry_result;
    s32 callback_arg;
    long row_or_column;
    unsigned long bounds_addr;
    s32 mode;
    register s32 row_index ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 row_offset;
    s32 check_offset;
    s32 mode_offset;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u8 entry_value ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s8 *row;
    register s8 *check_base ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s16 *bounds;
    S_8001D048_2 *global_base;
    S_8001D048_3 *callback_base;
    M2C_UNK (*callback)(s32, u8, s32);

    row_or_column = (long)D_80016000->unk_38.as_ps8;
    mode_check = func_8001E7E4(1);
    mode = 0;
    if (mode_check != 0) {
        goto mode_done;
    }
    mode_check = func_8001E7E4(2);
    mode = 2;
    if (mode_check == 0) {
        goto mode_done;
    }
    mode = 1;
mode_done:
    row_index = 0;
    ASM_KEEP(row_index);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    do {
        row_offset = row_index;
    } while (0);
    do {
        row = (s8 *)row_or_column;
    } while (0);
    check_offset = mode * 8;
    do {
        check_base = (s8 *)D_8001902C;
        bounds_addr = (unsigned long)check_offset + (unsigned long)check_base;
        ASM_KEEP(bounds_addr);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        row_or_column = 0;
        if (*(s16 *)bounds_addr > 0) {
            bounds_addr = 0x80020000UL;
            ASM_KEEP(bounds_addr);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            bounds = (s16 *)(bounds_addr - 0x6FD4);
            mode_offset = mode * 8;
process_entry:
            entry_value = ((S_8001D048_1 *)(row + row_or_column))->unk_3640;
            if (entry_value != 0) {
                entry_result = func_8001D280(row_index, row_or_column, mode);
                global_base = D_80016000;
                do {
                    callback_arg = entry_result;
                    ASM_KEEP(callback_arg);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                } while (0);
                callback_base = global_base->unk_20;
                callback = callback_base->unk_2D0;
                callback(callback_arg, entry_value, mode);
                row_or_column += 1;
                if (row_or_column < *(s16 *)((long)(mode_offset + row_offset) + (long)bounds)) {
                    goto process_entry;
                }
            }
        }
        row_offset += 0x18;
        row += 0xC;
        row_index += 1;
        check_offset += 0x18;
    } while (row_index < 0x10);
}

/* MECHANISM: Separate byte offsets keep row_offset in s5 and the two mode-derived
   offsets in s6/s7; the block-local bounds base stays live in fp across callbacks.
   This hold set reproduces the retail 0x38 frame and ra,fp,s7..s0 save contract. */
