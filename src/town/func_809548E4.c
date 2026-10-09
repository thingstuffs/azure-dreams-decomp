#include "shared/minigame_body.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
extern int abs(int);

/* The record behind a minigame object node (node + 0x20) and the base record D_800834B8 (the node's record half).
 * Its +0x14..+0x22 halfwords use the separate shared MinigameBody layout. */


/* The minigame state: four parallel pointer arrays (object 0 is the base record, 1..3 the balls) and the stage timers. */
typedef struct MinigameState {
    EntityRec *rec[4];              /* 0x00 */
    s16 *angle[4];                  /* 0x10: angle[0] = base record + 0x10, angle[i] = the node record's facing */
    ObjectNodeHeader *node[3];      /* 0x20: the node of ball i+1 (rec[i + 1]); angle[3] ends at 0x20 */
    union { s16 s; u16 u; u16 p; } stage;   /* 0x2C (accessed as both) */
    union { u16 s; s16 u; } timer;  /* 0x2E (accessed as both) */
    s16 flag[4];                    /* 0x30 */
    u8 pad_38[0x2];
    u16 flags;                      /* 0x3A */
    s16 slot[4];                    /* 0x3C */
    s16 unk_44;
    s16 unk_46;
    u16 unk_48;
    union { u16 s; s16 u; } unk_4A; /* (accessed as both) */
} MinigameState;

/* The same arrays walked with a stride of one pointer: the walker's rec/angle/node are its own index. */
typedef struct MinigameSlot {
    EntityRec *rec;
    u8 pad_04[0xC];
    s16 *angle;
    u8 pad_14[0x8];
    ObjectNodeHeader *node;
} MinigameSlot;


void func_80021120();   /* extern */
s32 func_8002263C(); /* extern */
void func_80023E6C();   /* extern */
void func_80033B78();                     /* extern */
void func_80033B9C();                     /* extern */
short SD_Call(); /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();           /* extern */
s32 rand();                      /* extern */
void func_800ABD74();                       /* extern */
s32 func_800B1BEC();       /* extern */
void func_800B1DBC();              /* extern */
extern s32 D_80012D5C[0xB58];
extern u8 D_80022514[0x100];
extern s32 D_80024338[3];

extern s16 D_80113158[8];
extern s32 D_8011315C[0xC58];

typedef struct DialogArgs {
    s16 unk_10;
    s16 unk_12;
    void *owner;
    s32 unk_18;
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    s16 unk_24;
    s16 unk_26;
    u8 unused[0x10];
} DialogArgs;


