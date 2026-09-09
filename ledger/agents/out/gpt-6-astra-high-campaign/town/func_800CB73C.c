/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef void (*Callback)(void *, s32, void *);

M2C_UNK func_800C2C80();
M2C_UNK func_800C2CB0();
s32 func_800C2E1C();
s32 func_800C2F14();

/* Run the object callback and update its selected entry and record flags when enabled. */
void func_800C8E9C(void *object, void *context, Rec_D_80082E80 *record) {
    s32 entry_index;
    u16 flags;

    (*(Callback *)((u8 *)object + 0x50))(object, context, record);
    if (!((*(u16 *)((u8 *)object + -2)) & 0x8000)) {
        entry_index = func_800C2E1C((*(s16 *)((u8 *)object + 0x72)), (*(s16 *)((u8 *)object + 0x64)));
        if ((*(s16 *)((u8 *)object + 0x74)) != entry_index) {
            func_800C2CB0(object, record, (*(M2C_UNK **)((u8 *)object + 0x78))[entry_index], record->unk_04.as_s8);
            (*(s16 *)((u8 *)object + 0x74)) = entry_index;
        }
        if ((func_800C2F14((*(s16 *)((u8 *)object + 0x72)), (*(s16 *)((u8 *)object + 0x64))) << 0x10) != 0) {
            flags = record->unk_14.at00_u16.v | 1;
        } else {
            flags = record->unk_14.at00_u16.v & 0xFFFE;
        }
        record->unk_14.at00_u16.v = flags;
        func_800C2C80(object, record, 0, 0);
    }
}
