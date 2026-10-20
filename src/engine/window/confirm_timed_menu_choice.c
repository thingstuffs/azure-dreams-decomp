#include "common.h"

#include "common.h"

typedef struct S_8003661C_1 {
    u8 pad_00[0x74];
    void * unk_74;
} S_8003661C_1;   /* arg0 in confirm_timed_menu_choice */

typedef struct S_8003661C_2 {
    u8 pad_00[0x27];
    u8 unk_27;
} S_8003661C_2;   /* ((S_8003661C_1 *)arg0)->unk_74 in confirm_timed_menu_choice */


typedef struct S_8003661C_0 {
    u8 pad_00[0x4D];
    u8 unk_4D;
    u8 pad_4E[0x16];
    s16 unk_64;
    u8 pad_66[0x2];
    s32 * unk_68;
} S_8003661C_0;   /* arg0 in confirm_timed_menu_choice */


short SD_Call(int flags);
void runtime_decrement_countdown_and_reset();

/* Save the object's flags in its linked data and initialize state 0x11. */
void confirm_timed_menu_choice(S_8003661C_0 *object) {
    ((S_8003661C_2 *)(((S_8003661C_1 *)object)->unk_74))->unk_27 = (u8) object->unk_4D;
    object->unk_64 = 0x11;
    object->unk_68 = &runtime_decrement_countdown_and_reset;
    object->unk_4D = (u8) (object->unk_4D | 0x80);
    SD_Call(0x503);
}
