#include "common.h"
#include "shared/object_node.h"

extern void *allocate_list_node();
extern s32 D_800C4E00[4];

/* Creates an object with the D_800C4E00 table and initializes its payload fields. */
void *create_timed_region_flag_expiry(s32 unused0, s32 unused1, s32 unused2, s16 payloadValueA, s16 payloadValueC) {
    void *object;
    void *payload;

    object = allocate_list_node(0, ((s32 *)&scene_object_list_anchor.next));
    if (object != 0) {
        *(s32 **)((s8 *)object + 0x10) = &D_800C4E00[0];
        payload = (s8 *)object + 0x20;
        *(s16 *)((s8 *)payload + 8) = 0x40;
        *(s16 *)((s8 *)payload + 0xA) = payloadValueA;
        *(s16 *)((s8 *)payload + 0xC) = payloadValueC;
    }
    return object;
}
