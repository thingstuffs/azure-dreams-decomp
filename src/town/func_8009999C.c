/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_800970FC_0 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0xC];
    u16 unk_14;
} S_800970FC_0;   /* entry in func_800970FC */

typedef struct S_800970FC_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800970FC_1;   /* coord in func_800970FC */

typedef struct S_800970FC_2 {
    u16 unk_00;
} S_800970FC_2;   /* &D_800D0504 in func_800970FC */

typedef struct S_800970FC_3 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800970FC_3;   /* CUR_PAGE in func_800970FC */

typedef struct S_800970FC_4 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    u8 pad_0E[0x6];
    s8 unk_14;
    s8 unk_15;
    s16 unk_16;
    u8 pad_18[0x4];
    s8 unk_1C;
    s8 unk_1D;
    u8 pad_1E[0x6];
    s8 unk_24;
    s8 unk_25;
} S_800970FC_4;   /* temp_s0_2 in func_800970FC */

typedef struct S_800970FC_5 {
    union { u16 u; s16 s; } unk_00;   /* accessed as both */
} S_800970FC_5;   /* D_800D04D0 in func_800970FC */

typedef struct S_800970FC_6 {
    u16 unk_00;
    union { u16 u; s16 s; } unk_02;   /* accessed as both */
    union { u8 u8; u16 u16; } unk_04;   /* accessed as both */
    union { u8 u8; u16 u16; } unk_06;   /* accessed as both */
} S_800970FC_6;   /* xy in func_800970FC */

typedef struct S_800970FC_7 {
    u16 unk_00;
} S_800970FC_7;   /* D_800D04D8 in func_800970FC */

typedef struct S_800970FC_8 {
    u8 pad_00[0x2];
    s16 unk_02;
    u16 unk_04;
    u16 unk_06;
} S_800970FC_8;   /* rect in func_800970FC */

typedef struct S_800970FC_9 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800970FC_9;   /* CUR_CTX in func_800970FC */

typedef struct S_800970FC_10 {
    u8 pad_00[0x4];
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
} S_800970FC_10;   /* temp_s0_3 in func_800970FC */

typedef struct S_800970FC_11 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    s8 unk_06;
    u8 pad_07[0x1];
    u16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    u16 unk_10;
    s16 unk_12;
    s16 unk_14;
} S_800970FC_11;   /* temp_s0_4 in func_800970FC */

