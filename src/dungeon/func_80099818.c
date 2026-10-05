#include "common.h"

extern void func_8009EEAC(void);
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
void func_8009EF78(void) {
    s32 i;

    func_8009EEAC();
    for (i = 0; i < 0x20; i++) {
        if ((D_800E3648[i].unk1 != 0) && (D_800E3648[i].unk0 != 0) &&
            !(D_800E3648[i].unk3 & 0x40)) {
            func_8009F3D4(D_800E39C8[i].unk6, D_800E39C8[i].unk7,
                          0x802080, 8, i);
        }
    }
}
