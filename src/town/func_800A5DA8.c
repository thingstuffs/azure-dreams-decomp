#include "common.h"

typedef struct S_800A3508_0 {
    s32 unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800A3508_0;   /* arg2 in func_800A3508 */

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
extern void func_800A360C(void *);

extern u8 D_80045340[];
extern u8 D_800A378C[];
extern s16 D_800D0B18[];
extern s32 D_800D0B20[];
extern s32 D_800D0B50[];

void func_800A3508(void *arg0, void *arg1, S_800A3508_0 *arg2)
{
    u8 *obj = arg0;
    s32 *vec = arg1;
    register s32 color ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 r3 ASM_REG("$19");   /* MATCH pin: retail register colouring depends on it */
    s32 scale;
    s32 r1;
    s32 held;
    s32 value;
    s32 product;
    s32 value2;
    s32 angle;
    s32 fixed;
    s32 *table1;
    s32 *table2;

    table1 = D_800D0B50;
    table2 = D_800D0B20;
    color = 0x808080;
    arg2->unk_0C = color;
    fixed = 0x1000;
    arg2->unk_1E = fixed;
    arg2->unk_1C = fixed;
    arg2->unk_08 = table1[((S_800A3508_1 *)obj)->unk_22];
    arg2->unk_00 = 0;
    arg2->unk_04 = 0;
    arg2->unk_05 = 0;

    value = table2[((S_800A3508_1 *)obj)->unk_22];
    if (value != 0) {
        func_8003DB94(arg2, value, 0);
    }

    func_8004491C(obj - 0x20, D_80045340);

    if (((S_800A3508_1 *)obj)->unk_22 < 4) {
        value = func_800374F4(0x1000);
        r3 = 0x400;
        r1 = D_800D0B18[((S_800A3508_1 *)obj)->unk_22] + (value & 0xFFFF);
        ASM_KEEP(r3);   /* MATCH pin: retail basic-block layout depends on it */
        ASM_TAILSLOT_PIN(r1);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        func_800A360C(D_800D0B18);
        return;
    }

    r1 = func_800374F4(0x1000) & 0xFFFF;
    r3 = func_800374F4(0x1000) & 0xFFFF;
    angle = func_800374F4(0x1000) & 0xFFFF;
    value2 = angle + 0x1000;
    if (value2 < 0) {
        value2 = angle + 0x101F;
    }
    scale = (s32)value2 >> 5;
    product = func_800644B8(r1) * func_800644B8(r3);
    if (product < 0) {
        product += 0xFFF;
    }
    vec[3] = product >> 12;

    held = func_80064584(r1);
    product = held * func_800644B8(r3);
    if (product < 0) {
        product += 0xFFF;
    }
    vec[4] = product >> 12;

    vec[5] = func_80064584(r3);
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
