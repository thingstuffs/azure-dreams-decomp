/* Relink of matched dungeon/func_80A9E9D0; every changed retail word is a paired relocation. */
#define create_tinted_rotated_sprite func_801501D0
#define D_80174D08 D_80150D08
#define advance_object_angle_and_height D_80150180
#include "modules/dungeon_resource08_slot0.h"
extern s32 rand(void);

void func_801501D0(s32 unused_0, R08_801741D0_S_801741D0_3 *source_pos, s32 unused_2, s8 green, u8 red_blue)
{
    void *node;
    R08_801741D0_S_801741D0_1 *sprite;
    R08_801741D0_S_801741D0_2 *position;
    u8 *node_params;

    node = func_8003FC64(0x212);
    if (node != NULL) {
        ((R08_801741D0_S_801741D0_0 *)node)->unk_10 = ((u8 *)advance_object_angle_and_height);
        func_8004491C(node, func_80045340);

        sprite = ((R08_801741D0_S_801741D0_0 *)node)->unk_0C;
        sprite->unk_10 = 0x60;
        sprite->unk_14 |= 0xC;

        position = ((R08_801741D0_S_801741D0_0 *)node)->unk_08;
        position->unk_02 = source_pos->unk_02;
        position->unk_06 = source_pos->unk_06;
        position->unk_0A = source_pos->unk_0A - 0x28;

        sprite = ((R08_801741D0_S_801741D0_0 *)node)->unk_0C;
        sprite->unk_1E = 0x400;
        sprite->unk_1C = 0x400;
        sprite->unk_06 = 6;
        node_params = (u8 *)node + 0x20;
        ((R08_801741D0_S_801741D0_0 *)node)->unk_20 = 0x70;
        node_params[1] = 0x10;
        node_params[2] = 0x10;
        sprite->unk_0D = green;
        sprite->unk_0C = red_blue;
        sprite->unk_0E = red_blue;
        sprite->unk_1A = rand() & 0xFFF;

        memcpy((u8 *)node + 0x48, ((u8 *)D_80150D08), 12);
        sprite->unk_08 = (u8 *)node + 0x48;
    }
}
