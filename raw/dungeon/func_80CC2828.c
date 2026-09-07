#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_80093E74(void *, void *, void *, void *);
extern void func_8009A028(void *);
extern void func_8009A21C(u8, u8, s32);
extern void func_8009A3D0(u8, u8, s32);
extern void func_800A18E8(u8, s32);
extern u8 func_800A1BD0(void *);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80175DA4(void *);
extern void func_8017614C(void) __attribute__((noreturn));
extern void func_8017629C(void) __attribute__((noreturn));

extern s32 D_800814A0;
extern u8 D_80082E80[];
extern s32 D_80083460;
extern u8 D_80083780[];
extern u8 *D_800E3D7C;
extern u8 D_80173B98;

void func_80176028(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    register u8 *owner = arg0;
    u8 *work = arg3;
    register s32 state = owner[0x9B];
    register u8 *actor = *(u8 **)(work + 0x60);
    register s32 type_check ASM_REG("$2");

    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        type_check = 3;
        if (state == 0) {
            goto state_0;
        }
        func_8017629C();
        return;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    {
        func_8017629C();
        return;
    }

state_0:
    {
        if ((FIELD(arg2, s8, 4) == type_check) &&
            (FIELD(arg2, u16, 0x14) & 0x1000)) {
            func_800A56E0(0x808);
        }
        if (FIELD(arg2, u16, 0x14) & 0xE000) {
            func_8017614C();
            return;
        }
        goto done;
    }

state_1:
    {
        u8 *saved_actor;
        u8 *counter;
        u8 *value_map;
        u16 saved_value;
        u8 value;
        register u8 *table1;
        register u8 *table2;

        saved_value = FIELD(D_800E3D7C, u16, 0x8A);
        saved_actor = FIELD(D_800E3D7C, u8 *, 0x60);
        value = func_800A1BD0(actor);
        table1 = D_80083780;
        table2 = D_80082E80;
        value_map = D_800E3D7C;
        owner[0xA9] = value;
        ASM_KEEP_DEP_NV(actor, value);
        ASM_JALDELAY_PIN(actor);
        ASM_KEEP_NV(actor);
        FIELD(D_800E3D7C, u8 *, 0x60) = actor;
        FIELD(value_map, u16, 0x8A) = value;
        func_80093E74(D_800E3D7C, table1, table2, D_800E3D7C);
        FIELD(D_800E3D7C, u8 *, 0x60) = saved_actor;
        FIELD(D_800E3D7C, u16, 0x8A) = saved_value;
        counter = (u8 *)&D_80083460;
        FIELD(counter, u16, 0xA)--;
        owner[0x9B]++;
        func_8017629C();
        return;
    }

state_2:
    {
        u8 *map;
        u8 *tile;
        u8 x;
        u8 y;
        s32 mode;

        if (!(FIELD(actor, u32, 0x1C) & 0x00800000)) {
            goto done;
        }

        map = D_800E3D7C;
        *(u32 *)(map + 0xAC + owner[0xA9] * 4) = 0;
        *(u32 *)(map + 0xD0 + owner[0xA9] * 4) = 0;
        func_800A18E8(actor[0x13], 3);
        tile = *(u8 **)(actor - 0x14);
        x = tile[0x24];
        y = tile[0x25];
        mode = (FIELD(actor, u32, 0x1C) & 0x2000) ? 0x300 : 0x3000;
        func_8009A3D0(x, y, mode);
        func_8009A028(actor);
        FIELD(actor, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        ASM_MEM_BARRIER();
        {
            register u8 *map_value ASM_REG("$2");
            register s32 owner_index ASM_REG("$3");

            map_value = D_800E3D7C;
            owner_index = owner[0xA9];
            ASM_KEEP_DEP_NV(owner_index, map_value);
            map_value += owner_index;
            map_value[0xFA] = state;
        }
        owner[0xA8] = owner[0xA9] + 1;
        owner[0x9B]++;
        func_8017629C();
        return;
    }

state_3:
    {
        register u8 *entry = arg2;

        func_800AD594(work, 0x800);
        FIELD(work, u32, 0x1C) |= 0x2000;
        func_8009A3D0(entry[0x24], entry[0x25], 0x3000);
        func_8009A21C(entry[0x24], entry[0x25], 0x300);
        work[0x12] = state;
        func_80175DA4(*(void **)(work + 0x60));
        FIELD(work, u16, 0x46) &= 0x7FFF;
        FIELD(owner, void *, 0x8C) = &D_80173B98;
        func_800A4ACC(work);
        work[0x6D]--;
    }

done:
    return;
}
