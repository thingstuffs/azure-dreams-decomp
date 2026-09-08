#include "common.h"

typedef struct {
    u32 unk0;
    u32 unk4;
    u8 pad8[0x18];
    u16 unk20;
    s16 unk22;
    u8 pad24[2];
    s16 unk26;
} S_800847D0;

typedef struct {
    u8 pad0[4];
    s32 unk4;
    s16 unk8;
    u8 padA[0xC];
    s16 unk16;
} S_800848F8;

extern S_800847D0 D_800847D0;
extern s16 D_80084810[][16];
extern void *D_80084878[][16];
extern S_800848F8 D_800848F8;
extern s32 D_800848FC[3];
extern s32 func_8005405C(s16);
extern void func_800553D4(s32);
extern s16 func_8005B470(s16, void *);
extern void func_8005537C(s32);
extern s16 func_8005AE08(void *, s32);
extern int func_8005B3D8(s16, s16);
extern void func_800552C8(void);
extern void func_8005AE90(s16, u8, s16);

/* Process the pending selection and initialize its entry and mode. */
void func_800550E8(void)
{
    u8 entry_data[32];
    s16 value_offset;
    u16 selection;
    s16 entry_index;
    s16 entry_value;
    u16 mode_bits;
    s16 is_ready;

    if (D_800847D0.unk26 == -1) {
        func_800553D4(0x71);
        return;
    }
    is_ready = func_8005405C(0);
    if (!is_ready) {
        D_800847D0.unk4 |= 2;
        return;
    }
    value_offset = -((((u8)D_800847D0.unk26) >> 4) << 1);
    if (func_8005B470(0, entry_data) == 0) {
        func_8005537C(entry_data[0x18] + value_offset);
    } else {
        func_8005537C(0x64);
    }

    selection = D_800847D0.unk26;
    mode_bits = selection & 0xF000;
    entry_index = selection & 0xF;
    D_800847D0.unk26 = entry_index;
    entry_value = D_80084810[D_800847D0.unk20][entry_index];
    if (entry_value != 0) {
        func_8005B3D8(entry_value, entry_value);
    }
    D_800847D0.unk22 = func_8005AE08(
        D_80084878[D_800847D0.unk20][D_800847D0.unk26], 0);
    D_800847D0.unk26 = -1;
    D_800847D0.unk0 &= ~0x1000;
    D_800847D0.unk4 &= ~2;
    if (mode_bits != 0) {
        D_800848F8.unk4 = 1;
        D_800848F8.unk8 = 0;
        if (mode_bits != 0x8000) {
            if (mode_bits != 0x9000) {
                goto set_default;
            }
            D_800848F8.unk16 = 4;
        } else {
            D_800848F8.unk16 = 2;
        }
        goto done;
    set_default:
        D_800848F8.unk16 = 0xA;
    } else {
        D_800848FC[0] = 3;
    }
done:
    D_800847D0.unk0 |= 0x100;
    func_800552C8();
    func_8005AE90(D_800847D0.unk22, 1, 1);
}
