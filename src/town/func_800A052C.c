#include "town/menu/window.h"

/* Sets the object state for the selected mode and flags. */
void set_object_state_for_mode(void *owner, void *object, s32 mode, s32 flags) {
    if (mode == 2) {
        ((Rec_func_80094268_arg0 *)owner)->unk_93 = 1;
        (*(s32 *)((u8 *)object + (0x28))) = D_80081458[0];
        select_sprite_entry(object, D_800D07AC, 0);
        return;
    }
    func_8003DB94(object, D_800D07A4[mode], 0);
    if (flags & 2) {
        ((Rec_D_80082E80 *)object)->unk_12.at00_s16.v = 0x100;
        return;
    }
    if (flags & 4) {
        ((Rec_D_80082E80 *)object)->unk_12.at00_s16.v = 0x200;
        return;
    }
    ((Rec_D_80082E80 *)object)->unk_12.at00_s16.v = 0;
}
