#include "common.h"
#include "m2c_compat.h"
#include "shared/dungeon_delay_views.h"

void configure_the_set_mode_n_1();         /* extern */
s32 get_transform_entry_by_index();                         /* extern */
extern s32 D_8006ADD4;
extern M2C_UNK D_800C2A10;

   /* motion in update_transform_motion_page */

typedef struct S_800C2988_1 {
    u8 pad_00[0x16];
    s16 unk_16;
    u8 pad_18[0x38];
    s32 * unk_50;
    u8 pad_54[0x1E];
    u16 unk_72;
} S_800C2988_1;   /* object in update_transform_motion_page */

/* Sets the motion page and updates the object state and orientation. */
void update_transform_motion_page(void *object_data, void *motion_data) {
    register DelayMotionZ *motion = motion_data;

    u32 page;

    if (D_8006ADD4 == 0x17000C) {
        motion->unk_08 = 0xFF600000;
    } else {
        motion->unk_08 = 0xFFE00000;
    }
    configure_the_set_mode_n_1(((S_800C2988_1 *)(object_data)), motion, get_transform_entry_by_index(0));
    ((S_800C2988_1 *)(object_data))->unk_50 = &D_800C2A10;
    ((S_800C2988_1 *)(object_data))->unk_16 = (s16) ((((S_800C2988_1 *)(object_data))->unk_72 - 0x800) & 0xFFF);
}
