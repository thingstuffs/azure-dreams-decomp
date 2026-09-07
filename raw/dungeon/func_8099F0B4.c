#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_800A48F0(void *, s32, s32);
extern s32 func_800A6D30();
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);
extern void func_80170A94(void);
extern void func_801710EC(void);

extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_801708B4[];
extern u8 D_801714C8[];
extern u8 D_80171500[];
extern u8 D_80171544[];
extern u8 D_80171554[];
extern u8 D_80171580[];
extern u8 D_801724D0[];
extern u8 D_80172508[];
extern u8 D_80172534[];
extern u8 D_80172550[];
extern u8 D_801725C8[];
extern u8 D_80172908[];
extern u8 D_80172A4C[];
extern u8 D_80172B48[];
extern u8 D_80172CFC[];
extern u8 D_80172D40[];
extern u8 D_80172E3C[];
extern u8 D_80172E68[];
extern u8 D_80172F5C[];
extern u8 D_80172FFC[];
extern u8 D_8017316C[];
extern u8 D_801731CC[];
extern u8 D_801735C4[];
extern u8 D_801735FC[];
extern u8 D_80173600[];
extern u8 D_80173608[];
extern u8 D_8017360C[];
extern u8 D_80173614[];
extern u8 D_80173618[];
extern u8 D_80173620[];
extern u8 D_801737E4[];
extern u8 D_80173864[];
extern u8 D_80173920[];
extern u8 D_80173964[];
extern u8 D_80175E40[];
extern u8 D_80175EA0[];

void *func_801708B4(s16 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    void *entity;
    void *part_a;
    void *part_b;
    void *result;
    s32 mode;
    s16 direction;
    u8 *inner;
    register s8 saved_arg1 ASM_REG("$22");
    register s16 saved_arg3;
    register s8 saved_arg2 ASM_REG("$21");

    direction = arg0;
    inner = 0;
    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    entity = func_8003FD64(0x112, D_80083498);
    if (entity != 0) {
        inner = (u8 *)entity + 0x20;
        FIELD(entity, void *, 0x10) = func_80170A94;
        FIELD(inner, s8, 0x13) = 2;
        func_8004491C(entity, &D_80045340);

        part_a = FIELD(entity, void *, 8);
        FIELD(part_a, s16, 0xA) = saved_arg3;
        part_b = FIELD(entity, void *, 0xC);
        mode = arg0 & 3;
        FIELD(part_b, s8, 0x25) = saved_arg2;
        result = inner;
        FIELD(part_b, void *, 0x2C) = D_80175E40;
        FIELD(part_b, s8, 0x24) = saved_arg1;

        if (mode == 1) {
            FIELD(inner, u32, 0x14) |= 0x6000;
            FIELD(inner, u32, 0x1C) |= 0x6000;
        } else if (mode >= 2) {
            FIELD(inner, u32, 0x14) |= 0x2000;
            FIELD(inner, u32, 0x1C) |= 0x2000;
        } else if (((arg0 & -4) << 16) == 0) {
            if (!(FIELD(inner, u32, 0x14) & 0x200)) {
                register void *call_entity ASM_REG("$4") = entity;
                register void *call_part_a ASM_REG("$5") = part_a;

                ASM_SET(call_entity);
                ASM_SET(call_part_a);
                if (func_800A6D30(call_entity, call_part_a) & 1) {
                    s32 value;
                    register void *second_entity ASM_REG("$4") = entity;

                    ASM_SET(second_entity);
                    value = func_800A6D30(second_entity);

                    func_800A48F0(inner, 1, (value & 0x3F) | 0x20);
                    FIELD(part_b, void *, 0x2C) = D_80175EA0;
                }
            }
        }

        func_800A9C18(entity, part_a, part_b, direction);
        FIELD(result, u8, 0x9A) = 0xFF;
        FIELD(result, s8, 0x9C) = -1;
        FIELD(result, void *, 0x8C) = func_801710EC;
        FIELD(inner, u32, 0x1C) |= 0x40000;
        FIELD(result, s16, 0x92) = -0x20;
        func_800AA36C(result, part_a, part_b, inner);
    }
    return inner;
}
