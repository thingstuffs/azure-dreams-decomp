/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_8002520C_22 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_8002520C_22;   /* ((side_index * 4) + arg0) in func_8002520C */

typedef struct S_8002520C_23 {
    u8 pad_00[0x2094];
    u16 unk_2094;
} S_8002520C_23;   /* ((temp_a0_8 * 2) + counter_page) in func_8002520C */

typedef struct S_8002520C_24 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_8002520C_24;   /* ((((S_8002520C_0 *)arg0)->unk_26 * 4) + arg0) in func_8002520C */

typedef struct S_8002520C_25 {
    u8 pad_00[0xB6];
    s16 unk_B6;
} S_8002520C_25;   /* ((S_8002520C_24 *)(((((S_8002520C_0 *)arg0)->unk_26 * 4) + arg0)))->unk_0C in func_8002520C */


typedef struct S_8002520C_0_pre {
    u16 unk_00;
} S_8002520C_0_pre;   /* the 0x2 bytes before arg0 in func_8002520C, addressed as arg0[-1] */

typedef struct S_8002520C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    void * unk_14;
    u8 pad_18[0x4];
    s16 unk_1C;
    s16 unk_1E;
    u16 unk_20;
    s16 unk_22;
    s16 unk_24;
    s16 unk_26;
} S_8002520C_0;   /* arg0 in func_8002520C */

typedef struct S_8002520C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0xA];
    u16 unk_16;
} S_8002520C_1;   /* temp_s1 in func_8002520C */

typedef struct S_8002520C_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x7];
    u16 unk_16;
    u8 pad_18[0x2];
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} S_8002520C_2;   /* arg2_local in func_8002520C */


typedef struct S_8002520C_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8002520C_4;   /* state_base in func_8002520C */

typedef struct S_8002520C_5_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8002520C_5_pre;   /* the 0x14 bytes before dest in func_8002520C, addressed as dest[-1] */

typedef struct S_8002520C_5 {
    u8 pad_00[0x96];
    s16 unk_96;
} S_8002520C_5;   /* dest in func_8002520C */

typedef struct S_8002520C_6 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8002520C_6;   /* cell in func_8002520C */

typedef struct S_8002520C_7 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_8002520C_7;   /* *var_v0_4 in func_8002520C */

typedef struct S_8002520C_8 {
    u8 pad_00[0x1E];
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
} S_8002520C_8;   /* (void *) slot_a0 in func_8002520C */

typedef struct S_8002520C_9 {
    u8 pad_00[0x3D7C];
    s32 unk_3D7C;
} S_8002520C_9;   /* world_page in func_8002520C */

typedef struct S_8002520C_10 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_8002520C_10;   /* world_node in func_8002520C */

typedef struct S_8002520C_11 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_8002520C_11;   /* (void *) world_off in func_8002520C */

typedef struct S_8002520C_12 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8002520C_12;   /* world_cell in func_8002520C */

typedef struct S_8002520C_13 {
    u8 pad_00[0x2094];
    u16 unk_2094;
} S_8002520C_13;   /* counter_ptr in func_8002520C */

typedef struct S_8002520C_14 {
    u8 pad_00[0x45];
    s8 unk_45;
} S_8002520C_14;   /* temp_s1_2 in func_8002520C */

typedef struct S_8002520C_15 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_8002520C_15;   /* var_v1_4 in func_8002520C */

typedef struct S_8002520C_16 {
    u8 pad_00[0xB6];
    s16 unk_B6;
} S_8002520C_16;   /* temp_v0_4 in func_8002520C */

typedef struct S_8002520C_17 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0x1490];
    s32 unk_14A0;
} S_8002520C_17;   /* slot_a2 in func_8002520C */

typedef struct S_8002520C_18 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_8002520C_18;   /* (void *) slot_v1 in func_8002520C */

typedef struct S_8002520C_19 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_8002520C_19;   /* slot_a3 in func_8002520C */

