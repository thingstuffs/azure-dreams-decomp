#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

typedef s32 M2C_UNK;

extern u8 D_80045340[];
extern u8 D_80083498[];
extern u8 D_8015EA8C[];
extern u8 D_80161D30[];
extern u8 D_80161D78[];
extern u8 D_8015EF74[];

extern void *func_8003FD64();
extern M2C_UNK func_8004491C();
extern s32 func_800A6D30();
extern M2C_UNK func_800A48F0();
extern M2C_UNK func_800A9C18();
extern M2C_UNK func_800AA36C();
extern M2C_UNK func_80044A50();
extern M2C_UNK func_800BC318();

#ifdef __mips__
#define BODY_STORAGE
#define BODY_ATTR __attribute__((used, section(".text.func_8015E854")))
#else
#define BODY_STORAGE
#define BODY_ATTR
#endif

BODY_STORAGE void *func_8015E854(s16 arg0, s16 arg1, s16 arg2, s16 arg3) BODY_ATTR;

BODY_STORAGE void *func_8015E854(s16 arg0, s16 arg1, s16 arg2, s16 arg3)
{
    s32 temp_v0_2;
    s32 var_s5;
    void *temp_s0;
    void *temp_s2;
    void *temp_s6;
    void *temp_s3;
    void *temp_v0;
    void *var_s1;

    var_s1 = 0;
    var_s5 = 1;
    temp_v0 = func_8003FD64(274, D_80083498);
    if (temp_v0 == 0) {
        goto done;
    }

    var_s1 = (u8 *)temp_v0 + 0x20;
    FIELD(temp_v0, void *, 0x10) = D_8015EA8C;
    FIELD(var_s1, s8, 0x13) = 0x23;
    func_8004491C(temp_v0, D_80045340);
    temp_s6 = FIELD(temp_v0, void **, 8);
    FIELD(temp_s6, s16, 0xA) = arg3;
    temp_s2 = FIELD(temp_v0, void **, 0xC);
    FIELD(temp_s2, s8, 0x25) = arg2;
    temp_s3 = var_s1;
    FIELD(temp_s2, void *, 0x2C) = D_80161D30;
    temp_v0_2 = arg0 & 3;
    FIELD(temp_s2, s8, 0x24) = arg1;
    if (temp_v0_2 == 1) {
        FIELD(var_s1, s32, 0x14) |= 0x6000;
        FIELD(var_s1, s32, 0x1C) |= 0x6000;
    } else if (temp_v0_2 >= 2) {
        FIELD(var_s1, s32, 0x14) |= 0x2000;
        FIELD(var_s1, s32, 0x1C) |= 0x2000;
    } else if (((arg0 & ~3) << 16) == 0) {
        if (FIELD(var_s1, s32, 0x14) & 0x200) {
            goto status_done;
        }
        if (!(func_800A6D30() & 1)) {
            goto status_done;
        }
        FIELD(var_s1, s32, 0x1C) |= 0x200;
        func_800A48F0(var_s1, 1, (func_800A6D30() & 0x3F) | 0x20);
        FIELD(temp_s2, void *, 0x2C) = D_80161D78;
    status_done:
        var_s5 = func_800A6D30() & 3;
    }
    func_800A9C18(temp_v0, temp_s6, temp_s2, arg0);
    FIELD(temp_s3, u8, 0x9A) = 0xFF;
    FIELD(temp_s3, s8, 0x9C) = -1;
    FIELD(temp_s3, void *, 0x8C) = D_8015EF74;
    FIELD(temp_s3, s16, 0xA4) = -1;
    if (var_s5 != 0) {
        FIELD(temp_s3, s16, 0xA6) = 0;
    } else {
        temp_s0 = (u8 *)temp_s3 - 0x20;
        FIELD(temp_s3, s16, 0xA6) = 1;
        FIELD(temp_s2, s16, 0x10) = 0x60;
        FIELD(temp_s2, u16, 0x14) |= 0xC;
        FIELD(temp_s2, u16, 0x12) -= 0x80;
        func_80044A50(temp_s0);
        func_800BC318(temp_s0);
    }
    func_800AA36C(temp_s3, temp_s6, temp_s2, var_s1);
done:
    return var_s1;
}
