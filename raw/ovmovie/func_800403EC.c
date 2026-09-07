#include "common.h"

typedef struct {
    /* 0x00 */ void *unk00;
    /* 0x04 */ void *unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ void *unk0C;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s32 unk2C;
} Struct800403EC;

extern unsigned long long func_80176C7C(s32, void *, s32);
extern s32 D_801781E0[3];
extern void *D_80189390[3];

s32 func_800403EC(Struct800403EC *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Struct800403EC *ptr = arg0;
    s32 temp_arg1 = arg1;
    s32 temp_arg2 = arg2;
    register s32 off0 ASM_REG("$4") = 0x15A40;
    register s32 off1 ASM_REG("$5") = 0x22AB0;
    register s32 off2 ASM_REG("$6") = 0x10040;
    register u8 *base ASM_REG("$3") = D_80189390[0];
    s32 flags = D_801781E0[0];
    void *temp_a1;

    ptr->unk08 = 0;
    ptr->unk20 = 0;
    ptr->unk2C = 0;
    ptr->unk00 = base + off0;
    temp_a1 = base + off1;
    ptr->unk04 = temp_a1;
    ptr->unk0C = base + off2;
    if (flags & 1) {
        register s32 temp_wide ASM_REG("$2") = 0x1E0;
        register s32 dead_h ASM_REG("$3") = 0xF0;

        ptr->unk14 = temp_wide;
        ptr->unk1C = temp_wide;
        ASM_KEEP(dead_h);
        func_80176C7C(arg4, temp_a1, off2);
        return 0x18;
    }
    ptr->unk14 = 0x140;
    ptr->unk1C = 0x140;
    ptr->unk10 = temp_arg1;
    ptr->unk12 = temp_arg2;
    ptr->unk16 = 0xF0;
    ptr->unk18 = arg3;
    ptr->unk1A = (s16) arg4;
    ptr->unk1E = 0xF0;
    ptr->unk24 = temp_arg1;
    ptr->unk26 = temp_arg2;
    ptr->unk28 = 0x10;
    ptr->unk2A = 0xF0;
}
