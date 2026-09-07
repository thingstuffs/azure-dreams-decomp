#include "common.h"

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 pad[10];
} Entry;

extern s32 D_800E3548[];
extern Entry D_800E36C8[];
extern void func_8009A3D0(u8, u8, s32);

void func_800A7030(s16 arg0, s16 arg1) {
    Entry *var_s0;
    s32 *var_s1;
    s32 var_s2;
    s32 x;
    s32 y;
    u8 temp_a0;
    u8 temp_a1;

    var_s2 = 0;
    x = arg0;
    y = arg1;
    var_s1 = D_800E3548;
    var_s0 = D_800E36C8;
    do {
        if (((u8 *) var_s1)[1] != 0) {
            temp_a0 = var_s0->unk0;
            if (temp_a0 == x) {
                temp_a1 = var_s0->unk1;
                if (temp_a1 == y) {
                    *var_s1 = 0;
                    func_8009A3D0(temp_a0, temp_a1, 0x800);
                }
            }
        }
        var_s1++;
        var_s2++;
        var_s0++;
    } while (var_s2 < 0x40);
}

/* MECHANISM: Natural pointer-loop reconstruction holds the two array bases
   across the loop and call; explicit signed arg copies precede both bases.
   This anchors the prologue's argument-extension/base materialization order. */
