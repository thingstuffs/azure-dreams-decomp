#include "common.h"


typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} LocalVector;

typedef struct {
    LocalVector vectors[4];
} __attribute__((packed)) LocalTable;

extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);

extern s32 D_800814A0;
extern LocalTable D_80170874;
extern void *D_80170898[27];


typedef struct S_80174C70_0 {
    u8 pad_00[0x18];
    s16 unk_18;
    union { s16 s; u16 u; } unk_1A;   /* accessed as both */
    u8 pad_1C[0x46];
    s16 unk_62;
} S_80174C70_0;   /* arg0 in func_80174C70 */

typedef struct S_80174C70_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    union { s16 s; u16 u; } unk_1A;   /* accessed as both */
} S_80174C70_1;   /* (void *)work_role in func_80174C70 */

typedef struct S_80174C70_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
} S_80174C70_2;   /* arg1 in func_80174C70 */

void func_80174C70(void *arg0, void *arg1, void *arg2)
{
    LocalVector vector;
    LocalTable table;
    s32 cosine;
    long work_role = (long)arg2;
    register s32 angle_raw ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
    s32 angle_diff;
    register s32 signed_angle ASM_REG("$16");   /* MATCH pin: load-bearing for the whole function shape */
    u8 color;
    u32 swi;
    static void *const sw_keep[27] = {
        &&case_0_3, &&case_0_3, &&case_0_3, &&case_0_3,
        &&case_4,
        &&case_5_14, &&case_5_14, &&case_5_14, &&case_5_14, &&case_5_14,
        &&case_5_14, &&case_5_14, &&case_5_14, &&case_5_14, &&case_5_14,
        &&case_15_25, &&case_15_25, &&case_15_25, &&case_15_25,
        &&case_15_25, &&case_15_25, &&case_15_25, &&case_15_25,
        &&case_15_25, &&case_15_25, &&case_15_25,
        &&case_26
    };

    table = D_80170874;

    swi = (u32)((S_80174C70_0 *)arg0)->unk_1A.s;
    if (swi >= 27) {
        goto common;
    }
    (void)sw_keep;
    goto *D_80170898[swi];

case_0_3:
    color = ((S_80174C70_1 *)((void *)work_role))->unk_0E + 0x18;
    ((S_80174C70_1 *)((void *)work_role))->unk_0E = color;
    ((S_80174C70_1 *)((void *)work_role))->unk_0D = color;
    ((S_80174C70_1 *)((void *)work_role))->unk_0C = color;

case_4:
    ((S_80174C70_0 *)arg0)->unk_62 = 0x20;
    ((S_80174C70_1 *)((void *)work_role))->unk_1A.s = 0xA00;
    goto common;

case_5_14:
    ((S_80174C70_0 *)arg0)->unk_62 = 0x18;
    ((S_80174C70_1 *)((void *)work_role))->unk_1A.u += 0x180;
    goto common;

case_15_25:
    color = ((S_80174C70_1 *)((void *)work_role))->unk_0E - 0xE;
    ((S_80174C70_1 *)((void *)work_role))->unk_0E = color;
    ((S_80174C70_1 *)((void *)work_role))->unk_0D = color;
    ((S_80174C70_1 *)((void *)work_role))->unk_0C = color;
    ((S_80174C70_0 *)arg0)->unk_62 = 0x18;
    ((S_80174C70_1 *)((void *)work_role))->unk_1A.u += 0x30;
    goto common;

case_26:
    (*(u16 *)((u8 *)arg0 + (-2))) |= 0x8000;
    D_800814A0 |= 0x8000;
    goto done;

common:
    ((S_80174C70_0 *)arg0)->unk_1A.u++;

    if (((S_80174C70_1 *)((void *)work_role))->unk_1A.u >= 0x1000) {
        ((S_80174C70_1 *)((void *)work_role))->unk_1A.u -= 0x1000;
    }

    angle_raw = ((S_80174C70_1 *)((void *)work_role))->unk_1A.u;
    angle_diff = angle_raw - 0x400;
    angle_raw = angle_diff;
    if ((s16)angle_diff < 0) {
        angle_raw = angle_diff + 0x1000;
    }
    signed_angle = angle_raw << 16;
    work_role = signed_angle >> 16;

    {
        s32 sine_result = func_80064584(work_role);
        register s32 sine_scale ASM_REG("$3") = ((S_80174C70_0 *)arg0)->unk_62;   /* MATCH pin: retail register colouring depends on it */
        register s32 sine ASM_REG("$7") = sine_scale * sine_result;   /* MATCH pin: retail register colouring depends on it */
        s32 cosine_arg = work_role;

        work_role = sine << 4;
        cosine = func_800644B8(cosine_arg);
    }

    {
        u8 *table_base = (u8 *)&table;
        s32 first_angle = ((S_80174C70_0 *)arg0)->unk_18;
        register s32 scale ASM_REG("$4") = ((S_80174C70_0 *)arg0)->unk_62;   /* MATCH pin: retail register colouring depends on it */

        vector.x = (*(u16 *)((u8 *)table_base + (((first_angle - 0x400) >> 7) & 0x1C)));

        {
            register s32 cosine_product ASM_REG("$7") = scale * cosine;   /* MATCH pin: retail register colouring depends on it */
            s32 second_angle = ((S_80174C70_0 *)arg0)->unk_18;

            table_base += ((second_angle - 0x400) >> 7) & 0x1C;
            vector.y = (*(u16 *)((u8 *)table_base + (2)));

            {
                register s32 delta ASM_REG("$3") = cosine_product << 4;   /* MATCH pin: retail register colouring depends on it */

                ((S_80174C70_2 *)arg1)->unk_08 += delta;
            }
        }
    }
    {
        register s32 component ASM_REG("$2") = vector.x;   /* MATCH pin: load-bearing for the whole function shape */
        register s32 product ASM_REG("$7") = component * work_role;   /* MATCH pin: retail register colouring depends on it */

        component = product >> 4;
        ((S_80174C70_2 *)arg1)->unk_0C = component;
    }
    {
        register s32 component ASM_REG("$2") = vector.y;   /* MATCH pin: load-bearing for the whole function shape */
        register s32 product ASM_REG("$7") = component * work_role;   /* MATCH pin: retail register colouring depends on it */

        component = product >> 4;
        ((S_80174C70_2 *)arg1)->unk_10 = component;
    }
    ((S_80174C70_2 *)arg1)->unk_00 += ((S_80174C70_2 *)arg1)->unk_0C;
    ((S_80174C70_2 *)arg1)->unk_04 += ((S_80174C70_2 *)arg1)->unk_10;

done:
    return;
}
