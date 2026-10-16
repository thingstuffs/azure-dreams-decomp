#include "common.h"

typedef struct { u8 pad[0x7C]; s32 index; } Owner;
typedef struct { u8 data[0x80]; } Slot;
extern Slot D_8009DDD8[];
extern void func_80404EA0(void *);
extern void func_804053A0(s32);
void func_804054E8(Owner *owner) {
    if (*(s32 *)&D_8009DDD8[owner->index]) {
        func_80404EA0(owner);
    } else {
        func_804053A0((s32)owner);
    }
}
