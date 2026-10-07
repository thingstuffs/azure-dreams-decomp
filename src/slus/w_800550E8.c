#include "shared/sound_state.h"
#include "common.h"



extern s16 D_80084810[][16];
extern void *D_80084878[][16];
extern s32 D_800848FC[3];
extern s32 func_8005405C(s16);
extern void func_800553D4(s32);
extern s16 func_8005B470(s16 idx, u8 *dst);
extern void func_8005537C(s32);
extern s16 func_8005AE08(void *, s32);
extern int func_8005B3D8(s16, s16);
extern void func_800552C8(void);
extern void func_8005AE90(s16, u8, s16);

/* Starts playback of the pending selection when available and initializes its mode. */
void func_800550E8(void)
{
    u8 entry_data[32];
    s16 note_offset;
    u16 selection;
    s16 entry_index;
    s16 entry_value;
    u16 mode_bits;
    s16 is_ready;

    if (D_800847D0.unk_26 == -1) {
        func_800553D4(0x71);
        return;
    }
    is_ready = func_8005405C(0);
    if (!is_ready) {
        D_800847D0.flags04 |= 2;
        return;
    }
    note_offset = -((((u8)D_800847D0.unk_26) >> 4) << 1);
    if (func_8005B470(0, entry_data) == 0) {
        func_8005537C(entry_data[0x18] + note_offset);
    } else {
        func_8005537C(0x64);
    }

    selection = D_800847D0.unk_26;
    mode_bits = selection & 0xF000;
    entry_index = selection & 0xF;
    D_800847D0.unk_26 = entry_index;
    entry_value = D_80084810[((u16)D_800847D0.unk_20)][entry_index];
    if (entry_value != 0) {
        func_8005B3D8(entry_value, entry_value);
    }
    D_800847D0.unk_22 = func_8005AE08(
        D_80084878[((u16)D_800847D0.unk_20)][D_800847D0.unk_26], 0);
    D_800847D0.unk_26 = -1;
    D_800847D0.flags00 &= ~0x1000;
    D_800847D0.flags04 &= ~2;
    if (mode_bits != 0) {
        D_800848F8.unk_04 = 1;
        D_800848F8.unk_08 = 0;
        switch (mode_bits) {
        case 0x9000:
            D_800848F8.unk_16 = 4;
            break;
        case 0x8000:
            D_800848F8.unk_16 = 2;
            break;
        default:
            D_800848F8.unk_16 = 0xA;
            break;
        }
    } else {
        D_800848FC[0] = 3;
    }
    D_800847D0.flags00 |= 0x100;
    func_800552C8();
    func_8005AE90(D_800847D0.unk_22, 1, 1);
}
