#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800243B8_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_800243B8_0;   /* obj in func_800243B8 */

typedef struct S_800243B8_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
    s32 unk_2C;
    s32 unk_30;
    s16 unk_34;
    s16 unk_36;
    u8 pad_38[0x2];
    u16 unk_3A;
} S_800243B8_1;   /* data in func_800243B8 */

typedef struct S_800243B8_2 {
    u8 pad_00[0x12];
    u16 unk_12;
} S_800243B8_2;   /* arg0 in func_800243B8 */

typedef struct S_800243B8_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800243B8_3;   /* arg1 in func_800243B8 */

typedef struct S_800243B8_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800243B8_4;   /* arg2 in func_800243B8 */

typedef struct S_800243B8_5 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_800243B8_5;   /* sprite in func_800243B8 */

typedef struct S_800243B8_6 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800243B8_6;   /* position in func_800243B8 */



extern void func_80024630(void) __attribute__((noreturn));
extern void *func_8003FC64(s32);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80069EF8(void);
extern u8 D_800240D8[];
extern u8 D_800777DC[];

void *func_800243B8(S_800243B8_2 *arg0, S_800243B8_3 *arg1, S_800243B8_4 *arg2)
{
    s16 amplitude;
    s32 angle_x;
    s32 angle_y;
    void *obj;
    S_800243B8_1 *data;
    S_800243B8_5 *sprite;
    S_800243B8_6 *position;
    register void *ret ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    register s32 tail_z ASM_REG("$4");   /* MATCH pin: build-fail */

    obj = func_8003FC64(0x212);
    if (obj != NULL) {
        data = (u8 *)obj + 0x20;
        ((S_800243B8_0 *)obj)->unk_10 = D_800240D8;
        ((S_800243B8_0 *)obj)->unk_20 = arg0;
        data->unk_34 = 0;
        data->unk_36 = 0;
        data->unk_3A = arg0->unk_12;

        amplitude = func_80069EF8() % 48;
        angle_x = func_80069EF8() % 0x1000;
        angle_y = func_80069EF8() % 0x1000;

        data->unk_04 = arg1->unk_00;
        data->unk_08 = arg1->unk_04;
        data->unk_0C = arg1->unk_08;

        {
            s32 tx, ty;
            s32 raw_tx;
            s32 trig_arg;
            raw_tx = func_800644B8(angle_x);
            trig_arg = angle_y;
            tx = raw_tx;
            ty = func_800644B8(trig_arg);
            tx >>= 4;
            ty >>= 4;
            data->unk_1C = arg2->unk_00 +
                (tx * ty * amplitude);
        }

        {
            s32 tx, ty;
            s32 raw_tx;
            s32 trig_arg;
            raw_tx = func_800644B8(angle_x);
            trig_arg = angle_y;
            tx = raw_tx;
            ty = func_80064584(trig_arg);
            tx >>= 4;
            ty >>= 4;
            data->unk_20 = arg2->unk_04 +
                (tx * ty * amplitude);
        }

        {
            s32 trig_x;
            trig_x = func_80064584(angle_x);
            data->unk_24 = arg2->unk_08 +
                (((trig_x >> 4) * amplitude) << 8);
        }

        data->unk_28 = data->unk_1C - arg1->unk_00;
        data->unk_2C = data->unk_20 - arg1->unk_04;
        data->unk_30 = data->unk_24 - arg1->unk_08;

        sprite = ((S_800243B8_0 *)obj)->unk_0C;
        sprite->unk_0E = 0xFF;
        sprite->unk_0D = 0xFF;
        sprite->unk_0C = 0xFF;
        sprite->unk_1E = 0x300;
        sprite->unk_1C = 0x300;
        sprite->unk_1A = func_80069EF8() % 0x1000;
        sprite->unk_12 = 0x7E06;
        sprite->unk_08 = D_800777DC;
        sprite->unk_14 |= 0x100;
        sprite->unk_10 |= 0x60;
        sprite->unk_14 |= 0xC;

        position = ((S_800243B8_0 *)obj)->unk_08;
        position->unk_00 = arg1->unk_00;
        position->unk_04 = arg1->unk_04;
        tail_z = arg1->unk_08;
        ASM_UNDEF(ret);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        ret = obj;
        ASM_KEEP4(ret, tail_z, ret, tail_z);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        position->unk_08 = tail_z;
        func_80024630();
    }
    ret = NULL;
    ASM_KEEP(ret);   /* MATCH pin: retail schedule: same instructions, different order without it */
    return ret;
}
