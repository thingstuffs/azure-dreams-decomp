#include "common.h"

extern void func_8009EEAC(s32, s32, s32, s32);
extern void func_8009F3D4(u8, u8, s32, s32, s32);

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
} Unk3648;

typedef struct {
    u8 unk0[6];
    u8 unk6;
    u8 unk7;
    u8 unk8[16];
} Unk39C8;

extern Unk3648 D_800E3648[0x20];
extern Unk39C8 D_800E39C8[0x20];

/* Create purple markers at eligible entry positions. */
void func_8009EF78(s32 setup_arg_0, s32 setup_arg_1, s32 setup_arg_2, s32 setup_arg_3) {
    volatile Unk3648 *entry_state;
    volatile Unk39C8 *entry_position;
    s32 entry_index;

    func_8009EEAC(setup_arg_0, setup_arg_1, setup_arg_2, setup_arg_3);
    entry_index = 0;
    entry_position = D_800E39C8;
    entry_state = D_800E3648;
    do {
        if ((entry_state->unk1 != 0) && (entry_state->unk0 != 0) &&
            !(entry_state->unk3 & 0x40)) {
            func_8009F3D4(entry_position->unk6, entry_position->unk7,
                          0x802080, 8, entry_index);
        }
        entry_position++;
        entry_index++;
        entry_state++;
    } while (entry_index < 0x20);
}
