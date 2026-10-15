#include "modules/dungeon_ovl_18ca83c.h"

void *func_800243B8(Rec_func_800243B8_arg0 *source, ovl_18ca83c_818AABB8_S_800243B8_3 *start, ovl_18ca83c_818AABB8_S_800243B8_4 *center, s16 index)
{
    s16 amplitude;
    s32 angle_x;
    s32 angle_y;
    void *obj;
    ovl_18ca83c_818AABB8_S_800243B8_1 *data;
    ovl_18ca83c_818AABB8_S_800243B8_5 *sprite;
    ovl_18ca83c_818AABB8_S_800243B8_6 *position;
    register s32 start_z;

    obj = func_8003FC64(0x212);
    if (obj != NULL) {
        data = (u8 *)obj + 0x20;
        ((ovl_18ca83c_818AABB8_S_800243B8_0 *)obj)->unk_10 = (void *)func_800240D8;
        ((ovl_18ca83c_818AABB8_S_800243B8_0 *)obj)->unk_20 = source;
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

        sprite = ((ovl_18ca83c_818AABB8_S_800243B8_0 *)obj)->unk_0C;
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

        position = ((ovl_18ca83c_818AABB8_S_800243B8_0 *)obj)->unk_08;
        position->unk_00 = start->unk_00;
        position->unk_04 = start->unk_04;
        start_z = start->unk_08;
        position->unk_08 = start_z;
        return obj;
    }
    return NULL;
}
