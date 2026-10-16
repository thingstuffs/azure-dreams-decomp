#include "common.h"

typedef struct { u8 pad[0x7C]; s32 index; } Owner;
typedef struct { u8 data[0x80]; } Slot;
extern Slot D_8009DDD8[];
extern void cardBuildSelectedSlotDetails(void *);
extern void townBuildMemoryTaskText(s32);
void townSelectMemoryTaskExit(Owner *owner) {
    if (*(s32 *)&D_8009DDD8[owner->index]) {
        cardBuildSelectedSlotDetails(owner);
    } else {
        townBuildMemoryTaskText((s32)owner);
    }
}
