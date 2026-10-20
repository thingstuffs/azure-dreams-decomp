#include "common.h"
#include "shared/object_index_slots.h"
#include "shared/object_flags.h"

typedef struct {
    u8 pad_00[0x72];
    s16 angle;
} Inner;

typedef struct {
    u8 pad_00[8];
    u16 *coords;
    u8 pad_0C[0x14];
    Inner inner;
} Object;

typedef struct {
    s32 unk_0;
    Object *object;
} ObjectSlot;

extern s32 service_script_controller(void);
extern void unlink_node_if_registered(void *);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);


/* Place the part's follow coordinates: when the mode query is off, detach it and raise its busy flags; otherwise offset the output from the anchor object's position by the anchor's angle. */
void update_linked_part_position(u16 *part, u16 *out_coords)
{
    u8 index = ((u8 *)part)[0x60];
    Object *object;
    Inner *inner;
    u16 *coords;

    if (service_script_controller() == 0) {
        unlink_node_if_registered(part);
        part[-1] |= 0x8000;
        object_flag_block.flags |= 0x8000;
        return;
    }

    if (index != 0) {
        object = object_index_slots[index].object;
        if (object != 0) {
            inner = &object->inner;
            coords = object->coords;
            out_coords[1] = coords[1] + func_800644B8(inner->angle + 0x200) / 170;
            out_coords[3] = coords[3] + func_80064584(inner->angle + 0x200) / 170;
            out_coords[5] = coords[5] - 46;
        }
    }
}
