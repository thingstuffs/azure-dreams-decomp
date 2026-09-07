#include "common.h"

typedef struct Entity {
    u8 pad00[0x13];
    u8 kind;
    u8 pad14[8];
    u32 flags;
    u8 pad20[0x68];
    s16 height;
} Entity;

typedef struct Node {
    Entity *entity;
} Node;

typedef union WorkY {
    s32 whole;
    struct {
        u16 lo;
        s16 angle;
    } half;
} WorkY;

typedef struct Work {
    Node *node;
    s32 x;
    WorkY y;
    s16 state;
    s16 timer;
    u16 counter;
    s16 mode;
    s32 cur_x;
    s32 cur_y;
    s16 amp;
    s16 pad1e;
    s16 bias;
    u16 pad22;
    u16 phase;
    u8 pad26[6];
    s32 handle;
} Work;

typedef struct Render {
    void *primitive;
    u8 pad04[8];
    s32 flags;
    u8 pad10[8];
    s16 rot_x;
    s16 rot_y;
} Render;

typedef struct Out {
    u8 pad00[2];
    s16 x;
    u8 pad04[2];
    s16 y;
    s32 z;
} Out;

typedef struct GlobalObj {
    u8 pad00[0xAC];
    Entity *left;
    Entity *right;
} GlobalObj;

extern u8 D_80083160[];
extern s32 D_800814A0[3];
extern GlobalObj *D_800814A8[3];
extern u8 D_80083460[16];
extern s16 D_800DCE66[5];
extern u8 D_800DDC40[16];
extern GlobalObj *D_800E3D7C[3];

extern s32 func_800644B8();
extern s32 func_80064584();
extern s32 func_80098C80();
extern s32 func_80098920();
extern s32 func_800BA33C();
extern void func_800478B8();
extern void func_8009F644();
extern void func_800C77D0();
extern void func_800B9BE4();
extern void func_800B9CB0();
extern void func_800B9EE4();
extern void func_800B9F18() __attribute__((noreturn));
extern void func_800B9F60();
extern void func_800BA050();

