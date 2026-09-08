#include "common.h"

typedef struct {
    u16 x;
    s16 y;
} Position;

typedef struct {
    u8 pad0[3];
    u8 size;
    u32 code;
    u16 x;
    s16 y;
    u32 data;
} Packet;

extern void func_8006658C(void *, void *);
extern void func_80067E2C(void *, void *);
extern void func_800B9144(Position *, s32, void *, s16);
extern s8 D_80083160[];
extern u8 D_801C9E40[16];

void func_800B8FC8(s32 arg0, Position *arg1, Position *arg2, s32 arg3, volatile s32 arg4)
{
    Position pos;
    s8 *context;
    void *first_context;
    void *ordering_table;
    Packet *packet;
    register s32 held_arg3 ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 shifted ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 held_arg4;
    s32 y;

    context = *(s8 **)D_80083160;
    held_arg3 = arg3;
    shifted = context != (s8 *)D_801C9E40;
    packet = *(Packet **)(context + 0x8D0);
    ordering_table = context + 0x8B0;
    *(Packet **)(context + 0x8D0) = (Packet *)((u8 *)packet + 0xC);
    first_context = *(void * volatile *)D_80083160;
    held_arg4 = arg4;
    ASM_KEEP_DEP_NV(packet, held_arg4);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    func_80067E2C(packet, first_context);
    func_8006658C(ordering_table, packet);

    pos.x = arg2->x;
    y = arg2->y;
    {
        s8 **context_slot;

        if (shifted) {
            y -= 0xE0;
        }
        context_slot = (s8 **)D_80083160;
        pos.y = y;
        func_800B9144(&pos, arg0, ordering_table, (s16)held_arg4);

        if ((u16)held_arg3 != 0) {
            Packet *packet2;

            context = *context_slot;
            packet2 = *(Packet **)(context + 0x8D0);
            *(Packet **)(context + 0x8D0) = (Packet *)((u8 *)packet2 + 0x10);
            packet2->code = 0x60000000;
            packet2->size = 3;
            packet2->x = arg1->x;
            y = arg1->y;
            if (shifted) {
                y -= 0xE0;
            }
            packet2->y = y;
            packet2->data = *(u32 *)((u8 *)arg1 + 4);
            func_8006658C(ordering_table, packet2);
        }
        ASM_KEEP(held_arg3);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        context = *context_slot;
        packet = *(Packet **)(context + 0x8D0);
        *(Packet **)(context + 0x8D0) = (Packet *)((u8 *)packet + 0xC);
        func_80067E2C(packet, arg1);
        func_8006658C(ordering_table, packet);
    }
}

/* MECHANISM: A two-halfword Position stack object preserves both stores passed by address.
   Split arg2/context-slot live ranges target s1 reuse; the global value remains reloadable.
   Natural long-lived arguments and packet bases are intended to produce the nine-register frame. */
