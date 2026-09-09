#include "common.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_800A3508_1 {
    void * unk_00;
    u8 pad_04[0x1E];
    s16 unk_22;
    s32 unk_24;
    u8 pad_28[0x8];
    s32 unk_30;
    s32 unk_34;
} S_800A3508_1;   /* obj in func_800A3508 */



extern s32 func_800374F4(s32);
extern void func_8003DB94(void *, s32, s32);
extern void func_8004491C(void *, void *);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_8009539C(void *);

extern u8 D_80045340[];
extern u8 D_800A378C[];
extern s16 D_800D0B18[];
extern s32 D_800D0B20[];
extern s32 D_800D0B50[];

/* Initializes the object record and a randomized motion vector. */
void func_800A3508(void *object, void *vector_data, Rec_D_80082E80 *record_data)
{
    register u8 *obj ASM_REG("$21") = object; /* MATCH: Preserve object register allocation across the shared tail. */
    register s32 *vec ASM_REG("$20") = vector_data; /* MATCH: Preserve vector register allocation across the shared tail. */
    s32 color;  
    s32 tilt_angle;  
    s32 scale;
    s32 direction_angle;
    s32 direction_term;
    s32 init_value;
    s32 product;
    s32 scale_numerator;
    s32 scale_sample;
    s32 unit_scale;
    s32 *record_values;
    s32 *setup_params;

    {
        register Rec_D_80082E80 *record ASM_REG("$4") = record_data; /* MATCH: Keep record initialization in the first call argument register. */
        color = 0x808080;
        unit_scale = 0x1000;
        ASM_KEEP4(obj, vec, record, unit_scale); /* MATCH: Preserve entry register setup before initialization. */
        record_values = D_800D0B50;
        setup_params = D_800D0B20;
        record->unk_0C.at00_s32.v = color;
        record->unk_1C.at02_s16.v = unit_scale;
        record->unk_1C.at00_s16.v = unit_scale;
        record->unk_08 = record_values[((S_800A3508_1 *)obj)->unk_22];
        record->unk_00 = 0;
        record->unk_04.as_s8 = 0;
        record->unk_05.as_s8 = 0;

        init_value = setup_params[((S_800A3508_1 *)obj)->unk_22];
        if (init_value != 0) {
            func_8003DB94(record, init_value, 0);
        }

    }

    func_8004491C(obj - 0x20, D_80045340);

    if (((S_800A3508_1 *)obj)->unk_22 < 4) {
        init_value = func_800374F4(0x1000);
        tilt_angle = 0x400;
        direction_angle = D_800D0B18[((S_800A3508_1 *)obj)->unk_22] + (init_value & 0xFFFF);
    } else {
        direction_angle = func_800374F4(0x1000) & 0xFFFF;
        tilt_angle = func_800374F4(0x1000) & 0xFFFF;
    }
    scale_sample = func_800374F4(0x1000) & 0xFFFF;
    scale_numerator = scale_sample + 0x1000;
    if (scale_numerator < 0) {
        scale_numerator = scale_sample + 0x101F;
    }
    scale = (s32)scale_numerator >> 5;
    product = func_800644B8(direction_angle) * func_800644B8(tilt_angle);
    if (product < 0) {
        product += 0xFFF;
    }
    vec[3] = product >> 12;

    direction_term = func_80064584(direction_angle);
    product = direction_term * func_800644B8(tilt_angle);
    if (product < 0) {
        product += 0xFFF;
    }
    vec[4] = product >> 12;

    vec[5] = func_80064584(tilt_angle);
    vec[3] *= scale;
    vec[4] *= scale;
    vec[5] *= scale;

    (*(volatile s32 *)((u8 *)obj + 0x2C)) = vec[3] / 23;
    ((S_800A3508_1 *)obj)->unk_30 = vec[4] / 23;
    ((S_800A3508_1 *)obj)->unk_34 = vec[5] / 23;
    ((S_800A3508_1 *)obj)->unk_24 = 0x18;
    ((S_800A3508_1 *)obj)->unk_00 = D_800A378C;

    func_8009539C(vec);
    func_8009539C(vec);
}
