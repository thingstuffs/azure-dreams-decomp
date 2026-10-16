#include "modules/dungeon_ovl_7e6b7800.h"

void dungeonUpdateHomingArcAndBrightenEffect(void *effect, void *motion, void *sprite)
{
    u16 offset[3];
    s32 state;

    state = ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_0C.n;
    switch (state) {
    case 0:
        func_8004491C((u8 *)effect - 0x20, func_80045340);
        ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_0C.n2 = ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_0C.n2 + 1;
                        /* fall through */

    case 1:
    {
        void *source;
        source = ((Row_8194C8F0_S_800240F0_6 *)(((Row_8194C8F0_S_800240F0_0 *)effect)->unk_00))->unk_0C;
        if ((((Row_8194C8F0_S_800240F0_1 *)source)->unk_14 & 0x8000) ||
            resolveRecordOrientationOrFallback(((Row_8194C8F0_S_800240F0_1 *)source)->unk_08, source, offset, 0) != 0) {
            void *position;
            u16 source_z;

            position = ((Row_8194C8F0_S_800240F0_6 *)(((Row_8194C8F0_S_800240F0_0 *)effect)->unk_00))->unk_08;
            ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_00.at02.v = ((Row_8194C8F0_S_800240F0_3 *)position)->unk_00.at02.v;
            ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_04.at02.v = ((Row_8194C8F0_S_800240F0_3 *)position)->unk_04.at02.v;
            source_z = ((Row_8194C8F0_S_800240F0_3 *)position)->unk_0A;
            ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_08.at02.v = source_z;

            if (!(((Row_8194C8F0_S_800240F0_1 *)source)->unk_14 & 0x8000)) {
                u16 offset_z;

                ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_00.at02.v += offset[0];
                ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_04.at02.v += offset[1];
                offset_z = ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_08.at02.v + offset[2];
                ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_08.at02.v = offset_z;
            } else {
                ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_08.at02.v = source_z - 0x20;
            }
        }
    }

        if (((Row_8194C8F0_S_800240F0_7 *)(((Row_8194C8F0_S_800240F0_0 *)effect)->unk_08))->unk_00 & 0x80) {
            u16 travel_frames;

            travel_frames = 10;
            ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_10.u = travel_frames;
            ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_0C.n2 += 1;
        }
        break;

    case 2:
    {
        u16 scale;
        scale = ((Row_8194C8F0_S_800240F0_4 *)sprite)->unk_1E + 0x200;
        ((Row_8194C8F0_S_800240F0_4 *)sprite)->unk_1E = scale;
        ((Row_8194C8F0_S_800240F0_4 *)sprite)->unk_1C = scale;
    }
        {
            void *position;
            position = ((Row_8194C8F0_S_800240F0_8 *)(((Row_8194C8F0_S_800240F0_0 *)effect)->unk_04))->unk_08;
            ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_0C = ((Row_8194C8F0_S_800240F0_3 *)position)->unk_00.at00.v;
            ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_10 = ((Row_8194C8F0_S_800240F0_3 *)position)->unk_04.at00.v;
        }
        ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_14 = (D_800814A8->unk_88 - 0x50) << 16;

        {
            s32 angle_index;
            angle_index = (gameWork.view.viewAngle + D_800814A8->facing + 0x100) >> 7;
            if (resolveRecordOrientationOrFallback(*(void **)((angle_index & 0x1C) + (s32)(*(s32 * *)D_800E3D18)),
                              ((u8 *)(&D_80082E80)), offset, 0) != 0) {
                ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_0C += ((s16 *)offset)[0] << 16;
                ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_10 += ((s16 *)offset)[1] << 16;
                ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_14 += ((s16 *)offset)[2] << 16;
            }
        }

        ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_00.at00.v +=
            (((Row_8194C8F0_S_800240F0_2 *)motion)->unk_0C - ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_00.at00.v) /
            ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_10.s;
        ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_04.at00.v +=
            (((Row_8194C8F0_S_800240F0_2 *)motion)->unk_10 - ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_04.at00.v) /
            ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_10.s;
        ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_08.at00.v +=
            (((Row_8194C8F0_S_800240F0_2 *)motion)->unk_14 - ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_08.at00.v) /
                ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_10.s -
            (func_800644B8(((Row_8194C8F0_S_800240F0_0 *)effect)->unk_10.s * 0xAA) << 7);
        {
            u16 frames_left;
            frames_left = ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_10.u - 1;
            ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_10.u = frames_left;
            if ((s16)frames_left > 0) {
                break;
            }
        }

        ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_00.at00.v = ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_0C;
        ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_04.at00.v = ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_10;
        ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_08.at00.v = ((Row_8194C8F0_S_800240F0_2 *)motion)->unk_14;
        ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_10.u = state;
        ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_0C.n2 += 1;
        break;

    case 3:
    {
        u16 scale;
        u8 brightness;
        scale = ((Row_8194C8F0_S_800240F0_4 *)sprite)->unk_1E + 0x200;
        brightness = ((Row_8194C8F0_S_800240F0_4 *)sprite)->unk_0E + 8;
        ((Row_8194C8F0_S_800240F0_4 *)sprite)->unk_1E = scale;
        ((Row_8194C8F0_S_800240F0_4 *)sprite)->unk_1C = scale;
        ((Row_8194C8F0_S_800240F0_4 *)sprite)->unk_0E = brightness;
        ((Row_8194C8F0_S_800240F0_4 *)sprite)->unk_0D = brightness;
        ((Row_8194C8F0_S_800240F0_4 *)sprite)->unk_0C = brightness;
    }
        {
            u16 frames_left;
            frames_left = ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_10.u - 1;
            ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_10.u = frames_left;
            if ((s16)frames_left > 0) {
                break;
            }
        }

        (*(u16 *)((u8 *)effect + (-2))) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        return;
    }

    ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_12 = ((Row_8194C8F0_S_800240F0_0 *)effect)->unk_12 + 1;
}
