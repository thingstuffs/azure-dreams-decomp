#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A4B88_0_pre {
    s32 unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_800A4B88_0_pre;   /* the 0x18 bytes before arg0 in func_800A4B88, addressed as arg0[-1] */

typedef struct S_800A4B88_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_800A4B88_0;   /* arg0 in func_800A4B88 */

typedef struct S_800A4B88_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800A4B88_1;   /* temp_s0 in func_800A4B88 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80089008[];
void func_8003DB94();     /* extern */
M2C_UNK func_8003E188();            /* extern */
void func_80041E70();                      /* extern */
M2C_UNK func_80096088();              /* extern */
void func_8009A21C();             /* extern */
M2C_UNK func_8009A3D0();             /* extern */
M2C_UNK func_800ACB98(); /* extern */
M2C_UNK func_800D8590();                      /* extern */
extern M2C_UNK D_80082E80;
extern s32 D_80083110[];
extern s16 D_80083228;
extern u8 D_800DD274[];

/* Applies an action to the object's flags and tile state, then updates the object. */
void func_800A4B88(void *object, s32 action) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12, &&jt_c13, &&jt_c14, &&jt_c15, &&jt_c16, &&jt_c17, &&jt_c18, &&jt_c19, &&jt_c20, &&jt_c21, &&jt_c22, &&jt_c23, &&jt_c24, &&jt_c25, &&jt_c26 };
    M2C_UNK clear_mask;
    M2C_UNK enable_clear_mask;
    M2C_UNK set_mask;
    M2C_UNK disable_clear_mask;
    s32 action_index;
    s32 *reset_slot;
    s32 updated_flags;
    s32 reset_index;
    M2C_UNK *update_state;
    u8 tile_x;
    u8 tile_y;
    void *position;

    action_index = (s16) (action - 1);
    if ((u32) action_index >= 0x1BU) {
        goto block_26;
    }
    (void)jt_keep; goto *D_80089008[(u32)(action_index)];
jt_c0:
    ((S_800A4B88_0 *)object)->unk_1C = (s32) (((S_800A4B88_0 *)object)->unk_1C | 0x200);
    goto block_26;
jt_c1:
    ((S_800A4B88_0 *)object)->unk_1C = (s32) (((S_800A4B88_0 *)object)->unk_1C | 0x400);
    goto block_26;
jt_c2:
    ((S_800A4B88_0 *)object)->unk_1C = (s32) ((((S_800A4B88_0 *)object)->unk_1C & 0xFFFDFFFF) | 0x10);
    goto block_26;
jt_c3:
    ((S_800A4B88_0 *)object)->unk_1C = (s32) (((S_800A4B88_0 *)object)->unk_1C | 0x20);
    goto block_26;
jt_c4:
    ((S_800A4B88_0 *)object)->unk_1C = (s32) (((S_800A4B88_0 *)object)->unk_1C | 0x40);
    goto block_26;
jt_c5:
    ((S_800A4B88_0 *)object)->unk_1C = (s32) (((S_800A4B88_0 *)object)->unk_1C | 0x80);
    goto block_26;
jt_c7:
    ((S_800A4B88_0 *)object)->unk_1C = (s32) (((S_800A4B88_0 *)object)->unk_1C | 0x800);
    goto block_26;
jt_c8:
    ((S_800A4B88_0 *)object)->unk_1C = (s32) (((S_800A4B88_0 *)object)->unk_1C | 0x1000);
    goto block_26;
jt_c26:
    position = ((S_800A4B88_0_pre *)object)[-1].unk_04;
    tile_x = ((S_800A4B88_1 *)position)->unk_24;
    tile_y = ((S_800A4B88_1 *)position)->unk_25;
    clear_mask = 0x3000;
    if (!(((S_800A4B88_0 *)object)->unk_1C & 0x2000)) {
        goto block_12;
    }
    clear_mask = 0x300;
block_12:
    func_8009A3D0(tile_x, tile_y, clear_mask);
    goto block_26;
jt_c10:
    position = ((S_800A4B88_0_pre *)object)[-1].unk_04;
    tile_x = ((S_800A4B88_1 *)position)->unk_24;
    tile_y = ((S_800A4B88_1 *)position)->unk_25;
    enable_clear_mask = 0x3000;
    if (!(((S_800A4B88_0 *)object)->unk_1C & 0x2000)) {
        goto block_15;
    }
    enable_clear_mask = 0x300;
block_15:
    func_8009A3D0(tile_x, tile_y, enable_clear_mask);
    updated_flags = ((S_800A4B88_0 *)object)->unk_1C | 0x2000;
    ((S_800A4B88_0 *)object)->unk_1C = updated_flags;
    tile_x = ((S_800A4B88_1 *)position)->unk_24;
    tile_y = ((S_800A4B88_1 *)position)->unk_25;
    set_mask = 0x3000;
    if (!(updated_flags & 0x2000)) {
        goto block_20;
    }
    set_mask = 0x300;
    goto block_20;
jt_c11:
    position = ((S_800A4B88_0_pre *)object)[-1].unk_04;
    tile_x = ((S_800A4B88_1 *)position)->unk_24;
    tile_y = ((S_800A4B88_1 *)position)->unk_25;
    disable_clear_mask = 0x3000;
    if (!(((S_800A4B88_0 *)object)->unk_1C & 0x2000)) {
        goto block_19;
    }
    disable_clear_mask = 0x300;
block_19:
    func_8009A3D0(tile_x, tile_y, disable_clear_mask);
    ((S_800A4B88_0 *)object)->unk_1C = (s32) (((S_800A4B88_0 *)object)->unk_1C & ~0x2000);
    tile_x = ((S_800A4B88_1 *)position)->unk_24;
    tile_y = ((S_800A4B88_1 *)position)->unk_25;
    do {
        set_mask = 0x3000;
    } while (0);
block_20:
    func_8009A21C(tile_x, tile_y, set_mask);
    goto block_26;
jt_c9:
    func_8003E188(0x2E, 0);
    if (!(((S_800A4B88_0 *)object)->unk_14 & 0x20000000)) {
        goto block_23;
    }
    func_800ACB98(object, ((S_800A4B88_0_pre *)object)[-1].unk_00, ((S_800A4B88_0_pre *)object)[-1].unk_04, object);
    return;
block_23:
    func_800D8590(object);
    if (((S_800A4B88_0 *)object)->unk_13 != 0) {
        goto block_26;
    }
    func_80096088(object, object);
    update_state = &D_80082E80;
    (*(M2C_UNK **)((u8 *)update_state + 0x2C)) = D_800DD274;
    func_8003DB94(update_state, *(s32 *)(D_800DD274 + ((((s32) (D_80083228 + (*(s16 *)((u8 *)object + 0x2A)) + 0x100) >> 7) & 0x1C))), 0);
    reset_index = 3;
    reset_slot = D_80083110;
    reset_slot += 3;
loop_25:
    *reset_slot = 0;
    reset_index -= 1;
    reset_slot -= 1;
    if (reset_index >= 0) {
        goto loop_25;
    }
jt_c6:
jt_c12:
jt_c13:
jt_c14:
jt_c15:
jt_c16:
jt_c17:
jt_c18:
jt_c19:
jt_c20:
jt_c21:
jt_c22:
jt_c23:
jt_c24:
jt_c25:
block_26:
    func_80041E70(object);
    return;
}
