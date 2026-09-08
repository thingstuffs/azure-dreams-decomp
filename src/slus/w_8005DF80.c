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

/* Copies selected fields to D_80079958, or all 32 fields when the mask is zero. */
void func_8005DF80(S_8005DF80_0 *source) {
    s32 field_mask;
    s32 copy_all;

    field_mask = source->unk_00;
    copy_all = field_mask == 0;
    if ((copy_all != 0) || (field_mask & 1)) {
        D_80079958->unk_1C0 = (u16) source->unk_04;
    }
    if ((copy_all != 0) || (field_mask & 2)) {
        D_80079958->unk_1C2 = (u16) source->unk_06;
    }
    if ((copy_all != 0) || (field_mask & 4)) {
        D_80079958->unk_1C4 = (u16) source->unk_08;
    }
    if ((copy_all != 0) || (field_mask & 8)) {
        D_80079958->unk_1C6 = (u16) source->unk_0A;
    }
    if ((copy_all != 0) || (field_mask & 0x10)) {
        D_80079958->unk_1C8 = (u16) source->unk_0C;
    }
    if ((copy_all != 0) || (field_mask & 0x20)) {
        D_80079958->unk_1CA = (u16) source->unk_0E;
    }
    if ((copy_all != 0) || (field_mask & 0x40)) {
        D_80079958->unk_1CC = (u16) source->unk_10;
    }
    if ((copy_all != 0) || (field_mask & 0x80)) {
        D_80079958->unk_1CE = (u16) source->unk_12;
    }
    if ((copy_all != 0) || (field_mask & 0x100)) {
        D_80079958->unk_1D0 = (u16) source->unk_14;
    }
    if ((copy_all != 0) || (field_mask & 0x200)) {
        D_80079958->unk_1D2 = (u16) source->unk_16;
    }
    if ((copy_all != 0) || (field_mask & 0x400)) {
        D_80079958->unk_1D4 = (u16) source->unk_18;
    }
    if ((copy_all != 0) || (field_mask & 0x800)) {
        D_80079958->unk_1D6 = (u16) source->unk_1A;
    }
    if ((copy_all != 0) || (field_mask & 0x1000)) {
        D_80079958->unk_1D8 = (u16) source->unk_1C;
    }
    if ((copy_all != 0) || (field_mask & 0x2000)) {
        D_80079958->unk_1DA = (u16) source->unk_1E;
    }
    if ((copy_all != 0) || (field_mask & 0x4000)) {
        D_80079958->unk_1DC = (u16) source->unk_20;
    }
    if ((copy_all != 0) || (field_mask & 0x8000)) {
        D_80079958->unk_1DE = (u16) source->unk_22;
    }
    if ((copy_all != 0) || (field_mask & 0x10000)) {
        D_80079958->unk_1E0 = (u16) source->unk_24;
    }
    if ((copy_all != 0) || (field_mask & 0x20000)) {
        D_80079958->unk_1E2 = (u16) source->unk_26;
    }
    if ((copy_all != 0) || (field_mask & 0x40000)) {
        D_80079958->unk_1E4 = (u16) source->unk_28;
    }
    if ((copy_all != 0) || (field_mask & 0x80000)) {
        D_80079958->unk_1E6 = (u16) source->unk_2A;
    }
    if ((copy_all != 0) || (field_mask & 0x100000)) {
        D_80079958->unk_1E8 = (u16) source->unk_2C;
    }
    if ((copy_all != 0) || (field_mask & 0x200000)) {
        D_80079958->unk_1EA = (u16) source->unk_2E;
    }
    if ((copy_all != 0) || (field_mask & 0x400000)) {
        D_80079958->unk_1EC = (u16) source->unk_30;
    }
    if ((copy_all != 0) || (field_mask & 0x800000)) {
        D_80079958->unk_1EE = (u16) source->unk_32;
    }
    if ((copy_all != 0) || (field_mask & 0x01000000)) {
        D_80079958->unk_1F0 = (u16) source->unk_34;
    }
    if ((copy_all != 0) || (field_mask & 0x02000000)) {
        D_80079958->unk_1F2 = (u16) source->unk_36;
    }
    if ((copy_all != 0) || (field_mask & 0x04000000)) {
        D_80079958->unk_1F4 = (u16) source->unk_38;
    }
    if ((copy_all != 0) || (field_mask & 0x08000000)) {
        D_80079958->unk_1F6 = (u16) source->unk_3A;
    }
    if ((copy_all != 0) || (field_mask & 0x10000000)) {
        D_80079958->unk_1F8 = (u16) source->unk_3C;
    }
    if ((copy_all != 0) || (field_mask & 0x20000000)) {
        D_80079958->unk_1FA = (u16) source->unk_3E;
    }
    if ((copy_all != 0) || (field_mask & 0x40000000)) {
        D_80079958->unk_1FC = (u16) source->unk_40;
    }
    if ((copy_all != 0) || (field_mask < 0)) {
        D_80079958->unk_1FE = (u16) source->unk_42;
    }
}
