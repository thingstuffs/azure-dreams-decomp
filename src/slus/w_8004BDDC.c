#include "common.h"
#include "m2c_compat.h"

/* first_pass warm draft: compiles, best score 115 @ 2.7.2 */
#include "common.h"

typedef struct S_8004BDDC_0 {
    u8 pad_00[0x3];
    s8 unk_03;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    s16 unk_08;
    s16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u16 unk_0E;
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_10;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; } unk_14;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u16 v; } at02; } unk_18;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_1C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; } unk_20;   /* overlapping accesses */
    u8 unk_24;
    s8 unk_25;
    u8 pad_26[0x2];
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_28;   /* overlapping accesses */
    s32 unk_2C;
    s8 unk_30;
    s8 unk_31;
} S_8004BDDC_0;   /* arg2 in func_8004BDDC */

typedef struct S_8004BDDC_1 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 pad_02[0x2];
    u16 unk_04;
    u16 unk_06;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
} S_8004BDDC_1;   /* arg4 in func_8004BDDC */

typedef struct S_8004BDDC_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8004BDDC_2;   /* temp_s3 in func_8004BDDC */


M2C_UNK func_8004C010();                 /* extern */

void *func_8004BDDC(s32 arg0, s32 arg1, void *arg2, void *arg3, void *arg4) {
    register void *temp_s3 ASM_REG("$19");   /* MATCH pin: slus-diff */
    s8 temp_v0;
    s8 temp_v1_3;
    u8 temp_v1;
    u8 temp_v1_2;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_s0_4;

    ((S_8004BDDC_0 *)arg2)->unk_2C = (s32) ((S_8004BDDC_0 *)arg2)->unk_20.at00.v;
    ((S_8004BDDC_0 *)arg2)->unk_20.at00.v = (s32) ((S_8004BDDC_0 *)arg2)->unk_18.at00.v;
    ((S_8004BDDC_0 *)arg2)->unk_14.at00.v = (s32) ((S_8004BDDC_0 *)arg2)->unk_10.at00.v;
    temp_s3 = arg3;
    {
        u8 f8 = *(volatile u8 *) ((u8 *) arg4 + 8);
        temp_v1 = *(volatile u8 *) ((u8 *) arg4 + 0xA);
        if ((temp_v1 + f8) >= 0x100) {
            ((S_8004BDDC_1 *)arg4)->unk_0A = (u8) (temp_v1 - 1);
        }
    }
    {
        u8 f9 = *(volatile u8 *) ((u8 *) arg4 + 9);
        temp_v1_2 = *(volatile u8 *) ((u8 *) arg4 + 0xB);
        if ((temp_v1_2 + f9) >= 0x100) {
            ((S_8004BDDC_1 *)arg4)->unk_0B = (u8) (temp_v1_2 - 1);
        }
    }
    temp_s3 = (void *) ((u8 *) temp_s3 + 0xC);
    temp_s0 = arg2 + 0x10;
    ((S_8004BDDC_0 *)arg2)->unk_10.at00.v = (s32) ((S_8004BDDC_2 *)temp_s3)->unk_00;
    ((S_8004BDDC_0 *)arg2)->unk_04 = (u8) ((S_8004BDDC_0 *)arg2)->unk_10.at03.v;
    func_8004C010(temp_s0, arg0);
    func_8004C010(temp_s0, arg1);
    temp_s0_2 = arg2 + 0x1C;
    ((S_8004BDDC_0 *)arg2)->unk_1C.at00.v = (s32) ((S_8004BDDC_2 *)temp_s3)->unk_04;
    ((S_8004BDDC_0 *)arg2)->unk_05 = (u8) ((S_8004BDDC_0 *)arg2)->unk_1C.at03.v;
    func_8004C010(temp_s0_2, arg0);
    func_8004C010(temp_s0_2, arg1);
    temp_s0_3 = arg2 + 0x28;
    ((S_8004BDDC_0 *)arg2)->unk_28.at00.v = (s32) ((S_8004BDDC_2 *)temp_s3)->unk_08;
    ((S_8004BDDC_0 *)arg2)->unk_06 = (u8) ((S_8004BDDC_0 *)arg2)->unk_28.at03.v;
    func_8004C010(temp_s0_3, arg0);
    func_8004C010(temp_s0_3, arg1);
    temp_s0_4 = arg2 + 4;
    func_8004C010(temp_s0_4, arg0);
    func_8004C010(temp_s0_4, arg1);
    ((S_8004BDDC_0 *)arg2)->unk_03 = 0xC;
    ((S_8004BDDC_0 *)arg2)->unk_07 = (u8) ((S_8004BDDC_1 *)arg4)->unk_01;
    ((S_8004BDDC_0 *)arg2)->unk_0C = (u8) ((S_8004BDDC_1 *)arg4)->unk_08;
    ((S_8004BDDC_0 *)arg2)->unk_0E = (u16) ((S_8004BDDC_1 *)arg4)->unk_06;
    ((S_8004BDDC_0 *)arg2)->unk_0D = (u8) ((S_8004BDDC_1 *)arg4)->unk_09;
    if ((((S_8004BDDC_0 *)arg2)->unk_14.at00u.v < ((S_8004BDDC_0 *)arg2)->unk_08) ||
        (((S_8004BDDC_0 *)arg2)->unk_08 != ((S_8004BDDC_0 *)arg2)->unk_20.at00u.v)) {
        ((S_8004BDDC_1 *)arg4)->unk_0A = (u8) (((S_8004BDDC_1 *)arg4)->unk_0A - 1);
    }
    temp_v0 = ((S_8004BDDC_1 *)arg4)->unk_08 + ((S_8004BDDC_1 *)arg4)->unk_0A;
    ((S_8004BDDC_0 *)arg2)->unk_30 = temp_v0;
    ((S_8004BDDC_0 *)arg2)->unk_18.at00u.v = temp_v0;
    ((S_8004BDDC_0 *)arg2)->unk_18.at01.v = (u8) ((S_8004BDDC_1 *)arg4)->unk_09;
    ((S_8004BDDC_0 *)arg2)->unk_18.at02.v = (u16) ((S_8004BDDC_1 *)arg4)->unk_04;
    ((S_8004BDDC_0 *)arg2)->unk_24 = (u8) ((S_8004BDDC_1 *)arg4)->unk_08;
    if ((((S_8004BDDC_0 *)arg2)->unk_20.at02.v < ((S_8004BDDC_0 *)arg2)->unk_0A) ||
        (((S_8004BDDC_0 *)arg2)->unk_0A != ((S_8004BDDC_0 *)arg2)->unk_14.at02.v)) {
        ((S_8004BDDC_1 *)arg4)->unk_0B = (u8) (((S_8004BDDC_1 *)arg4)->unk_0B - 1);
    }
    temp_v1_3 = ((S_8004BDDC_1 *)arg4)->unk_09 + ((S_8004BDDC_1 *)arg4)->unk_0B;
    ((S_8004BDDC_0 *)arg2)->unk_31 = temp_v1_3;
    ((S_8004BDDC_0 *)arg2)->unk_25 = temp_v1_3;
    return temp_s3;
}
