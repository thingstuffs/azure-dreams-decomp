#include "common.h"

typedef struct S_80085458 {
    s16 f00, f02, f04;
    u16 f06;
    u8 pad08[2];
    u16 f0a;
    u8 pad0c[0xC];
    s16 f18;
    u16 f1a;
    s8 f1c, f1d;
    u8 pad1e[8];
    s8 f26, f27, f28;
    u8 pad29[3];
    s32 f2c, f30;
    u8 pad34[8];
    s32 f3c;
    u8 pad40[2];
    s8 f42, f43, f44;
    u8 pad45[3];
    s32 f48, f4c;
    u8 pad50[8];
    s32 f58;
    u8 pad5c[0x14];
    s32 f70, f74;
} S_80085458;

extern S_80085458 D_80085458[64];
extern s32 D_80073740[];
extern s32 D_80085F98[3];

extern s32 func_80056D44(s32 arg0, S_80085458 *arg1);
extern void func_80056DB4(s32 arg0);
extern void func_8005E97C(s32 arg0, s32 arg1);
extern s32 func_8005EB78(s32 arg0);

/* Services an active SPU slot until completion and clears the busy flag. */
s32 func_8005C4D0(s16 slot_id)
{
    u8 *busy_or_slot = (u8 *)D_80085F98;
    u8 *slots = (u8 *)D_80085458;
    s32 slot_index = slot_id;
    s32 slot_handle;
    u8 *slot;
    s32 status;
    u16 active;

    slot = slots + slot_index * 0x78;
    active = *(u16 *)(slot + 0x1A);
    *(s32 *)busy_or_slot = 1;
    if (active == 0) {
        goto fail;
    }
    if (*(u16 *)(slot + 6) < 0x10) {
        goto fail;
    }

    slot_handle = D_80073740[slot_index];
    busy_or_slot = slot;
    *(u16 *)(busy_or_slot + 0x1A) = 0;
    *(u16 *)(busy_or_slot + 0x0A) = 0;
    func_80056D44(slot_index, (S_80085458 *)busy_or_slot);
    func_80056DB4(slot_index);
    func_8005E97C(0, D_80073740[slot_index]);
    do {
        func_8005E97C(0, slot_handle);
        status = func_8005EB78(slot_handle);
        if (status == 2) {
            goto success;
        }
    } while (status != 0);
    goto success;

fail:
    D_80085F98[0] = 0;
    return -1;

success:
    D_80085F98[0] = 0;
    return 0;
}
