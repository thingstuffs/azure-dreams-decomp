#include "common.h"
#include "m2c_compat.h"

typedef struct S_806D85A0_0 {
    void * unk_00;
} S_806D85A0_0;   /* &D_80016000 in func_806D85A0 */

typedef struct S_806D85A0_1 {
    u8 pad_00[0x2D0];
    void * unk_2D0;
    u8 pad_2D4[0x5D2C];
    void * unk_6000;
} S_806D85A0_1;   /* temp_func in func_806D85A0 */

typedef struct S_806D85A0_2 {
    u8 pad_00[0x20];
    void * unk_20;
} S_806D85A0_2;   /* temp_v1 in func_806D85A0 */

typedef struct S_806D85A0_3 {
    u8 pad_00[0x3640];
    u8 unk_3640;
} S_806D85A0_3;   /* var_s6 + var_s2 in func_806D85A0 */

typedef struct S_806D85A0_4 {
    s16 unk_00;
    s16 unk_02;
} S_806D85A0_4;   /* temp_s3 in func_806D85A0 */

typedef struct S_806D85A0_5 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0x14];
    void * unk_38;
} S_806D85A0_5;   /* ((S_806D85A0_0 *)(&D_80016000))->unk_00 in func_806D85A0 */

typedef struct S_806D85A0_6 {
    u8 pad_00[0x2D0];
    M2C_UNK (*unk_2D0)(s32, s32, s32);
} S_806D85A0_6;   /* ((S_806D85A0_5 *)(((S_806D85A0_0 *)(&D_80016000))->unk_00))->unk_20 in func_806D85A0 */


void *func_80017024();                 /* extern */
s32 func_8001876C();                         /* extern */
extern volatile M2C_UNK D_80016000;
extern M2C_UNK D_80018FE0;

/* Processes active entries for the selected variant and updates 2x2 cells for the first group. */
void func_806D85A0(void) {
    s32 cell_x;
    s32 cell_y;
    s32 cell_value;
    s32 y_offset;
    s32 x_offset;
    s32 entry_index;
    s32 group_index;
    s32 count_offset;
    register s32 variant ASM_REG("$23");   /* MATCH pin: retail register colouring depends on it */
    s32 second_variant_active;
    s32 initial_x;
    register s32 initial_y ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 initial_value;
    register void *context ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *dispatch_ptr ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    void *entry_flags;
    register void *position ASM_REG("$19");   /* MATCH pin: retail register colouring depends on it */
    void *group_flags;

    entry_flags = ((S_806D85A0_5 *)(((S_806D85A0_0 *)(&D_80016000))->unk_00))->unk_38;
    if (func_8001876C(1) == 0) {
        second_variant_active = func_8001876C(2);
        variant = 2;
        if (second_variant_active != 0) {
            variant = 1;
        }
    } else {
        variant = 0;
    }
    initial_x = 4;
    ASM_KEEP_NV(initial_x);   /* MATCH pin: keeps a statement from moving across a call/branch */
    initial_y = initial_x;
    initial_value = 0;
    ASM_KEEP_NV(initial_y);   /* MATCH pin: keeps a statement from moving across a call/branch */
    ASM_KEEP_NV(initial_value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    dispatch_ptr = (void *)0x80010000;
    ASM_KEEP_NV(dispatch_ptr);   /* MATCH pin: keeps a statement from moving across a call/branch */
    context = ((S_806D85A0_1 *)dispatch_ptr)->unk_6000;
    group_index = initial_value;
    dispatch_ptr = ((S_806D85A0_2 *)context)->unk_20;
    count_offset = variant * 8;
    dispatch_ptr = ((S_806D85A0_1 *)dispatch_ptr)->unk_2D0;
    ASM_KEEP(dispatch_ptr);   /* MATCH pin: keeps a statement from moving across a call/branch */
    group_flags = entry_flags;
    ((M2C_UNK (*)(M2C_UNK, M2C_UNK, M2C_UNK))dispatch_ptr)(initial_x, initial_y, initial_value);
    do {
        entry_index = 0;
        if ((*(s16 *)((u8 *)(&D_80018FE0) + count_offset)) > 0) {
            s16 *entry_counts;

            dispatch_ptr = (void *)0x80020000;
            ASM_KEEP_NV(dispatch_ptr);   /* MATCH pin: keeps a statement from moving across a call/branch */
            entry_counts = (s16 *)((s8 *)dispatch_ptr - 0x7020);
next_entry:
            if (((S_806D85A0_3 *)(group_flags + entry_index))->unk_3640 != 0) {
                position = func_80017024(group_index, entry_index, variant);
                if (group_index == 0) {
                    x_offset = 0;
                    do {
                        y_offset = 0;
next_cell:
                        cell_value = x_offset + y_offset;
                        cell_x = ((S_806D85A0_4 *)position)->unk_00 + x_offset;
                        cell_y = ((S_806D85A0_4 *)position)->unk_02 + y_offset;
                        ((S_806D85A0_6 *)(((S_806D85A0_5 *)(((S_806D85A0_0 *)(&D_80016000))->unk_00))->unk_20))->unk_2D0(cell_x, cell_y, cell_value);
                        y_offset += 1;
                        if (y_offset < 2) {
                            goto next_cell;
                        }
                        x_offset += 1;
                    } while (x_offset < 2);
                }
                entry_index += 1;
                if (entry_index < (*(s16 *)((u8 *)((s8 *)(u32)count_offset) + (s32)entry_counts))) {
                    goto next_entry;
                }
            }
        }
        count_offset += 0x18;
        group_index += 1;
        group_flags += 0xC;
    } while (group_index < 0x10);
}