/* Updates the minigame state, pays out gold, and resolves object collisions. */
s32 func_800218E4(MinigameState *game) {
    DialogArgs dialog_args;
    s32 motion_mode;
    s32 init_flags;
    s32 x_or_distance;
    s32 one;
    register s32 x_step ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 other_x ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 state;
    s32 pair_value;
    s32 transition_timer;
    s32 timer_bits;
    s32 phase_value;
    s32 scroll;
    s32 collision_value;
    s32 gold_total;
    s32 gold_remaining;
    s32 payout_handle;
    s32 winning_mask;
    s32 shuffle_value;
    s32 y_step;
    s32 other_y;
    EntityRec *fall_position;
    EntityRec *drop_position;
    ObjectNodeHeader *shuffle_object;
    s32 payout_amount;
    s32 payout_carry;
    s32 *payout_gold;
    s32 settle_timer_signed;
    ObjectNodeHeader *moving_object;
    s32 fall_random;
    s32 drop_random;
    s32 init_value;
    s32 object_index;
    s32 partner_index;
    s32 bounce_x;
    s32 forward_y_gap;
    s32 other_speed_y;
    s32 other_forward_y_gap;
    u16 settle_timer;
    u16 exit_timer;
    u16 start_timer;
    u16 fall_timer;
    u16 drop_timer;
    u16 result_timer;
    u16 effect_state;
    EntityRec *partner_position;
    EntityRec *object_position;
    MinigameBody *object_motion;
    EntityRec *object_velocity;
    EntityRec *partner_velocity;
    ObjectNodeHeader *init_object;
    ObjectNodeHeader *init_object_base;
    EntityRec *partner_xy;
    EntityRec *object_xy;
    ObjectNodeHeader *fall_object;
    EntityRec **init_slot;
    MinigameState *angle_slot;
    MinigameSlot *object_slot;
    MinigameSlot *position_slot;
    MinigameSlot *motion_slot;
    MinigameBody *base_object;
    EntityRec *init_position;

    state = game->stage.s;
    base_object = &D_800834B8;
    switch (state) {
    case 0:
        object_index = 3;
        do {
            game->flag[object_index] = 0;
            object_index -= 1;
        } while (object_index >= 0);
        object_index = 2;
        motion_mode = 1;
        game->unk_46 = -1;
        game->unk_44 = -1;
        game->rec[0] = &D_80083780;
        game->angle[0] = (s16 *)&base_object->unk_10;
        for (; object_index >= 0; object_index--) {
            init_object = game->node[object_index];
            game->rec[object_index + 1] = init_object->unk_08;
            init_object_base = game->node[object_index];
            object_motion = (MinigameBody *)(init_object_base + 1);
            object_motion->unk_18 = motion_mode;
            object_motion->unk_04 = 0;
            object_motion->unk_16 = 0;
            object_motion->unk_14 = 0;
            game->angle[object_index + 1] = &((EntityRec *)(init_object_base + 1))->facing;
        }
        base_object->unk_08 = 0;
        object_index = 3;
        init_flags = 0x10000000;
        angle_slot = (MinigameState *) ((u8 *) game + 6);
        init_slot = &game->rec[3];
        init_value = 0x04A00000;
loop_3:
            (*init_slot)->x.v = init_flags;
            object_index -= 1;
            (*init_slot)->y.v = init_value;
            init_position = *init_slot;
            init_slot -= 1;
            init_value += 0xFFC00000;
            init_position->flags14 = 0;
            init_position->unk_10 = 0;
            init_position->unk_0C = 0;
            init_position->z.v = 0;
            angle_slot->slot[0] = 0;
            angle_slot = (MinigameState *) ((u8 *) angle_slot - 2);
        if (object_index >= 0)
            goto loop_3;
        game->stage.s = (s16) ((u16) game->stage.s + 1);
                        /* fallthrough */
    case 1:
        start_timer = game->timer.s - 1;
        game->timer.s = start_timer;
        if ((start_timer << 0x10) <= 0) {
            base_object->unk_08 = 1;
            game->timer.s = 0x20U;
            game->stage.s = (s16) ((u16) game->stage.s + 1);
            SD_Call(0x521);
        }
        break;
    case 2:
        if ((s16) game->timer.s == 0x10) {
            SD_Call(0x700);
            SD_Call(0x702);
            object_index = 2;
            phase_value = 3;
            do {
                fall_object = game->node[object_index];
                object_index -= 1;
                ((MinigameBody *)(fall_object + 1))->unk_18 = phase_value;
            } while (object_index >= 0);
        }
        if ((s16) game->timer.s < 0x10) {
            object_index = 3;
            partner_index = 0xFFF00000;
            do {
                fall_position = game->rec[object_index];
                timer_bits = game->timer.u;
                pair_value = fall_position->x.v;
                timer_bits <<= 0x10;
                pair_value += partner_index;
                pair_value += timer_bits;
                fall_position->x.v = pair_value;
                fall_random = rand(fall_position);
                if (fall_random == ((fall_random / 3) * 3)) {
                    func_800ABD74(game->rec[object_index]);
                }
                object_index -= 1;
            } while (object_index >= 0);
        }
        fall_timer = game->timer.s - 1;
        game->timer.s = fall_timer;
        if ((fall_timer << 0x10) <= 0) {
            s32 stage;

            base_object->unk_08 = 2;
            stage = game->stage.u;
                                     /* MATCH: the state load precedes timer materialization. */
            transition_timer = 0x10;
            game->timer.s = transition_timer;
            game->stage.s = (s16) (stage + 1);
        }
        break;
    case 3:
        object_index = 3;
        do {
            drop_position = game->rec[object_index];
            drop_position->x.v += 0xFFF00000;
            drop_random = rand();
            if (drop_random == ((drop_random / 3) * 3)) {
                func_800ABD74(game->rec[object_index]);
            }
            object_index -= 1;
        } while (object_index >= 0);
        drop_timer = game->timer.s - 1;
        game->timer.s = drop_timer;
        if ((drop_timer << 0x10) <= 0) {
            s32 stage;

            base_object->unk_08 = 3;
            object_index = 2;
            shuffle_value = 0x100;
            shuffle_object = (ObjectNodeHeader *)0xC0000;
            do {
                object_motion = (MinigameBody *)(game->node[object_index] + 1);
                object_motion->unk_22 = object_index;
                object_index -= 1;
                object_motion->unk_18 = shuffle_value;
                object_motion->unk_1C = 0;
                object_motion->unk_04 = (s32) shuffle_object;
            } while (object_index >= 0);
            object_index = 0xA;
            do {
                object_index -= 1;
                partner_index = rand() % 3;
                bounce_x = rand() % 3;
                shuffle_value = ((MinigameBody *)(game->node[partner_index] + 1))->unk_22;
                ((MinigameBody *)(game->node[partner_index] + 1))->unk_22 = ((MinigameBody *)(game->node[bounce_x] + 1))->unk_22;
                ((MinigameBody *)(game->node[bounce_x] + 1))->unk_22 = shuffle_value;
            } while (object_index >= 0);
            SD_Call(0x1702);
            stage = game->stage.p;
            game->stage.s = (s16) (stage + 1);
        }
        break;
    case 4:
        game->timer.s = (u16) (game->timer.s + 1);
        if (game->unk_46 >= 0) {
            s32 stage;

            if (game->unk_44 != 0) {
                func_80033B78(0x58F);
            } else {
                func_80033B9C(0x58F);
            }
            object_index = game->unk_44;
            if (game->unk_46 < object_index) {
                game->unk_44 = (s16) (u16) game->unk_46;
                game->unk_46 = object_index;
            }
            one = 1;
            collision_value = game->unk_44;
            pair_value = game->unk_46;
            winning_mask = D_80113158[0];
            collision_value = one << collision_value;
            pair_value = one << pair_value;
            object_index = collision_value + pair_value;
            if (winning_mask != object_index) {
                D_8011315C[0] = 0;
            }
            game->timer.s = 0x40U;
            game->unk_4A.s = 0x400U;
            game->unk_48 = 0U;
            dialog_args.x = 0x28;
            dialog_args.y = 0x58;
            dialog_args.width = 0xF0;
            dialog_args.height = 0x50;
            dialog_args.unk_24 = 2;
            dialog_args.unk_26 = one;
            dialog_args.unk_18 = 0;
            dialog_args.unk_10 = 0;
            dialog_args.unk_12 = 8;
            dialog_args.owner = game;
            func_80021120(&D_80022514, &dialog_args);
            stage = game->stage.p;
            game->stage.s = (s16) (stage + 1);
        }
        break;
    case 5:
        transition_timer = game->unk_48;
        scroll = game->timer.s;
        transition_timer += 0x12C;
        scroll <<= 1;
        transition_timer += scroll;
        scroll = game->unk_4A.s;
        game->unk_48 = transition_timer;
        transition_timer = game->timer.s;
        scroll += 0x10;
        transition_timer -= 1;
        game->timer.s = transition_timer;
        transition_timer <<= 0x10;
        game->unk_4A.s = scroll;
        if (transition_timer <= 0) {
            s32 stage;

            if (D_80113158[0] != 0) {
                D_80024338[0] = func_800B1BEC(0, -0x50, 0x40);
            }
            stage = game->stage.u;
                                     /* MATCH: the state load precedes timer materialization. */
            game->timer.s = 0x10;
            game->stage.s = (s16) (stage + 1);
        }
        break;
    case 6:
        scroll = 0x10;
        transition_timer = game->unk_48;
        phase_value = game->timer.s;
        transition_timer += 0x12C;
        scroll -= phase_value;
        scroll <<= 3;
        transition_timer -= scroll;
        game->unk_48 = transition_timer;
        transition_timer = game->timer.s;
        scroll = game->unk_4A.s;
        transition_timer -= 1;
        game->timer.s = transition_timer;
        transition_timer <<= 0x10;
        scroll += 0x15E;
        game->unk_4A.s = scroll;
        if (transition_timer <= 0) {
            s32 stage;

            stage = game->stage.u;
                                     /* MATCH: the state load precedes timer materialization. */
            transition_timer = 0x21;
            game->timer.s = transition_timer;
            game->stage.s = (s16) (stage + 1);
        }
        break;
    case 7:
        game->unk_48 = (u16) (game->unk_48 + 0xA0);
        settle_timer = game->timer.s - 1;
        game->timer.s = settle_timer;
        settle_timer_signed = settle_timer << 0x10;
        game->unk_4A.s = (u16) (game->unk_4A.s + ((s32) (0x1EDC
            - (s16) game->unk_4A.s) >> 1));
        if (settle_timer_signed <= 0) {
            s32 stage;

            game->unk_48 = 0U;
            stage = game->stage.u;
            transition_timer = 0x10;
            game->timer.s = transition_timer;
            game->stage.s = (s16) (stage + 1);
        }
        break;
    case 8:
        transition_timer = 0x2001;
        scroll = game->unk_4A.u;
        phase_value = game->timer.s;
        transition_timer -= scroll;
        transition_timer >>= 1;
        scroll = game->unk_4A.s;
        phase_value -= 1;
        game->timer.s = phase_value;
        phase_value <<= 0x10;
        scroll += transition_timer;
        game->unk_4A.s = scroll;
        if (phase_value <= 0) {
            s32 stage;

            if (D_80113158[0] != 0) {
                gold_total = D_80012D5C[0];
                gold_remaining = D_8011315C[0];
                payout_handle = D_80024338[0];
                gold_total += gold_remaining;
                D_80012D5C[0] = gold_total;
                func_800B1DBC(payout_handle);
            }
            stage = game->stage.u;
                                     /* MATCH: the state load precedes timer materialization. */
            transition_timer = 0x8F;
            game->timer.s = transition_timer;
            game->stage.s = (s16) (stage + 1);
        }
        break;
    case 9:
        if ((s16) game->timer.s == 0x64) {
            SD_Call(0x702);
        }
        result_timer = game->timer.s - 1;
        game->timer.s = result_timer;
        if ((result_timer << 0x10) <= 0) {
            SD_Call(0x72);
            game->timer.s = 0x1EU;
            game->flags = (u16) (game->flags | 0x8000);
            game->stage.p = (u16) (game->stage.p + 1);
        }
        break;
    case 10:
        exit_timer = game->timer.s - 1;
        game->timer.s = exit_timer;
        if ((exit_timer << 0x10) <= 0) {
            s32 stage;

            base_object->unk_08 = 4;
            stage = game->stage.p;
            game->stage.s = (s16) (stage + 1);
        }
        break;
    }
    if ((u32) ((u16) game->stage.s - 6) < 3U) {
        payout_amount = D_8011315C[0];
        if (payout_amount >= 0x3E8) {
            payout_gold = D_80012D5C;
            payout_carry = *payout_gold;
            payout_amount -= 0x3E8;
            D_8011315C[0] = payout_amount;
            payout_carry += 0x3E8;
            *payout_gold = payout_carry;
        } else if (payout_amount >= 0x64) {
            payout_gold = D_80012D5C;
            payout_carry = *payout_gold;
            payout_amount -= 0x64;
            D_8011315C[0] = payout_amount;
            payout_carry += 0x64;
            *payout_gold = payout_carry;
        }
    }
    effect_state = (u16) game->stage.s;
    if ((u32) (effect_state - 5) < 5U) {
        object_index = (s16) effect_state < 9;
        func_80023E6C(0x50, game->unk_44, game, object_index);
        func_80023E6C(-0xF0, game->unk_46, game, object_index);
        func_80023E6C(0xA0, 4, game, object_index);
        func_80023E6C(-0xA0, 4, game, object_index);
    }
    object_index = 0;
    if (game->stage.s >= 4) {
        object_slot = (MinigameSlot *)game;
object_pairs:
        partner_index = object_index + 1;
        if (partner_index < 4) {
            position_slot = object_slot;
            motion_slot = object_slot;
            do {
                object_position = position_slot->rec;
                partner_position = game->rec[partner_index];
                if (abs(object_position->z.w.i - partner_position->z.w.i) < 0x40) {
                    s32 near_x;
                    s32 near_y;
                    s32 far_y;

                    far_y = partner_position->y.w.i;
                    near_x = abs(object_position->x.w.i - partner_position->x.w.i);
                    near_y = abs(object_position->y.w.i - far_y);
                    near_x += near_y;
                    if (near_x < 0x38) {
                        pair_value = object_position->unk_0C;
                        collision_value = object_position->unk_10;
                        pair_value = abs(pair_value);
                        collision_value = abs(collision_value);
                        pair_value += collision_value;
                        if (pair_value <= 0x3FFFF) {
                            position_slot->rec->unk_0C =
                                (s32) (func_80064584(*position_slot->angle) << 6);
                            position_slot->rec->unk_10 =
                                (s32) (func_800644B8(*position_slot->angle) << 6);
                        }
                        object_velocity = position_slot->rec;
                        partner_xy = game->rec[partner_index];
                        x_or_distance = object_velocity->x.w.i;
                        x_step = ((s16 *) &object_velocity->unk_10)[1];
                        other_x = partner_xy->x.w.i;
                        pair_value = object_velocity->y.w.i;
                        y_step = ((s16 *) &object_velocity->unk_0C)[1];
                        other_y = partner_xy->y.w.i;
                        phase_value = x_or_distance + x_step;
                        phase_value -= other_x;
                        collision_value = phase_value;
                        collision_value = abs(collision_value);
                        forward_y_gap = (pair_value - y_step) - other_y;
                        forward_y_gap = abs(forward_y_gap);
                        bounce_x = collision_value + forward_y_gap;
                        x_or_distance -= x_step;
                        x_or_distance -= other_x;
                        x_or_distance = abs(x_or_distance);
                        pair_value += y_step;
                        pair_value -= other_y;
                        pair_value = abs(pair_value);
                        x_or_distance += pair_value;
                        if (x_or_distance < bounce_x) {
                            x_or_distance = -object_velocity->unk_0C;
                            bounce_x = object_velocity->unk_10;
                        } else {
                            x_or_distance = object_velocity->unk_0C;
                            bounce_x = -object_velocity->unk_10;
                        }
                        collision_value = 0x30000;
                        if (object_index != 0) {
                            object_motion = (MinigameBody *)(motion_slot->node + 1);
                            object_motion->unk_0C = (s32) (object_motion->unk_0C + bounce_x);
                            object_motion->unk_10 = (s32) (object_motion->unk_10 + x_or_distance);
                            collision_value |= 0xFFFF;
                            other_speed_y = game->rec[partner_index]->unk_0C;
                            pair_value = game->rec[partner_index]->unk_10;
                            other_speed_y = abs(other_speed_y);
                            pair_value = abs(pair_value);
                            collision_value = collision_value < (other_speed_y + pair_value);
                            if (!collision_value) {
                                game->rec[partner_index]->unk_0C =
                                    (s32) (func_80064584(*game->angle[partner_index],
                                    (void *) x_or_distance, y_step, other_y) << 6);
                                game->rec[partner_index]->unk_10 =
                                    (s32) (func_800644B8(*game->angle[partner_index]) << 6);
                            }
                            partner_velocity = game->rec[partner_index];
                            object_xy = motion_slot->rec;
                            x_or_distance = partner_velocity->x.w.i;
                            x_step = ((s16 *) &partner_velocity->unk_10)[1];
                            other_x = object_xy->x.w.i;
                            pair_value = partner_velocity->y.w.i;
                            y_step = ((s16 *) &partner_velocity->unk_0C)[1];
                            other_y = object_xy->y.w.i;
                            phase_value = x_or_distance + x_step;
                            phase_value -= other_x;
                            collision_value = phase_value;
                            collision_value = abs(collision_value);
                            other_forward_y_gap = (pair_value - y_step) - other_y;
                            other_forward_y_gap = abs(other_forward_y_gap);
                            bounce_x = collision_value + other_forward_y_gap;
                            x_or_distance -= x_step;
                            x_or_distance -= other_x;
                            x_or_distance = abs(x_or_distance);
                            pair_value += y_step;
                            pair_value -= other_y;
                            pair_value = abs(pair_value);
                            x_or_distance += pair_value;
                            if (x_or_distance < bounce_x) {
                                x_or_distance = -partner_velocity->unk_0C;
                                bounce_x = partner_velocity->unk_10;
                            } else {
                                x_or_distance = partner_velocity->unk_0C;
                                bounce_x = -partner_velocity->unk_10;
                            }
                            if (partner_index != 0) {
                                goto object_collision;
                            }
                        }
                        base_object->unk_58 = (s32) (base_object->unk_58 + bounce_x);
                        base_object->unk_5C = (s32) (base_object->unk_5C + x_or_distance);
                        break;
object_collision:
                        object_motion = (MinigameBody *)(game->node[partner_index - 1] + 1);
                        object_motion->unk_0C = (s32) (object_motion->unk_0C + bounce_x);
                        object_motion->unk_10 = (s32) (object_motion->unk_10 + x_or_distance);
                    }
                }
                partner_index += 1;
            } while (partner_index < 4);
        }
        object_index += 1;
        object_slot = (MinigameSlot *) ((u8 *) object_slot + 4);   /* one pointer slot */
        if (object_index >= 3) {
            if (func_8002263C(game->rec[0], &game->slot[0], &base_object->unk_58, &base_object->unk_5C)
                != 0) {
                base_object->unk_48 = 0;
            }
            object_index = 1;
            do {
                moving_object = game->node[object_index - 1];
                object_motion = (MinigameBody *)(moving_object + 1);
                if (func_8002263C(game->rec[object_index], &game->slot[object_index],
                    &object_motion->unk_0C, &object_motion->unk_10) != 0) {
                    object_motion->unk_04 = 0;
                }
                object_index += 1;
            } while (object_index < 4);
        } else {
            goto object_pairs;
        }
    } else {
        return;
    }
}
