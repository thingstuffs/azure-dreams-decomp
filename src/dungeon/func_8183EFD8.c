#include "common.h"
#include "m2c_compat.h"

typedef struct S_8183EFD8_0_pre {
    u16 unk_00;
} S_8183EFD8_0_pre;   /* the 0x2 bytes before r_arg0 in func_8183EFD8, addressed as r_arg0[-1] */

typedef struct S_8183EFD8_0 {
    void * unk_00;
    u8 pad_04[0x44];
    u16 unk_48;
    u8 pad_4A[0x2];
    union { u16 u; s16 s; } unk_4C;   /* accessed as both */
} S_8183EFD8_0;   /* r_arg0 in func_8183EFD8 */

typedef struct S_8183EFD8_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_8183EFD8_1;   /* temp_v1 in func_8183EFD8 */

typedef struct S_8183EFD8_2 {
    u8 pad_00[0xC];
    union { struct { u8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
} S_8183EFD8_2;   /* arg2 in func_8183EFD8 */

typedef struct S_8183EFD8_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_8183EFD8_3;   /* arg1 in func_8183EFD8 */

typedef struct S_8183EFD8_4 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_8183EFD8_4;   /* temp_v0_4 in func_8183EFD8 */

typedef struct S_8183EFD8_5 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8183EFD8_5;   /* child in func_8183EFD8 */

typedef struct S_8183EFD8_6 {
    u8 * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8183EFD8_6;   /* temp_s0 in func_8183EFD8 */

typedef struct S_8183EFD8_7 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8183EFD8_7;   /* D_800DECF8 in func_8183EFD8 */

typedef struct S_8183EFD8_8 {
    u8 pad_00[0x48];
    s16 unk_48;
    s16 unk_4A;
    s16 unk_4C;
} S_8183EFD8_8;   /* temp_v1_3 in func_8183EFD8 */

typedef struct S_8183EFD8_9 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
} S_8183EFD8_9;   /* ((S_8183EFD8_4 *)temp_v0_4)->unk_08 in func_8183EFD8 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80083498[];
extern u8 D_800DECF8[];
extern s32 D_800814A0[];
void func_80024A5C() __attribute__((noreturn)); /* extern */
void *func_8003FD64();                 /* extern */
s32 func_80069EF8();                          /* extern */
extern u8 D_80024688[];

void func_8183EFD8(void *arg0, S_8183EFD8_3 *arg1, S_8183EFD8_2 *arg2) {
    register void *r_arg0 ASM_REG("$19") = arg0;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 color;
    s32 temp_v1_2;
    s32 temp_v0_3;
    s32 random;
    s32 var_s2;
    u8 temp_v0;
    u8 temp_v0_2;
    S_8183EFD8_6 *temp_s0;
    void *temp_v0_4;
    S_8183EFD8_1 *temp_v1;
    S_8183EFD8_8 *temp_v1_3;
    void *global_s6;

    ASM_KEEP_NV(r_arg0);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    temp_v1 = ((S_8183EFD8_0 *)r_arg0)->unk_00;
    temp_v1->unk_52 = (u16) (temp_v1->unk_52 | 0x8000);
    temp_v1_2 = *(s16 *)((s8 *)r_arg0 + 0x4C);
    ((S_8183EFD8_0 *)r_arg0)->unk_48 = (u16) (((S_8183EFD8_0 *)r_arg0)->unk_48 - 1);
    if (temp_v1_2 == 1) {
        goto case_1;
    }
    if (temp_v1_2 < 2) {
        if (temp_v1_2 == 0) {
            goto case_0;
        }
        func_80024A5C();
    }
    ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    var_s2 = 0x10;
    if (temp_v1_2 == 2) {
        goto case_2;
    }
    func_80024A5C();

case_0:
        func_800478B8(arg2);
        if ((u8) arg2->unk_0C.at00.v < 0x81U) {
            temp_v0 = arg2->unk_0C.at02.v + 0x20;
            arg2->unk_0C.at02.v = temp_v0;
            arg2->unk_0C.at01.v = temp_v0;
            arg2->unk_0C.at00.v = temp_v0;
        }
        if ((s16) ((S_8183EFD8_0 *)r_arg0)->unk_48 <= 0) {
            ((S_8183EFD8_0 *)r_arg0)->unk_48 = 0x10U;
            ((S_8183EFD8_0 *)r_arg0)->unk_4C.u = (u16) (((S_8183EFD8_0 *)r_arg0)->unk_4C.u + 1);
            func_80024A5C();
        }
        goto end;

case_1:
        temp_v0_3 = arg1->unk_14 + 0x8000;
        arg1->unk_14 = temp_v0_3;
        arg1->unk_08 = (s32) (arg1->unk_08 + temp_v0_3);
        var_s2 = 0x14;
        if ((s16) ((S_8183EFD8_0 *)r_arg0)->unk_48 <= 0) {
            global_s6 = D_80024688;
            ((S_8183EFD8_0 *)r_arg0)->unk_4C.s = (s16) ((u16) ((S_8183EFD8_0 *)r_arg0)->unk_4C.s + 1);
            do {
                temp_v0_4 = func_8003FD64(0x312, D_80083498);
                if (temp_v0_4 != NULL) {
                    ((S_8183EFD8_4 *)temp_v0_4)->unk_10 = global_s6;
                    temp_s0 = ((S_8183EFD8_4 *)temp_v0_4)->unk_0C;
                    ((S_8183EFD8_9 *)(((S_8183EFD8_4 *)temp_v0_4)->unk_08))->unk_00 = (s32) arg1->unk_00;
                    ((S_8183EFD8_9 *)(((S_8183EFD8_4 *)temp_v0_4)->unk_08))->unk_04 = (s32) arg1->unk_04;
                    random = func_80069EF8();
                    {
                        S_8183EFD8_5 *child = ((S_8183EFD8_4 *)temp_v0_4)->unk_08;
                        child->unk_08 = (s32) (arg1->unk_08 + ((random & 0x1F) << 0x10));
                        random = func_80069EF8(child);
                    }
                    ((S_8183EFD8_9 *)(((S_8183EFD8_4 *)temp_v0_4)->unk_08))->unk_0C = (s32) (((random & 0xFFF) - 0x7FF) << 8);
                    random = func_80069EF8();
                    color = 0x800000;
                    ASM_KEEP_NV(color);   /* MATCH pin: retail immediate-load split depends on it */
                    ((S_8183EFD8_9 *)(((S_8183EFD8_4 *)temp_v0_4)->unk_08))->unk_10 = (s32) (((random & 0xFFF) - 0x7FF) << 8);
                    temp_s0->unk_1E = 0x1000;
                    temp_s0->unk_1C = 0x1000;
                    temp_s0->unk_10 = 0x20;
                    temp_s0->unk_00 = D_800DECF8;
                    temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0xC);
                    random = (s32) ((S_8183EFD8_7 *)D_800DECF8)->unk_04;
                    color |= 0x8080;
                    temp_s0->unk_04 = 0;
                    temp_s0->unk_05 = 0;
                    temp_s0->unk_0C = color;
                    temp_s0->unk_08 = random;
                    temp_v1_3 = temp_v0_4 + 0x20;
                    temp_v1_3->unk_48 = (s16) (func_80069EF8((void *)color) & 3);
                    temp_v1_3->unk_4A = 0xC;
                    temp_v1_3->unk_4C = 0;
                    ((S_8183EFD8_4 *)temp_v0_4)->unk_20 = (void *) ((S_8183EFD8_0 *)r_arg0)->unk_00;
                }
                var_s2 -= 1;
            } while (var_s2 >= 0);
            func_80024A5C();
        }
        goto end;

case_2:
        if (var_s2 >= (s32) arg2->unk_0C.at00.v) {
            arg2->unk_0C.at00u.v = 0;
            ((S_8183EFD8_0_pre *)r_arg0)[-1].unk_00 = (u16) (((S_8183EFD8_0_pre *)r_arg0)[-1].unk_00 | 0x8000);
            D_800814A0[0] |= 0x8000;
            func_80024A5C();
        }
        temp_v0_2 = arg2->unk_0C.at02.v - 0x10;
        arg2->unk_0C.at02.v = temp_v0_2;
        arg2->unk_0C.at01.v = temp_v0_2;
        arg2->unk_0C.at00.v = temp_v0_2;

end:
    return;
}
