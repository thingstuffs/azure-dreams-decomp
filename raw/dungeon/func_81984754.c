#include "common.h"

typedef struct Pos {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    s16 z;
} Pos;

typedef struct Part {
    void *unk0;
    u8 pad4[4];
    void *table;
    u8 padC[4];
    u16 f10;
    u8 pad12[2];
    u16 flags;
    s16 f16;
    u8 pad18[2];
    s16 f1A;
} Part;

typedef struct History {
    u16 x;
    u16 y;
    u16 z;
    u16 pad6;
} History;

typedef struct Entity {
    u8 pad0[0x20];
    void *parent;
    void *next;
    u8 pad28[0x34 - 0x28];
    s16 f34;
    s16 f36;
    s16 angle;
    s16 f3A;
    s16 f3C;
    u8 pad3E[0x44 - 0x3E];
    s16 f44;
    u8 pad46[2];
    History history[8];
    s16 index;
    u8 pad8A[0x96 - 0x8A];
    s16 direction;
} Entity;

typedef struct Object {
    u8 pad0[8];
    Pos *pos;
    Part *part;
    void (*state)(void *);
    u8 pad14[0x20 - 0x14];
    Entity entity;
} Object;

extern u8 D_80024DAC[];
extern u8 D_80026B2C[];
extern u8 D_80026BBC[];
extern u8 D_80026BC8[];
extern u8 D_80080010[];
extern u8 D_80083498[];
extern u8 D_80083780[];
extern u8 D_800C9034[];

extern void func_80025FD4(void) __attribute__((noreturn));
extern void func_800260AC(void) __attribute__((noreturn));
extern void func_8002620C(void) __attribute__((noreturn));
extern void func_80026240(Entity *, void *);
extern void func_800262B0(Part *, s32);
extern s32 func_8003FA44(s32);
extern Object *func_8003FD64(s32, void *);
extern void func_8004491C(Object *, void *);
extern s32 func_800A07D0(s16, s16, s16, s16);

void *func_81984754(s32 x, s32 y, s32 z, s32 angle)
{
    Object *objects[9];
    u16 local_x;
    u16 local_y;
    u16 local_z;
    s32 angle_value;
    u8 *reference;
    Object **base;
    Object **cur;
    Pos *pos;
    Part *part;
    Entity *entity;
    Entity *previous;
    register Entity *call_entity ASM_REG("$4");
    void *call_data;
    register s32 i ASM_REG("$20");
    s32 j;
    s32 target;
    register s32 normalized_target ASM_REG("$2");
    s32 signed_target;
    s32 current;
    s32 difference;
    register u8 *allocation_page ASM_REG("$2");
    u8 *allocation_data;

    angle_value = angle;
    previous = 0;
    local_x = x;
    local_y = y;
    local_z = z;
    if (func_8003FA44(9) == 0) {
        register void *failure_result ASM_REG("$2");
        failure_result = previous;
        ASM_TAILSLOT_PIN_TIED(failure_result);
        func_8002620C();
        return failure_result;
    }

    i = 0;
    base = &objects[i];
    reference = D_80083780;
    cur = base;
    do {
#ifdef NON_MATCHING
        allocation_page = D_80080010 - 0x10;
#else
        allocation_page = (u8 *)0x80080000;
#endif
        if (i != 0) {
            register Object *prior ASM_REG("$5");
            prior = cur[-1];
            ASM_KEEP(prior);
            func_80025FD4();
        }
        ASM_KEEP(allocation_page);
        allocation_data = allocation_page + 0x3498;
        ASM_KEEP(i);
        *cur = func_8003FD64(2, allocation_data);
        (*cur)->state = (void (*)(void *))D_80024DAC;
        func_8004491C(*cur, D_800C9034);

        pos = (*cur)->pos;
        pos->x = local_x;
        pos->y = local_y;
        pos->z = local_z;

        part = (*cur)->part;
        part->f16 = 0x400;
        part->f1A = angle_value - 0x400;
        part->table = D_80026B2C + (i * 0x10);
        part->f10 = 0x60;
        part->flags |= 0xC;

        entity = &(*cur)->entity;
        if (i != 0) {
            register u32 link_value ASM_REG("$2");
            register u32 link_work ASM_REG("$3");
            link_value = (u32)D_80026BBC;
            link_work = link_value + i;
            ASM_KEEP(link_work);
            link_value = *(u8 *)link_work;
            if (link_value != 0) {
                link_work = 0x7FFFFFFF;
                link_value = (u32)base[link_value - 1] & link_work;
                ASM_KEEP(link_work);
                ASM_TAILSLOT_PIN_TIED(link_value);
                func_800260AC();
            } else {
                entity->parent = cur[-1];
            }
        }

        entity->f34 = 0x10;
        entity->angle = angle_value + 0x400;
        entity->f44 = ((u32)angle_value >> 9) & 7;
        entity->f3C = 0;
        entity->f3A = D_80026BC8[i] != 0 ? 0xF : 0;
        entity->f36 = 1;
        entity->index = i;

        if (previous != 0) {
            previous->next = *cur;
        }

        target = func_800A07D0(pos->x, pos->y,
                              *(s16 *)(reference + 2),
                              *(s16 *)(reference + 6));

        current = (u16)entity->angle;
        entity->angle = (current & 0x800)
            ? (current | 0xF800)
            : (current & 0x7FF);

        normalized_target = target & 0x800;
        if (normalized_target != 0) {
            normalized_target = target | 0xF800;
        } else {
            normalized_target = target & 0x7FF;
        }
        target = normalized_target;

        current = (s32)((u32)target << 16);
        signed_target = current >> 16;
        difference = (s16)entity->angle;
        difference -= signed_target;
        current = (u16)entity->angle;
        if (difference < 0) {
            difference = -difference;
        }
        if (difference >= 0x801) {
            entity->angle = (target & -0x1000) |
                            (current & 0xFFF);
        }

        entity->direction = (s16)entity->angle < signed_target;

        j = 7;
        do {
            entity->history[j].x = pos->x;
            entity->history[j].y = pos->y;
            entity->history[j].z = pos->z;
            j--;
        } while (j >= 0);

        func_800262B0(part, 0);
        call_entity = entity;
        ASM_KEEP(call_entity);
        call_data = part->unk0;
        previous = call_entity;
        ASM_KEEP(previous);
        cur++;
        i++;
        func_80026240(call_entity, call_data);
    } while (i < 9);

    return objects[0];
}
