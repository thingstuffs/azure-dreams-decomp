#include "common.h"
#include "m2c_compat.h"

typedef struct S_80023C80_0_pre {
    u16 unk_00;
} S_80023C80_0_pre;   /* the 0x2 bytes before obj in func_80023C80, addressed as obj[-1] */

typedef struct S_80023C80_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    u8 pad_02[0x2];
    void ** unk_04;
    u8 pad_08[0x4];
    union { u16 s; volatile u16 u; } unk_0C;   /* accessed as both */
    union { u16 s; volatile u16 u; } unk_0E;   /* accessed as both */
    s16 unk_10;
    s16 unk_12;
} S_80023C80_0;   /* obj in func_80023C80 */

typedef struct S_80023C80_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80023C80_1;   /* (void *)work in func_80023C80 */


extern s32 D_800814A0;

void func_80023C80(void *arg0) {
    void *obj;
    s32 temp_v1;
    s32 var_v0_3;
    u16 temp_a1;

    obj = arg0;
    
    temp_v1 = ((S_80023C80_0 *)obj)->unk_00.s;
    temp_a1 = (u16) ((S_80023C80_0 *)obj)->unk_00.s;

    if (temp_v1 == 1) {
        goto case1;
    }
    if (temp_v1 >= 2) {
        goto check2;
    }
    if (temp_v1 == 0) {
        goto case0;
    }
    goto end;

check2:
    if (temp_v1 == 2) {
        goto case2;
    }
    goto end;

case0:
    ((S_80023C80_0 *)obj)->unk_00.u = temp_a1 + 1;
    goto end;

case1:
{
    void **temp_v1_2;
    s32 work;
    s32 var_a1;

    temp_v1_2 = ((S_80023C80_0 *)obj)->unk_04;
    work = (s32)*temp_v1_2;
    work = ((S_80023C80_1 *)((void *)work))->unk_02;
    if (work < 0) {
        work += 0x1F;
    }
    ((S_80023C80_0 *)obj)->unk_0C.s = (u16) ((work >> 5) + 0x94);
    work = (s32)*temp_v1_2;
    work = ((S_80023C80_1 *)((void *)work))->unk_06;
    if (work < 0) {
        work += 0x1F;
    }
    ((S_80023C80_0 *)obj)->unk_0E.s = (u16) ((work >> 5) + 0x75);
    work = (s32)*temp_v1_2;
    work = ((S_80023C80_1 *)((void *)work))->unk_0A;
    work = 0 - work;
    var_a1 = work >> 6;
    if (work < 0) {
        var_a1 = (s32) (work + 0x3F) >> 6;
    }
    var_v0_3 = var_a1 + 3;
    if (var_a1 < 0) {
        var_a1 = 0;
        ASM_KEEP_NV(var_a1);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        var_v0_3 = var_a1 + 3;
    }
    ((S_80023C80_0 *)obj)->unk_12 = var_v0_3;
    ((S_80023C80_0 *)obj)->unk_10 = var_v0_3;
    ((S_80023C80_0 *)obj)->unk_0C.s =
        (u16) (((S_80023C80_0 *)obj)->unk_0C.u - var_a1);
    ((S_80023C80_0 *)obj)->unk_0E.s =
        (u16) (((S_80023C80_0 *)obj)->unk_0E.u - var_a1);
    goto end;
}

case2:
    (*(u16 *)((u8 *)obj + -2)) =
        (u16) (((S_80023C80_0_pre *)obj)[-1].unk_00 | 0x8000);
    D_800814A0 |= 0x8000;

end:
    
}

/* MECHANISM: The signed 0/1/2 dispatch is laid out in retail block order and
   joins the true-space epilogue at 0x80023D98, so the leaf stays frameless.
   ABI $a0 holds the object; $v1/$v0 carry the two-level pointer loads. */
