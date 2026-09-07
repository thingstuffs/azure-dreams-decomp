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

void func_81820DB4(DungeonObj *arg)
{
    register DungeonObj *obj ASM_REG("$18") = arg;
    s32 i;
    s32 value;
    s32 base;
    s32 random_value;
    s32 bcb_height;
    s32 packet_angle;
    s32 packet_height;
    u8 *vertex;
    LocalPacket packet;

    ASM_KEEP(obj);

    obj->parent->timer |= 0x8000;
    value = obj->timer--;
    if ((s16)value < 0) {
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
        i = (-*(s16 *)((u8 *)obj + 0x0E) >> 2) + 15;
        if (i < 16) {
            i = 16;
        }
        obj->red = (((func_80069EF8() & 15) + 0xBE) << 4) / i;
        obj->green = (((func_80069EF8() & 15) + 0x91) << 4) / i;
        obj->blue = (((func_80069EF8() & 15) + 10) << 4) / i;
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

    bcb_height = obj->height;
    ASM_SCHED_BARRIER();
    bcb_height = (s16)(bcb_height - 0x30);
    i = (s16)func_800BCB04(*(u16 *)((u8 *)obj + 6),
                           *(u16 *)((u8 *)obj + 0x0A), bcb_height);
    if (i < 0x200) {
        obj->height = i;
    }

    if (obj->state < 2) {
        obj->dz += 0x1700;
        obj->z += obj->dz;

        i = -*(s16 *)((u8 *)obj + 0x0E);
        random_value = func_80069EF8();
        base = (i >> 1) + ((i >> 3) * (i >> 4));
        i = 3;
        random_value &= 7;
        random_value += 8;
        value = base + random_value;
        obj->vy1 = value;
        obj->vx0 = value;

        random_value = func_80069EF8();
        ASM_SCHED_BARRIER();
        vertex = (u8 *)obj + 0x18;
        value = (random_value & 7) + 8;
        base += value;
        base = -base;
        obj->vy3 = base;
        obj->vx2 = base;
        obj->vx3 = 0;
        obj->vy2 = 0;
        obj->vx1 = 0;
        obj->vy0 = 0;
        obj->angle2 += 0x100;

        do {
            *(u16 *)(vertex + 0x2C) = func_80069EF8() & 15;
            vertex -= 8;
        } while (--i >= 0);

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
        register LocalPacket *packet_ptr ASM_REG("$4") = &packet;
        ASM_KEEP(packet_ptr);
        packet_angle = *(u16 *)((u8 *)obj + 0x0E);
        ASM_SCHED_BARRIER();
        packet_height = obj->height;
        ASM_SCHED_BARRIER();
        packet_height += packet_angle << 1;
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
        DungeonFinalView *view = (DungeonFinalView *)obj;
        i = 3;
        do {
            view->block.v[i].x += *(u16 *)((u8 *)obj + 0x12);
            view->block.v[i].y += *(u16 *)((u8 *)obj + 0x16);
        } while (--i >= 0);
        }
    }
}
