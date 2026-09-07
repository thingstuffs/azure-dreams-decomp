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

void func_8009EF78(void) {
    volatile Unk3648 *var_s0;
    volatile Unk39C8 *var_s1;
    s32 var_s2;

    func_8009EEAC();
    var_s2 = 0;
    var_s1 = D_800E39C8;
    var_s0 = D_800E3648;
    do {
        if ((var_s0->unk1 != 0) && (var_s0->unk0 != 0) &&
            !(var_s0->unk3 & 0x40)) {
            func_8009F3D4(var_s1->unk6, var_s1->unk7,
                          0x802080, 8, var_s2);
        }
        var_s1++;
        var_s2++;
        var_s0++;
    } while (var_s2 < 0x20);
}
