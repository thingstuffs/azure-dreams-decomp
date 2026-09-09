#include "common.h"
#include "records/Rec_func_800243B8_arg0.h"

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



extern void *func_8003FC64(s32);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80069EF8(void);
extern u8 D_800240D8[];
extern u8 D_800777DC[];

/* Creates a sprite effect at the start position with a randomized target around the center. */
void *func_800243B8(Rec_func_800243B8_arg0 *source, S_800243B8_3 *start, S_800243B8_4 *center)
{
    s16 amplitude;
    s32 angle_x;
    s32 angle_y;
    void *obj;
    S_800243B8_1 *data;
    S_800243B8_5 *sprite;
    S_800243B8_6 *position;
    register void *result;
    register s32 start_z ASM_REG("$4");   /* Register pin retained: removing it adds an instruction. */

    obj = func_8003FC64(0x212);
    if (obj != NULL) {
        data = (u8 *)obj + 0x20;
        ((S_800243B8_0 *)obj)->unk_10 = D_800240D8;
        ((S_800243B8_0 *)obj)->unk_20 = source;
        data->unk_34 = 0;
        data->unk_36 = 0;
        data->unk_3A = source->unk_12.as_u16;

        amplitude = func_80069EF8() % 48;
        angle_x = func_80069EF8() % 0x1000;
        angle_y = func_80069EF8() % 0x1000;

        data->unk_04 = start->unk_00;
        data->unk_08 = start->unk_04;
        data->unk_0C = start->unk_08;

        {
            s32 trig_x, trig_y;
            s32 raw_trig_x;
            s32 sample_angle;
            raw_trig_x = func_800644B8(angle_x);
            sample_angle = angle_y;
            trig_x = raw_trig_x;
            trig_y = func_800644B8(sample_angle);
            trig_x >>= 4;
            trig_y >>= 4;
            data->unk_1C = center->unk_00 +
                (trig_x * trig_y * amplitude);
        }

        {
            s32 trig_x, trig_y;
            s32 raw_trig_x;
            s32 sample_angle;
            raw_trig_x = func_800644B8(angle_x);
            sample_angle = angle_y;
            trig_x = raw_trig_x;
            trig_y = func_80064584(sample_angle);
            trig_x >>= 4;
            trig_y >>= 4;
            data->unk_20 = center->unk_04 +
                (trig_x * trig_y * amplitude);
        }

        {
            s32 trig_x;
            trig_x = func_80064584(angle_x);
            data->unk_24 = center->unk_08 +
                (((trig_x >> 4) * amplitude) << 8);
        }

        data->unk_28 = data->unk_1C - start->unk_00;
        data->unk_2C = data->unk_20 - start->unk_04;
        data->unk_30 = data->unk_24 - start->unk_08;

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
        position->unk_00 = start->unk_00;
        position->unk_04 = start->unk_04;
        start_z = start->unk_08;
        result = obj;
        position->unk_08 = start_z;
    } else {
        result = NULL;
    }
    return result;
}
