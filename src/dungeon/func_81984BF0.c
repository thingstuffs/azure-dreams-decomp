#include "modules/dungeon_ovl_19a332c.h"

void func_800263F0(void *unused_actor)
{
    void *link;
    void *object;
    void *head;
    s32 link_value;
    s32 next;

    link = D_800814A8;
    next = ((ovl_19a332c_81984BF0_S_81984BF0_0 *)link)->unk_5C;
    link_value = (u32)link;
    next += 0x20;
    link = next;
    if (link == (void *)(u32)link_value) {
        return;
    }
    head = (void *)(u32)link_value;
    do {
        object = link - 0x20;
        next = ((ovl_19a332c_81984BF0_S_81984BF0_1 *)object)->unk_1E;
        next &= 0xDFFF;
        ((ovl_19a332c_81984BF0_S_81984BF0_1 *)object)->unk_1E = next;
        link_value = ((ovl_19a332c_81984BF0_S_81984BF0_0 *)link)->unk_5C;
        link = (void *)(link_value + 0x20);
    } while (link != head);
}
