/* Paired actor motion (G00645). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D20CC, PD:town/engine:800E9E14, PD:town/engine:800E9E34, PD:town/engine:800E9E7C. */
#include "town/map/paired_actor_motion_g00645.h"

/* Updates randomized movement, animation, and landing states for a town actor. */
void update_randomized_actor_movement(void *actor, void *motion, void *sprite, s32 update_mode)
{
    register s32 *sequence;
    register s32 state;
    s32 glide_state;
    s32 home_dx;

    sequence = 0;
    if ((service_script_controller() != 0) && (check_transform_identifier_and_hook((s32)actor) != 0)) {
        if (!(((Rec_D_80082D58 *)actor)->unk_AC & 1)) {
            SD_Call(0x60B);
            ((Rec_D_80082D58 *)actor)->unk_AC |= 1;
        }
    } else {
        ((Rec_D_80082D58 *)actor)->unk_AC &= ~1;
    }

    state = ((Rec_D_80082D58 *)actor)->unk_68;
    glide_state = 0x31;
    glide_state = 0x31;
    switch (state) {
case 0:
    {
        s32 action_choice;
        s32 random_value;
        register s32 quotient;
        s32 home_distance;
        register s32 vx;

        ((S_800BCE78_1 *)motion)->unk_08.at02.v = query_lowered_transform_position(motion);
        if (!(((SpriteFrameState *)sprite)->flags & 0x6000)) {
            break;
        }
        action_choice = rand();
        quotient = action_choice / 4;
        action_choice -= quotient * 4;
        switch (action_choice) {
        case 0:
            sequence = (s32 *)D_800E9E7C;
            ((Rec_D_80082D58 *)actor)->unk_68 = 0x10;
            ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = (rand() % 2) + 2;
            break;

        case 1:
        {
            s32 limit;
            s32 hop_vx;

            ((Rec_D_80082D58 *)actor)->unk_68 = 0x20;
            ((SpriteFrameState *)sprite)->flags |= 0x800;
            ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = (rand() & 1) + 2;
            limit = 0x1FFFFF;
            ((S_800BCE78_1 *)motion)->unk_14 = -0x30000;
            home_dx = ((S_800BCE78_1 *)motion)->unk_00;
            home_dx -= ((Rec_D_80082D58 *)actor)->unk_A0;
            home_distance = __builtin_abs(home_dx);
            limit = limit < home_distance;
            if (!limit) {
                ((S_800BCE78_1 *)motion)->unk_0C = 0x10000;
                if (rand() & 1) {
                    hop_vx = -((S_800BCE78_1 *)motion)->unk_0C;
                    ((S_800BCE78_1 *)motion)->unk_0C = hop_vx;
                }
            } else {
                hop_vx = -0x10000;
                if (home_dx < 0) {
                    hop_vx = 0x10000;
                }
                ((S_800BCE78_1 *)motion)->unk_0C = hop_vx;
            }
            if (((S_800BCE78_1 *)motion)->unk_0C > 0) {
                ((SpriteFrameState *)sprite)->flags |= 1;
            } else {
                ((SpriteFrameState *)sprite)->flags &= 0xFFFE;
            }
            break;
        }

        case 2:
        {
            s32 limit;
            s32 random_speed;
            s32 *launch_sequence;

            launch_sequence = D_800E9ECC;
            sequence = launch_sequence;
            ((Rec_D_80082D58 *)actor)->unk_68 = 0x30;
            random_speed = rand();
            limit = 0xFFFFF;
            vx = (random_speed & 0x1FF) << 8;
            ((S_800BCE78_1 *)motion)->unk_0C = vx;
            home_dx = ((S_800BCE78_1 *)motion)->unk_00;
            home_dx -= ((Rec_D_80082D58 *)actor)->unk_A0;
            home_distance = __builtin_abs(home_dx);
            limit = limit < home_distance;
            if (!limit) {
                s32 t;
                if (rand() & 1) {
                    t = ((S_800BCE78_1 *)motion)->unk_0C;
                } else {
                    t = -((S_800BCE78_1 *)motion)->unk_0C;
                }
                ((S_800BCE78_1 *)motion)->unk_0C = t;
            } else if (home_dx > 0) {
                ((S_800BCE78_1 *)motion)->unk_0C = -vx;
            }
            if (((S_800BCE78_1 *)motion)->unk_0C > 0) {
                ((SpriteFrameState *)sprite)->flags |= 1;
            } else {
                ((SpriteFrameState *)sprite)->flags &= 0xFFFE;
            }
            ((S_800BCE78_1 *)motion)->unk_14 = -0x20000;
            break;
        }

        case 4:
            ((Rec_D_80082D58 *)actor)->unk_68 = 0x40;
            ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = 0x14;
            ((SpriteFrameState *)sprite)->flags |= 0x800;
        }
        break;
    }

case 0x10:
    {
        register u16 timer;

        if (((SpriteFrameState *)sprite)->flags & 0x6000) {
            timer = ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 - 1;
            ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = timer;
            if ((s16)timer <= 0) {
                ((Rec_D_80082D58 *)actor)->unk_68 = 0;
            }
            sequence = (s32 *)D_800E9E7C;
        }
        break;
    }

case 0x20:
    {
        s32 x;
        s32 vy;
        s32 vx;
        s32 y;
        register u16 timer;

        x = ((S_800BCE78_1 *)motion)->unk_00;
        vx = ((S_800BCE78_1 *)motion)->unk_0C;
        y = ((S_800BCE78_1 *)motion)->unk_08.at00.v;
        vy = ((S_800BCE78_1 *)motion)->unk_14;
        ((S_800BCE78_1 *)motion)->unk_00 = x + vx;
        ((S_800BCE78_1 *)motion)->unk_08.at00.v = y + vy;
        ((S_800BCE78_1 *)motion)->unk_14 += 0x10000;
        home_dx = query_lowered_transform_position(motion);
        state = home_dx < ((S_800BCE78_1 *)motion)->unk_08.at02.v;
        if (state) {
            ((S_800BCE78_1 *)motion)->unk_08.at02.v = home_dx;
            timer = ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 - 1;
            ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = timer;
            if ((s16)timer <= 0) {
                ((S_800BCE78_1 *)motion)->unk_14 = 0;
                ((S_800BCE78_1 *)motion)->unk_0C = 0;
                ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
                ((Rec_D_80082D58 *)actor)->unk_68 = 0;
            } else {
                ((S_800BCE78_1 *)motion)->unk_14 = -0x30000;
            }
        }
        break;
    }

case 0x30:
    {
        s32 x;
        s32 vx;
        s32 vy;
        s32 y;

        x = ((S_800BCE78_1 *)motion)->unk_00;
        vx = ((S_800BCE78_1 *)motion)->unk_0C;
        vy = ((S_800BCE78_1 *)motion)->unk_14;
        ((S_800BCE78_1 *)motion)->unk_00 = x + vx;
        y = ((S_800BCE78_1 *)motion)->unk_08.at00.v;
        ((S_800BCE78_1 *)motion)->unk_08.at00.v = y + vy;
        ((S_800BCE78_1 *)motion)->unk_14 -= 0x4000;
        if (((SpriteFrameState *)sprite)->flags & 0x6000) {
            sequence = D_800E9E34;
            ((Rec_D_80082D58 *)actor)->unk_68 = glide_state;
            ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = 3;
        }
        break;
    }

case 0x31:
    {
        register s32 x;
        register s32 vx;
        register s32 y;
        register s32 vy;
        register u16 timer;

        x = ((S_800BCE78_1 *)motion)->unk_00;
        vx = ((S_800BCE78_1 *)motion)->unk_0C;
        y = ((S_800BCE78_1 *)motion)->unk_08.at00.v;
        vy = ((S_800BCE78_1 *)motion)->unk_14;
        ((S_800BCE78_1 *)motion)->unk_00 = x + vx;
        ((S_800BCE78_1 *)motion)->unk_08.at00.v = y + vy;
        if (((SpriteFrameState *)sprite)->flags & 0x6000) {
            timer = ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 - 1;
            ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = timer;
            if ((s16)timer <= 0) {
                sequence = D_800E9E34;
                ((S_800BCE78_1 *)motion)->unk_14 = -0x10000;
                ((S_800BCE78_1 *)motion)->unk_0C >>= 1;
                ((Rec_D_80082D58 *)actor)->unk_68 = 0x32;
                ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = (rand() & 3) + 3;
            }
        }
        break;
    }

case 0x32:
    {
        register s32 x;
        register s32 vx;
        register s32 y;
        register s32 vy;
        register s32 new_vx;
        s32 height;
        s32 floor_fixed;
        register s16 floor;
        register u16 timer;

        x = ((S_800BCE78_1 *)motion)->unk_00;
        vx = ((S_800BCE78_1 *)motion)->unk_0C;
        y = ((S_800BCE78_1 *)motion)->unk_08.at00.v;
        vy = ((S_800BCE78_1 *)motion)->unk_14;
        ((S_800BCE78_1 *)motion)->unk_00 = x + vx;
        ((S_800BCE78_1 *)motion)->unk_08.at00.v = y + vy;
        if (((SpriteFrameState *)sprite)->flags & 0x6000) {
            timer = ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 - 1;
            ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = timer;
            if ((s16)timer <= 0) {
                ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = 8;
                new_vx = -((S_800BCE78_1 *)motion)->unk_0C;
                ((S_800BCE78_1 *)motion)->unk_0C = new_vx;
                if (new_vx > 0) {
                    ((SpriteFrameState *)sprite)->flags |= 1;
                } else {
                    ((SpriteFrameState *)sprite)->flags &= 0xFFFE;
                }
                floor = query_lowered_transform_position(motion);
                floor_fixed = (s32)floor << 16;
                height = ((S_800BCE78_1 *)motion)->unk_08.at00.v + 0x100000;
                ((S_800BCE78_1 *)motion)->unk_14 =
                    (floor_fixed - height) /
                    (s16)((Rec_D_80082D58 *)actor)->unk_6C.as_u16;
                sequence = D_800E9E14;
                ((Rec_D_80082D58 *)actor)->unk_68 = 0x33;
            }
        }
        break;
    }

case 0x33:
    {
        register s32 x;
        register s32 vx;
        register s32 y;
        register s32 vy;
        register u16 timer;

        x = ((S_800BCE78_1 *)motion)->unk_00;
        vx = ((S_800BCE78_1 *)motion)->unk_0C;
        y = ((S_800BCE78_1 *)motion)->unk_08.at00.v;
        vy = ((S_800BCE78_1 *)motion)->unk_14;
        ((S_800BCE78_1 *)motion)->unk_00 = x + vx;
        ((S_800BCE78_1 *)motion)->unk_08.at00.v = y + vy;
        if (((SpriteFrameState *)sprite)->flags & 0x6000) {
            sequence = D_800E9E14;
        }
        timer = ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 - 1;
        ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = timer;
        if ((s16)timer <= 0) {
            sequence = D_800E9E54;
            ((S_800BCE78_1 *)motion)->unk_14 = 0;
            ((S_800BCE78_1 *)motion)->unk_0C = 0;
            ((Rec_D_80082D58 *)actor)->unk_68 = 0x34;
        }
        break;
    }

case 0x34:
    {
        register s16 floor;

        ((S_800BCE78_1 *)motion)->unk_00 += ((S_800BCE78_1 *)motion)->unk_0C;
        floor = query_lowered_transform_position(motion);
        ((S_800BCE78_1 *)motion)->unk_08.at02.v =
            (u16)((S_800BCE78_1 *)motion)->unk_08.at02.v + ((floor - ((S_800BCE78_1 *)motion)->unk_08.at02.v) >> 1);
        if (((SpriteFrameState *)sprite)->flags & 0x6000) {
            sequence = (s32 *)D_800E9E7C;
            ((Rec_D_80082D58 *)actor)->unk_68 = 0;
        }
        break;
    }

case 0x40:
    {
        register u16 timer;

        timer = ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 - 1;
        ((Rec_D_80082D58 *)actor)->unk_6C.as_u16 = timer;
        if ((s16)timer <= 0) {
            ((Rec_D_80082D58 *)actor)->unk_68 = 0;
            ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
        }
        break;
    }

case 0xFF:
    unlink_scene_list_node(actor);
    unlink_node_if_registered(actor);
    (*(u16 *)((u8 *)actor + -2)) |= 0x8000;
    object_flag_block.flags |= 0x8000;

    }

    advance_sprite_animation_and_textures(sprite);
    if (sequence != 0) {
        select_record_entry_and_value((struct Dst *)(sprite), (struct Elem *)(sequence), 0);
    }
}

