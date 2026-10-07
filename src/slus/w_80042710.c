#include "common.h"

typedef struct
{
    u8 a;
    u8 b;
    u8 c;
}
Slot1_80042710;
typedef struct
{
    s8 a;
    s8 b;
}
Slot2_80042710;
typedef union
{
    u32 raw;
    struct
    {
        u8 b0;
        u8 tag;
        u8 b2;
        u8 b3;
    }
    f;
}
Grp48_80042710;
typedef struct
{
    u8 f00;
    u8 f01;
    u8 f02;
    u8 f03;
    u8 f04;
    u8 f05;
    u16 f06;
    Slot1_80042710 slots1[3];
    u8 f11;
    u8 f12;
    u8 f13;
    u32 f14;
    u32 f18;
    u32 f1c;
    u16 f20;
    u16 f22;
    u16 f24;
    u8 f26;
    u8 f27;
    u8 f28;
    u16 f2a;
    Slot2_80042710 slots2[4];
    u8 name[13];
    u8 pad41[2];
    u8 f43;
    u8 f44;
    u8 f45;
    Grp48_80042710 grp48;
    void *f4c;
    u32 pad50;
    u32 f54;
}
S_80042710;
extern void func_80041E70(S_80042710 *a0);
/* Copy record fields, merge flags, update the tagged group, and refresh the destination. */
void func_80042710(S_80042710 *dst_record, S_80042710 *src_record)
{
    s32 index;
    dst_record->f00 = src_record->f00;
    dst_record->f01 = src_record->f01;
    dst_record->f02 = src_record->f02;
    dst_record->f03 = src_record->f03;
    dst_record->f04 = src_record->f04;
    dst_record->f05 = src_record->f05;
    dst_record->f06 = src_record->f06;
    for (index = 2; index >= 0; index--) {
        dst_record->slots1[index].a = src_record->slots1[index].a;
        dst_record->slots1[index].c = src_record->slots1[index].c;
    }
    dst_record->f11 = src_record->f11;
    dst_record->f12 = src_record->f12;
    dst_record->f13 = src_record->f13;
    dst_record->f14 = (dst_record->f14 | src_record->f14) & 0xFFEFFFFF;
    dst_record->f18 = src_record->f18;
    dst_record->f1c = (dst_record->f1c | src_record->f1c) & 0xEFF6FEFF;
    dst_record->f20 = src_record->f20;
    dst_record->f22 = src_record->f22;
    dst_record->f24 = src_record->f24;
    dst_record->f26 = src_record->f26;
    dst_record->f27 = src_record->f27;
    dst_record->f28 = src_record->f28;
    dst_record->f2a = src_record->f2a;
    index = 3;
    {
        s8 *src_slot2 = (s8 *)src_record + 6;
        s8 *dst_slot2 = (s8 *)dst_record + 6;
        do {
            *(Slot2_80042710 *)(dst_slot2 + 44) = *(Slot2_80042710 *)(src_slot2 + 44);
            src_slot2 -= 2;
            index--;
            dst_slot2 -= 2;
        }
        while (index >= 0);
    }
    index = 12;
    do {
        dst_record->name[index] = src_record->name[index];
        index--;
    }
    while (index >= 0);
    dst_record->f43 = src_record->f43;
    dst_record->f44 = src_record->f44;
    if (dst_record->grp48.f.tag == 0) {
        dst_record->grp48 = src_record->grp48;
    }
    if (src_record->grp48.f.tag == 0xF) {
        dst_record->grp48 = src_record->grp48;
        if (src_record->f4c != 0) {
            dst_record->f4c = &dst_record->grp48;
        }
    }
    dst_record->f45 = src_record->f45;
    dst_record->f54 = src_record->f54;
    func_80041E70(dst_record);
}
