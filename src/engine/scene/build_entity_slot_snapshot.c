#include "common.h"
#include "engine/scene.h"
#include "slus.h"
#include "engine/entity.h"

/* "self" object updated by this function (destination of the field copy). */
typedef struct S_800422DC_Self {
    u8  pad0[0x4C];
    u8  f4C;
    u8  f4D;
    u8  pad4E[2];
    s32 f50;
} S_800422DC_Self;

/* "other" object read/prepped by this function (source of the field copy). */
typedef struct S_800422DC_Other {
    u8  pad0[0x13];
    u8  f13;
    u8  pad14[0x1C - 0x14];
    s32 f1C;
    u8  pad20[0x25 - 0x20];
    u8  f25;
    u8  pad26[0x4C - 0x26];
    s32 f4C;
    s32 f50;
    s32 f54;
} S_800422DC_Other;

extern int  find_slot_by_type(void *a0, int a1);

/* Prepare source slot state and copy it into a snapshot with resolved slot indices. */
void build_entity_slot_snapshot(S_800422DC_Self *snapshot, S_800422DC_Other *source)
{
    clear_slots_of_type(source, 0x1A);
    find_slot_by_type(source, 0x1B);
    clear_slots_of_type(source, 0x1C);
    clear_slots_of_type(source, 0x1D);

    if (source->f25 == 0) {
        if (source->f13 != 0) {
            source->f1C |= 8;
        }
    }

    copy_words_forward((int *)snapshot, (int *)source, 0x13);

    snapshot->f4C = (u8)get_bounded_stride_index((unsigned int)source->f4C, 0x80010248, 4, 0x14);
    snapshot->f4D = (u8)get_bounded_stride_index((unsigned int)source->f50, 0x80010248, 4, 0x14);
    snapshot->f50 = source->f54;
}