/* Initialize the object and dispatch setup according to its state. */
void initialize_object_and_dispatch_by_state(Func800BFE50Object *object, s32 *params, void *dispatch_context) {
    u8 state;

    *(void **)((u8 *)object - 0x10) = D_800BCE78;
    object->field50 = 0;
    register_node((struct RegistrationNode *)((u8 *)object - 0x20), (s32)project_sprite_chain);

    object->fieldA0 = params[0];
    object->fieldA4 = params[1];
    state = object->field95;

    switch (state) {
    default:
        return;

    case 0:
        configure_the_set_mode_n_1(object, params, D_800D20CC);
        select_record_entry_and_value((struct Dst *)(dispatch_context), (struct Elem *)(D_800E9E7C), 0);
        object->field68 = 0;
        object->field48 = D_800D2130;
        return;

    case 1:
        select_record_entry_and_value((struct Dst *)(dispatch_context), (struct Elem *)(D_800E9E7C), 0);
        object->field68 = 0;
        break;
    }
}

/* Randomize paired object motion until both pass the stop position, then set completion flags. */
void randomize_paired_object_motion(void *pair_in) {
    void *pair = pair_in;
    s32 state;
    s32 random_value;
    s32 stop_x;
    s32 speed_limit;
    s32 speed_bias;
    s32 member_index;
    s32 x_gap;
    s32 x_speed;
    u16 tick;
    s32 *flag_page;
    void **member_slot;
    S_800BD688_6 *second_depth;
    S_800BD688_8 *second_motion;
    S_800BD688_7 *first_motion;
    S_800BD688_4 *x_motion;
    S_800BD688_5 *y_motion;
    S_800BD688_3 *member_motion;

    state = ((S_800BD688_0 *)pair)->unk_20.s;
    tick = (((S_800BD688_0 *)pair)->unk_22 + 1) & 7;
    ((S_800BD688_0 *)pair)->unk_22 = tick;
    switch (state) {
    case 0:
        member_motion = (void *)0xFEC00000;
        if (tick == 0) {
            {
                S_800BD688_1 *first_position;
                S_800BD688_2 *second_position;

                first_position = ((S_800BD688_0 *)pair)->unk_00;
                second_position = ((S_800BD688_0 *)pair)->unk_04;
                x_gap = first_position->unk_00;
                x_gap -= second_position->unk_00;
            }
            x_gap = abs(x_gap);
            {

                random_value = x_gap + 0xFFE00000;
                if (random_value > 0x200000U) {
                    member_index = 1;
                    speed_limit = 0x7FFFF;
                    speed_bias = 0xFFF80000;
                    member_slot = pair + 4;
                    do {
                        random_value = rand();
                        member_motion = *member_slot;
                        x_speed = (random_value & 0x1FF) << 8;
                        if (member_motion->unk_0C > speed_limit) {
                            x_speed = 0 - x_speed;
                        }
                        member_motion->unk_0C = x_speed;
                        x_motion = *member_slot;
                        member_slot = (void **)((s8 *)((void **)((s8 *)member_slot - 4)));
                        member_index -= 1;
                        x_motion->unk_0C = (s32) (x_motion->unk_0C + speed_bias);
                    } while (member_index >= 0);
                }
            }
            member_index = 1;
            member_slot = pair + 4;
            do {
                random_value = rand();
                member_index -= 1;
                y_motion = *member_slot;
                member_slot = (void **)((s8 *)((void **)((s8 *)member_slot - 4)));
                y_motion->unk_10 = (s32) (((random_value & 0x1FF) - 0x100) << 9);
            } while (member_index >= 0);
            ((S_800BD688_10 *)(((S_800BD688_9 *)pair)->unk_00))->unk_14 = (s32) (((rand() & 0x1FF) - 0x100) << 8);
            ((S_800BD688_11 *)(((S_800BD688_9 *)pair)->unk_04))->unk_14 = (s32) ((rand() & 0x1FF) << 7);
            second_depth = ((S_800BD688_0 *)pair)->unk_04;
            if (((S_800BD688_10 *)(((S_800BD688_9 *)pair)->unk_00))->unk_08 < second_depth->unk_08) {
                second_depth->unk_14 = (s32) (0 - second_depth->unk_14);
            }
        }
        first_motion = ((S_800BD688_0 *)pair)->unk_00;
        stop_x = ((S_800BD688_0 *)pair)->unk_08 + 0xFEC00000;
        if (first_motion->unk_00 < stop_x) {
            second_motion = ((S_800BD688_0 *)pair)->unk_04;
            if (second_motion->unk_00 < stop_x) {
                second_motion->unk_0C = 0;
                first_motion->unk_0C = 0;
                ((S_800BD688_0 *)pair)->unk_20.u += 1;
            }
        }
        break;
    case 1:
        flag_page = (s32 *)0x80080000;
        ((ObjectStatusPrefix16 *)pair)[-1].unk_00 = (u16) (((ObjectStatusPrefix16 *)pair)[-1].unk_00 | 0x8000);
        flag_page[0x14A0 / 4] |= 0x8000;
        break;
    }
}

