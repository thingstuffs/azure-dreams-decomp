#include "common.h"
#include "town/scene/flags.h"


extern s32 scene_object_flags;


typedef struct S_80810F98_0 {
    s16 unk_00;
    u8 pad_02[0x2];
    void * unk_04;
    s32 unk_08;
} S_80810F98_0;   /* ptr in fade_scene_color_after_linked_flag */

typedef struct S_80810F98_1 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_80810F98_1;   /* object in fade_scene_color_after_linked_flag */

/* After linked flag 2 is set, subtracts 0x080808 per update and retires the node at <= 0x080808. */
void fade_scene_color_after_linked_flag(S_80810F98_0 *ptr)
{
    s16 state;
    S_80810F98_1 *object;

    state = ptr->unk_00;
    object = ptr->unk_04;
    switch (state) {
    case 0:
        if (object->unk_0C & 2) {
            ptr->unk_00 = state + 1;
        }
        break;
    case 1:
        ptr->unk_08 -= 0x80808;
        if (ptr->unk_08 <= 0x80808) {
            *(u16 *)((u8 *)ptr - 2) |= 0x8000;
            scene_object_flags |= 0x8000;
        }
        break;
    }
}