void func_800B9A78(Work *w, Out *out, Render *render_arg)
{
    register Render *render;
    register u8 *controls_page ASM_REG("$2");
    register u8 *controls ASM_REG("$19");
    s32 n;
    s32 t;
    s32 r;
    u32 input;

    ASM_KEEP_NV(render);
    controls_page = (u8 *)0x80080000;
    ASM_KEEP_DEP_NV(controls_page, render);
    render = render_arg;
    controls = controls_page + 0x3160;

    {
    Node *node;
    s32 *target;
    node = w->node;
    target = *(s32 **)((u8 *)node->entity - 0x18);
    if (w->timer != 0) {
        w->cur_x += (target[0] - w->cur_x) / w->timer;
        w->cur_y += (target[1] - w->cur_y) / w->timer;
        if (w->mode != 2) {
            register u8 *height_base ASM_REG("$3");
            register Entity *height_entity ASM_REG("$4");
            s32 current_y;
            r = func_800644B8(w->timer << 8);
            height_base = (u8 *)w->node;
            current_y = w->y.whole;
            height_entity = ((Node *)height_base)->entity;
            height_base = (u8 *)0x800E0000;
            ASM_KEEP_NV(height_base);
            height_entity = (Entity *)(u32)height_entity->kind;
            ASM_SCHED_BARRIER();
            height_base -= 0x23C0;
            ASM_KEEP_DEP_NV(height_base, height_entity);
            height_entity = (Entity *)((u8 *)height_entity + (u32)height_base);
            ASM_KEEP_NV(height_entity);
            t = (target[2] - ((s32)*(u8 *)height_entity << 16) - current_y) / w->timer;
            t -= (r * w->timer) << 6;
            w->y.whole += t;
            if (w->node->entity->flags & 0x80000) {
                w->y.half.angle -= 0x80;
                func_800B9BE4();
                return;
            }
        } else {
            w->y.whole += (((s32)w->node->entity->height << 16) - w->y.whole) / w->timer;
        }
    }

    if (--w->timer <= 0) {
        w->cur_x = target[0];
        w->cur_y = target[1];
        if (w->mode != 2) {
            register u8 *height_base ASM_REG("$2");
            register Entity *entity ASM_REG("$4");
            register u8 *height_addr ASM_REG("$3");
            s32 angle;
            height_base = (u8 *)w->node;
            entity = ((Node *)height_base)->entity;
            height_base = (u8 *)0x800E0000;
            ASM_KEEP_NV(height_base);
            height_base -= 0x23C0;
            ASM_KEEP_NV(height_base);
            height_addr = (u8 *)(u32)entity->kind;
            angle = entity->height;
            height_addr += (u32)height_base;
            ASM_KEEP_NV(height_addr);
            height_base = (u8 *)(u32)*height_addr;
            angle -= (s32)(u32)height_base;
            if (entity->flags & 0x40000) {
                angle -= 0x40;
            }
            w->y.half.angle = angle;
            if (w->node->entity->flags & 0x80000) {
                w->y.half.angle = angle - 0x80;
                func_800B9CB0();
                return;
            }
        } else {
            w->y.half.angle = w->node->entity->height;
        }
        w->timer = 0;
    }
    }

    if (w->state == 0) {
        if (w->timer == 0) {
            if ((*(u32 *)(controls + 0x10) & 2) != 0) {
                register u8 *objects_page ASM_REG("$17");
                register u8 *status_page ASM_REG("$2");
                register s32 new_timer ASM_REG("$3");
                GlobalObj *object;
                Entity *left;
                objects_page = (u8 *)0x800E0000;
                ASM_KEEP_NV(objects_page);
                left = (*(GlobalObj **)(objects_page + 0x3D7C))->left;
                if (func_800BA33C(left)) {
                    status_page = (u8 *)0x80080000;
                    ASM_KEEP_NV(status_page);
                    if ((*(GlobalObj **)(status_page + 0x14A8))->left != w->node->entity) {
                        new_timer = 8;
                        ASM_KEEP_NV(new_timer);
                        object = *(GlobalObj **)(objects_page + 0x3D7C);
                        w->timer = new_timer;
                        w->node = (Node *)&object->left;
                        if (w->mode == 2) {
                            ((Render *)render)->flags = 0x00101080;
                        }
                    }
                }
            }
            if ((*(u32 *)(controls + 0x10) & 1) != 0) {
                register u8 *objects_page ASM_REG("$17");
                register u8 *status_page ASM_REG("$2");
                register s32 new_timer ASM_REG("$3");
                GlobalObj *object;
                Entity *right;
                objects_page = (u8 *)0x800E0000;
                ASM_KEEP_NV(objects_page);
                right = (*(GlobalObj **)(objects_page + 0x3D7C))->right;
                if (func_800BA33C(right)) {
                    status_page = (u8 *)0x80080000;
                    ASM_KEEP_NV(status_page);
                    if ((*(GlobalObj **)(status_page + 0x14A8))->right != w->node->entity) {
                        new_timer = 8;
                        ASM_KEEP_NV(new_timer);
                        object = *(GlobalObj **)(objects_page + 0x3D7C);
                        w->timer = new_timer;
                        w->node = (Node *)&object->right;
                        if (w->mode == 2) {
                            ((Render *)render)->flags = 0x00801010;
                        }
                    }
                }
            }
        }

        input = *(u32 *)(controls + 0x10);
        if (input & 0x20) {
            register u8 *tail_base ASM_REG("$3");
            if (w->mode != 0) {
                goto finish;
            }
            tail_base = (u8 *)0x80080000;
            ASM_KEEP_NV(tail_base);
            tail_base += 0x3460;
            ASM_TAILSLOT_PIN_TIED(tail_base);
            func_800B9EE4();
            return;
        }
        if (input & 0x40) {
            w->state = 1;
            if (w->mode == 0) {
                if (w->node->entity->kind == 0) {
                    register u8 *objects_page ASM_REG("$2");
                    register s32 action ASM_REG("$5");
                    register s32 amount ASM_REG("$6");
                    register s32 shifted ASM_REG("$2");
                    GlobalObj *object;
                    n = func_80098C80(w->handle);
                    action = 0x48;
                    ASM_KEEP_DEP_NV(action, n);
                    shifted = (s32)((u32)n << 16);
                    amount = shifted >> 16;
                    objects_page = (u8 *)0x800E0000;
                    ASM_KEEP_DEP_NV(objects_page, amount);
                    object = *(GlobalObj **)(objects_page + 0x3D7C);
                    func_8009F644(object, action, amount, 0);
                    func_800B9F18();
                    return;
                } else {
                    register u8 *objects_page ASM_REG("$2");
                    register s32 amount ASM_REG("$7");
                    GlobalObj *object;
                    n = func_80098C80(w->handle);
                    amount = (s16)n;
                    objects_page = (u8 *)0x800E0000;
                    ASM_KEEP_DEP_NV(objects_page, amount);
                    object = *(GlobalObj **)(objects_page + 0x3D7C);
                    func_8009F644(object, 0x50,
                                   w->node->entity == object->right, amount);
                    func_800B9F18();
                    return;
                }
            }
        }
    } else {
        if (w->mode == 0) {
            register u8 *counter_base ASM_REG("$3");
            register Node *state_node ASM_REG("$2");
            register s32 count ASM_REG("$6");
            Entity *entity;
            s32 *target;
            count = 8;
            ASM_KEEP_NV(count);
            state_node = w->node;
            ASM_SCHED_BARRIER();
            counter_base = (u8 *)0x800E0000;
            ASM_KEEP_NV(counter_base);
            entity = state_node->entity;
            target = *(s32 **)((u8 *)entity - 0x18);
            func_800C77D0((u8 *)entity - 0x20, target, count,
                           *(s16 *)(counter_base - 0x319A));
            n = func_80098920(w->node->entity, w->handle, 0x15, 0);
            if ((s16)n < 0) {
                goto done;
            }
            counter_base = (u8 *)0x80080000;
            ASM_KEEP(counter_base);
            counter_base += 0x3460;
            (*(s16 *)(counter_base + 10))--;
        }
finish:
        {
            register u8 *flags_page ASM_REG("$3");
            u16 work_flags;
            work_flags = ((u16 *)w)[-1];
            ASM_KEEP(work_flags);
            flags_page = (u8 *)0x80080000;
            ASM_KEEP_NV(flags_page);
            ((u16 *)w)[-1] = work_flags | 0x8000;
            *(u32 *)(flags_page + 0x14A0) |= 0x8000;
        }
        func_800BA050();
        return;
    }

    w->counter++;
    if (w->mode == 2) {
        render->rot_y += 0x40;
        func_800B9F60();
        return;
    }

    r = func_800644B8((s16)w->counter << 7);
    w->x += r << 5;
    ASM_MEM_BARRIER();
    if (w->mode == 0) {
        w->phase &= 0x1F;
        if ((s16)w->phase < 0x10) {
            render->rot_x += 0x80;
        }
        render->rot_x = ((render->rot_x + 0x400) & 0x7FF) - 0x400;
        w->phase++;
    }
    if (render->primitive != 0) {
        func_800478B8(render);
    }
    r = func_80064584(*(s16 *)(controls + 0xC8));
    out->x = (r * w->amp >> 11) + *(u16 *)((u8 *)&w->cur_x + 2);
    r = func_800644B8(*(s16 *)(controls + 0xC8));
    out->y = (r * w->amp >> 11) + *(u16 *)((u8 *)&w->cur_y + 2);
    out->z = w->x + w->y.whole + (w->bias << 15);
done:
    return;
}