typedef struct S_800970FC_12 {
    u8 pad_00[0x10];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_800970FC_12;   /* late_entry in func_800970FC */

typedef struct S_800970FC_13 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800970FC_13;   /* late_ctx in func_800970FC */

typedef struct S_800970FC_14 {
    u8 pad_00[0x4];
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
} S_800970FC_14;   /* temp_s0_8 in func_800970FC */


extern void func_80044D24(void *, void *, s32);
extern void func_800453E0(void *, void *, void *, s16);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_8006658C(void *, void *);
extern void func_80066640(void *, s32);
extern void func_800666E0(void *);
extern void func_800666F4(void *);
extern void func_80067E2C(void *, void *);
extern void func_80067EF4(void *, s32, s32);
extern s32 func_8008C180(s16, s16);
extern s32 func_800C1D44(s32);
extern u8 D_80082E80[];
extern u8 D_800834B8[];
extern u8 D_80083780[];
extern s32 D_800D0460[3];
extern u8 D_800D04D0[];
extern u8 D_800D04D8[];
extern u8 D_800D04E0[];
extern u8 D_800D0504[];
extern s16 D_800D45AA[];
extern u8 D_801C9E40[];

extern void *D_80083160[3];

#define CUR_CTX (*state)
#define CUR_PAGE (D_80083160[0])

s32 func_800970FC(void) {
    s32 carrier;
    s32 remainder_source;
    s32 remainder_adjusted;
    s16 temp_s0_6;
    s16 temp_s1;
    s32 var_s1;
    s32 var_s4;
    s32 temp_fp_calc;
    s16 temp_fp;
    s32 temp_s7;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 lhsv;
    s32 coord_x;
    s32 coord_y;
    s32 color;
    s32 mask;
    s32 two;
    u16 temp_s7_2;
    u32 temp_fp_2;
    u16 temp_s2;
    u16 temp_s3;
    void *temp_s0;
    u8 *entry;
    u8 *coord;
    u8 *xy;
    u8 *late_entry;
    u8 *late_ctx;
    void **state;
    u32 *scr_13c;
    u16 *scr_h0;
    u16 *scr_h2;
    u16 rf4;
    u32 rf6;
    u32 rf6b;

#define temp_s0_2 temp_s0
#define temp_s0_3 temp_s0
#define temp_s0_4 temp_s0
#define temp_s0_5 temp_s0
#define temp_s0_7 temp_s0
#define temp_s0_8 temp_s0
#define temp_s0_9 temp_s0
#define temp_s0_10 temp_s0
#define temp_s3_2 temp_s3
#define var_v0_2 var_v0
#define var_v0_3 var_v0
#define var_v0_4 var_v0
#define var_v0_5 var_v0
#define var_v0_6 var_v0
#define var_v0_7 var_v0
#define var_v0_8 var_v0

    state = &D_80083160[0];
    entry = D_80082E80;
    temp_fp_calc = CUR_PAGE != (void *)D_801C9E40;
    temp_s2 = ((S_800970FC_0 *)entry)->unk_06;
    temp_fp = (u16) temp_fp_calc;
    if (!(((S_800970FC_0 *)entry)->unk_14 & 0x80)) {
        coord = D_80083780;
#define D_80083780 (*coord)
        D_800D0460[0] = 0;
        coord_x = ((S_800970FC_1 *)coord)->unk_02;
        coord_y = ((S_800970FC_1 *)coord)->unk_06;
        temp_v0 = func_800C1D44(func_8008C180(coord_x, coord_y) & 0xFFFF);
        if (temp_v0 != 0) {
            lhsv = ((S_800970FC_1 *)coord)->unk_0A;
            temp_v0_2 = (s32) (lhsv - D_800D45AA[temp_v0]) / 2;
            temp_s7 = temp_v0_2;
            temp_s7 = temp_s7 + 6;
            if ((u32) ((temp_v0_2 + 5) & 0xFFFF) < 0x3FU) {
                D_800D0460[0] = 1;
                scr_13c = (u32 *)0x1F80013C;
                *scr_13c = 0;
                func_800453E0(NULL, coord, D_800D04E0, (s16) (temp_s2 + ((S_800970FC_2 *)(&D_800D0504))->unk_00));
                scr_13c = (void *)0;
                scr_13c = (u32 *)0x1F80013C;
                *scr_13c = 0;
                func_800453E0(D_800834B8, coord, entry, (s16) (temp_s2 + ((S_800970FC_2 *)(&D_800D0504))->unk_00));
                temp_s0 = ((S_800970FC_3 *)CUR_PAGE)->unk_8D0;
                ((S_800970FC_3 *)CUR_PAGE)->unk_8D0 = (void *) (temp_s0 + 0xC);
                func_80067E2C(temp_s0, CUR_PAGE);
                func_8006658C(CUR_PAGE + 0x830, temp_s0);
                temp_s0_2 = ((S_800970FC_3 *)CUR_PAGE)->unk_8D0;
                ((S_800970FC_3 *)CUR_PAGE)->unk_8D0 = (void *) (temp_s0_2 + 0x28);
                color = 0x808080;
                ((S_800970FC_4 *)temp_s0_2)->unk_04 = color;
                func_800666F4(temp_s0_2);
                two = 2;
                color = two;
                xy = D_800D04D0;
                mask = ~0xFF;
                ((S_800970FC_4 *)temp_s0_2)->unk_16 = func_80066460(two, color, (s16) (((S_800970FC_5 *)D_800D04D0)->unk_00.u & mask), (s16) (((S_800970FC_6 *)xy)->unk_02.u & mask));
                func_80066640(temp_s0_2, 1);
                ((S_800970FC_4 *)temp_s0_2)->unk_0C = (s8) (((S_800970FC_5 *)D_800D04D0)->unk_00.s % 0x100);
                ((S_800970FC_4 *)temp_s0_2)->unk_0D = (s8) (((S_800970FC_6 *)xy)->unk_02.s % 0x100);
                ((S_800970FC_4 *)temp_s0_2)->unk_14 = (s8) ((((S_800970FC_5 *)D_800D04D0)->unk_00.s % 0x100) + ((S_800970FC_6 *)xy)->unk_04.u8);
                ((S_800970FC_4 *)temp_s0_2)->unk_15 = (s8) (((S_800970FC_6 *)xy)->unk_02.s % 0x100);
                ((S_800970FC_4 *)temp_s0_2)->unk_1C = (s8) (((S_800970FC_5 *)D_800D04D0)->unk_00.s % 0x100);
                ((S_800970FC_4 *)temp_s0_2)->unk_1D = (s8) ((((S_800970FC_6 *)xy)->unk_02.s % 0x100) + ((S_800970FC_6 *)xy)->unk_06.u8);
                ((S_800970FC_4 *)temp_s0_2)->unk_24 = (s8) ((((S_800970FC_5 *)D_800D04D0)->unk_00.s % 0x100) + ((S_800970FC_6 *)xy)->unk_04.u8);
                remainder_source = ((S_800970FC_6 *)xy)->unk_02.s;
                if (remainder_source < 0) {
                    remainder_adjusted = remainder_source + 0xFF;
                    carrier = temp_fp_calc;
                } else {
                    remainder_adjusted = remainder_source;
                    carrier = temp_fp;
                }
                ((S_800970FC_4 *)temp_s0_2)->unk_25 =
                    (s8)(remainder_source - ((remainder_adjusted >> 8) * 0x100) +
                         ((S_800970FC_6 *)xy)->unk_06.u8);
                {
                u8 *rect;
                u32 rect_y;
                rect = D_800D04D8;
                temp_s3 = ((S_800970FC_7 *)D_800D04D8)->unk_00;
                    var_s1 = ((S_800970FC_8 *)rect)->unk_02;
                    carrier = temp_fp;
                    if (carrier != 0) {
                        var_s1 -= 0xE0;
                    }
                (*(u16 *)((u8 *)temp_s0_2 + 8)) = temp_s3;
                (*(s16 *)((u8 *)temp_s0_2 + 0xA)) = var_s1;
                rf4 = ((S_800970FC_8 *)rect)->unk_04;
                (*(s16 *)((u8 *)temp_s0_2 + 0x10)) = (s16) (temp_s3 + rf4);
                (*(s16 *)((u8 *)temp_s0_2 + 0x12)) = var_s1;
                (*(u16 *)((u8 *)temp_s0_2 + 0x18)) = temp_s3;
                rf6 = ((S_800970FC_8 *)rect)->unk_06;
                (*(s16 *)((u8 *)temp_s0_2 + 0x1A)) = (s16) (var_s1 + rf6);
                rf4 = 0;
                rf4 = ((S_800970FC_8 *)rect)->unk_04;
                (*(s16 *)((u8 *)temp_s0_2 + 0x20)) = (s16) (temp_s3 + rf4);
                rf6 = 0;
                rf6 = ((S_800970FC_8 *)rect)->unk_06;
                (*(s16 *)((u8 *)temp_s0_2 + 0x22)) = (s16) (var_s1 + rf6);
                func_8006658C(CUR_CTX + 0x830, temp_s0_2);
                temp_s0_3 = ((S_800970FC_9 *)CUR_CTX)->unk_8D0;
                ((S_800970FC_9 *)CUR_CTX)->unk_8D0 = (void *) (temp_s0_3 + 0x18);
                ((S_800970FC_10 *)temp_s0_3)->unk_04 = 0x40;
                ((S_800970FC_10 *)temp_s0_3)->unk_05 = 0x40;
                ((S_800970FC_10 *)temp_s0_3)->unk_06 = 0xC0;
                func_800666E0(temp_s0_3);
                func_80066640(temp_s0_3, 0);
                (*(u16 *)((u8 *)temp_s0_3 + 8)) = temp_s3;
                rf6b = ((S_800970FC_8 *)rect)->unk_06;
                (*(s16 *)((u8 *)temp_s0_3 + 0xA)) = (s16) ((var_s1 + rf6b) - temp_s7);
                rf4 = ((S_800970FC_8 *)rect)->unk_04;
                (*(s16 *)((u8 *)temp_s0_3 + 0xC)) = (s16) (temp_s3 + rf4);
                rf6b = 0;
                rect_y = ((S_800970FC_8 *)rect)->unk_06;
                (*(u16 *)((u8 *)temp_s0_3 + 0x10)) = temp_s3;
                (*(s16 *)((u8 *)temp_s0_3 + 0xE)) = (s16) ((var_s1 + rect_y) - temp_s7);
                rect_y = 0;
                rf6b = ((S_800970FC_8 *)rect)->unk_06;
                (*(s16 *)((u8 *)temp_s0_3 + 0x12)) = (s16) (var_s1 + rf6b);
                rf4 = 0;
                rf4 = ((S_800970FC_8 *)rect)->unk_04;
                (*(s16 *)((u8 *)temp_s0_3 + 0x14)) = (s16) (temp_s3 + rf4);
                rf6b = 0;
                rf6b = ((S_800970FC_8 *)rect)->unk_06;
                (*(s16 *)((u8 *)temp_s0_3 + 0x16)) = (s16) (var_s1 + rf6b);
                func_8006658C(CUR_CTX + 0x830, temp_s0_3);
                temp_s0_4 = ((S_800970FC_9 *)CUR_CTX)->unk_8D0;
                ((S_800970FC_9 *)CUR_CTX)->unk_8D0 = (void *) (temp_s0_4 + 0x18);
                ((S_800970FC_11 *)temp_s0_4)->unk_06 = 0;
                ((S_800970FC_11 *)temp_s0_4)->unk_05 = 0;
                ((S_800970FC_11 *)temp_s0_4)->unk_04 = 0;
                func_800666E0(temp_s0_4);
                func_80066640(temp_s0_4, 0);
                ((S_800970FC_11 *)temp_s0_4)->unk_08 = temp_s3;
                ((S_800970FC_11 *)temp_s0_4)->unk_0A = var_s1;
                rf4 = ((S_800970FC_8 *)rect)->unk_04;
                ((S_800970FC_11 *)temp_s0_4)->unk_0C = (s16) (temp_s3 + rf4);
                ((S_800970FC_11 *)temp_s0_4)->unk_0E = var_s1;
                ((S_800970FC_11 *)temp_s0_4)->unk_10 = temp_s3;
                rf6 = ((S_800970FC_8 *)rect)->unk_06;
                ((S_800970FC_11 *)temp_s0_4)->unk_12 = (s16) (var_s1 + rf6);
                rf4 = 0;
                rf4 = ((S_800970FC_8 *)rect)->unk_04;
                ((S_800970FC_11 *)temp_s0_4)->unk_14 = (s16) (temp_s3 + rf4);
                rf6 = 0;
                rf6 = ((S_800970FC_8 *)rect)->unk_06;
                (*(s16 *)((u8 *)temp_s0_4 + 0x16)) = (s16) (var_s1 + rf6);
                func_8006658C(CUR_CTX + 0x830, temp_s0_4);
                temp_s0_5 = ((S_800970FC_9 *)CUR_CTX)->unk_8D0;
                ((S_800970FC_9 *)CUR_CTX)->unk_8D0 = (void *) (temp_s0_5 + 0xC);
                func_80067E2C(temp_s0_5, rect);
                func_8006658C(CUR_CTX + 0x830, temp_s0_5);
                }
                late_entry = D_80082E80;
                temp_s3_2 = ((S_800970FC_6 *)xy)->unk_00;
                var_s4 = ((S_800970FC_6 *)xy)->unk_02.s;
                temp_fp_2 = ((S_800970FC_12 *)late_entry)->unk_14;
                temp_s7_2 = ((S_800970FC_12 *)late_entry)->unk_10;
                {
                    if (carrier != 0) {
                        var_s4 -= 0xE0;
                    }
                }
                temp_s1 = temp_s3_2 + 0x20;
                temp_s0_6 = var_s4 + 0x39;
                scr_h0 = (u16 *)0x1F800000;
                scr_h2 = (u16 *)0x1F800002;
                *scr_h0 = (u16) temp_s1;
                *scr_h2 = (u16) temp_s0_6;
                ((S_800970FC_12 *)late_entry)->unk_10 = 0x40U;
                ((S_800970FC_12 *)late_entry)->unk_14 = (u16) ((*(u16 *)((u8 *)late_entry + 0x14)) | 0xC);
                func_80044D24(0, late_entry, 0x1F0);
                scr_h0 = (void *)0; scr_h2 = (void *)0;
                scr_h0 = (u16 *)0x1F800000;
                scr_h2 = (u16 *)0x1F800002;
                *scr_h0 = (u16) temp_s1;
                *scr_h2 = (u16) temp_s0_6;
                ((S_800970FC_12 *)late_entry)->unk_10 = 0x20U;
                ((S_800970FC_12 *)late_entry)->unk_14 = (u16) ((*(u16 *)((u8 *)late_entry + 0x14)) & 0xFFF3);
                func_80044D24(0, late_entry, 0x1F0);
                late_ctx = CUR_CTX;
                ((S_800970FC_12 *)late_entry)->unk_14 = temp_fp_2;
                ((S_800970FC_12 *)late_entry)->unk_10 = temp_s7_2;
                temp_s0_7 = ((S_800970FC_13 *)late_ctx)->unk_8D0;
                ((S_800970FC_13 *)late_ctx)->unk_8D0 = (void *) (temp_s0_7 + 0xC);
                func_80067EF4(temp_s0_7, 0, 0);
                func_8006658C(CUR_CTX + 0x830, temp_s0_7);
                temp_s0_8 = ((S_800970FC_9 *)CUR_CTX)->unk_8D0;
                ((S_800970FC_9 *)CUR_CTX)->unk_8D0 = (void *) (temp_s0_8 + 0x18);
                ((S_800970FC_14 *)temp_s0_8)->unk_06 = 0xFF;
                ((S_800970FC_14 *)temp_s0_8)->unk_05 = 0xFF;
                ((S_800970FC_14 *)temp_s0_8)->unk_04 = 0xFF;
                func_800666E0(temp_s0_8);
                func_80066640(temp_s0_8, 0);
                (*(u16 *)((u8 *)temp_s0_8 + 8)) = temp_s3_2;
                (*(s16 *)((u8 *)temp_s0_8 + 0xA)) = var_s4;
                (*(s16 *)((u8 *)temp_s0_8 + 0xC)) = (s16) (temp_s3_2 + ((S_800970FC_6 *)xy)->unk_04.u16);
                (*(s16 *)((u8 *)temp_s0_8 + 0xE)) = var_s4;
                (*(u16 *)((u8 *)temp_s0_8 + 0x10)) = temp_s3_2;
                (*(s16 *)((u8 *)temp_s0_8 + 0x12)) = (s16) (var_s4 + ((S_800970FC_6 *)xy)->unk_06.u16);
                (*(s16 *)((u8 *)temp_s0_8 + 0x14)) = (s16) (temp_s3_2 + ((S_800970FC_6 *)xy)->unk_04.u16);
                (*(s16 *)((u8 *)temp_s0_8 + 0x16)) = (s16) (var_s4 + ((S_800970FC_6 *)xy)->unk_06.u16);
                func_8006658C(CUR_CTX + 0x830, temp_s0_8);
                temp_s0_9 = ((S_800970FC_9 *)CUR_CTX)->unk_8D0;
                ((S_800970FC_9 *)CUR_CTX)->unk_8D0 = (void *) (temp_s0_9 + 0xC);
                func_80067EF4(temp_s0_9, 0, 1);
                func_8006658C(CUR_CTX + 0x830, temp_s0_9);
                temp_s0_10 = ((S_800970FC_9 *)CUR_CTX)->unk_8D0;
                ((S_800970FC_9 *)CUR_CTX)->unk_8D0 = (void *) (temp_s0_10 + 0xC);
                func_80067E2C(temp_s0_10, xy);
                func_8006658C(CUR_CTX + 0x830, temp_s0_10);
                return 0;
            }
        }
        scr_13c = (void *)0;
        scr_13c = (u32 *)0x1F80013C;
        *scr_13c = 0;
        func_800453E0(D_800834B8, coord, entry, (s16) (temp_s2 + ((S_800970FC_2 *)(&D_800D0504))->unk_00));
        /* Duplicate return node #26. Try simplifying control flow for better match */
        return 0;
    }
    return 0;
}
