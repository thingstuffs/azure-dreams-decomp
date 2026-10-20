#include "common.h"
#include "shared/entity_objects.h"

typedef struct {
    u8 pad0;
    u8 field1;
    u8 pad2[6];
} Slot;

extern Slot object_index_slots[];
extern void copy_global_position_output_offset(void);

/* Move coordinates halfway toward the target and advance state when the timer expires. */
void move_coordinates_halfway_toward_target(void *state, s32 *coords) {
    s32 target;
    s32 value;
    s32 value2;
    u16 timer;

    target = D_80083780.x.v;
    value = coords[0];
    coords[0] = value + ((target - value) / 2);
    target = D_80083780.y.v;
    value2 = coords[1];
    coords[1] = value2 + ((target - value2) / 2);

    timer = *(u16 *)((u8 *)state + 0x6C) - 1;
    *(u16 *)((u8 *)state + 0x6C) = timer;
    if ((s16)timer <= 0) {
        *(void (**)(void))((u8 *)state + 0x54) = copy_global_position_output_offset;
        object_index_slots[*(s32 *)((u8 *)state + 0x60)].field1 = 0;
    }
}
