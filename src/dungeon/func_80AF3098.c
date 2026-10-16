#include "modules/dungeon_resource10_slot0.h"

void func_80174898(void *action, void *position, void *sprite, EntityRec *entity)
{
    R10_80174898_OffsetTable direction_offsets = (*(R10_80174898_OffsetTable *)&D_80170854);
    s32 offset_coord;

    switch (((R10_80174898_S_80174898_0 *)action)->unk_9B) {
    case 0:
        ((R10_80174898_S_80174898_1 *)position)->unk_14 = 0;
        ((R10_80174898_S_80174898_1 *)position)->unk_10 = 0;
        ((R10_80174898_S_80174898_1 *)position)->unk_0C = 0;
        ((R10_80174898_S_80174898_0 *)action)->unk_96 = 0x14;
        ((R10_80174898_S_80174898_0 *)action)->unk_9B++;
        break;

    case 1:
        if ((--((R10_80174898_S_80174898_0 *)action)->unk_96 == 0x11) ||
            (((R10_80174898_S_80174898_2 *)sprite)->unk_14 & 0x8000)) {
            R10_80174898_OffsetPair *direction_offset;
            u16 flags;
            s32 height;
            s32 target_x;
            s32 tile_x;
            s32 y_offset;
            s32 x_offset;

            flags = ((R10_80174898_S_80174898_2 *)sprite)->unk_14;
            ((R10_80174898_S_80174898_2 *)sprite)->unk_14 = flags | 0x0800;
            height = ((R10_80174898_S_80174898_1 *)position)->unk_0A;
            tile_x = ((R10_80174898_S_80174898_2 *)sprite)->unk_24;
            direction_offset = &direction_offsets.entries[(((u16)entity->facing) >> 9) & 7];
            x_offset = direction_offset->x;
            target_x = tile_x + x_offset;
            y_offset = direction_offset->y;
            offset_coord = ((R10_80174898_S_80174898_2 *)sprite)->unk_25 + y_offset;
            target_x = target_x & 0xFFFF;
            func_80174670(entity, target_x, offset_coord & 0xFFFF, height);
        }
        if ((((R10_80174898_S_80174898_0 *)action)->unk_96 == 0x0A) ||
            (((R10_80174898_S_80174898_2 *)sprite)->unk_14 & 0x8000)) {
            ((R10_80174898_S_80174898_2 *)sprite)->unk_14 &= 0xF7FF;
            func_800A56E0(0x606);
        }
        if ((((R10_80174898_S_80174898_0 *)action)->unk_96 == 9) ||
            (((R10_80174898_S_80174898_2 *)sprite)->unk_14 & 0x8000)) {
            R10_80174898_OffsetPair *direction_offset;
            u16 angle;
            s32 height;
            s32 tile_x;
            s32 x;
            s32 target_x;
            s32 y_offset;

            angle = ((u16)entity->facing);
            direction_offset = direction_offsets.entries + ((angle >> 9) & 7);
            height = ((R10_80174898_S_80174898_1 *)position)->unk_0A;
            tile_x = ((R10_80174898_S_80174898_2 *)sprite)->unk_24;
            offset_coord = direction_offset->x;
            target_x = tile_x + offset_coord;
            y_offset = direction_offset->y;
            offset_coord = ((R10_80174898_S_80174898_2 *)sprite)->unk_25 + y_offset;
            x = target_x & 0xFFFF;
            func_8017442C(entity, x, offset_coord & 0xFFFF, height);
        }
        if ((((R10_80174898_S_80174898_0 *)action)->unk_96 <= 0) ||
            (((R10_80174898_S_80174898_2 *)sprite)->unk_14 & 0x8000)) {
            ((R10_80174898_S_80174898_0 *)action)->unk_96 = 0;
            ((R10_80174898_S_80174898_0 *)action)->unk_9B++;
        }
        break;

    case 2:
        if (((R10_80174898_S_80174898_2 *)sprite)->unk_14 & 0xE000) {
            ((R10_80174898_S_80174898_1 *)position)->unk_14 = 0;
            ((R10_80174898_S_80174898_1 *)position)->unk_10 = 0;
            ((R10_80174898_S_80174898_1 *)position)->unk_0C = 0;
            func_800A2B04(position,
                ((R10_80174898_S_80174898_2 *)sprite)->unk_24, ((R10_80174898_S_80174898_2 *)sprite)->unk_25);
            if (((R10_80174898_S_80174898_2 *)sprite)->unk_2C != ((u8 *)D_80175988)) {
                ((R10_80174898_S_80174898_2 *)sprite)->unk_2C = ((u8 *)D_80175988);
                ((R10_80174898_S_80174898_2 *)sprite)->unk_14 &= 0xF7FF;
                func_80047784(sprite,
                    ((R10_80174898_S_80174898_2 *)sprite)->unk_2C[((gameWork.view.viewAngle +
                        entity->facing + 0x100) >> 9) & 7],
                    0);
                ((R10_80174898_S_80174898_0 *)action)->unk_9B++;
            }
        }
        break;

    case 3:
        func_800AD594(entity, 0x400);
        ((R10_80174898_S_80174898_0 *)action)->unk_8C = ((void *)func_801717F4);
        dungeonStatus.unk_0C = 0;
        (entity->unk_46) &= 0x7FFF;
        break;
    }
}

