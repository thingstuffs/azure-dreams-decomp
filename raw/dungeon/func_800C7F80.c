#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern s32 func_8003FA44();
extern void *func_8003FC64();
extern void func_8004491C();
extern void func_800A56E0();
extern void func_800A6508();
extern s32 func_800A6D30();
extern void func_800CD6AC();
extern void func_800CD744();
extern void func_800CD8E4();

extern u8 D_80045C34[];
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern u16 D_80083460[6];
extern u8 D_800CD474[];
extern u8 D_800E03E0[];
extern u8 D_800E3D40;

s32 func_800CD6E0(void *arg0) {
    void *obj;
    void *owner;
    void *prim;
    void *spr;
    void *link;
    s16 *xpos;
    u16 *counter;
    s32 i;
    s32 random;
    register s32 call_arg ASM_REG("$4");
    register s32 divisor ASM_REG("$2");
    register s32 gate ASM_REG("$2");
    register s32 color ASM_REG("$7");
    register s32 count ASM_REG("$3");
    register s32 owner_coord ASM_REG("$3");
    register s32 coord ASM_REG("$2");
    register s32 table_offset ASM_REG("$5");
    register void *callback_base ASM_REG("$22");

    if (D_800E3D40 == 0) {
        call_arg = func_800A6D30() & 0xFFFF;
        count = FIELD(arg0, u8, 3);
        if (count != 0) {
            divisor = count;
            ASM_KEEP(divisor);
            count = call_arg % divisor;
            ASM_KEEP(count);
            func_800CD744();
            return count;
        }
    }

    gate = 0;
    ASM_KEEP(gate);
    if (gate < 0x30) {
        owner = FIELD(arg0, void *, -0x14);
        if (FIELD(owner, u16, 0x14) & 0x8000) {
            func_800CD6AC(arg0, 0x10);
            func_800CD8E4();
            return 1;
        }
        if (func_8003FA44(4) == 0) {
            func_800CD8E4();
            return 0;
        }

        i = 0;
        coord = 0x800D0000;
        ASM_KEEP_NV(coord);
        callback_base = (void *)(coord - 0x2B8C);
        counter = D_80083460;
        xpos = D_8006CCD8;
        do {
            FIELD((obj = func_8003FC64(2)), void *, 0x10) = callback_base;
            func_8004491C(obj, D_80045C34);
            color = 0x808080;
            call_arg = 0x50D;
            ASM_KEEP_NV(call_arg);
            table_offset = i << 2;
            ASM_KEEP_NV(table_offset);

            owner_coord = FIELD(owner, u8, 0x24);
            coord = *xpos;
            prim = FIELD(obj, void *, 8);
            owner_coord <<= 6;
            coord = (coord << 5) + 0x20;
            owner_coord += coord;
            coord = (u32)D_8006CCE8;
            table_offset += coord;
            ASM_KEEP_NV(table_offset);
            FIELD(prim, s16, 2) = owner_coord;
            owner_coord = FIELD(owner, u8, 0x25);
            coord = FIELD((void *)table_offset, s16, 0);
            owner_coord <<= 6;
            coord = (coord << 5) + 0x20;
            owner_coord += coord;
            FIELD(prim, s16, 6) = owner_coord;
            xpos += 2;
            FIELD(prim, s16, 0xA) = FIELD(arg0, u16, 0x88) - 0x200;

            spr = FIELD(obj, void *, 0xC);
            coord = 0x1000;
            FIELD(spr, s16, 0x1C) = coord;
            coord = 0x2000;
            FIELD(spr, s16, 0x1E) = coord;
            coord = (s32)D_800E03E0;
            FIELD(spr, void *, 8) = (void *)coord;
            FIELD(spr, s16, 0x10) = 0x20;
            FIELD(spr, s16, 0x16) = 0x400;
            FIELD(spr, s32, 0xC) = color;
            FIELD(spr, s16, 0x18) = (i << 10) + 0x400;
            FIELD(spr, u16, 0x14) |= 0xC;

            link = (u8 *)obj + 0x20;
            FIELD(link, u16, 0xA) = FIELD(arg0, u16, 0x88);
            FIELD(obj, void *, 0x20) = arg0;
            FIELD(link, s16, 6) = 0xC;
            FIELD(link, s16, 8) = i;
            FIELD(obj, void *, 0x20) = arg0;
            i++;
            counter[5]++;
            func_800A56E0(call_arg, spr, prim, color);
        } while (i < 4);

        func_800CD8E4();
        return 1;
    }

    if (FIELD(arg0, u8, 0x13) == 0) {
        func_800A6508(call_arg);
    }
    return 1;
}
