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

typedef struct {
    /* 0x00 */ u8 pad00[0xC];
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ u8 pad10[2];
    /* 0x12 */ u16 unk12;
    /* 0x14 */ u8 pad14[4];
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
} Sound;

extern S_80086A40 D_80086A40[16];
extern s32 D_8007382C[3]; /* size > 8: forced hi/lo, no $gp */
extern void func_8005A1D0(s32);
extern s32 func_80059E94(s32);

/* Initializes a requested or free sound slot and returns its index. */
s32 func_8005A608(Sound *sound, s16 requested_slot)
{
    s16 slot_index;
    s16 selected_slot;
    s32 result_index;
    S_80086A40 *slot;

    D_8007382C[0] = 0;
    slot_index = 0;
    selected_slot = requested_slot;
    if (selected_slot == -1) {
        do {
            if (D_80086A40[slot_index].marker == -1) {
                goto found;
            }
            slot_index++;
        } while (slot_index < 16);
        return -1;
    }
    slot_index = selected_slot;
    if (D_80086A40[slot_index].marker != -1) {
        func_8005A1D0(D_80086A40[slot_index].unk10);
    }
found:
    result_index = slot_index;
    slot = &D_80086A40[result_index];
    slot->marker = slot_index;
    slot->unk04 = (s32)sound;
    slot->unk08 = (sound->unk12 << 9) + 0xA20;
    slot->unk14 = sound->unk0C - slot->unk08;
    slot->unk18 = sound->unk18;
    slot->unk1B = sound->unk19;
    slot->unk10 = func_80059E94(slot->unk14);
    if (slot->unk10 == -1) {
        return -1;
    }
    return result_index;
}
