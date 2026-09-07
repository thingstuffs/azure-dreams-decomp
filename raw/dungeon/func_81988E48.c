#include "common.h"

#ifdef __GNUC__
#define NORETURN __attribute__((noreturn))
#else
#define NORETURN
#endif

typedef struct MainObject {
    void *link;
    u8 pad04[0x18];
    s32 x;
    s32 y;
    s32 z;
    u8 pad28[0x18];
    s16 tex_u;
    s16 tex_v;
    s16 size_a;
    s16 size_b;
    s16 age;
    s16 timer;
    s16 state;
    u16 angle;
    s16 value_a;
    s16 value_b;
} MainObject;

typedef struct LinkObject {
    u8 pad00[0x52];
    u16 flags;
} LinkObject;

typedef struct Vec3 {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

typedef struct ChildObject {
    void *resource;
    u8 byte04;
    u8 byte05;
    u8 pad06[2];
    void *resource_data;
    u32 color;
    u16 life;
    u8 pad12[2];
    volatile u16 flags;
    u8 pad16[6];
    s16 scale_x;
    s16 scale_y;
} ChildObject;

typedef struct EffectObject {
    u8 pad00[8];
    Vec3 *position;
    ChildObject *child;
    void *callback;
    u8 pad14[12];
    void *owner;
    u8 pad24[0x48];
    s16 state;
} EffectObject;

typedef struct EffectTail {
    void *owner;
    u8 pad24[0x48];
    s16 state;
} EffectTail;

typedef struct Resource {
    u32 pad00;
    void *data;
} Resource;

typedef struct GlobalFlag {
    s32 value;
    s32 pad04[2];
} GlobalFlag;

extern u8 D_80082E80[];
extern u8 D_80083498[];
extern s16 D_80083780[];
extern GlobalFlag D_800814A0;
extern s32 D_80024AA4;
extern s32 D_80045340;
extern u8 D_800DEC00[];

extern void func_80024908(void) NORETURN;
extern void func_80024948(void);
extern void func_8002494C(void) NORETURN;
extern s32 func_8003DE58(void *, void *, s16 *, s32);
extern EffectObject *func_8003FD64(s32, void *);
extern void func_8004491C(EffectObject *, void *);
extern s32 func_800644B8(s32);
extern s32 func_80066460(s32, s32, s32, s32);
extern s32 func_8006649C(s32, s32);
extern s32 func_80069EF8(void);

void func_81988E48(MainObject *obj)
{
    s16 hit[3];
    register s32 state_count ASM_REG("$16");
    register s32 count ASM_REG("$19");
    EffectObject *effect;
    volatile EffectTail *tail;
    ChildObject *child;
    void *callback;
    Resource *resource;
    register u8 *call_data ASM_REG("$5");
    s32 state;
    s32 case3;

    obj->age++;
    ((LinkObject *)obj->link)->flags |= 0x8000;
    state_count = -1;

    state = obj->state;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        ASM_KEEP_NV(state_count);
        if (state == 0) {
            goto state_0;
        }
        ASM_KEEP(state_count);
        func_8002494C();
    }
    if (state == 2) {
        goto state_2;
    }
    case3 = 3;
    ASM_USE_NV(case3);
    ASM_KEEP_NV(state_count);
    count = state_count;
    if (state == case3) {
        goto state_3;
    }
    ASM_KEEP(count);
    func_8002494C();

state_0:
        count = state_count;
        ASM_KEEP(count);
        obj->value_a = func_80066460(0, 1, 0x2C0, 0x100);
        obj->value_b = func_8006649C(0x80, 0x1F7);
        obj->size_b = 0x1F;
        obj->size_a = 0x1F;
        obj->age = 0;
        obj->angle = 0x30;
        obj->state++;
state_1:
        state_count = 14;
        call_data = D_80082E80;
        if (func_8003DE58(*(void **)(call_data + 8), call_data, hit, 0)) {
            obj->x += (hit[0] + D_80083780[1] - *(s16 *)((u8 *)obj + 0x1E)) << 14;
            obj->y += (hit[1] + D_80083780[3] - *(s16 *)((u8 *)obj + 0x22)) << 14;
            obj->z += (hit[2] + D_80083780[5] - *(s16 *)((u8 *)obj + 0x26)) << 14;
            obj->z -= func_800644B8((obj->age << 11) / 10) << 9;
        }
        if (obj->age >= 10) {
            register u16 old_state ASM_REG("$2") = obj->state;
            register u16 new_timer ASM_REG("$3") = 0x10;

            ASM_USE_NV(old_state);
            obj->timer = new_timer;
            func_80024908();
            return;
        }
        goto state_done;

state_2:
        state_count = 9;
        if (obj->age >= 11) {
            state_count = 4;
        }
        obj->angle += 2;
        call_data = D_80082E80;
        if (func_8003DE58(*(void **)(call_data + 8), call_data, hit, 0)) {
            obj->x += (hit[0] + D_80083780[1] - *(s16 *)((u8 *)obj + 0x1E)) << 15;
            obj->y += (hit[1] + D_80083780[3] - *(s16 *)((u8 *)obj + 0x22)) << 15;
            obj->z += (hit[2] + D_80083780[5] - *(s16 *)((u8 *)obj + 0x26)) << 15;
        }
        if (obj->age >= 13) {
            obj->age = 8;
        }
        obj->timer--;
        if (obj->timer > 0) {
            goto state_done;
        }
        if (obj->age == 12) {
            obj->state++;
            func_80024948();
            return;
        }
        goto state_done;

state_3:
        ASM_USE2_NV(count, state_count);
        state_count = 5;
        if (obj->age == 15) {
            ((u16 *)obj)[-1] |= 0x8000;
            D_800814A0.value |= 0x8000;
        }
        goto state_done;

state_done:

    count = state_count;

    obj->tex_u = (obj->age & 3) << 5;
    obj->tex_v = ((s16)obj->age >> 2) * 32 + 0x80;

    if (count < 0) {
        return;
    }

    callback = &D_80024AA4;
    resource = (Resource *)D_800DEC00;
    do {
        effect = func_8003FD64(0x312, D_80083498);
        if (effect != (EffectObject *)0) {
            effect->callback = callback;
            func_8004491C(effect, &D_80045340);
            child = effect->child;

            effect->position->x = obj->x +
                (((func_80069EF8() & 0x3FF) - 0x1FF) << 12);
            effect->position->y = obj->y +
                (((func_80069EF8() & 0x3FF) - 0x1FF) << 12);
            effect->position->z = obj->z +
                (((func_80069EF8() & 0x3FF) - 0x1FF) << 11);

            child->scale_y = 0x1000;
            child->scale_x = 0x1000;
            child->life = 0x60;
            child->resource = resource;
            child->flags |= 0xC;
            child->resource_data = resource->data;
            child->byte04 = 0;
            child->byte05 = 0;
            child->color = 0x00808080;
            effect->owner = obj->link;
            tail = (EffectTail *)&effect->owner;
            tail->state = 0;
        }
        count--;
    } while (count >= 0);
}
