#include "common.h"

#include "common.h"

typedef struct S_80036880_1 {
    u8 pad_00[0x74];
    void * unk_74;
} S_80036880_1;   /* arg0 in confirm_list_menu_choice */

typedef struct S_80036880_2 {
    u8 pad_00[0x27];
    u8 unk_27;
} S_80036880_2;   /* ((S_80036880_1 *)arg0)->unk_74 in confirm_list_menu_choice */


typedef struct S_80036880_0 {
    u8 pad_00[0x4D];
    u8 unk_4D;
    u8 pad_4E[0x16];
    s16 unk_64;
    u8 pad_66[0x2];
    s32 * unk_68;
} S_80036880_0;   /* arg0 in confirm_list_menu_choice */
short SD_Call(int flags);                     /* extern */
void runtime_decrement_countdown_and_reset();

/* Save the object's flags, install state 0x11 and its handler, and set flag 0x80. */
void confirm_list_menu_choice(S_80036880_0 *object) {
    ((S_80036880_2 *)(((S_80036880_1 *)object)->unk_74))->unk_27 = (u8) object->unk_4D;
    object->unk_64 = 0x11;
    object->unk_68 = &runtime_decrement_countdown_and_reset;
    object->unk_4D = (u8) (object->unk_4D | 0x80);
    SD_Call(0x503);
}
