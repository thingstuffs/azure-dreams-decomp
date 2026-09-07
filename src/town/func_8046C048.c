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

void func_8001D048(void) {
    s32 result;
    s32 call_result;
    s32 arg0;
    long work_s0;
    unsigned long temp_v0;
    s32 mode;
    register s32 outer ASM_REG("$19");   /* MATCH pin: retail register colouring depends on it */
    s32 row_offset;
    s32 check_offset;
    register s32 mode_offset ASM_REG("$22");   /* MATCH pin: retail register colouring depends on it */
    register u8 value ASM_REG("$17");   /* MATCH pin: retail register colouring depends on it */
    s8 *row;
    register s8 *check_base ASM_REG("$7");   /* MATCH pin: keeps a constant in a register as retail does */
    s16 *bounds;
    S_8001D048_2 *global_base;
    S_8001D048_3 *callback_base;
    M2C_UNK (*callback)(s32, u8, s32);

    work_s0 = (long)D_80016000->unk_38.as_ps8;
    result = func_8001E7E4(1);
    mode = 0;
    if (result != 0) {
        goto mode_done;
    }
    result = func_8001E7E4(2);
    mode = 2;
    if (result == 0) {
        goto mode_done;
    }
    mode = 1;
mode_done:
    ASM_KEEP(mode);   /* MATCH pin: retail register colouring depends on it */
    outer = 0;
    ASM_KEEP(outer);   /* MATCH pin: retail register colouring depends on it */
    row_offset = outer;
    ASM_KEEP(row_offset);   /* MATCH pin: retail register colouring depends on it */
    row = (s8 *)work_s0;
    ASM_KEEP(row);   /* MATCH pin: retail register colouring depends on it */
    check_offset = mode * 8;
    do {
        check_base = (s8 *)D_8001902C;
        temp_v0 = (unsigned long)check_offset + (unsigned long)check_base;
        ASM_KEEP(temp_v0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        work_s0 = 0;
        if (*(s16 *)temp_v0 > 0) {
            temp_v0 = 0x80020000UL;
            ASM_KEEP(temp_v0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            bounds = (s16 *)(temp_v0 - 0x6FD4);
            mode_offset = mode * 8;
loop_6:
            value = ((S_8001D048_1 *)(row + work_s0))->unk_3640;
            if (value != 0) {
                call_result = func_8001D280(outer, work_s0, mode);
                global_base = D_80016000;
                ASM_USE(global_base);   /* MATCH pin: load-bearing for the whole function shape */
                arg0 = call_result;
                ASM_KEEP(arg0);   /* MATCH pin: load-bearing for the whole function shape */
                callback_base = global_base->unk_20;
                callback = callback_base->unk_2D0;
                callback(arg0, value, mode);
                work_s0 += 1;
                if (work_s0 < *(s16 *)((long)(mode_offset + row_offset) + (long)bounds)) {
                    goto loop_6;
                }
            }
        }
        row_offset += 0x18;
        row += 0xC;
        outer += 1;
        check_offset += 0x18;
    } while (outer < 0x10);
}

/* MECHANISM: Separate byte offsets keep row_offset in s5 and the two mode-derived
   offsets in s6/s7; the block-local bounds base stays live in fp across callbacks.
   This hold set reproduces the retail 0x38 frame and ra,fp,s7..s0 save contract. */
