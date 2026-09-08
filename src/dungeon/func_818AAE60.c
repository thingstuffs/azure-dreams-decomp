#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800243B8_arg0.h"


typedef struct S_80024660_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0x24];
    s16 unk_88;
} S_80024660_1;   /* temp_s7 in func_80024660 */

typedef struct S_80024660_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_80024660_2;   /* arg2 in func_80024660 */

typedef struct S_80024660_3 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80024660_3;   /* temp_s0 in func_80024660 */

typedef struct S_80024660_4 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80024660_4;   /* temp_a1 in func_80024660 */

typedef struct S_80024660_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80024660_5;   /* arg1 in func_80024660 */

typedef struct S_80024660_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024660_6;   /* temp_v1_2 in func_80024660 */

typedef struct S_80024660_7_pre {
    M2C_UNK * unk_00;
    u8 pad_04[0x14];
} S_80024660_7_pre;   /* the 0x18 bytes before temp_v0 in func_80024660, addressed as temp_v0[-1] */

typedef struct S_80024660_8 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} S_80024660_8;   /* var_s3 in func_80024660 */

typedef struct S_80024660_9 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80024660_9;   /* temp_v1_5 in func_80024660 */

typedef struct S_80024660_10 {
    u8 pad_00[0x18];
    s32 unk_18;
} S_80024660_10;   /* var_s0 in func_80024660 */

typedef struct S_80024660_11 {
    s32 unk_00;
} S_80024660_11;   /* &D_800814A0 in func_80024660 */

typedef struct S_80024660_12 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80024660_12;   /* ((S_80024660_3 *)temp_s0)->unk_0C in func_80024660 */


extern void *D_80024020[];
M2C_UNK func_8002403C();
s32 func_800243B8();
s32 func_8003DE58();
s32 func_800A44E0();
M2C_UNK func_800A56E0();
s16 func_800BCB04();
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern u16 D_8006CCD8_2[] __asm__("D_8006CCD8");
extern u16 D_8006CCE8_2[] __asm__("D_8006CCE8");
extern s16 D_8006CCD8_3[] __asm__("D_8006CCD8");
extern s16 D_8006CCE8_3[] __asm__("D_8006CCE8");
extern M2C_UNK D_800814A0;
extern s32 D_8008346C;

typedef struct {
    s32 pos[3];
    u8 pad18[0xC];
    u16 dist[3];
    u8 pad2E[2];
    u16 saved_y;
} Func818AAE60Scratch;

void func_80024660(void *arg0, void *arg1, void *arg2) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6 };
    Func818AAE60Scratch scratch;
    s16 *var_a1;
    s16 *var_a2;
    M2C_UNK *var_s3;
    s16 temp_v0_4;
    s32 temp_v1;
    s16 temp_v1_4;
    s16 temp_v1_7;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a1_2;
    register s32 var_v0_5 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_7;
    s32 temp_v1_6;
    s32 var_s1;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 signed_x;
    s32 signed_y;
    u16 temp_v1_3;
    u16 var_v0;
    void *temp_a1;
    void *temp_s0;
    void *temp_s7;
    void *temp_v0;
    void *temp_v1_2;
    void *temp_v1_5;
    register void *var_s0 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u16 cnt;

    cnt = ((Rec_func_800243B8_arg0 *)arg0)->unk_10;
    temp_v1 = ((Rec_func_800243B8_arg0 *)arg0)->unk_0A;
    temp_s7 = ((Rec_func_800243B8_arg0 *)arg0)->unk_00;
    ((Rec_func_800243B8_arg0 *)arg0)->unk_10 = cnt + 1;
    if ((u32) temp_v1 >= 7U) {
        goto block_52;
    }
    (void)jt_keep; goto *D_80024020[(u32)(temp_v1)];
jt_c0:
    ((Rec_func_800243B8_arg0 *)arg0)->unk_10 = 0U;
    ((Rec_func_800243B8_arg0 *)arg0)->unk_0A = (s16) ((u16) ((Rec_func_800243B8_arg0 *)arg0)->unk_0A + 1);
    ((Rec_func_800243B8_arg0 *)arg0)->unk_0E = (u16) (((u16) ((S_80024660_1 *)temp_s7)->unk_2A >> 9) & 7);
    ((S_80024660_2 *)arg2)->unk_0C = 0x808080;
