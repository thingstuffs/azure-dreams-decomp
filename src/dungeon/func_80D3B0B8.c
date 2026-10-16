#include "modules/dungeon_ovl_d5b0b8.h"

void createOwnerLinkedDirectionalObject(u8 *owner_data, u8 *source_position, u8 *source_sprite) {
    u8 *object;
    u8 *object_data;
    u8 *sprite;
    u8 *position;
    u8 *direction_table;

    object = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
    object_data = object + 0x20;
    if (object != 0) {
        ((S_80D3B0B8_0 *)object_data)->unk_96 = 0x78;
        ((S_80D3B0B8_1 *)object)->unk_10 = D_800D5594;
        ((S_80D3B0B8_0 *)object_data)->unk_AC = owner_data - 0x20;
        ((S_80D3B0B8_0 *)object_data)->unk_94 = ((S_80D3B0B8_2 *)owner_data)->unk_2A.s;
        ((S_80D3B0B8_0 *)object_data)->unk_2A = ((S_80D3B0B8_2 *)owner_data)->unk_2A.s;
        sprite = ((S_80D3B0B8_1 *)object)->unk_0C;

        *(Copy48 *)sprite = *(Copy48 *)source_sprite;

        func_8004491C(object, func_80045340);
        direction_table = D_800E23F0;
        ((S_80D3B0B8_3 *)sprite)->unk_2C = direction_table;
        func_80047784(sprite,
            direction_table[((gameWork.view.viewAngle +
                ((S_80D3B0B8_2 *)owner_data)->unk_2A.u + 0x100) >> 9) & 7], 0);

        position = ((S_80D3B0B8_1 *)object)->unk_08;
        ((S_80D3B0B8_5 *)position)->unk_02 = ((S_80D3B0B8_6 *)source_position)->unk_02;
        ((S_80D3B0B8_5 *)position)->unk_06 = ((S_80D3B0B8_6 *)source_position)->unk_06;
        ((S_80D3B0B8_5 *)position)->unk_0A = ((S_80D3B0B8_6 *)source_position)->unk_0A;
        {
            u16 sprite_field_1c;
            u16 sprite_field_1e;

            sprite_field_1c = ((S_80D3B0B8_7 *)source_sprite)->unk_1C;
            ((S_80D3B0B8_3 *)sprite)->unk_1C = sprite_field_1c;
            sprite_field_1e = ((S_80D3B0B8_7 *)source_sprite)->unk_1E;
            ((S_80D3B0B8_3 *)sprite)->unk_0E = 0x80;
            ((S_80D3B0B8_3 *)sprite)->unk_0D = 0x80;
            ((S_80D3B0B8_3 *)sprite)->unk_0C = 0x80;
            ((S_80D3B0B8_3 *)sprite)->unk_1E = sprite_field_1e;
        }
        ((S_80D3B0B8_3 *)sprite)->unk_06 =
            D_800DCECC[((gameWork.view.viewAngle +
                ((S_80D3B0B8_2 *)owner_data)->unk_2A.u + 0x100) >> 9) & 7] * 4;
        ((S_80D3B0B8_2 *)owner_data)->unk_B0++;
        dungeonCreateTrackedEffect(object, 0, sprite + 0x2C, object_data + 0x2A);
    }
}
