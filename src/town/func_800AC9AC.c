#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))
#define OTSLOT() FIELD(FIELD(scratch, u32 *, 0x24), u32, FIELD(scratch, s32, 0xC4) * 4)

extern u8 *D_80083160[3];

extern void func_800649A0(void);
extern void func_80064A40(void);
extern s32 func_800654B0(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80066640(void *, s32);
extern void func_80066844(void *);
extern void func_80067F20(void *, s32, s32, u16, s32);
extern s32 rand(void);
extern void func_800A1330(void *, void *);
extern void func_800A2DF0(void *, void *);
extern void func_800AA068(void *, void *, void *);

void func_800AA10C(u8 *arg0, void *arg1)
{
    u8 *scratch;
    u8 *initialState;
    u8 *vertexBase;
    u32 *masks;
    s16 *indices;
    u8 *p74;
    u8 *p7C;
    u8 *p84;
    u8 *p8C;
    u8 *p44;
    u8 *state;
    u8 **statePtr;
    u32 *poly;
    u32 *packet;
    s32 random;
    u32 rgbMask;
    u32 codeMask;

    indices = FIELD(arg0, s16 *, 4);
    vertexBase = FIELD(arg0, u8 *, 0);
    statePtr = D_80083160;
    initialState = *statePtr;
    masks = FIELD(arg0, u32 *, 0x20);
    scratch = (u8 *)0x1F800000;
    FIELD(scratch, u8 *, 0x24) = initialState + 0xB0;

    if (*indices != -1) {
        p74 = scratch + 0x74;
        p7C = scratch + 0x7C;
        p84 = scratch + 0x84;
        p8C = scratch + 0x8C;
        p44 = scratch + 0x44;
        rgbMask = 0x00FFFFFF;

        do {
            state = *statePtr;
            poly = FIELD(state, u32 *, 0x8D0);
            FIELD(state, u8 *, 0x8D0) = (u8 *)poly + 0x28;

            random = rand();
            poly[1] = (random * rand()) & masks[0];
            random = rand();
            poly[3] = (random * rand()) & masks[1];
            random = rand();
            poly[5] = (random * rand()) & masks[2];
            random = rand();
            poly[7] = (random * rand()) & masks[3];

            func_80066844(poly);
            func_80066640(poly, 1);

            func_800A1330(p74, vertexBase + (indices[0] * 8));
            func_800A1330(p7C, vertexBase + (indices[1] * 8));
            func_800A1330(p84, vertexBase + (indices[2] * 8));
            func_800A1330(p8C, vertexBase + (indices[3] * 8));

            func_800649A0();
            func_800AA068(arg0, p74, p44);
            func_800AA068(arg0, p7C, p44);
            func_800AA068(arg0, p84, p44);
            func_800AA068(arg0, p8C, p44);
            func_80064A40();

            func_800A2DF0(p74, arg1);
            func_800A2DF0(p7C, arg1);
            func_800A2DF0(p84, arg1);
            func_800A2DF0(p8C, arg1);

            FIELD(scratch, s32, 0xC4) = func_800654B0(
                p74, p7C, p84, p8C,
                scratch + 0xE8, scratch + 0xEC,
                scratch + 0xF0, scratch + 0xF4,
                scratch + 0x94, scratch + 0x98) - 0x30;

            FIELD(poly, u16, 0x08) = FIELD(scratch, u16, 0xE8);
            FIELD(poly, u16, 0x0A) = FIELD(scratch, u16, 0xEA);
            FIELD(poly, u16, 0x10) = FIELD(scratch, u16, 0xEC);
            FIELD(poly, u16, 0x12) = FIELD(scratch, u16, 0xEE);
            FIELD(poly, u16, 0x18) = FIELD(scratch, u16, 0xF0);
            FIELD(poly, u16, 0x1A) = FIELD(scratch, u16, 0xF2);
            FIELD(poly, u16, 0x20) = FIELD(scratch, u16, 0xF4);
            FIELD(poly, u16, 0x22) = FIELD(scratch, u16, 0xF6);

            if (FIELD(scratch, s32, 0xC4) >= 0x1E0)
                FIELD(scratch, s32, 0xC4) = 0x1DF;
            if (FIELD(scratch, s32, 0xC4) < 0)
                FIELD(scratch, s32, 0xC4) = 0;

            state = *statePtr;
            packet = FIELD(state, u32 *, 0x8D0);
            FIELD(state, u8 *, 0x8D0) = (u8 *)packet + 0xC;
            func_80067F20(packet, 1, 0,
                          (u16)func_80066460(0, 0, 0x140, 0), 0);

            codeMask = 0xFF000000;
            packet[0] = (packet[0] & codeMask) | (OTSLOT() & rgbMask);
            OTSLOT() = (OTSLOT() & codeMask) | ((u32)packet & rgbMask);
            poly[0] = (poly[0] & codeMask) | (OTSLOT() & rgbMask);
            OTSLOT() = (OTSLOT() & codeMask) | ((u32)poly & rgbMask);

            state = *statePtr;
            packet = FIELD(state, u32 *, 0x8D0);
            FIELD(state, u8 *, 0x8D0) = (u8 *)packet + 0xC;
            func_80067F20(packet, 1, 0,
                          (u16)func_80066460(0, 1, 0x140, 0), 0);

            codeMask = 0xFF000000;
            indices += 4;
            packet[0] = (packet[0] & codeMask) | (OTSLOT() & rgbMask);
            OTSLOT() = (OTSLOT() & codeMask) | ((u32)packet & rgbMask);
        } while (*indices != -1);
    }
}