typedef struct S_8002520C_20 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_8002520C_20;   /* (void *) slot_a1 in func_8002520C */

typedef struct S_8002520C_21 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_8002520C_21;   /* (s32 *) slot_v0 in func_8002520C */


M2C_UNK func_8004491C();           /* extern */
s32 func_800644B8();                        /* extern */
s32 func_8009074C();               /* extern */
M2C_UNK func_8009F644();      /* extern */
u32 func_800A0818(); /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern void *D_80025000[];
__asm__(".set D_80025000, 0x80025000");
extern u16 D_80012094[5];
extern u16 D_80012096[5];
extern u8 D_80026864[16];
extern s16 D_80027156[5];
extern u16 D_80027158[5];
extern s16 D_8002715C[5];
extern u16 D_8006CCD8[8];
extern u16 D_8006CCE8[8];
extern u8 D_80080A87[16];
extern s32 D_800814A0;
extern u8 D_80083160[32];
extern u8 D_800E3D7C[16384];

void func_8002520C(void *arg0_in, void *arg1_in, void *arg2) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_default };
    u16 sp18;
    u16 entry_counter;
    s16 temp_a0;
    s16 temp_a0_10;
    s16 temp_a0_4;
    s16 temp_a0_8;
    s16 temp_a0_9;
    s16 temp_v0;
    s16 temp_v0_3;
    s16 temp_v0_6;
    s32 temp_v1;
    s16 temp_v1_8;
    s32 temp_a0_2;
    s32 temp_a0_6;
    s32 temp_flags_raw;
    s32 temp_flags;
    s32 temp_a3_2;
    s32 temp_t1;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s32 var_a1_2;
    s32 var_v0_5;
    u16 *temp_a0_3;
    u16 *temp_t3;
    u16 *var_a0;
    u16 *var_v0_6;
    u16 *var_v0_7;
    u16 *var_v1_2;
    u16 *var_v1_3;
    u16 temp_a0_11;
    u16 temp_a1;
    u16 temp_v0_5;
    u16 temp_v1_2;
    u16 temp_v1_9;
    u32 temp_v0_2;
    u32 temp_v1_5;
    u32 var_v0_3;
    u8 temp_t2;
    u8 temp_v1_10;
    u8 temp_v1_11;
    u8 temp_v1_3;
    u8 temp_v1_4;
    u8 var_a2;
    void **var_v0_2;
    void **var_v0_4;
    void **var_v1;
    void *temp_a0_12;
    void *temp_a0_5;
    void *temp_a0_7;
    void *temp_a1_2;
    void *temp_a3;
    S_8002520C_1 *temp_s1;
    S_8002520C_14 *temp_s1_2;
    void *temp_t0;
    void *temp_t0_2;
    void *temp_v0_4;
    void *temp_v1_12;
    register void *var_a1 ASM_REG("$5");   /* MATCH pin: retail delay-slot fill depends on it */
    s32 *var_a2_2;
    void *var_v1_4;
    u8 *state_base;
    S_8002520C_2 *arg2_local;
    u8 *counter_page;
    s32 *world_page;
    void *arg0 = arg0_in;
    void *arg1 = arg1_in;
    entry_counter = D_8002715C[0];
    D_8002715C[0] = entry_counter + 1;
    temp_s1 = arg1;
    arg2_local = arg2;
    state_base = D_80083160;
    temp_v1 = ((S_8002520C_0 *)arg0)->unk_1C;
    (void)jt_keep;
    if ((u32)temp_v1 >= 5U) {
        goto jt_default;
    }
    goto *D_80025000[(u32)temp_v1];
