#include "modules/dungeon_ovl_7e6b7800.h"

void create_textured_offset_object(void *source_object)
{
    s16 local_offset[3];
    u16 world_offset[3];
    s16 scale_component;
    s32 value;
    s32 word_x;
    s32 word_y;
    s32 word_z;
    u16 offset_length;
    u16 offset_angle;
    s32 *link;
    void *source = source_object;
    void *object;
    Row_8194CF00_S_80024700_0 *data;
    void *primitive;
    void *primitive_2;
    s32 angle_or_zero;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        link = D_8002455C;
        (*(s32 * *)((u8 *)object + 0x10)) = link;
        value = (*(s32 *)((u8 *)source + 0));
        data = (u8 *)object + 0x20;
        (*(s32 *)((u8 *)object + 0x20)) = value;
        (*(Row_8194CF00_WordQuad *)((u8 *)object + 0x24)) = (*(Row_8194CF00_WordQuad *)((u8 *)source + 0x4C));
        (*(Row_8194CF00_WordQuad *)((u8 *)object + 0x34)) = (*(Row_8194CF00_WordQuad *)((u8 *)source + 0x5C));

        offset_length = (*(u16 *)((u8 *)source + 0x78));
        angle_or_zero = 0;
        data->unk_2C.u = offset_length;
        offset_angle = (*(u16 *)((u8 *)source + 0x76));
        data->unk_30 = 1;
        data->unk_2E.u = offset_angle;

        primitive = (*(void * *)((u8 *)object + 0xC));
        ((Row_8194CF00_S_80024700_1 *)primitive)->unk_0C.at02.v = 0x40;
        ((Row_8194CF00_S_80024700_1 *)primitive)->unk_0C.at01.v = 0x40;
        ((Row_8194CF00_S_80024700_1 *)primitive)->unk_0C.at00.v = 0x40;
        func_8003DB94(primitive, D_800DE938, angle_or_zero);

        value = 0x2000;
        ((Row_8194CF00_S_80024700_1 *)primitive)->unk_1E = value;
        ((Row_8194CF00_S_80024700_1 *)primitive)->unk_1C = value;
        scale_component = data->unk_24;
        ((Row_8194CF00_S_80024700_1 *)primitive)->unk_14.at02.v = scale_component >> 12;
        scale_component = data->unk_26;
        ((Row_8194CF00_S_80024700_1 *)primitive)->unk_18 = scale_component >> 12;
        angle_or_zero = data->unk_2E.u;
        ((Row_8194CF00_S_80024700_1 *)primitive)->unk_10.u16 |= 0x20;
        ((Row_8194CF00_S_80024700_1 *)primitive)->unk_14.at00.v |= 0xC;
        ((Row_8194CF00_S_80024700_1 *)primitive)->unk_1A = angle_or_zero;
        func_8004491C(object, func_80045340);

        primitive_2 = (*(void * *)((u8 *)object + 8));
        word_x = (*(s32 *)((u8 *)source + 0x34));
        ((Row_8194CF00_S_80024700_1 *)primitive_2)->unk_0C.at00u.v = word_x;
        ((Row_8194CF00_S_80024700_1 *)primitive_2)->unk_00.at00.v = word_x;
        word_y = (*(s32 *)((u8 *)source + 0x38));
        ((Row_8194CF00_S_80024700_1 *)primitive_2)->unk_10.s32 = word_y;
        ((Row_8194CF00_S_80024700_1 *)primitive_2)->unk_04.at00.v = word_y;
        word_z = (*(s32 *)((u8 *)source + 0x3C));
        ((Row_8194CF00_S_80024700_1 *)primitive_2)->unk_14.at00u.v = word_z;
        ((Row_8194CF00_S_80024700_1 *)primitive_2)->unk_08.at00.v = word_z;

        local_offset[0] = ((func_800644B8(data->unk_2E.s) >> 4) *
            data->unk_2C.s) >> 8;
        local_offset[1] = ((func_80064584(data->unk_2E.s) >> 4) *
            data->unk_2C.s) >> 8;
        local_offset[2] = 0;
        func_800649A0();
        func_80064B30((u8 *)object + 0x24, local_offset, world_offset);
        func_80064A40();

        ((Row_8194CF00_S_80024700_1 *)primitive_2)->unk_00.at02.v += world_offset[0];
        ((Row_8194CF00_S_80024700_1 *)primitive_2)->unk_04.at02.v += world_offset[1];
        ((Row_8194CF00_S_80024700_1 *)primitive_2)->unk_08.at02.v += world_offset[2];
    }
}
