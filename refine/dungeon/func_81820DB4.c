#include "common.h"

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
} DungeonVertex;

typedef struct {
    u8 pad[0x10];
    DungeonVertex v[4];
} DungeonVertexBlock;

typedef struct {
    u8 pad[0x18];
    DungeonVertexBlock block;
} DungeonFinalView;

typedef struct DungeonObj DungeonObj;

struct DungeonObj {
    DungeonObj *parent;
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
    u8 pad1C[0x0C];
    u16 vx0;
    u16 vy0;
    u16 vr0;
    u16 pad2E;
    u16 vx1;
    u16 vy1;
    u16 vr1;
    u16 pad36;
    u16 vx2;
    u16 vy2;
    u16 vr2;
    u16 pad3E;
    u16 vx3;
    u16 vy3;
    u16 vr3;
    u16 pad46;
    u8 red;
    u8 green;
    u8 blue;
    u8 pad4B;
    u16 angle;
    u16 angle2;
    u16 height;
    u16 timer;
    s16 aux;
    s16 state;
};

typedef struct {
    void *p0;
    void *p4;
    s16 h8;
    s16 hA;
    u16 angle;
    s16 padE;
    s16 x;
    s16 y;
    u16 height;
    s16 pad16;
    s16 type;
    s16 pad1A;
} LocalPacket;

extern s32 D_800814A0;
extern void func_80024674(void) __attribute__((noreturn));
extern void func_80024764(void) __attribute__((noreturn));
extern void func_800249FC(void) __attribute__((noreturn));
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80069EF8(void);
extern s32 func_800BCB04(s32, s32, s16);
extern void func_800DBA90(LocalPacket *, s32);

/* Update a dungeon effect's motion, flickering vertices, and fade state. */
void func_81820DB4(DungeonObj *effect)
{
    register DungeonObj *obj ASM_REG("$18") = effect;   /* MATCH pin: keeps a constant in a register as retail does */
    s32 height_or_index;
    s32 old_timer;
    s32 vertex_extent;
    s32 size_jitter;
    s32 vertex_size;
    s32 size_random;
    s32 query_height;
    s32 z_offset;
    s32 packet_height;
    u8 *vertex_cursor;
    LocalPacket packet;

    ASM_KEEP(obj);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    obj->parent->timer |= 0x8000;
    old_timer = obj->timer--;
    if ((s16)old_timer < 0) {
        obj->state++;
        if (obj->state == 1) {
            goto state_one;
        }
        if (obj->state == 2) {
            goto state_two;
        }
        func_80024674();
        return;
state_one:
        obj->timer = 5;
        if (obj->aux >= 0) {
            goto transition_done;
        }
        obj->state++;
state_two:
        obj->timer = 12;
        obj->dx *= 2;
        obj->dy *= 2;
    }

transition_done:
    if (obj->state == 1) {
        if (*(s16 *)((u8 *)obj + 0x52) < 5) {
            obj->aux = 1;
            obj->red += (0xFF - obj->red) >> 2;
            obj->green += (0x80 - obj->green) >> 2;
            func_80024764();
            return;
        }
    }

    if (obj->state < 2) {
        height_or_index = (-*(s16 *)((u8 *)obj + 0x0E) >> 2) + 15;
        if (height_or_index < 16) {
            height_or_index = 16;
        }
        obj->red = (((func_80069EF8() & 15) + 0xBE) << 4) / height_or_index;
        obj->green = (((func_80069EF8() & 15) + 0x91) << 4) / height_or_index;
        obj->blue = (((func_80069EF8() & 15) + 10) << 4) / height_or_index;
    }

    obj->angle = (obj->angle + ((func_80069EF8() & 0xFF)
                  - (*(u16 *)((u8 *)obj + 0x0E) << 2))) & 0xFFF;

    if (obj->z < (s32)0xFFD00000 || obj->state == 3) {
        *((u16 *)obj - 1) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

    if (obj->state == 0) {
        obj->x += obj->dx;
        obj->y += obj->dy;
    }

    query_height = obj->height;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    query_height = (s16)(query_height - 0x30);
    height_or_index = (s16)func_800BCB04(*(u16 *)((u8 *)obj + 6),
                           *(u16 *)((u8 *)obj + 0x0A), query_height);
    if (height_or_index < 0x200) {
        obj->height = height_or_index;
    }

    if (obj->state < 2) {
        obj->dz += 0x1700;
        obj->z += obj->dz;

        height_or_index = -*(s16 *)((u8 *)obj + 0x0E);
        size_random = func_80069EF8();
        vertex_size = (height_or_index >> 1) + ((height_or_index >> 3) * (height_or_index >> 4));
        height_or_index = 3;
        size_random &= 7;
        size_random += 8;
        vertex_extent = vertex_size + size_random;
        obj->vy1 = vertex_extent;
        obj->vx0 = vertex_extent;

        size_random = func_80069EF8();
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        vertex_cursor = (u8 *)obj + 0x18;
        size_jitter = (size_random & 7) + 8;
        vertex_size += size_jitter;
        vertex_size = -vertex_size;
        obj->vy3 = vertex_size;
        obj->vx2 = vertex_size;
        obj->vx3 = 0;
        obj->vy2 = 0;
        obj->vx1 = 0;
        obj->vy0 = 0;
        obj->angle2 += 0x100;

        do {
            *(u16 *)(vertex_cursor + 0x2C) = func_80069EF8() & 15;
            vertex_cursor -= 8;
        } while (--height_or_index >= 0);

        packet.p0 = &obj->vx0;
        packet.p4 = &obj->vx0;
        packet.hA = 0;
        packet.h8 = 0;
        packet.angle = obj->angle;
        packet.x = *(u16 *)((u8 *)obj + 6)
                 + (func_80064584(*(s16 *)((u8 *)obj + 0x4E)
                    + (*(s16 *)((u8 *)obj + 0x0E) << 4)) >> 8);
        packet.y = *(u16 *)((u8 *)obj + 0x0A)
                 + (func_800644B8(*(s16 *)((u8 *)obj + 0x4E)
                    + (*(s16 *)((u8 *)obj + 0x0E) << 4)) >> 8);
        {
            LocalPacket *packet_ptr = &packet;
            ASM_KEEP(packet_ptr);   /* MATCH pin: retail schedule: same instructions, different order without it */
            z_offset = *(u16 *)((u8 *)obj + 0x0E);
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            packet_height = obj->height;
            packet_height += z_offset << 1;
            packet.height = packet_height;
            packet.type = 4;
            packet.pad1A = 0;
            func_800DBA90(packet_ptr, packet_height);
        }
        func_800249FC();
        return;
    }

    obj->red -= obj->red >> 2;
    obj->green -= obj->green >> 2;
    obj->blue -= obj->blue >> 2;
    if (*(s16 *)((u8 *)obj + 0x52) < 10) {
        {
            DungeonFinalView *vertex_view = (DungeonFinalView *)obj;
            height_or_index = 3;
            do {
                vertex_view->block.v[height_or_index].x += *(u16 *)((u8 *)obj + 0x12);
                vertex_view->block.v[height_or_index].y += *(u16 *)((u8 *)obj + 0x16);
            } while (--height_or_index >= 0);
        }
    }
}
