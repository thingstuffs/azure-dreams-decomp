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

/* Updates entity selection, interpolates its position, and animates the rendered output. */
void func_800B9A78(Work *work, Out *out, Render *render_arg)
{
    register Render *render;
    u8 *controls_page;
    u8 *controls;
    u8 *counter_base;
    s32 result;
    s32 height_step;
    s32 trig_value;
    u32 input;

    ASM_KEEP_NV(render);
    controls_page = (u8 *)0x80080000;
    ASM_KEEP_DEP_NV(controls_page, render);
    render = render_arg;
    controls = controls_page + 0x3160;

    {
        Node *node;
        s32 *target_pos;
        node = work->node;
        target_pos = *(s32 **)((u8 *)node->entity - 0x18);
        if (work->timer != 0) {
            work->cur_x += (target_pos[0] - work->cur_x) / work->timer;
            work->cur_y += (target_pos[1] - work->cur_y) / work->timer;
            if (work->mode != 2) {
                u8 *height_base;
                register Entity *height_entity ASM_REG("$4");
                s32 current_height;
                trig_value = func_800644B8(work->timer << 8);
                height_base = (u8 *)work->node;
                current_height = work->y.whole;
                height_entity = ((Node *)height_base)->entity;
                height_base = (u8 *)0x800E0000;
                ASM_KEEP_NV(height_base);
                height_entity = (Entity *)(u32)height_entity->kind;
                height_base -= 0x23C0;
                height_entity = (Entity *)((u8 *)height_entity + (u32)height_base);
                ASM_KEEP_NV(height_entity);
                height_step = (target_pos[2] - ((s32)*(u8 *)height_entity << 16) - current_height) / work->timer;
                height_step -= (trig_value * work->timer) << 6;
                work->y.whole += height_step;
                if (work->node->entity->flags & 0x80000) {
                    work->y.half.angle -= 0x80;
                }
            } else {
                work->y.whole += (((s32)work->node->entity->height << 16) - work->y.whole) / work->timer;
            }
        }

        if (--work->timer <= 0) {
            work->cur_x = target_pos[0];
            work->cur_y = target_pos[1];
            if (work->mode != 2) {
                u8 *height_base;
                Entity *entity;
                register u8 *height_addr ASM_REG("$3");
                s32 target_height;
                height_base = (u8 *)work->node;
                entity = ((Node *)height_base)->entity;
                height_addr = (u8 *)(u32)entity->kind;
                target_height = entity->height;
                height_addr += (u32)((u8 *)&D_800DDC40);
                ASM_KEEP_NV(height_addr);
                height_base = (u8 *)(u32)*height_addr;
                target_height -= (s32)(u32)height_base;
                if (entity->flags & 0x40000) {
                    target_height -= 0x40;
                }
                work->y.half.angle = target_height;
                if (work->node->entity->flags & 0x80000) {
                    work->y.half.angle = target_height - 0x80;
                }
            } else {
                work->y.half.angle = work->node->entity->height;
            }
            work->timer = 0;
        }
    }

    if (work->state == 0) {
        if (work->timer == 0) {
            if ((*(u32 *)(controls + 0x10) & 2) != 0) {
                u8 *objects_page;
                u8 *status_page;
                s32 new_timer;
                GlobalObj *object;
                Entity *left;
                objects_page = (u8 *)0x800E0000;
                ASM_KEEP_NV(objects_page);
                left = (*(GlobalObj **)(objects_page + 0x3D7C))->left;
                if (func_800BA33C(left)) {
                    status_page = (u8 *)0x80080000;
                    ASM_KEEP_NV(status_page);
                    if ((*(GlobalObj **)(status_page + 0x14A8))->left != work->node->entity) {
                        new_timer = 8;
                        object = *(GlobalObj **)(objects_page + 0x3D7C);
                        work->timer = new_timer;
                        work->node = (Node *)&object->left;
                        if (work->mode == 2) {
                            ((Render *)render)->flags = 0x00101080;
                        }
                    }
                }
            }
            if ((*(u32 *)(controls + 0x10) & 1) != 0) {
                u8 *objects_page;
                u8 *status_page;
                s32 new_timer;
                GlobalObj *object;
                Entity *right;
                objects_page = (u8 *)0x800E0000;
                ASM_KEEP_NV(objects_page);
                right = (*(GlobalObj **)(objects_page + 0x3D7C))->right;
                if (func_800BA33C(right)) {
                    status_page = (u8 *)0x80080000;
                    ASM_KEEP_NV(status_page);
                    if ((*(GlobalObj **)(status_page + 0x14A8))->right != work->node->entity) {
                        new_timer = 8;
                        object = *(GlobalObj **)(objects_page + 0x3D7C);
                        work->timer = new_timer;
                        work->node = (Node *)&object->right;
                        if (work->mode == 2) {
                            ((Render *)render)->flags = 0x00801010;
                        }
                    }
                }
            }
        }

        input = *(u32 *)(controls + 0x10);
        if (input & 0x20) {
            register u8 *counter_page ASM_REG("$3");
            if (work->mode != 0) {
                goto finish;
            }
            counter_page = (u8 *)0x80080000;
            ASM_KEEP_NV(counter_page);
            counter_page += 0x3460;
            counter_base = counter_page;
            goto decrement_counter;
        }
        if (input & 0x40) {
            work->state = 1;
            if (work->mode == 0) {
                if (work->node->entity->kind == 0) {
                    u8 *objects_page;
                    s32 action;
                    register s32 amount ASM_REG("$6");
                    GlobalObj *object;
                    result = func_80098C80(work->handle);
                    action = 0x48;
                    ASM_KEEP_DEP_NV(action, result);
                    result = (s32)((u32)result << 16);
                    amount = result >> 16;
                    objects_page = (u8 *)0x800E0000;
                    ASM_KEEP_DEP_NV(objects_page, amount);
                    object = *(GlobalObj **)(objects_page + 0x3D7C);
                    func_8009F644(object, action, amount, 0);
                } else {
                    u8 *objects_page;
                    register s32 amount ASM_REG("$7");
                    GlobalObj *object;
                    result = func_80098C80(work->handle);
                    amount = (s16)result;
                    objects_page = (u8 *)0x800E0000;
                    ASM_KEEP_DEP_NV(objects_page, amount);
                    object = *(GlobalObj **)(objects_page + 0x3D7C);
                    func_8009F644(object, 0x50,
                                   work->node->entity == object->right, amount);
                }
            }
        }
    } else {
        if (work->mode == 0) {
            Node *state_node;
            s32 count;
            Entity *entity;
            s32 *target_pos;
            count = 8;
            ASM_KEEP_NV(count);
            state_node = work->node;
            ASM_SCHED_BARRIER();
            counter_base = (u8 *)0x800E0000;
            ASM_KEEP_NV(counter_base);
            entity = state_node->entity;
            target_pos = *(s32 **)((u8 *)entity - 0x18);
            func_800C77D0((u8 *)entity - 0x20, target_pos, count,
                           *(s16 *)(counter_base - 0x319A));
            result = func_80098920(work->node->entity, work->handle, 0x15, 0);
            if ((s16)result < 0) {
                goto done;
            }
            counter_base = (u8 *)0x80080000;
            ASM_KEEP(counter_base);
            counter_base += 0x3460;
decrement_counter:
            (*(s16 *)(counter_base + 10))--;
        }
finish:
        {
            u8 *flags_page;
            u16 work_flags;
            work_flags = ((u16 *)work)[-1];
            ASM_KEEP(work_flags);
            flags_page = (u8 *)0x80080000;
            ASM_KEEP_NV(flags_page);
            ((u16 *)work)[-1] = work_flags | 0x8000;
            *(u32 *)(flags_page + 0x14A0) |= 0x8000;
        }
        return;
    }

    work->counter++;
    if (work->mode == 2) {
        render->rot_y += 0x40;
    } else {
        trig_value = func_800644B8((s16)work->counter << 7);
        work->x += trig_value << 5;
    }
    if (work->mode == 0) {
        work->phase &= 0x1F;
        if ((s16)work->phase < 0x10) {
            render->rot_x += 0x80;
        }
        render->rot_x = ((render->rot_x + 0x400) & 0x7FF) - 0x400;
        work->phase++;
    }
    if (render->primitive != 0) {
        func_800478B8(render);
    }
    trig_value = func_80064584(*(s16 *)(controls + 0xC8));
    out->x = (trig_value * work->amp >> 11) + *(u16 *)((u8 *)&work->cur_x + 2);
    trig_value = func_800644B8(*(s16 *)(controls + 0xC8));
    out->y = (trig_value * work->amp >> 11) + *(u16 *)((u8 *)&work->cur_y + 2);
    out->z = work->x + work->y.whole + (work->bias << 15);
done:
    return;
}
