/* Selector 72, retail file [0x19DF3A0, 0x19DF3F4); complete callable clone. */
#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"

/* Clears flag 0x2000 on every object in the circular list. */
void func_80024BA0(void)
{
    EntityRec *link;
    ObjectNodeHeader *object;
    EntityRec *head;
    s32 link_value;
    s32 next;

    link = D_800814A8;
    /* unk_5C links to the next object's header; its record follows the header */
    next = link->unk_5C;
    link_value = (u32)link;
    next += 0x20;
    link = (EntityRec *)next;
    if (link == (EntityRec *)(u32)link_value) {
        return;
    }
    head = (EntityRec *)(u32)link_value;
    do {
        object = (ObjectNodeHeader *)link - 1;
        next = object->flags;
        next &= 0xDFFF;
        object->flags = next;
        link_value = link->unk_5C;
        link = (EntityRec *)(link_value + 0x20);
    } while (link != head);
}

