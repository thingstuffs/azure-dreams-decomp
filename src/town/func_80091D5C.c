#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} UnkStruct;

extern s16 get_maximum_sampled_offset_value(UnkStruct *, s32 *, s32);
extern s32 D_800CFDB8[];

/* Check the position with its second coordinate adjusted by the stored offset. */
s16 query_position_with_second_component_offset(void *source_record) {
    UnkStruct adjusted_position;

    adjusted_position.unk0 = *(s32 *)((u8 *)source_record + 0);
    adjusted_position.unk4 = *(s32 *)((u8 *)source_record + 4) - *(s32 *)((u8 *)source_record + 0x10);
    adjusted_position.unk8 = *(s32 *)((u8 *)source_record + 8);
    return get_maximum_sampled_offset_value(&adjusted_position, &D_800CFDB8[0], 2);
}
