#include "common.h"

typedef struct { u8 pad[0x7C]; s32 index; } Owner;
typedef struct { u8 data[0x80]; } Slot;
extern Slot D_8009DDD8[];
extern void card_build_selected_slot_details(void *);
extern void build_memory_task_text(s32);
void select_memory_task_exit(Owner *owner) {
    if (*(s32 *)&D_8009DDD8[owner->index]) {
        card_build_selected_slot_details(owner);
    } else {
        build_memory_task_text((s32)owner);
    }
}
