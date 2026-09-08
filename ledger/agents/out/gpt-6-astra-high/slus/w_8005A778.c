#include "common.h"

typedef struct S_8005A778_D80086A40 {
    s16 unk00;
    u8 pad02[2];
    void *unk04;
    s32 unk08;
    u8 pad0C[4];
    s32 unk10;
    s32 unk14;
    u8 unk18;
    u8 pad19[2];
    u8 unk1B;
} S_8005A778_D80086A40;

typedef struct S_8007382C {
    s32 unk00;
    u8 pad04[8];
} S_8007382C;

typedef struct S_8005A778_Arg0 {
    u8 pad00[0xC];
    s32 unk0C;
    u8 pad10[2];
    u16 unk12;
    u8 pad14[4];
    u8 unk18;
    u8 unk19;
} S_8005A778_Arg0;

extern S_8005A778_D80086A40 D_80086A40[16];
extern S_8007382C D_8007382C;

extern void func_8005A1D0(s32 arg0);
extern s32 func_80059F8C(void *arg0, s32 arg1);

/* Initializes a free or requested slot from the header and returns its index. */
s32 func_8005A778(S_8005A778_Arg0 *header, s32 requested_slot, void *payload)
{
    s16 slot;
    s32 result;
    register s32 raw_slot ASM_REG("$3");   /* MATCH pin: slus-diff */
    s32 offset_blocks;
    S_8005A778_D80086A40 *entry;
    S_8005A778_Arg0 *header_fields;

    slot = 0;
    D_8007382C.unk00 = 0;
    raw_slot = requested_slot;
    ASM_KEEP_NV(raw_slot);   /* MATCH pin: slus-diff */
    header_fields = header;
    ASM_KEEP_NV(header_fields);   /* MATCH pin: slus-diff */
    requested_slot <<= 16;
    requested_slot >>= 16;

    if (requested_slot == -1) {
        for (;;) {
            if (D_80086A40[slot].unk00 == -1) {
                goto found;
            }
            slot = slot + 1;
            if (slot >= 16) {
                return -1;
            }
        }
    } else {
        S_8005A778_D80086A40 *slots;
        S_8005A778_D80086A40 *old_entry;

        slot = raw_slot;
        if (slot >= 16) {
            return -1;
        }
        slots = D_80086A40;
        old_entry = &slots[slot];
        if (old_entry->unk00 != -1) {
            func_8005A1D0(old_entry->unk10);
        }
    }

found:
    entry = &D_80086A40[slot];
    entry->unk00 = (s16)slot;
    entry->unk04 = header;
    offset_blocks = header_fields->unk12;
    entry->unk10 = (s32)payload;
    entry->unk08 = (offset_blocks << 9) + 0xA20;
    entry->unk14 = header_fields->unk0C - *(volatile s32 *)&entry->unk08;
    entry->unk18 = header_fields->unk18;
    entry->unk1B = header_fields->unk19;

    result = (entry->unk10 = func_80059F8C(payload, entry->unk14));
    if (result == -1) {
        return -1;
    }
    return slot;
}
