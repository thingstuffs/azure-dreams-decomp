#include "common.h"
#include "shared/object_flags.h"

typedef struct S_800AEFD8_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
} S_800AEFD8_0;   /* object in townCreateItemMenuChildAtPosition */

typedef struct S_800AEFD8_1 {
    u8 pad_00[0xD4];
    void * unk_D4;
    void * unk_D8;
} S_800AEFD8_1;   /* payload in townCreateItemMenuChildAtPosition */

extern void *func_8003FD64(s32 value, void *parent);
extern s32 townLoadItemMenuDisplayResource(void *payload, s32 value);
extern void *townLinkItemMenuDisplayEntries(void *value);
extern void townInitializeItemMenuListDisplay(void *payload, void *parent, s32 resource_id, s32 resource_data,
                          s32 x, s32 y, s32 context);
extern void func_8004491C(void *object, void *callback);
extern void func_8004B248(void *address);
extern void func_8004CAA0(void);
extern void townAdvanceItemMenuObjectAnimation(void);


/* Create and initialize a child object at (x, y), marking allocation failure for cleanup. */
void *townCreateItemMenuChildAtPosition(void *parent, s32 x, s32 y, s32 resource_id,
                    s32 resource_data, s32 context)
{
    void *object;
    S_800AEFD8_1 *payload;

    object = func_8003FD64(0, parent);
    if (object != 0) {
        payload = (u8 *)object + 0x20;
        if (townLoadItemMenuDisplayResource(payload, 0x1A) != 0) {
            ((S_800AEFD8_0 *)object)->unk_0C = (u8 *)object + 0xE8;
            payload->unk_D4 = townLinkItemMenuDisplayEntries(payload->unk_D8);
            townInitializeItemMenuListDisplay(payload, parent, resource_id, resource_data, x, y, context);
            func_8004491C(object, func_8004CAA0);
            ((S_800AEFD8_0 *)object)->unk_10 = townAdvanceItemMenuObjectAnimation;
        } else {
            func_8004B248((u8 *)object + 0xFC);
            ((S_800AEFD8_0 *)object)->unk_1E |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
            object = 0;
        }
    }
    return object;
}
