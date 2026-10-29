#include "common.h"
#include "town/scene/motion/offset_queries.h"
#include "town/scene/motion.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} UnkStruct;

extern s16 find_minimum_sampled_position(UnkStruct *, s32 *, s32);
extern s32 D_800CFD98[];

/*
 * Copies the position with its stored Y offset subtracted and returns the minimum of two samples
 * using D_800CFD98.
 */
s16 check_the_position_second_coordinate_adjusted_stored_offset(void *source_record) {
    UnkStruct adjusted_position;

    adjusted_position.unk0 = *(s32 *)((u8 *)source_record + 0);
    adjusted_position.unk4 = *(s32 *)((u8 *)source_record + 4) - *(s32 *)((u8 *)source_record + 0x10);
    adjusted_position.unk8 = *(s32 *)((u8 *)source_record + 8);
    return find_minimum_sampled_position(&adjusted_position, &D_800CFD98[0], 2);
}