jt_c1:
    temp_s0 = temp_s7 - 0x20;
    temp_a1 = ((S_80024660_3 *)temp_s0)->unk_0C;
    if (func_8003DE58(((S_80024660_4 *)temp_a1)->unk_08, temp_a1, &scratch.dist[0], 0) != 0) {
        goto block_5;
    }
    if (!(((S_80024660_12 *)(((S_80024660_3 *)temp_s0)->unk_0C))->unk_14 & 0x8000)) {
        goto block_52;
    }
block_5:
    temp_v1_2 = ((S_80024660_3 *)temp_s0)->unk_08;
    ((S_80024660_5 *)arg1)->unk_00.at02.v = (u16) ((S_80024660_6 *)temp_v1_2)->unk_02;
    ((S_80024660_5 *)arg1)->unk_04.at02.v = (u16) ((S_80024660_6 *)temp_v1_2)->unk_06;
    temp_v1_3 = ((S_80024660_6 *)temp_v1_2)->unk_0A;
    ((S_80024660_5 *)arg1)->unk_08.at02.v = temp_v1_3;
    if (((S_80024660_12 *)(((S_80024660_3 *)temp_s0)->unk_0C))->unk_14 & 0x8000) {
        goto block_7;
    }
    ((S_80024660_5 *)arg1)->unk_00.at02.v = (u16) (((S_80024660_5 *)arg1)->unk_00.at02.v + scratch.dist[0]);
    ((S_80024660_5 *)arg1)->unk_04.at02.v = (u16) (((S_80024660_5 *)arg1)->unk_04.at02.v + scratch.dist[1]);
    var_v0 = ((S_80024660_5 *)arg1)->unk_08.at02.v;
    ASM_KEEP(var_v0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    {
        register u16 temp_d2 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        temp_d2 = scratch.dist[2];
        var_v0 = var_v0 + temp_d2;
    }
    goto block_8;
block_7:
    var_v0 = temp_v1_3 - 0x40;
block_8:
    ((S_80024660_5 *)arg1)->unk_08.at02.v = var_v0;
    if (!(*((Rec_func_800243B8_arg0 *)arg0)->unk_04 & 0x80)) {
        goto block_52;
    }
    temp_v0 = ((S_80024660_1 *)temp_s7)->unk_60;
    var_s1 = 1;
    if (temp_v0 != NULL) {
    var_s3 = ((S_80024660_7_pre *)temp_v0)[-1].unk_00;
    var_a0 = ((S_80024660_8 *)var_s3)->unk_00.at02.v;
    var_a0 -= ((S_80024660_5 *)arg1)->unk_00.at02u.v;
    if (var_a0 >= 0) {
        goto block_12;
    }
    var_a0 = 0 - var_a0;
block_12:
    scratch.dist[0] = (u16) var_a0;
    var_v0_2 = ((S_80024660_8 *)var_s3)->unk_04.at02.v;
    var_v0_3 = ((S_80024660_5 *)arg1)->unk_04.at02u.v;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    var_a1 = (s16 *)((u8 *)&scratch + 2);
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    var_v0_2 -= var_v0_3;
    if (var_v0_2 >= 0) {
        goto block_14;
    }
    var_v0_2 = 0 - var_v0_2;
block_14:
    scratch.dist[1] = (u16) var_v0_2;
    var_v0_3 = ((S_80024660_5 *)arg1)->unk_08.at02u.v;
    var_v0_3 += 0x20;
    var_v0_2 = ((S_80024660_8 *)var_s3)->unk_08.at02.v - var_v0_3;
    if (var_v0_2 >= 0) {
        goto block_16;
    }
    var_v0_2 = 0 - var_v0_2;
block_16:
    scratch.dist[2] = (u16) var_v0_2;
    ((Rec_func_800243B8_arg0 *)arg0)->unk_12.as_s16 = var_a0;
loop_17:
    if (var_a1[12] <= ((Rec_func_800243B8_arg0 *)arg0)->unk_12.as_s16) {
        goto block_19;
    }
    ((Rec_func_800243B8_arg0 *)arg0)->unk_12.as_s16 = (s16) (u16) var_a1[12];
block_19:
    var_s1 += 1;
    var_a1 += 1;
    if (var_s1 < 3) {
        goto loop_17;
    }
    temp_v0_2 = (u16) ((Rec_func_800243B8_arg0 *)arg0)->unk_12.as_s16 << 0x10;
    temp_v1_4 = (temp_v0_2 >> 0x14) + (temp_v0_2 >> 0x15);
    ((Rec_func_800243B8_arg0 *)arg0)->unk_12.as_s16 = temp_v1_4;
    if (temp_v1_4 != 0) {
        goto block_22;
    }
    ((Rec_func_800243B8_arg0 *)arg0)->unk_12.as_s16 = 1;
block_22:
    ((S_80024660_5 *)arg1)->unk_0C = (s32) ((s32) (((S_80024660_8 *)var_s3)->unk_00.at00.v - ((S_80024660_5 *)arg1)->unk_00.at00.v) / (s16) ((Rec_func_800243B8_arg0 *)arg0)->unk_12.as_s16);
    ((S_80024660_5 *)arg1)->unk_10 = (s32) ((s32) (((S_80024660_8 *)var_s3)->unk_04.at00.v - ((S_80024660_5 *)arg1)->unk_04.at00.v) / (s16) ((Rec_func_800243B8_arg0 *)arg0)->unk_12.as_s16);
    ((S_80024660_5 *)arg1)->unk_14 = (s32) ((s32) (((S_80024660_8 *)var_s3)->unk_08.at00.v - ((S_80024660_5 *)arg1)->unk_08.at00.v) / (s16) ((Rec_func_800243B8_arg0 *)arg0)->unk_12.as_s16);
    func_800A56E0(0x300, var_a1);
    var_v0 = (u16) ((Rec_func_800243B8_arg0 *)arg0)->unk_0A + 1;
    goto block_41;
    } else {
    register s32 temp_a1_3 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 temp_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u16 saved_y_t0 ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u16 *tptr ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 *first_ptr;
    register s32 search_z ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u32 dead_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 var_fp;
    register s32 var_s4 ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 var_s6 ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    var_s1 = 0;
    temp_v1_5 = ((S_80024660_3 *)temp_s0)->unk_0C;
    ASM_KEEP(temp_v1_5);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    dead_page = 0x80070000;
    ASM_USE(dead_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    var_s4 = ((S_80024660_9 *)temp_v1_5)->unk_24;
    var_s6 = ((S_80024660_9 *)temp_v1_5)->unk_25;
    var_fp = var_s4;
    scratch.saved_y = (u16) var_s6;
    do {
    signed_x = (s16)var_s4;
    signed_y = (s16)var_s6;
    if ((func_800A44E0((signed_x << 6) & 0xFFC0, (signed_y << 6) & 0xFFC0, ((S_80024660_1 *)temp_s7)->unk_88, (s16) (((Rec_func_800243B8_arg0 *)arg0)->unk_0E << 9)) << 0x10) != 0) {
        break;
    }
    temp_v0_3 = (s16) ((Rec_func_800243B8_arg0 *)arg0)->unk_0E;
    tptr = D_8006CCD8;
    first_ptr = &tptr[temp_v0_3];
    search_z = (u16) ((S_80024660_1 *)temp_s7)->unk_88;
    ASM_KEEP_DEP_NV(search_z, first_ptr);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    search_z = (s16) (search_z - 32);
    ASM_KEEP(search_z);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    tptr = D_8006CCE8;
    temp_a0 = *first_ptr;
    temp_a1_3 = tptr[temp_v0_3];
    temp_a0 = (((signed_x + (s16)temp_a0) << 6) + 32) & 0xFFE0;
    temp_a1_3 = (((signed_y + (s16)temp_a1_3) << 6) + 32) & 0xFFE0;
    temp_v0_4 = func_800BCB04(temp_a0, temp_a1_3, search_z);
    if (temp_v0_4 >= 513) {
        break;
    }
    if ((s16) (temp_v0_4 - (u16) ((S_80024660_1 *)temp_s7)->unk_88) < -63) {
        break;
    }
    {
        register s32 next_x ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 next_y ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 update_idx ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        u16 *update_xp;
        u16 *update_yp;
        tptr = D_8006CCD8_2;
        update_idx = (s16) ((Rec_func_800243B8_arg0 *)arg0)->unk_0E;
        var_s1 += 1;
        update_xp = (u16 *) (((unsigned long) update_idx << 1) + (unsigned long) tptr);
        tptr = D_8006CCE8_2;
        update_yp = update_idx + tptr;
        next_x = *update_xp;
        next_y = *update_yp;
        next_x = var_s4 + next_x;
        var_s4 = next_x;
        ASM_KEEP(var_s4);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        next_y = var_s6 + next_y;
        var_s6 = next_y;
        scratch.saved_y = (u16) next_y;
        var_fp = next_x;
    }
    } while (var_s1 < 8);
block_28:
    var_s3 = (M2C_UNK *)&scratch;
    var_s1 = 1;
    ASM_KEEP(var_s1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    {
        s16 *tptr3;
        temp_a1_3 = var_fp << 16;
        tptr3 = D_8006CCD8_3;
        ASM_KEEP(tptr3);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        temp_a1_3 >>= 10;
        var_a2 = (s16 *)((u8 *)&scratch + 2);
        temp_a1_3 += ((tptr3[(s16) ((Rec_func_800243B8_arg0 *)arg0)->unk_0E] + 1) << 5);
        tptr3 = D_8006CCE8_3;
        ((S_80024660_8 *)var_s3)->unk_00.at02.v = temp_a1_3;
        temp_a1_3 = (s16) temp_a1_3;
        saved_y_t0 = scratch.saved_y;
        ASM_KEEP(saved_y_t0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        temp_a0 = ((s32) (saved_y_t0 << 0x10));
        temp_a0 = (temp_a0 >> 0xA) + ((tptr3[(s16) ((Rec_func_800243B8_arg0 *)arg0)->unk_0E] + 1) << 5);
        ((S_80024660_8 *)var_s3)->unk_04.at02.v = temp_a0;
        var_v0 = ((S_80024660_5 *)arg1)->unk_08.at02.v + 32;
        temp_a0 <<= 16;
        ((S_80024660_8 *)var_s3)->unk_08.at02.v = var_v0;
        temp_v1_6 = ((S_80024660_5 *)arg1)->unk_00.at02u.v;
        temp_a0 >>= 16;
        var_a1_2 = temp_a1_3 - temp_v1_6;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        if (var_a1_2 >= 0) {
            goto block_30;
        }
        var_a1_2 = 0 - var_a1_2;
    block_30:
        scratch.dist[0] = var_a1_2;
        var_v0_5 = var_v0 << 16;
        var_a0_2 = temp_a0 - ((S_80024660_5 *)arg1)->unk_04.at02u.v;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        if (var_a0_2 >= 0) {
            goto block_32;
        }
        var_a0_2 = 0 - var_a0_2;
    block_32:
        scratch.dist[1] = var_a0_2;
        var_v0_5 >>= 16;
        var_v0_5 -= ((S_80024660_5 *)arg1)->unk_08.at02u.v;
        if (var_v0_5 >= 0) {
            goto block_34;
        }
        var_v0_5 = 0 - var_v0_5;
    block_34:
        scratch.dist[2] = var_v0_5;
        ((Rec_func_800243B8_arg0 *)arg0)->unk_12.as_s16 = var_a1_2;
    }
loop_35:
    if (var_a2[12] <= ((Rec_func_800243B8_arg0 *)arg0)->unk_12.as_s16) {
        goto block_37;
    }
    ((Rec_func_800243B8_arg0 *)arg0)->unk_12.as_s16 = (s16) (u16) var_a2[12];
block_37:
    var_s1 += 1;
    var_a2 += 1;
    if (var_s1 < 3) {
        goto loop_35;
    }
    temp_v0_7 = (u16) ((Rec_func_800243B8_arg0 *)arg0)->unk_12.as_s16 << 0x10;
    temp_v1_7 = (temp_v0_7 >> 0x14) + (temp_v0_7 >> 0x15);
    ((Rec_func_800243B8_arg0 *)arg0)->unk_12.as_s16 = temp_v1_7;
    if (temp_v1_7 != 0) {
        goto block_40;
    }
    ((Rec_func_800243B8_arg0 *)arg0)->unk_12.as_s16 = 1;
block_40:
    ((S_80024660_5 *)arg1)->unk_0C = (s32) ((s32) (((S_80024660_8 *)var_s3)->unk_00.at00.v - ((S_80024660_5 *)arg1)->unk_00.at00.v) / (s16) ((Rec_func_800243B8_arg0 *)arg0)->unk_12.as_s16);
    ((S_80024660_5 *)arg1)->unk_10 = (s32) ((s32) (((S_80024660_8 *)var_s3)->unk_04.at00.v - ((S_80024660_5 *)arg1)->unk_04.at00.v) / (s16) ((Rec_func_800243B8_arg0 *)arg0)->unk_12.as_s16);
    ((S_80024660_5 *)arg1)->unk_14 = (s32) ((s32) (((S_80024660_8 *)var_s3)->unk_08.at00.v - ((S_80024660_5 *)arg1)->unk_08.at00.v) / (s16) ((Rec_func_800243B8_arg0 *)arg0)->unk_12.as_s16);
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    var_v0 = 5;
    }
block_41:
    ((Rec_func_800243B8_arg0 *)arg0)->unk_0A = var_v0;
    var_s1 = 0x1F;
    var_s0 = arg0 + 0x7C;
loop_42:
    ((S_80024660_10 *)var_s0)->unk_18 = func_800243B8(arg0, arg1, var_s3, (s16)var_s1);
    var_s1 -= 1;
    var_s0 -= 4;
    if (var_s1 >= 0) {
        goto loop_42;
    }
    ((Rec_func_800243B8_arg0 *)arg0)->unk_10 = 0U;
    goto block_52;
jt_c3:
    if ((s16) ((Rec_func_800243B8_arg0 *)arg0)->unk_10 < 0x28) {
        goto block_52;
    }
    func_8002403C(((S_80024660_1 *)temp_s7)->unk_60, ((Rec_func_800243B8_arg0 *)arg0)->unk_09, temp_s7);
    goto block_49;
jt_c4:
    if (((Rec_func_800243B8_arg0 *)arg0)->unk_14 != 0) {
        goto block_52;
    }
    D_8008346C = 0;
    (*(u16 *)((u8 *)arg0 + -2)) = (u16) ((*(u16 *)((u8 *)arg0 + -2)) | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (((S_80024660_11 *)(&D_800814A0))->unk_00 | 0x8000);
    goto block_52;
jt_c2:
jt_c5:
    ((S_80024660_5 *)arg1)->unk_00.at00.v = (s32) (((S_80024660_5 *)arg1)->unk_00.at00.v + ((S_80024660_5 *)arg1)->unk_0C);
    ((S_80024660_5 *)arg1)->unk_04.at00.v = (s32) (((S_80024660_5 *)arg1)->unk_04.at00.v + ((S_80024660_5 *)arg1)->unk_10);
    ((S_80024660_5 *)arg1)->unk_08.at00.v = (s32) (((S_80024660_5 *)arg1)->unk_08.at00.v + ((S_80024660_5 *)arg1)->unk_14);
    if ((s16) ((Rec_func_800243B8_arg0 *)arg0)->unk_10 < ((Rec_func_800243B8_arg0 *)arg0)->unk_12.as_s16) {
        goto block_52;
    }
block_49:
    ((Rec_func_800243B8_arg0 *)arg0)->unk_10 = 0U;
    ((Rec_func_800243B8_arg0 *)arg0)->unk_0A = (s16) ((u16) ((Rec_func_800243B8_arg0 *)arg0)->unk_0A + 1);
    goto block_52;
jt_c6:
    if ((s16) ((Rec_func_800243B8_arg0 *)arg0)->unk_10 < 0x28) {
        goto block_52;
    }
    ((Rec_func_800243B8_arg0 *)arg0)->unk_0A = 4;
    ((Rec_func_800243B8_arg0 *)arg0)->unk_10 = 0U;
block_52:
    ((Rec_func_800243B8_arg0 *)arg0)->unk_14 = 0;
    return;
}
