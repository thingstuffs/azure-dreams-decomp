#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

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

void func_80174C70(void *arg0, void *arg1, void *arg2)
{
    LocalVector vector;
    LocalTable table;
    s32 cosine;
    long work_role = (long)arg2;
    register s32 angle_raw ASM_REG("$6");
    register s32 angle_diff ASM_REG("$3");
    register s32 signed_angle ASM_REG("$16");
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

    swi = (u32)FIELD(arg0, s16, 0x1A);
    if (swi >= 27) {
        goto common;
    }
    (void)sw_keep;
    goto *D_80170898[swi];

case_0_3:
    color = FIELD((void *)work_role, u8, 0xE) + 0x18;
    FIELD((void *)work_role, u8, 0xE) = color;
    FIELD((void *)work_role, u8, 0xD) = color;
    FIELD((void *)work_role, u8, 0xC) = color;

case_4:
    FIELD(arg0, s16, 0x62) = 0x20;
    FIELD((void *)work_role, s16, 0x1A) = 0xA00;
    goto common;

case_5_14:
    FIELD(arg0, s16, 0x62) = 0x18;
    FIELD((void *)work_role, u16, 0x1A) += 0x180;
    goto common;

case_15_25:
    color = FIELD((void *)work_role, u8, 0xE) - 0xE;
    FIELD((void *)work_role, u8, 0xE) = color;
    FIELD((void *)work_role, u8, 0xD) = color;
    FIELD((void *)work_role, u8, 0xC) = color;
    FIELD(arg0, s16, 0x62) = 0x18;
    FIELD((void *)work_role, u16, 0x1A) += 0x30;
    goto common;

case_26:
    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0 |= 0x8000;
    goto done;

common:
    FIELD(arg0, u16, 0x1A)++;

    if (FIELD((void *)work_role, u16, 0x1A) >= 0x1000) {
        FIELD((void *)work_role, u16, 0x1A) -= 0x1000;
    }

    angle_raw = FIELD((void *)work_role, u16, 0x1A);
    ASM_KEEP(angle_raw);
    angle_diff = angle_raw - 0x400;
    ASM_KEEP(angle_diff);
    angle_raw = angle_diff;
    if ((s16)angle_diff < 0) {
        angle_raw = angle_diff + 0x1000;
    }
    signed_angle = angle_raw << 16;
    ASM_KEEP(signed_angle);
    work_role = signed_angle >> 16;

    {
        s32 sine_result = func_80064584(work_role);
        register s32 sine_scale ASM_REG("$3") = FIELD(arg0, s16, 0x62);
        register s32 sine ASM_REG("$7") = sine_scale * sine_result;
        register s32 cosine_arg ASM_REG("$4") = work_role;

        work_role = sine << 4;
        cosine = func_800644B8(cosine_arg);
    }

    {
        register u8 *table_base ASM_REG("$5") = (u8 *)&table;
        register s32 first_angle ASM_REG("$3") = FIELD(arg0, s16, 0x18);
        register s32 scale ASM_REG("$4") = FIELD(arg0, s16, 0x62);

        vector.x = FIELD(table_base, u16,
            ((first_angle - 0x400) >> 7) & 0x1C);

        {
            register s32 cosine_product ASM_REG("$7") = scale * cosine;
            register s32 second_angle ASM_REG("$2") = FIELD(arg0, s16, 0x18);

            table_base += ((second_angle - 0x400) >> 7) & 0x1C;
            vector.y = FIELD(table_base, u16, 2);

            {
                register s32 delta ASM_REG("$3") = cosine_product << 4;

                FIELD(arg1, s32, 8) += delta;
            }
        }
    }
    {
        register s32 component ASM_REG("$2") = vector.x;
        register s32 product ASM_REG("$7") = component * work_role;

        component = product >> 4;
        FIELD(arg1, s32, 0xC) = component;
    }
    {
        register s32 component ASM_REG("$2") = vector.y;
        register s32 product ASM_REG("$7") = component * work_role;

        component = product >> 4;
        FIELD(arg1, s32, 0x10) = component;
    }
    FIELD(arg1, s32, 0) += FIELD(arg1, s32, 0xC);
    FIELD(arg1, s32, 4) += FIELD(arg1, s32, 0x10);

done:
    return;
}
