#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8005DF80_0 {
    s32 unk_00;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    u16 unk_26;
    u16 unk_28;
    u16 unk_2A;
    u16 unk_2C;
    u16 unk_2E;
    u16 unk_30;
    u16 unk_32;
    u16 unk_34;
    u16 unk_36;
    u16 unk_38;
    u16 unk_3A;
    u16 unk_3C;
    u16 unk_3E;
    u16 unk_40;
    u16 unk_42;
} S_8005DF80_0;   /* arg0 in func_8005DF80 */

typedef struct S_8005DF80_1 {
    u8 pad_00[0x1C0];
    u16 unk_1C0;
    u16 unk_1C2;
    u16 unk_1C4;
    u16 unk_1C6;
    u16 unk_1C8;
    u16 unk_1CA;
    u16 unk_1CC;
    u16 unk_1CE;
    u16 unk_1D0;
    u16 unk_1D2;
    u16 unk_1D4;
    u16 unk_1D6;
    u16 unk_1D8;
    u16 unk_1DA;
    u16 unk_1DC;
    u16 unk_1DE;
    u16 unk_1E0;
    u16 unk_1E2;
    u16 unk_1E4;
    u16 unk_1E6;
    u16 unk_1E8;
    u16 unk_1EA;
    u16 unk_1EC;
    u16 unk_1EE;
    u16 unk_1F0;
    u16 unk_1F2;
    u16 unk_1F4;
    u16 unk_1F6;
    u16 unk_1F8;
    u16 unk_1FA;
    u16 unk_1FC;
    u16 unk_1FE;
} S_8005DF80_1;   /* D_80079958 in func_8005DF80 */


extern S_8005DF80_1 *D_80079958;

void func_8005DF80(S_8005DF80_0 *arg0) {
    s32 temp_a1;
    s32 temp_a2;

    temp_a1 = arg0->unk_00;
    temp_a2 = temp_a1 == 0;
    if ((temp_a2 != 0) || (temp_a1 & 1)) {
        D_80079958->unk_1C0 = (u16) arg0->unk_04;
    }
    if ((temp_a2 != 0) || (temp_a1 & 2)) {
        D_80079958->unk_1C2 = (u16) arg0->unk_06;
    }
    if ((temp_a2 != 0) || (temp_a1 & 4)) {
        D_80079958->unk_1C4 = (u16) arg0->unk_08;
    }
    if ((temp_a2 != 0) || (temp_a1 & 8)) {
        D_80079958->unk_1C6 = (u16) arg0->unk_0A;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x10)) {
        D_80079958->unk_1C8 = (u16) arg0->unk_0C;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x20)) {
        D_80079958->unk_1CA = (u16) arg0->unk_0E;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x40)) {
        D_80079958->unk_1CC = (u16) arg0->unk_10;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x80)) {
        D_80079958->unk_1CE = (u16) arg0->unk_12;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x100)) {
        D_80079958->unk_1D0 = (u16) arg0->unk_14;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x200)) {
        D_80079958->unk_1D2 = (u16) arg0->unk_16;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x400)) {
        D_80079958->unk_1D4 = (u16) arg0->unk_18;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x800)) {
        D_80079958->unk_1D6 = (u16) arg0->unk_1A;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x1000)) {
        D_80079958->unk_1D8 = (u16) arg0->unk_1C;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x2000)) {
        D_80079958->unk_1DA = (u16) arg0->unk_1E;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x4000)) {
        D_80079958->unk_1DC = (u16) arg0->unk_20;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x8000)) {
        D_80079958->unk_1DE = (u16) arg0->unk_22;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x10000)) {
        D_80079958->unk_1E0 = (u16) arg0->unk_24;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x20000)) {
        D_80079958->unk_1E2 = (u16) arg0->unk_26;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x40000)) {
        D_80079958->unk_1E4 = (u16) arg0->unk_28;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x80000)) {
        D_80079958->unk_1E6 = (u16) arg0->unk_2A;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x100000)) {
        D_80079958->unk_1E8 = (u16) arg0->unk_2C;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x200000)) {
        D_80079958->unk_1EA = (u16) arg0->unk_2E;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x400000)) {
        D_80079958->unk_1EC = (u16) arg0->unk_30;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x800000)) {
        D_80079958->unk_1EE = (u16) arg0->unk_32;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x01000000)) {
        D_80079958->unk_1F0 = (u16) arg0->unk_34;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x02000000)) {
        D_80079958->unk_1F2 = (u16) arg0->unk_36;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x04000000)) {
        D_80079958->unk_1F4 = (u16) arg0->unk_38;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x08000000)) {
        D_80079958->unk_1F6 = (u16) arg0->unk_3A;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x10000000)) {
        D_80079958->unk_1F8 = (u16) arg0->unk_3C;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x20000000)) {
        D_80079958->unk_1FA = (u16) arg0->unk_3E;
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x40000000)) {
        D_80079958->unk_1FC = (u16) arg0->unk_40;
    }
    if ((temp_a2 != 0) || (temp_a1 < 0)) {
        D_80079958->unk_1FE = (u16) arg0->unk_42;
    }
}