jt_c0:
        func_8004491C(arg0 - 0x20, &D_80026864);
        temp_s1->unk_02 = -0x180;
        temp_s1->unk_06 = -0x20;
        arg2_local->unk_16 = 0x1000U;
        arg2_local->unk_1E = 0x1000U;
        arg2_local->unk_1C = 0x1000U;
        ((S_8002520C_0 *)arg0)->unk_22 = 8;
        ((S_8002520C_0 *)arg0)->unk_1C = (s16) ((u16) ((S_8002520C_0 *)arg0)->unk_1C + 1);
        /* fallthrough */
jt_c1:
        temp_a0 = ((S_8002520C_0 *)arg0)->unk_22;
        if (temp_a0 != 0) {
            temp_s1->unk_02 = (s16) ((u16) temp_s1->unk_02 + ((s32) (-0x80 - temp_s1->unk_02) / temp_a0));
            temp_s1->unk_0A.s = (s16) (func_800644B8(((S_8002520C_0 *)arg0)->unk_22 << 5) + 0x400);
            temp_v1_2 = arg2_local->unk_16;
            arg2_local->unk_16 = (u16) (temp_v1_2 + ((s32) (0xD00 - temp_v1_2) / (s16) ((S_8002520C_0 *)arg0)->unk_22));
            temp_v1_3 = arg2_local->unk_0E;
            temp_v1_4 = temp_v1_3 + ((s32) (0x80 - temp_v1_3) / (s16) ((S_8002520C_0 *)arg0)->unk_22);
            arg2_local->unk_0E = temp_v1_4;
            arg2_local->unk_0D = temp_v1_4;
            arg2_local->unk_0C = temp_v1_4;
        }
        temp_v0 = (u16) ((S_8002520C_0 *)arg0)->unk_22 - 1;
        ((S_8002520C_0 *)arg0)->unk_22 = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            temp_s1->unk_02 = -0x80;
            temp_s1->unk_06 = -0x20;
            temp_s1->unk_0A.s = 0x400;
            arg2_local->unk_16 = 0xD00U;
            arg2_local->unk_0E = 0x80U;
            arg2_local->unk_0D = 0x80U;
            arg2_local->unk_0C = 0x80U;
            ((S_8002520C_0 *)arg0)->unk_22 = 0;
            ((S_8002520C_0 *)arg0)->unk_1C = (s16) ((u16) ((S_8002520C_0 *)arg0)->unk_1C + 1);
        jt_c2:
        }
        if (D_80027156[0] == 0) {
            temp_v1_5 = func_8009074C(((u16) arg2_local->unk_1A >> 9) & 7, ((Rec_D_800E3D7C *)(&D_800E3D7C))->unk_00.at00_s32.v + 0xA2, 0) & 0xFFFF;
            if ((temp_v1_5 != 0xFFF) && (((S_8002520C_4 *)state_base)->unk_10 & 0xF000)) {
                s32 table_idx;
                s32 slot_a0;
                s32 side_index;
                void *dest;
                u16 *x_table;
                register S_8002520C_6 *cell ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
                register u32 base_x ASM_REG("$10");   /* MATCH pin: retail delay-slot fill depends on it */
                u32 x_value;
                u32 y_value;
                s32 compare_x;   /* MATCH pin: load-bearing for the whole function shape */

                {
                    u32 shifted;

                    shifted = temp_v1_5 >> 9;
                    side_index = ((S_8002520C_0 *)arg0)->unk_26;
                    ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                    table_idx = shifted & 7;
                }
                slot_a0 = table_idx * 2;
                temp_v0_4 = ((S_8002520C_22 *)(((side_index * 4) + arg0)))->unk_0C;
                dest = temp_v0_4 + 0x20;
                ASM_KEEP(dest);   /* MATCH pin: load-bearing for the whole function shape */
                cell = ((S_8002520C_5_pre *)dest)[-1].unk_00;
                {
                    s32 load_v0;
                    s32 load_v1;   /* MATCH pin: load-bearing for the whole function shape */

                    load_v0 = (s32) D_8006CCD8;
                    x_table = (u16 *) (slot_a0 + load_v0);
                    load_v0 = *x_table;
                    load_v1 = cell->unk_24;
                    base_x = load_v1 + load_v0;
                    load_v0 = (s32) D_8006CCE8;
                    slot_a0 += load_v0;
                    load_v1 = cell->unk_25;
                    ASM_KEEP(load_v1);   /* MATCH pin: retail basic-block layout depends on it */
                    load_v0 = *(u16 *) slot_a0;
                    ASM_KEEP_DEP_NV(base_x, load_v0);   /* MATCH pin: retail basic-block layout depends on it */
                    x_value = base_x;
                    y_value = load_v1 + load_v0;
                }
                sp18 = (u16) y_value;
                ASM_USE2_NV(table_idx, dest);   /* MATCH pin: retail register colouring depends on it */
                   /* MATCH pin: retail register colouring depends on it */
                compare_x = x_value & 0xFFFF;
                if (compare_x == 1) {
                    if ((y_value & 0xFFFF) == compare_x) {
                        register s32 add_v0 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
                        s32 add_v1;   /* MATCH pin: load-bearing for the whole function shape */

                        add_v1 = *x_table;
                        add_v0 = *(u16 *) slot_a0;
                        x_value = add_v1 + base_x;
                        add_v0 = y_value + add_v0;
                        sp18 = (u16) add_v0;
                        goto block_14;
                    }
                    var_v1 = arg0 + 0xC;
                } else {
block_14:
                    var_v1 = arg0 + 0xC;
                }
                slot_a0 = ((S_8002520C_0 *)arg0)->unk_26;
                var_v0_2 = var_v1;
                if (slot_a0 == 0) {
                    var_v0_2 = arg0 + 0x10;
                }
                if (*var_v0_2 != NULL) {
                    var_v0_4 = var_v1;
                    if (slot_a0 == 0) {
                        var_v0_4 = arg0 + 0x10;
                    }
                    slot_a0 = (s32) ((S_8002520C_7 *)(*var_v0_4))->unk_0C;
                    temp_v1_6 = ((S_8002520C_8 *)((void *) slot_a0))->unk_24;
                    ASM_CLOBBER("$2");   /* MATCH pin: load-bearing for the whole function shape */
                    temp_v0_2 = x_value & 0xFFFF;
                    if (temp_v0_2 != temp_v1_6) {
                        var_v0_5 = temp_v0_2 < 3U;
                    } else {
                        y_value = sp18;
                        if (y_value == ((S_8002520C_8 *)((void *) slot_a0))->unk_25) {
                            register s32 repeat_v0 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
                            s32 repeat_v1;

                            slot_a0 = table_idx & 0xFFFF;
                            ASM_KEEP_NV(slot_a0);   /* MATCH pin: retail delay-slot fill depends on it */
                            repeat_v1 = (s32) D_8006CCD8;
                            slot_a0 *= 2;
                            repeat_v1 = slot_a0 + repeat_v1;
                            repeat_v0 = (s32) D_8006CCE8;
                            slot_a0 += repeat_v0;
                            repeat_v1 = *(u16 *) repeat_v1;
                            repeat_v0 = *(u16 *) slot_a0;
                            x_value += repeat_v1;
                            repeat_v0 = y_value + repeat_v0;
                            sp18 = (u16) repeat_v0;
                        }
                        var_v0_5 = (x_value & 0xFFFF) < 3U;
                    }
                } else {
                    var_v0_5 = (x_value & 0xFFFF) < 3U;
                }
                if ((var_v0_5 != 0) && (sp18 < 3U)) {
                    ((S_8002520C_5 *)dest)->unk_96 = 8;
                    cell->unk_24 = (u8) x_value;
                    cell->unk_25 = (u8) sp18;
                }
            }
            if (((S_8002520C_4 *)state_base)->unk_10 & 0x40) {
                register s32 direction ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */

                func_800A56E0(0x503);
                {
                    s32 call_a0;
                    s32 call_a1;
                    s32 world_off;
                    register s32 world_base ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
                    S_8002520C_10 *world_node;
                    register S_8002520C_12 *world_cell ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */

                    call_a0 = 1;
                    call_a1 = call_a0;
                    ASM_KEEP_NV(call_a0);   /* MATCH pin: keeps a constant in a register as retail does */
                    ASM_KEEP_NV(call_a1);   /* MATCH pin: keeps a statement from moving across a call/branch */
                    world_page = (s32 *)0x800E0000;
                    ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                    world_off = ((S_8002520C_0 *)arg0)->unk_26;
                    ASM_KEEP_NV(world_off);   /* MATCH pin: retail basic-block layout depends on it */
                    world_base = ((S_8002520C_9 *)world_page)->unk_3D7C;
                    ASM_KEEP_NV(world_base);   /* MATCH pin: retail delay-slot fill depends on it */
                    world_off *= 4;
                    world_node = (void *) (world_off + (s32) arg0);
                    world_node = world_node->unk_0C;
                    world_off += world_base;
                    world_cell = world_node->unk_0C;
                    temp_s1_2 = ((S_8002520C_11 *)((void *) world_off))->unk_AC;
                    direction = (func_800A0818(call_a0, call_a1, world_cell->unk_24, world_cell->unk_25, &sp18) >> 9) & 7;
                }
                {
                    s32 compare_dir;
                    s32 side_v0;
                    u8 *counter_ptr;

                    compare_dir = direction - 2;
                    ASM_KEEP_NV(direction);   /* MATCH pin: retail delay-slot fill depends on it */
                    side_v0 = ((S_8002520C_0 *)arg0)->unk_26;
                    counter_page = (u8 *)0x80010000;
                    counter_ptr = (side_v0 * 2) + counter_page;
                    if ((compare_dir & 7) != ((S_8002520C_13 *)counter_ptr)->unk_2094) {
                        direction = (direction - 2) & 7;
                        ((S_8002520C_13 *)counter_ptr)->unk_2094 = direction;
                        temp_s1_2->unk_45 = (s8) direction;
                        func_8009F644(((S_8002520C_9 *)world_page)->unk_3D7C, 0x90, ((S_8002520C_0 *)arg0)->unk_26, direction);
                    temp_a0_8 = ((S_8002520C_0 *)arg0)->unk_26;
                    var_v1_2 = (u16 *)0x80012094;
                    if (temp_a0_8 == 0) {
                        var_v1_2 = (u16 *)0x80012096;
                    }
                    if (*var_v1_2 == ((S_8002520C_23 *)(((temp_a0_8 * 2) + counter_page)))->unk_2094) {
                        var_v1_3 = (u16 *)0x80012094;
                        if (temp_a0_8 == 0) {
                            var_v1_3 = (u16 *)0x80012096;
                        }
                        var_v0_6 = (u16 *)0x80012094;
                        if (temp_a0_8 == 0) {
                            var_v0_6 = (u16 *)0x80012096;
                        }
                        *var_v1_3 = *var_v0_6 + 1;
                        temp_v1_8 = ((S_8002520C_0 *)arg0)->unk_26;
                        var_a0 = (u16 *)0x80012094;
                        if (temp_v1_8 == 0) {
                            var_a0 = (u16 *)0x80012096;
                        }
                        var_v0_7 = (u16 *)0x80012094;
                        if (temp_v1_8 == 0) {
                            var_v0_7 = (u16 *)0x80012096;
                        }
                        *var_a0 = *var_v0_7 & 7;
                    }
                }
                }
                if (D_80080A87[0] != 0) {
                    D_80027158[0] = (u16) ((S_8002520C_0 *)arg0)->unk_26;
                    D_80027156[0] = (s16) (0x20 / (s32) D_80080A87[0]);
                }
                ((S_8002520C_25 *)(((S_8002520C_24 *)(((((S_8002520C_0 *)arg0)->unk_26 * 4) + arg0)))->unk_0C))->unk_B6 = 1;
            }
            if (((S_8002520C_4 *)state_base)->unk_10 & 8) {
                ((S_8002520C_0 *)arg0)->unk_20 = (u16) (((S_8002520C_0 *)arg0)->unk_20 - 0x200);
            }
            if (((S_8002520C_4 *)state_base)->unk_10 & 4) {
                ((S_8002520C_0 *)arg0)->unk_20 = (u16) (((S_8002520C_0 *)arg0)->unk_20 + 0x200);
            }
        }
        if (((S_8002520C_0 *)arg0)->unk_1E != (s16) ((S_8002520C_0 *)arg0)->unk_20) {
            ((S_8002520C_0 *)arg0)->unk_1E = (s16) ((S_8002520C_0 *)arg0)->unk_20;
            ((S_8002520C_0 *)arg0)->unk_24 = 8;
        }
        temp_a0_9 = ((S_8002520C_0 *)arg0)->unk_24;
        if (temp_a0_9 != 0) {
            arg2_local->unk_1A = (u16) (arg2_local->unk_1A + ((s32) (((S_8002520C_0 *)arg0)->unk_1E - (s16) arg2_local->unk_1A) / temp_a0_9));
            temp_v0_3 = (u16) ((S_8002520C_0 *)arg0)->unk_24 - 1;
            ((S_8002520C_0 *)arg0)->unk_24 = temp_v0_3;
            if ((temp_v0_3 << 0x10) <= 0) {
                arg2_local->unk_1A = (u16) ((S_8002520C_0 *)arg0)->unk_1E;
                ((S_8002520C_0 *)arg0)->unk_24 = 0;
                arg2_local->unk_1A = (u16) (arg2_local->unk_1A & 0xFFF);
                ((S_8002520C_0 *)arg0)->unk_1E = (s16) ((u16) ((S_8002520C_0 *)arg0)->unk_1E & 0xFFF);
                ((S_8002520C_0 *)arg0)->unk_20 = (u16) (((S_8002520C_0 *)arg0)->unk_20 & 0xFFF);
                return;
            }
        }
    goto jt_default;
