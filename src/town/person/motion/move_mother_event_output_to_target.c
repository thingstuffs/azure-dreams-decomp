#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/dungeon_moving_views.h"


extern void *D_800834A0;

#include "town/person/object_setup.h"


typedef struct S_800C7CF0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800C7CF0_2;   /* out in move_mother_event_output_to_target */

/* Move the output toward the target position until the object countdown expires. */
void move_mother_event_output_to_target(void *object, void *out, void *setup_context) {
    s16 signed_frames;
    u16 target_x;
    u16 target_y;
    u16 frames;

    target_x = ((MovingPosition *)D_800834A0)->x;
    target_y = ((MovingPosition *)D_800834A0)->y - 0x42;
    frames = ((Rec_func_80094268_arg0 *)object)->unk_6C.as_u16 - 1;
    ((Rec_func_80094268_arg0 *)object)->unk_6C.as_u16 = frames;
    signed_frames = (s32)((u32)frames << 16) >> 16;

    if (signed_frames <= 0) {
        apply_object_setup_and_update(object, out, setup_context);
        ((S_800C7CF0_2 *)out)->unk_02 = target_x;
        ((S_800C7CF0_2 *)out)->unk_06 = target_y;
        return;
    }

    ((S_800C7CF0_2 *)out)->unk_02 =
        (u16)(((S_800C7CF0_2 *)out)->unk_02 +
              ((s16)target_x - (s16)((S_800C7CF0_2 *)out)->unk_02) /
              signed_frames);
    ((S_800C7CF0_2 *)out)->unk_06 =
        (s16)((u16)((S_800C7CF0_2 *)out)->unk_06 +
              ((s16)target_y - ((S_800C7CF0_2 *)out)->unk_06) /
              (s16)((Rec_func_80094268_arg0 *)object)->unk_6C.as_u16);
}
