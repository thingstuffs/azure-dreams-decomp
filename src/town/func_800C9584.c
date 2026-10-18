#include "common.h"
#include "shared/object_flags.h"
#include "shared/types3b_types.h"




extern s32 func_800644B8(s32 angle);
extern s32 func_80064584(s32 angle);
extern s32 check_actor_data_references_match(void *actor);
extern void func_80033D08(void *object);

/* Computes an offset position from the linked object, flagging failed validation. */
void compute_offset_position_linked_object(void *object, IntVector3 *out_pos)
{
    void *linked_object = *(void **)((u8 *)object + 0x9C);
    IntVector3 *base_pos = *(IntVector3 **)((u8 *)linked_object - 0x18);

    if (check_actor_data_references_match(linked_object) == 0) {
        func_80033D08(object);
        *(u16 *)((u8 *)object - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
        return;
    }
    out_pos->x = base_pos->x + func_800644B8(*(s16 *)((u8 *)*(void **)((u8 *)object + 0x9C) + 0x72)) * 0x140;
    out_pos->y = base_pos->y + func_80064584(*(s16 *)((u8 *)*(void **)((u8 *)object + 0x9C) + 0x72)) * 0x140;
    out_pos->z = base_pos->z + (s32)0xFFE60000;
}
