#include "common.h"



extern s32 test_sound_channel_availability(s16 bit_index);
extern void sound_start_scaled_primary_and_secondary_voices(s32 a0, s32 a1);
extern void func_80055730(void);

/* Decode a packed selector and dispatch its index and offset if its code is available. */
void decode_audio_selector(s32 selector) {
    /* Pin keeps andi a0,a0 (not CSE-from-saved_selector) and value temps in $v0. */
    s32 type_bits = selector;
    s16 selected_code;
    s16 saved_selector;
    s32 dispatch_code;
    s32 entry_index;
    s32 entry_offset;

    saved_selector = type_bits;
    type_bits = type_bits & 0xF00;
    switch (type_bits) {
    case 0x500: /* code 0x500 (the dispatcher w_800542BC sends 0x500-0x800 here); retail's tree needs one label below 0x600 sharing default, any value < 0x600 compiles identically (decision 66) */
    default:
        selected_code = 1;
        break;
    case 0x600:
        selected_code = 2;
        break;
    case 0x700:
        selected_code = 3;
        break;
    case 0x800:
        selected_code = 0;
        break;
    }
    dispatch_code = selected_code;

    if ((test_sound_channel_availability(dispatch_code) << 0x10) != 0) {
        entry_index = (dispatch_code << 8) | ((u32)(saved_selector & 0xFF) >> 4);
        entry_offset = ((saved_selector & 0xF) << 0xA) + 0x1C00;
        if (dispatch_code == 0) {
            entry_index += 0x10;
        }
        if (saved_selector & 0x1000) {
            func_80055730();
            return;
        }
        sound_start_scaled_primary_and_secondary_voices(entry_index, entry_offset);
    }
}
