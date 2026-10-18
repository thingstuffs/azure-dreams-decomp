#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
extern u8 D_800E0000[];
extern u8 D_80080000[];

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


extern s32 func_800644B8(s32, ...);
extern s32 func_80064584(s32, ...);
extern s32 get_special_table_data_index();
extern s32 dispatch_dungeon_category_action();
struct S_800BA33C_0;
extern s32 is_selectable_menu_target(struct S_800BA33C_0 *object);
extern void func_800478B8();
extern void append_packed_action_record();
extern s32 select_nearby_target_and_initialize_slot();

/* Updates entity selection, interpolates its position, and animates the rendered output. */
void update_item_target_marker(Work *work, Out *out, Render *render_arg)
{
    register Render *render;
    GameWork *controls;
    u8 *counter_base_2;
    s32 result;
    s32 height_step;
    s32 trig_value;
    u32 input;
    u8 *height_addr;
    Entity *entity;

    render = render_arg;
    controls = &g_game_work;

    {
        Node *node;
        s32 *target_pos;
        node = work->node;
        target_pos = *(s32 **)((u8 *)node->entity - 0x18);
        if (work->timer != 0) {
            work->cur_x += (target_pos[0] - work->cur_x) / work->timer;
            work->cur_y += (target_pos[1] - work->cur_y) / work->timer;
            if ((*(s16 *)((u8 *)work + 0x12)) != 2) {
                u8 *height_base;
                s32 current_height;
                trig_value = func_800644B8(work->timer << 8);
                height_base = (u8 *)work->node;
                current_height = work->y.whole;
                entity = ((Node *)height_base)->entity;
                entity = (Entity *)(u32)entity->kind;
                entity = (Entity *)((u8 *)entity + (u32)D_800DDC40);
                height_step = (target_pos[2] - ((s32)*(u8 *)entity << 16) - current_height) / (*(s16 *)((u8 *)work
                    + 0xE));
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
                s32 target_height;
                height_base = (u8 *)work->node;
                entity = ((Node *)height_base)->entity;
                height_addr = (u8 *)(u32)entity->kind;
                target_height = entity->height;
                height_addr += (u32)((u8 *)D_800DDC40);
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
            if ((((u32)controls->unk_010) & 2) != 0) {
                u8 *status_page;
                s32 new_timer;
                GlobalObj *object;
                Entity *left;
                left = (*(GlobalObj **)((GlobalObj * *)(&D_800E3D7C)))->left;
                if (is_selectable_menu_target(left)) {
                    status_page = D_80080000;
                    if ((*(GlobalObj **)(status_page + 0x14A8))->left != work->node->entity) {
                        new_timer = 8;
                        object = *(GlobalObj **)((GlobalObj * *)(&D_800E3D7C));
                        work->timer = new_timer;
                        work->node = (Node *)&object->left;
                        if (work->mode == 2) {
                            ((Render *)render)->flags = 0x00101080;
                        }
                    }
                }
            }
            if ((((u32)controls->unk_010) & 1) != 0) {
                u8 *status_page;
                s32 new_timer;
                GlobalObj *object;
                Entity *right;
                right = (*(GlobalObj **)((GlobalObj * *)(&D_800E3D7C)))->right;
                if (is_selectable_menu_target(right)) {
                    status_page = D_80080000;
                    if ((*(GlobalObj **)(status_page + 0x14A8))->right != work->node->entity) {
                        new_timer = 8;
                        object = *(GlobalObj **)((GlobalObj * *)(&D_800E3D7C));
                        work->timer = new_timer;
                        work->node = (Node *)&object->right;
                        if (work->mode == 2) {
                            ((Render *)render)->flags = 0x00801010;
                        }
                    }
                }
            }
        }

        input = ((u32)controls->unk_010);
        if (input & 0x20) {
            if (work->mode == 0) {
                (g_dungeon_status.unk_0A)--;
            }
            {
                u8 *flags_page;
                u16 work_flags;
                work_flags = (*(u16 *)((u8 *)work + -2));
                flags_page = (u8 *)0x80080000;
                (*(u16 *)((u8 *)work + -2)) = work_flags | 0x8000;
                *(u32 *)(flags_page + 0x14A0) |= 0x8000;
            }
            return;
        }
        if (input & 0x40) {
            work->state = 1;
            if (work->mode == 0) {
                if (work->node->entity->kind == 0) {
                    s32 action;
                    s32 amount;
                    GlobalObj *object;
                    result = get_special_table_data_index(((Work *)work)->handle);
                    action = 0x48;
                    result = (s32)((u32)result << 16);
                    amount = result >> 16;
                    object = *(GlobalObj **)((GlobalObj * *)(&D_800E3D7C));
                    append_packed_action_record(object, action, amount, 0);
                } else {
                    s32 amount;
                    GlobalObj *object;
                    result = get_special_table_data_index((*(s32 *)((u8 *)work + 0x2C)));
                    amount = (s16)result;
                    object = *(GlobalObj **)((GlobalObj * *)(&D_800E3D7C));
                    append_packed_action_record(object, 0x50,
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
            state_node = (*(Node **)((u8 *)work + 0));
            counter_base_2 = (u8 *)D_800E0000;
            entity = state_node->entity;
            target_pos = *(s32 **)((u8 *)entity - 0x18);
            select_nearby_target_and_initialize_slot((u8 *)entity - 0x20, target_pos, count,
                          *(s16 *)(counter_base_2 - 0x319A));
            result = dispatch_dungeon_category_action(work->node->entity, work->handle, 0x15, 0);
            if ((s16)result < 0) {
                return;
            }
            (g_dungeon_status.unk_0A)--;
        }
        {
            u8 *flags_page;
            u16 work_flags;
            work_flags = (*(u16 *)((u8 *)work + -2));
            flags_page = (u8 *)0x80080000;
            (*(u16 *)((u8 *)work + -2)) = work_flags | 0x8000;
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
    trig_value = func_80064584(controls->view.viewAngle);
    *(s16 *)((u8 *)out + 2) = (trig_value * work->amp >> 11) + *(u16 *)((u8 *)&work->cur_x + 2);
    trig_value = func_800644B8(controls->view.viewAngle);
    out->y = (trig_value * work->amp >> 11) + *(u16 *)((u8 *)&work->cur_y + 2);
    out->z = work->x + work->y.whole + (work->bias << 15);
    return;
}
