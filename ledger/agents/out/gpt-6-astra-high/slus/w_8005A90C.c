#include "common.h"

typedef struct {
    /* 0x00 */ s16 marker;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
} S_80086A40;

extern S_80086A40 D_80086A40[16];
extern s32 D_8007382C[3]; /* size > 8: forced hi/lo, no $gp */

extern void func_8005A1D0(s32);
extern s32 func_80059F8C(s32, s32);
extern s32 func_8005ECA0(s32);
extern s32 func_8005EC40(s32, u32);

/* Reserves a sound slot and transfers sample data to the requested sound RAM address. */
s32 func_8005A90C(s32 src_addr, s32 sound_addr, s32 size, s16 requested_slot)
{
    s16 slot_id;
    s16 selected_slot;
    s32 slot_index;
    S_80086A40 *slot;
    s32 reserved_addr;
    s32 reserve_size;

    D_8007382C[0] = 0;
    slot_id = 0;
    selected_slot = requested_slot;
    if (selected_slot == -1) {
        do {
            if (D_80086A40[slot_id].marker == -1) {
                goto found;
            }
            slot_id++;
        } while (slot_id < 16);
        return -1;
    }
    slot_id = selected_slot;
    if (D_80086A40[slot_id].marker != -1) {
        func_8005A1D0(D_80086A40[slot_id].unk10);
    }
found:
    slot_index = slot_id;
    slot = &D_80086A40[slot_index];

    slot->unk14 = size;
    ASM_SCHED_BARRIER();   /* MATCH pin: slus-diff */
    slot->marker = slot_id;
    slot->unk04 = src_addr;
    slot->unk08 = size;
    reserve_size = size;
    ASM_KEEP_NV(reserve_size);   /* MATCH pin: slus-diff */
    reserved_addr = sound_addr;
    slot->unk18 = 0x7F;
    slot->unk1B = 0x40;
    slot->unk10 = reserved_addr;
    reserved_addr = func_80059F8C(reserved_addr, reserve_size);
    slot->unk10 = reserved_addr;
    if (reserved_addr == -1) {
        return -1;
    }
    sound_addr = func_8005ECA0(reserved_addr);
    if (func_8005EC40(src_addr, slot->unk14) != slot->unk14) {
        return -1;
    }
    slot->unk0C = src_addr;
    reserved_addr = sound_addr;
    slot->unk10 = reserved_addr;
    return slot_index;
}