jt_c3:
        var_a1 = NULL;
        var_v1_4 = arg0;
loop_55:
        temp_v0_4 = ((S_8002520C_15 *)var_v1_4)->unk_0C;
        if ((temp_v0_4 == NULL) || (((S_8002520C_16 *)temp_v0_4)->unk_B6 == 0)) {
            var_a1 += 1;
            var_v1_4 += 4;
            if ((s32) var_a1 >= 2) {
                ((S_8002520C_0 *)arg0)->unk_22 = 8;
                temp_s1->unk_16 = 8U;
                ((S_8002520C_0 *)arg0)->unk_1C = (s16) ((u16) ((S_8002520C_0 *)arg0)->unk_1C + 1);
            jt_c4:
                temp_a0_10 = ((S_8002520C_0 *)arg0)->unk_22;
                if (temp_a0_10 != 0) {
                    temp_s1->unk_02 = (s16) ((u16) temp_s1->unk_02 + ((s32) (-0x480 - temp_s1->unk_02) / temp_a0_10));
                    temp_s1->unk_0A.u = (u16) (temp_s1->unk_0A.u + func_800644B8(((S_8002520C_0 *)arg0)->unk_22 << 5, (s32) var_a1));
                    temp_v1_9 = arg2_local->unk_16;
                    arg2_local->unk_16 = (u16) (temp_v1_9 + ((s32) (0x1000 - temp_v1_9) / (s16) ((S_8002520C_0 *)arg0)->unk_22));
                    temp_v1_10 = arg2_local->unk_0E;
                    temp_a0_11 = arg2_local->unk_1C;
                    temp_v1_11 = temp_v1_10 + ((s32) (0 - temp_v1_10) / (s16) ((S_8002520C_0 *)arg0)->unk_22);
                    arg2_local->unk_0E = temp_v1_11;
                    arg2_local->unk_0D = temp_v1_11;
                    arg2_local->unk_0C = temp_v1_11;
                    temp_v0_5 = arg2_local->unk_1E;
                    arg2_local->unk_1C = (u16) (temp_a0_11 + ((s32) (0x200 - temp_a0_11) / (s16) ((S_8002520C_0 *)arg0)->unk_22));
                    arg2_local->unk_1E = (u16) (temp_v0_5 + ((s32) (0x200 - temp_v0_5) / (s16) ((S_8002520C_0 *)arg0)->unk_22));
                    temp_s1->unk_16 = (u16) (temp_s1->unk_16 * 2);
                }
                temp_v0_6 = (u16) ((S_8002520C_0 *)arg0)->unk_22 - 1;
                ((S_8002520C_0 *)arg0)->unk_22 = temp_v0_6;
                if ((temp_v0_6 << 0x10) <= 0) {
                    s32 slot_a0;
                    s32 slot_a1;
                    register s32 slot_v0 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
                    s32 slot_v1;
                    register s32 *slot_a2 ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
                    s32 *slot_a3;

                    slot_a2 = (s32 *) 0x80080000;
                    ((S_8002520C_0_pre *)arg0)[-1].unk_00 = (u16) (((S_8002520C_0_pre *)arg0)[-1].unk_00 | 0x8000);
                    slot_v0 = ((S_8002520C_17 *)slot_a2)->unk_14A0;
                    slot_v1 = (s32) ((S_8002520C_0 *)arg0)->unk_08;
                    slot_a0 = slot_v0 | 0x8000;
                    ((S_8002520C_17 *)slot_a2)->unk_14A0 = slot_a0;
                    if (slot_v1 != 0) {
                        ((S_8002520C_18 *)((void *) slot_v1))->unk_1E = (u16) (((S_8002520C_18 *)((void *) slot_v1))->unk_1E | 0x8000);
                    }
                    slot_a1 = 0;
                    ASM_KEEP_NV(slot_a2);   /* MATCH pin: load-bearing for the whole function shape */
                    slot_a3 = slot_a2;
                    slot_a2 = (s32 *) arg0;
                    do {
                        slot_a0 = (s32) ((S_8002520C_17 *)slot_a2)->unk_0C;
                        if (slot_a0 != 0) {
                            slot_v0 = ((S_8002520C_8 *)((void *) slot_a0))->unk_1E;
                            slot_v1 = ((S_8002520C_19 *)slot_a3)->unk_14A0;
                            slot_v0 |= 0x8000;
                            slot_v1 |= 0x8000;
                            ((S_8002520C_8 *)((void *) slot_a0))->unk_1E = (u16) slot_v0;
                            ((S_8002520C_19 *)slot_a3)->unk_14A0 = slot_v1;
                        }
                        slot_a1 += 1;
                        slot_a2 += 1;
                    } while (slot_a1 < 2);
                    slot_a1 = (s32) ((S_8002520C_0 *)arg0)->unk_14;
                    if (slot_a1 != 0) {
                        slot_v0 = (s32) 0x80080000;
                        slot_v1 = ((S_8002520C_20 *)((void *) slot_a1))->unk_1E;
                        slot_a0 = ((S_8002520C_21 *)((s32 *) slot_v0))->unk_14A0;
                        slot_v1 |= 0x8000;
                        slot_a0 |= 0x8000;
                        ((S_8002520C_20 *)((void *) slot_a1))->unk_1E = (u16) slot_v1;
                        ((S_8002520C_21 *)((s32 *) slot_v0))->unk_14A0 = slot_a0;
                    }
                }
            } else {
                goto loop_55;
            }
        }
    jt_default:
        return;
}
