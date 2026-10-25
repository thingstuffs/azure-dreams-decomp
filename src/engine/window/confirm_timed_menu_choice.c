#include "common.h"
#include "records/Rec_func_80036210_arg0.h"

#include "common.h"
#include "engine/window.h"
#include "slus.h"

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
    void (*unk_68)(struct S_80036484_0 *);
} S_8003661C_0;   /* arg0 in confirm_timed_menu_choice */

/* Save the object's flags in its linked data and initialize state 0x11. */
void confirm_timed_menu_choice(S_8003661C_0 *object) {
    ((S_8003661C_2 *)(((Rec_func_80036210_arg0 *)object)->unk_74.as_pv))->unk_27 = (u8) object->unk_4D;
    object->unk_64 = 0x11;
    object->unk_68 = &runtime_decrement_countdown_and_reset;
    object->unk_4D = (u8) (object->unk_4D | 0x80);
    SD_Call(0x503);
}
