#include "common.h"
#include "records/Rec_func_800243C4_arg1.h"


extern s32 func_8003DE58(void *, void *, void *, s32);
extern void func_80024450(void) __attribute__((noreturn));
extern s32 func_80024ED4(void *);
extern void func_8004491C(void *, void *);
extern void func_8002455C(void) __attribute__((noreturn));

typedef struct CounterView {
    u16 value;
    u16 pad[5];
} CounterView;

typedef struct FlagsView {
    s32 value;
    s32 pad[2];
} FlagsView;

extern CounterView D_800281F8;
extern u8 D_80045340[];
extern FlagsView D_800814A0;


typedef struct S_800243C4_0_pre {
    u16 unk_00;
} S_800243C4_0_pre;   /* the 0x2 bytes before arg0 in func_800243C4, addressed as arg0[-1] */

typedef struct S_800243C4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x18];
    u16 unk_24;
    u16 unk_26;
    union { s16 s; u16 u; } unk_28;   /* accessed as both */
    u8 pad_2A[0x2];
    union { s16 s; u16 u; } unk_2C;   /* accessed as both */
    s16 unk_2E;
} S_800243C4_0;   /* arg0 in func_800243C4 */

typedef struct S_800243C4_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_800243C4_1;   /* temp_s0 in func_800243C4 */


typedef struct S_800243C4_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800243C4_3;   /* temp_a0_2 in func_800243C4 */

typedef struct S_800243C4_4 {
    u8 pad_00[0xC];
    union { u8 u8; u32 u32; } unk_0C;   /* accessed as both */
} S_800243C4_4;   /* arg2 in func_800243C4 */

typedef struct S_800243C4_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800243C4_5;   /* ((S_800243C4_0 *)arg0)->unk_08 in func_800243C4 */

void func_800243C4(void *arg0, Rec_func_800243C4_arg1 *arg1, S_800243C4_4 *arg2)
{
    s16 temp_v1;
    u16 temp_a0;
    S_800243C4_3 *temp_a0_2;
    S_800243C4_1 *temp_s0;

    D_800281F8.value = D_800281F8.value + 1;
    temp_v1 = ((S_800243C4_0 *)arg0)->unk_2C.s;
    temp_a0 = ((S_800243C4_0 *)arg0)->unk_2C.u;

    if (temp_v1 == 0) {
        temp_s0 = ((S_800243C4_5 *)(((S_800243C4_0 *)arg0)->unk_08))->unk_0C;
        if (((S_800243C4_0 *)arg0)->unk_2E == 0) {
            if (func_8003DE58(temp_s0->unk_08, temp_s0,
                              (u8 *)arg0 + 0x24, 0) != 0) {
                ((S_800243C4_0 *)arg0)->unk_2E = 1;
                func_80024450();
            }
            if (temp_s0->unk_14 & 0x8000) {
                ((S_800243C4_0 *)arg0)->unk_2E = 1;
                ((S_800243C4_0 *)arg0)->unk_28.s = -0x40;
            }
            if (((S_800243C4_0 *)arg0)->unk_2E == 0) {
                goto end;
            }
        }

        temp_a0_2 = ((S_800243C4_5 *)(((S_800243C4_0 *)arg0)->unk_08))->unk_08;
        arg1->unk_02 =
            temp_a0_2->unk_02 + ((S_800243C4_0 *)arg0)->unk_24;
        arg1->unk_06 =
            temp_a0_2->unk_06 + ((S_800243C4_0 *)arg0)->unk_26;
        arg1->unk_0A.as_s16 =
            temp_a0_2->unk_0A + ((S_800243C4_0 *)arg0)->unk_28.u;
        if (func_80024ED4(arg1) != 0) {
            func_8004491C((u8 *)arg0 - 0x20, D_80045340);
            ((S_800243C4_0 *)arg0)->unk_2C.u = ((S_800243C4_0 *)arg0)->unk_2C.u + 1;
            func_8002455C();
        }
    } else if (temp_v1 == 1) {
        if (arg2->unk_0C.u8 < 0xC0) {
            arg2->unk_0C.u32 += 0x202020;
            func_8002455C();
        }
        ((S_800243C4_0 *)arg0)->unk_2C.u = temp_a0 + 1;
        func_8002455C();
    } else if (temp_v1 == 2) {
        arg2->unk_0C.u32 += 0xFFFBFBFC;
        if (arg2->unk_0C.u8 == 0) {
            ((S_800243C4_0_pre *)arg0)[-1].unk_00 |= 0x8000;
            D_800814A0.value |= 0x8000;
        }
    }
end:
    ;
}
