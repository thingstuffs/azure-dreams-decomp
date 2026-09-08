#include "common.h"

#define U8(base, offset) (*(u8 *)((u8 *)(base) + (offset)))
#define S16(base, offset) (*(s16 *)((u8 *)(base) + (offset)))
#define U16(base, offset) (*(u16 *)((u8 *)(base) + (offset)))
#define S32(base, offset) (*(s32 *)((u8 *)(base) + (offset)))
#define PTR(base, offset) (*(u8 **)((u8 *)(base) + (offset)))

extern s8 D_80083160[];

extern s32 func_80066460(s32, s32, s32, s32);
extern void func_8006658C(void *, void *);
extern void func_80066708(void *);
extern void func_80067F20(void *, s32, s32, s32, s32);

/* Queues four shaded quadrants and a draw-mode packet for each linked rectangle. */
s32 func_80026F68(void *rect_arg, void *owner_arg)
{
    u8 *rect_data;
    u8 *owner;
    u8 **render_state_ptr;
    s32 quadrant;
    u8 *render_state;
    u8 *packet;
    u8 *next_node;
    u16 center_coord;
    s16 edge_coord;
    s32 packet_word;

    rect_data = rect_arg;
    owner = owner_arg;
    render_state_ptr = (u8 **)D_80083160;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    quadrant = 3;

loop:
    render_state = *render_state_ptr;
    packet = PTR(render_state, 0x8D0);
    PTR(render_state, 0x8D0) = packet + 0x24;

    center_coord = U16(rect_data, 0);
    U16(packet, 0x18) = center_coord;
    U16(packet, 8) = center_coord;

    if (quadrant & 1) {
        edge_coord = U16(rect_data, 0) - U16(rect_data, 4);
    } else {
        edge_coord = U16(rect_data, 0) + U16(rect_data, 4);
    }
    S16(packet, 0x20) = edge_coord;
    S16(packet, 0x10) = edge_coord;

    center_coord = U16(rect_data, 2);
    U16(packet, 0x12) = center_coord;
    U16(packet, 0xA) = center_coord;

    if (quadrant & 2) {
        edge_coord = U16(rect_data, 2) - U16(rect_data, 6);
    } else {
        edge_coord = U16(rect_data, 2) + U16(rect_data, 6);
    }
    S16(packet, 0x22) = edge_coord;
    S16(packet, 0x1A) = edge_coord;

    packet_word = S32(rect_data, 8);
    S32(packet, 0x1C) = 0;
    S32(packet, 0xC) = 0;
    S32(packet, 0x14) = 0;
    S32(packet, 4) = packet_word;
    func_80066708(packet);

    quadrant--;
    U8(packet, 7) |= 2;
    func_8006658C(*render_state_ptr + ((S16(owner, 0xA) * 4) + 0xB0), packet);
    if (quadrant >= 0) {
        goto loop;
    }

    render_state = *render_state_ptr;
    packet = PTR(render_state, 0x8D0);
    PTR(render_state, 0x8D0) = packet + 0xC;
    packet_word = func_80066460(0, 2, 0, 0);
    func_80067F20(packet, 0, 0, packet_word & 0xFFFF, 0);
    func_8006658C(*render_state_ptr + ((S16(owner, 0xA) * 4) + 0xB0), packet);

    next_node = PTR(rect_data, -8);
    rect_data = next_node + 0x20;
    if (next_node != 0) {
        owner = PTR(next_node, 8);
        quadrant = 3;
        goto loop;
    }
    return 0;
}
