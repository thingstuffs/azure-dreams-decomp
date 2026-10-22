#include "common.h"
#include "shared/object_flags.h"
#include "frontend/libcard/message.h"

extern s32 D_80028808[4];

// Optionally flags the linked record, processes the global record, and sets status bits.
s32 card_boot_close_message_dialog(s32 flagLinkedRecord) {
    void *record = &D_80028808[0];
    if (flagLinkedRecord != 0) {
        void *linkedRecord = *(void **)((u8 *) record + 0x14);
        *(u16 *)((u8 *) linkedRecord + 0x1E) |= 0x2000;
    }
    card_boot_release_five_message_entries(record);
    *(u16 *)((u8 *) record - 2) |= NODE_REMOVE;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    return D_80028808[0];
}
