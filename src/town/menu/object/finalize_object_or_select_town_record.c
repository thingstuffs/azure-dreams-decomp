#include "common.h"
#include "shared/object_flags.h"

typedef struct {
    s32 words[3];
} TownRecord;

extern s32 classify_object_against_bounds(void *object, void *position_data);
extern void unlink_node_if_registered(void *object);

extern s32 D_800D0E44;
extern s32 D_800D0E40[3];
extern TownRecord D_800F8A70[];

/* Clears and flags a handled object, or clamps the town index and selects a record. */
void finalize_object_or_select_town_record(void *object, void *check_context, void *record_holder)
{
    u8 *state_byte;

    if (classify_object_against_bounds(object, check_context) != 0) {
        state_byte = *(u8 **)((u8 *)object + 0x98);
        if (state_byte != 0) {
            *state_byte = 0;
        }
        unlink_node_if_registered(object);
        *(u16 *)((u8 *)object - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
        return;
    }

    if (D_800D0E44 < 0) {
        D_800D0E44 = 0;
    } else if (D_800D0E44 >= 21) {
        D_800D0E44 = 20;
    }
    *(TownRecord **)((u8 *)record_holder + 8) = &D_800F8A70[D_800D0E40[1]];
}