/* Advance motion, update every eighth tick, and flag zero horizontal velocity. */
void advance_motion_and_flag_zero_velocity(Actor *actor, Motion *motion, s32 actor_id) {
    u16 tick;

    advance_sprite_animation_and_textures((void *)actor_id);
    motion->x += motion->dx;
    motion->y += motion->dy;
    motion->z += motion->dz;

    tick = (actor->counter + 1) & 7;
    actor->counter = tick;
    if (tick == 0) {
        if (motion->dz < 0) {
            select_record_entry_and_value((struct Dst *)((void *)actor_id), (struct Elem *)(D_800E9E34), 0);
        } else {
            select_record_entry_and_value((struct Dst *)((void *)actor_id), (struct Elem *)(D_800E9E14), 0);
        }
    }
    if (motion->dx == 0) {
        *(u16 *)((u8 *)actor - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}

/* event_tori_in: Creates a parent object and two linked render objects offset from the supplied position. */
s32 event_tori_in(void *source) {
    void *source_data;
    s32 child_index;
    s32 x_step;
    SpriteFrameState *render_state;
    S_800BD980_1 *transform;
    void *object;
    S_800BD980_0 *origin;
    void *child_slot;
    void (*child_handler)(void *, void *, s32);

    source_data = source;
    child_slot = NULL;
    object = allocate_list_node(0x202, ((s32 *)&scene_object_list_anchor.next));
    if (object != NULL) {
        child_slot = object + 0x20;
        ((LinkedMotionObject *)object)->update.parent = randomize_paired_object_motion;
        ((LinkedMotionObject *)object)->position = ((MotionSource *)source_data)->position;
        ((LinkedMotionObject *)object)->motion = ((MotionSource *)source_data)->motion;
    }
    child_index = 1;
    child_handler = advance_motion_and_flag_zero_velocity;
    x_step = 0x300000;
    child_slot = child_slot + 4;
    do {
        object = allocate_list_node(0x312, ((s32 *)&scene_object_list_anchor.next));
        if (object != NULL) {
            s32 motion_base = 0;
            s32 color;
            u16 source_x_hi;
            u16 source_y_hi;
            s32 x_offset;
            s32 y_offset;
            s32 z_offset;

            register_node((struct RegistrationNode *)object, (s32)project_sprite_chain);
            motion_base = 0xFFF88000;
            color = 0x800000;
            transform = ((ObjectNodeHeader *)object)->unk_08;
            color |= 0x8080;
            ((LinkedMotionObject *)object)->update.child = child_handler;
            *(void **)child_slot = transform;
            render_state = ((ObjectNodeHeader *)object)->unk_0C;
            source_x_hi = (u16)((EntityRec *)source_data)->x.w.i;
            origin = object + 0x20;
            origin->unk_0C = source_x_hi;
            source_y_hi = (u16)((EntityRec *)source_data)->y.w.i;
            origin->unk_0E = source_y_hi;
            origin->unk_10 = (u16)((EntityRec *)source_data)->z.w.i;
            x_offset = x_step + 0x01400000;
            transform->unk_00 = (s32) (((EntityRec *)source_data)->x.v + x_offset);
            {
                s32 source_y;
                source_y = ((EntityRec *)source_data)->y.v;
                y_offset = child_index << 0x15;
                transform->unk_04 = (s32) (source_y + y_offset);
            }
            z_offset = (child_index << 0x13) + 0xFF800000;
            transform->unk_08 = (s32) (((EntityRec *)source_data)->z.v + z_offset);
            transform->unk_0C = (s32) (motion_base - (child_index << 0x10));
            render_state->scale_y = 0x1000;
            render_state->scale_x = 0x1000;
            render_state->color.word = color;
            select_record_entry_and_value((struct Dst *)(render_state), (struct Elem *)(&D_800E9E14), 0);
        }
        x_step += 0xFFD00000;
        child_index -= 1;
        child_slot = (void *)((s8 *)child_slot - 4);
    } while (child_index >= 0);
    return 0;
}
