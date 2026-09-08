#include "common.h"

extern u8 D_80083160[];

extern s32 func_80065420();
extern s32 func_80066460();
extern void func_80066640();
extern void func_800667D0();
extern void func_80067F20();
extern s32 rand();
extern void func_800A130C();

void func_800A2AF8(s32 arg0, s32 arg1)
{
    s32 arg0r = arg0;
    s32 arg1r = arg1;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *base;
    register u32 *prim ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u32 *packet;
    register s32 random ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 result;
    u32 rgb_mask = 0x00FFFFFF;
    u32 code_mask;
    register s32 z0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    register s32 z3 ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    base = *(u8 **)D_80083160;
    *(u8 **)(scratch + 0x24) = base + 0xB0;
    prim = *(u32 **)(base + 0x8D0);
    *(u8 **)(base + 0x8D0) = (u8 *)prim + 0x14;

    random = rand();
    prim[1] = (random * rand()) & rgb_mask;
    random = rand();
    prim[3] = (random * rand()) & rgb_mask;

    func_800667D0(prim);
    func_80066640(prim, 1);

    func_800A130C(scratch + 0x74, arg1r);
    func_800A130C(scratch + 0x7C, arg0r);
    *(s32 *)(scratch + 0xC4) = func_80065420(
        scratch + 0x74, scratch + 0xE8, scratch + 0x94, scratch + 0x98);
    func_80065420(
        scratch + 0x7C, scratch + 0xEC, scratch + 0x94, scratch + 0x98);

    {
        register u16 first ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        result = *(s32 *)(scratch + 0xC4);
        first = *(u16 *)(scratch + 0xE8);
        result -= 0x30;
        *(s32 *)(scratch + 0xC4) = result;
        *(u16 *)((u8 *)prim + 8) = first;
    }
    *(u16 *)((u8 *)prim + 0xA) = *(u16 *)(scratch + 0xEA);
    *(u16 *)((u8 *)prim + 0x10) = *(u16 *)(scratch + 0xEC);
    *(u16 *)((u8 *)prim + 0x12) = *(u16 *)(scratch + 0xEE);

    if (*(volatile s32 *)(scratch + 0xC4) >= 0x1E0) {
        *(s32 *)(scratch + 0xC4) = 0x1DF;
    }
    if (*(volatile s32 *)(scratch + 0xC4) < 0) {
        *(s32 *)(scratch + 0xC4) = 0;
    }

    base = *(u8 **)D_80083160;
    packet = *(u32 **)(base + 0x8D0);
    *(u8 **)(base + 0x8D0) = (u8 *)packet + 0xC;
    result = func_80066460(0, 0, 0x140, 0);
    func_80067F20(packet, 1, 0, (u16)result, 0);

    code_mask = 0xFF000000;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    z0 = 0;
    z3 = 0;
    {
        u32 *entry;
        entry = (u32 *)(((u32)*(s32 *)(scratch + 0xC4) << 2) +
            (u32)*(u32 **)(scratch + 0x24));
        packet[0] = (packet[0] & code_mask) | (*entry & rgb_mask);
    }
    {
        s32 index = *(s32 *)(scratch + 0xC4);
        u32 value = ((u32 *)*(u32 **)(scratch + 0x24))[index];
        ((u32 *)*(u32 **)(scratch + 0x24))[index] =
            (value & code_mask) | ((u32)packet & rgb_mask);
    }

    {
        u32 value;
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        value = ((u32 *)*(u32 **)(scratch + 0x24))[*(s32 *)(scratch + 0xC4)];
        prim[0] = (prim[0] & code_mask) | (value & rgb_mask);
    }
    {
        register s32 index ASM_REG("$6") = *(s32 *)(scratch + 0xC4);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        u32 value = ((u32 *)*(u32 **)(scratch + 0x24))[index];
        ((u32 *)*(u32 **)(scratch + 0x24))[index] =
            (value & code_mask) | ((u32)prim & rgb_mask);
    }

    ASM_KEEP(prim);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    base = *(u8 **)D_80083160;
    packet = *(u32 **)(base + 0x8D0);
    *(u8 **)(base + 0x8D0) = (u8 *)packet + 0xC;
    result = func_80066460(z0, 1, 0x140, z3);
    func_80067F20(packet, 1, 0, (u16)result, 0);

    {
        u32 *entry =
            (u32 *)(((u32)*(s32 *)(scratch + 0xC4) << 2) +
                (u32)*(u32 **)(scratch + 0x24));
        packet[0] = (packet[0] & code_mask) | (*entry & rgb_mask);
    }
    {
        u32 value = ((u32 *)*(u32 **)(scratch + 0x24))[*(s32 *)(scratch + 0xC4)];
        ((u32 *)*(u32 **)(scratch + 0x24))[*(s32 *)(scratch + 0xC4)] =
            (value & code_mask) | ((u32)packet & rgb_mask);
    }
}
