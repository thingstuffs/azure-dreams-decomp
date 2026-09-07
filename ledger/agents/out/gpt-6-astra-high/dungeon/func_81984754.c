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

/* Create nine linked objects and initialize their positions, headings, and position histories. */
void *func_81984754(s32 x, s32 y, s32 z, s32 angle)
{
    Object *objects[9];
    u16 spawn_x;
    u16 spawn_y;
    u16 spawn_z;
    s32 spawn_angle;
    u8 *target_pos;
    Object **object_base;
    Object **object_slot;
    Pos *pos;
    Part *part;
    Entity *entity;
    Entity *prev_entity;
    Entity *update_entity;
    void *part_data;
    register s32 object_index ASM_REG("$20");   /* MATCH pin: retail register colouring depends on it */
    s32 history_index;
    s32 target_angle;
    s32 normalized_target;
    s32 signed_target;
    s32 angle_bits;
    s32 angle_delta;
    register u8 *allocation_page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *allocation_data;

    spawn_angle = angle;
    prev_entity = 0;
    spawn_x = x;
    spawn_y = y;
    spawn_z = z;
    if (func_8003FA44(9) == 0) {
        register void *failure_result ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        failure_result = prev_entity;
        ASM_TAILSLOT_PIN_TIED(failure_result);   /* MATCH pin: retail delay-slot contents depend on it */
        func_8002620C();
        return failure_result;
    }

    object_index = 0;
    object_base = &objects[object_index];
    target_pos = D_80083780;
    object_slot = object_base;
    do {
#ifdef NON_MATCHING
        allocation_page = D_80080010 - 0x10;
#else
        allocation_page = (u8 *)0x80080000;
#endif
        if (object_index != 0) {
            register Object *prev_object ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
            prev_object = object_slot[-1];
            ASM_KEEP(prev_object);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            func_80025FD4();
        }
        ASM_KEEP(allocation_page);   /* MATCH pin: retail immediate-load split depends on it */
        allocation_data = allocation_page + 0x3498;
        ASM_KEEP(object_index);   /* MATCH pin: retail immediate-load split depends on it */
        *object_slot = func_8003FD64(2, allocation_data);
        (*object_slot)->state = (void (*)(void *))D_80024DAC;
        func_8004491C(*object_slot, D_800C9034);

        pos = (*object_slot)->pos;
        pos->x = spawn_x;
        pos->y = spawn_y;
        pos->z = spawn_z;

        part = (*object_slot)->part;
        part->f16 = 0x400;
        part->f1A = spawn_angle - 0x400;
        part->table = D_80026B2C + (object_index * 0x10);
        part->f10 = 0x60;
        part->flags |= 0xC;

        entity = &(*object_slot)->entity;
        if (object_index != 0) {
            u32 parent_link;
            u32 link_scratch;
            parent_link = (u32)D_80026BBC;
            link_scratch = parent_link + object_index;
            parent_link = *(u8 *)link_scratch;
            if (parent_link != 0) {
                link_scratch = 0x7FFFFFFF;
                parent_link = (u32)object_base[parent_link - 1] & link_scratch;
                ASM_TAILSLOT_PIN_TIED(parent_link);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                func_800260AC();
            } else {
                entity->parent = object_slot[-1];
            }
        }

        entity->f34 = 0x10;
        entity->angle = spawn_angle + 0x400;
        entity->f44 = ((u32)spawn_angle >> 9) & 7;
        entity->f3C = 0;
        entity->f3A = D_80026BC8[object_index] != 0 ? 0xF : 0;
        entity->f36 = 1;
        entity->index = object_index;

        if (prev_entity != 0) {
            prev_entity->next = *object_slot;
        }

        target_angle = func_800A07D0(pos->x, pos->y,
                              *(s16 *)(target_pos + 2),
                              *(s16 *)(target_pos + 6));

        angle_bits = (u16)entity->angle;
        entity->angle = (angle_bits & 0x800)
            ? (angle_bits | 0xF800)
            : (angle_bits & 0x7FF);

        normalized_target = target_angle & 0x800;
        if (normalized_target != 0) {
            normalized_target = target_angle | 0xF800;
        } else {
            normalized_target = target_angle & 0x7FF;
        }
        target_angle = normalized_target;

        angle_bits = (s32)((u32)target_angle << 16);
        signed_target = angle_bits >> 16;
        angle_delta = (s16)entity->angle;
        angle_delta -= signed_target;
        angle_bits = (u16)entity->angle;
        if (angle_delta < 0) {
            angle_delta = -angle_delta;
        }
        if (angle_delta >= 0x801) {
            entity->angle = (target_angle & -0x1000) |
                            (angle_bits & 0xFFF);
        }

        entity->direction = (s16)entity->angle < signed_target;

        history_index = 7;
        do {
            entity->history[history_index].x = pos->x;
            entity->history[history_index].y = pos->y;
            entity->history[history_index].z = pos->z;
            history_index--;
        } while (history_index >= 0);

        func_800262B0(part, 0);
        update_entity = entity;
        ASM_KEEP(update_entity);   /* MATCH pin: keeps a statement from moving across a call/branch */
        part_data = part->unk0;
        prev_entity = update_entity;
        ASM_KEEP(prev_entity);   /* MATCH pin: keeps a statement from moving across a call/branch */
        object_slot++;
        object_index++;
        func_80026240(update_entity, part_data);
    } while (object_index < 9);

    return objects[0];
}
