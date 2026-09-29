#include "common.h"
typedef struct S_80083968
{
    u8 unk00;
    u8 pad1[3];
    s32 unk04;
    u8 unk08[16];
}
S_80083968;
extern S_80083968 D_80083968[32];
extern u8 D_800814D1;
extern void func_8003E758(void);
typedef struct
{
    u8 b[16];
}
S_8003E39C_blk16;
/* Waits for queue space, fills an entry, and advances the write index. */
S_80083968 *func_8003E39C(s16 entry_type, s32 entry_value, s32 payload)
{
    u8 write_index;
    s32 sentinel;
    u8 *queue_index;
    u8 *wait_index;
    S_80083968 *entries;
    queue_index = (u8 *) (&D_800814D1);
    if (((D_800814D1 + 1) & 0x1F) == queue_index[-1]) {
        wait_index = queue_index;
        do {
            func_8003E758();
        }
        while (((D_800814D1 + 1) & 0x1F) == wait_index[-1]);
    }

    entries = D_80083968;
    sentinel = 0xFF;
    write_index = D_800814D1;
    entries[write_index].unk00 = (u8) entry_type;
    entries[write_index].unk04 = entry_value;
    entries[write_index].unk08[15] = 0;
    if ((entry_type & 0xFF) == sentinel) {
        u8 *value_slot;

        value_slot = entries->unk08;
        value_slot += write_index * 24;
        *((s32 *) value_slot) = payload;
    }
    else if (payload == 1) {
        entries[write_index].unk08[15] = sentinel;
    }
    else if (payload != 0) {
        u8 *block_slot;

        block_slot = entries->unk08;
        block_slot += write_index * 24;
        *((S_8003E39C_blk16 *) block_slot) = *((S_8003E39C_blk16 *) payload);
    }
    D_800814D1 = (D_800814D1 + 1) & 0x1F;
    return &D_80083968[write_index];
}
