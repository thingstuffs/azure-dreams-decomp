#include "common.h"
#include "shared/game_work.h"
#include "records/Rec_D_800CFCB4.h"

typedef struct S_8009567C_0 {
    u8 pad_00[0x3A];
    u8 unk_3A;
} S_8009567C_0;

typedef struct S_8009567C_1 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_8009567C_1;


typedef struct S_8009567C_3 {
    u8 pad_00[0x14];
    u8 unk_14;
} S_8009567C_3;


extern s16 D_800D0464;
extern s32 D_800D046C;

extern s16 input_angle_with_offset(s32, s16);

/* Selects an available entry matching the current direction and returns its status. */
s32 select_an_available_entry_matching_direction_returns_status(void *record)
{
    s16 *direction_ptr;
    s16 angle;
    s32 *slot_ptr;
    s32 direction;
    s32 slot;
    u8 entry_type;
    s32 special_type;
    s32 direction_index;
    S_8009567C_3 *entry;

    angle = input_angle_with_offset(g_game_work.buttons, g_game_work.view.camera_rotation.parts.viewAngle);
    if (angle != -1) {
        direction_index = 0;
        direction = ((angle + 0x100) / 0x200) & 7;
        special_type = 1;
        slot_ptr = &D_800D046C;
        direction_ptr = &D_800D0464;
        do {
            if (direction == *direction_ptr) {
                slot = *slot_ptr;
                if (((S_8009567C_0 *)((u8 *)record + slot))->unk_3A != 0) {
                    entry = ((S_8009567C_1 *)((u8 *)record + slot * 4))->unk_1C;
                    ((Rec_D_800CFCB4 *)record)->unk_18 = slot;
                    ((Rec_D_800CFCB4 *)record)->unk_10 = entry;
                    entry_type = entry->unk_14;
                    if (entry_type == special_type) {
                        return -1;
                    }
                    return 1;
                }
            }
            slot_ptr++;
            direction_index++;
            direction_ptr++;
        } while (direction_index < 4);
    }
    return 0;
}
