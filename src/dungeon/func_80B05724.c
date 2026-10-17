/* Relink of matched dungeon/func_80AF3724; every changed retail word is a paired relocation. */
#define D_80170874 D_8015E874
#define D_80175A0C D_80163A0C
#include "modules/dungeon_resource10_slot0.h"
extern void func_80162C70(void *, void *, void *);
extern s32 rand(void);

void func_80162F24(s32 unused, R10_80174F24_S_func_80AF3724_0 *origin, void *unused_record, void *unused_actor)
{
    R10_80174F24_LocalVector direction;
    R10_80174F24_LocalTable directions;
    s16 angle;
    s32 jitter;
    s32 coordinate;
    s32 x_offset;
    R10_80174F24_S_func_80AF3724_2 *direction_entry;
    R10_80174F24_S_func_80AF3724_3 *object;
    R10_80174F24_S_func_80AF3724_4 *state;
    R10_80174F24_S_func_80AF3724_5 *transform;
    R10_80174F24_S_func_80AF3724_6 *display;

    directions = (*(R10_80174F24_LocalTable *)&D_8015E874);
    object = func_8003FC64(0x212);
    state = (R10_80174F24_S_func_80AF3724_4 *)((u8 *)object + 0x20);
    if (object != 0) {
        state->unk_1A = 0;
        angle = 0;
        do {
            if (((gameWork.view.viewAngle + angle + 0x100) >> 9 & 7) == 2) {
                state->unk_18 = angle;
            }
            angle += 0x200;
        } while (angle < 0x1000);

        object->unk_10 = ((u8 *)func_80162C70);
        func_8004491C(object, func_80045340);

        display = object->unk_0C;
        display->unk_10 = 0x20;
        display->unk_14 |= 0xC;

        transform = object->unk_08;
        jitter = rand() & 0x1F;
        coordinate = origin->unk_02 - 0x10;
        coordinate += jitter;
        transform->unk_00.unk_02.unk_02 = coordinate;
        jitter = rand() & 0x1F;
        coordinate = origin->unk_06 - 0x10;
        coordinate += jitter;
        transform->unk_04.unk_06.unk_06 = coordinate;
        jitter = (rand() & 0x1F) - 0x70;
        coordinate = origin->unk_0A;
        coordinate += jitter;
        transform->unk_0A = coordinate;

        direction_entry = (R10_80174F24_S_func_80AF3724_2 *)&directions;
        direction.x = ((R10_80174F24_S_func_80AF3724_2 *)((u8 *)direction_entry +
            (((state->unk_18 - 0x400) >> 7) & 0x1C)))->unk_00;
        direction_entry = (R10_80174F24_S_func_80AF3724_2 *)((u8 *)direction_entry +
            (((state->unk_18 - 0x400) >> 7) & 0x1C));
        direction.y = direction_entry->unk_02;
        x_offset = direction.x << 19;
        transform->unk_0C = x_offset;
        transform->unk_10 = direction.y << 19;
        transform->unk_00.unk_00 += x_offset;
        transform->unk_04.unk_04 += transform->unk_10;

        display = object->unk_0C;
        display->unk_1E = 0x200;
        display->unk_1C = 0x200;
        display->unk_0E = 0x20;
        display->unk_0D = 0x20;
        display->unk_0C = 0x20;
        display->unk_12 = 0x7DCF;
        display->unk_14 |= 0x100;
        state->unk_28 = (*(R10_80174F24_LocalPacket *)D_80163A0C);
        display->unk_08 = &state->unk_28;
    }
}
