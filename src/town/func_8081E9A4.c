#include "common.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/entity.h"


typedef struct {
    u8 *child;
    u8 pad04[0x10];
    s32 amount;
    s16 state;
    s16 timer;
    s16 count;
    s16 ticks;
    u16 flags;
    s16 phase;
    s16 phase2;
} TownEffect;

typedef struct {
    s16 kind;
    s16 unused;
    void *owner;
    u8 pad08[0x4C];
    s16 x;
    s16 y;
} EffectMessage;

typedef struct {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 e;
    s32 f;
} EffectScratch;

typedef struct {
    EffectMessage message;
    EffectScratch scratch;
    s16 digits[3];
} EffectFrame;


extern u8 D_800220A8[];
extern u8 D_80024450[];
extern u8 D_800834B8[];
extern s32 D_80012D5C[3];
extern s32 D_80024558[3];
extern s32 D_80100E18[3];
extern u8 D_800D0078[];
extern u8 D_800D0080[];
extern u8 D_800D00A0[];
extern u8 D_800D00A8[];
extern u8 D_800D00B8[];
extern u8 D_80097D2C[];
extern void func_8002222C(void);

extern void func_80020570(void *, void *);
extern s32 func_800352FC(s32);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void SD_Call(s32);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80069EF8(void);
extern void func_80093864(void);
extern void func_80093C70(void);
extern void func_80093CEC(void *);
extern void func_80093D48(void *, void *, void *, ...);
extern s32 func_800B1BEC(s32, s32, s32);
extern void func_800B1DBC(s32);


typedef struct S_800211A4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_800211A4_0;   /* object in func_800211A4 */

typedef struct S_800211A4_1 {
    u8 pad_00[0x4];
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    u32 unk_08;
    u32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_800211A4_1;   /* object_child in func_800211A4 */

typedef struct S_800211A4_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800211A4_2;   /* object_link in func_800211A4 */

typedef struct S_800211A4_3 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
    u8 pad_18[0x2];
    s16 unk_1A;
} S_800211A4_3;   /* arg0 in func_800211A4 */

typedef struct S_800211A4_5 {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x8];
    u16 unk_10;
} S_800211A4_5;   /* primitive in func_800211A4 */

typedef struct S_800211A4_6 {
    u8 pad_00[0x70];
    s16 unk_70;
    s16 unk_72;
    s16 unk_74;
} S_800211A4_6;   /* child in func_800211A4 */


typedef struct S_800211A4_10 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800211A4_10;   /* (u8 *)counter in func_800211A4 */

typedef struct S_800211A4_11 {
    u8 pad_00[0x1D];
    u8 unk_1D;
} S_800211A4_11;   /* &message in func_800211A4 */

typedef struct S_800211A4_12 {
    u8 pad_00[0x70];
    union { s16 s; u16 u; } unk_70;   /* accessed as both */
} S_800211A4_12;   /* digit in func_800211A4 */

typedef struct S_800211A4_13 {
    u32 unk_00;
    u32 unk_04;
    u32 unk_08;
} S_800211A4_13;   /* ((S_800211A4_0 *)object)->unk_08 in func_800211A4 */

/* Updates the betting effect, handling input, animation, payouts, and refunds. */
void func_800211A4(TownEffect *input)
{
    GameWork *controls;
    u8 *primitive;
    u8 *child;
    TownEffect *effect = input;
    EffectFrame frame;
    s32 state;
#define message frame.message
#define scratch frame.scratch
#define digits frame.digits

    controls = &gameWork;
    child = (u8 *)effect->child + 0x20;
    state = effect->state;
    primitive = D_800834B8;
    switch (state) {

    case 0:
    {
        void *object;
        S_800211A4_1 *object_child;
        u8 *object_link;
        s32 column;
        s32 grid_origin_x;
        u16 flags;
        void *message_ptr;
        flags = effect->flags;
        D_80100E18[0] = 1;
        effect->phase = 3;
        effect->ticks = 0;
        effect->amount = 0;
        flags &= ~2;
        effect->flags = flags;
        func_80093864();
        SD_Call(0x700);
        effect->state = 1;
        effect->flags &= ~8;
        grid_origin_x = 0x05200000;

        message.kind = 0;
        message.owner = effect;
        message.x = 2;
        do {
            message.y = 9;
            message_ptr = &message;
state0_inner:
            {
                s32 row_depth;
                s32 grid_x;
                grid_x = message.x;
                row_depth = 0x03E00000;
                scratch.b = row_depth;
                scratch.f = 0;
                scratch.e = 0;
                scratch.d = 0;
                scratch.a = grid_origin_x - (grid_x << 22);
                scratch.c = -((s32)message.y << 19);
                func_80020570(message_ptr, &scratch);
            }
            if (--message.y >= 0) {
                message_ptr = &message;
                goto state0_inner;
            }
        } while (--message.x >= 0);

        for (column = 2; column >= 0; column--) {
            object = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
            if (object != 0) {
                object_child = ((S_800211A4_0 *)object)->unk_0C;
                ((S_800211A4_0 *)object)->unk_10 = D_800220A8;
                object_link = (u8 *)object + 0x20;
                func_8004491C(object, func_80045340);
                ((S_800211A4_13 *)(((S_800211A4_0 *)object)->unk_08))->unk_00 =
                    (column << 23) + 0x04600000;
                ((S_800211A4_13 *)(((S_800211A4_0 *)object)->unk_08))->unk_04 = 0x03600000;
                ((S_800211A4_13 *)(((S_800211A4_0 *)object)->unk_08))->unk_08 = 0xFE000000;
                object_child->unk_1C =
                    object_child->unk_1E = 0x1000;
                object_child->unk_14 |= 0x000C;
                object_child->unk_08 = *(u32 *)(D_80024450 + (column << 2));
                object_child->unk_04 = 0;
                object_child->unk_05 = 0;
                object_child->unk_0C = 0x00808080;
                ((S_800211A4_2 *)object_link)->unk_04 = effect;
            }
        }
        break;
    }

    case 1:
    {
        EntityRec *motion;
        s32 handle;
        s32 payout_scale;
        if (effect->phase == 3) {
            break;
        }
        SD_Call(0x523);
        handle = func_800B1BEC(0, -80, 64);
        payout_scale = 6 / (effect->phase + 1);
        D_80024558[0] = handle;
        ((S_800211A4_3 *)effect)->unk_10 = payout_scale;
        if (func_800352FC(payout_scale) == 0) {
            motion = &D_80083780;
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            ((S_800211A4_5 *)primitive)->unk_10 = 0;
            func_80093CEC(D_800D0078);
            ((S_800211A4_5 *)primitive)->unk_00 = D_80097D2C;
            ((S_800211A4_5 *)primitive)->unk_04 = func_8002222C;
        }
        ((S_800211A4_6 *)child)->unk_70 = 1;
        ((S_800211A4_6 *)child)->unk_72 = 16;
        ((S_800211A4_6 *)child)->unk_74 = 20;
        effect->timer = 5;
        effect->state = 2;
        break;
    }

    case 2:
    {
        s32 pressed_buttons;
        if ((controls->buttons & 0x5000) != 0) {
            if (effect->timer-- < 0) {
                effect->timer = 0;
            }
        } else {
            effect->timer = 5;
        }
        if ((((s32)controls->unk_010) & 0x1000) == 0) {
            if ((controls->buttons & 0x1000) == 0 || effect->timer > 0) {
                goto state_3_body;
            }
        }
        if (effect->amount < 10000 && (u32)D_80012D5C[0] >= 100) {
            SD_Call(0x502);
            D_80012D5C[0] -= 100;
            effect->amount = effect->amount + 100;
            goto state_3_after_shake;
        }

state_3_body:
        if ((((s32)controls->unk_010) & 0x4000) == 0) {
            if ((controls->buttons & 0x4000) == 0 || effect->timer > 0) {
                goto state_3_after_shake;
            }
        }
        if (effect->amount >= 100) {
            SD_Call(0x502);
            D_80012D5C[0] += 100;
            effect->amount = effect->amount - 100;
        }

state_3_after_shake:
        effect->ticks = effect->amount / 100;
        if (effect->ticks != 0) {
            pressed_buttons = ((s32)controls->unk_010);
        } else {
            pressed_buttons = ((s32)controls->unk_010);
        }
        if ((pressed_buttons & 0x40) != 0) {
            if (effect->amount > 0) {
                effect->state = 3;
                effect->timer = 9;
                ((EntityRec *)((u8 *)(&D_80083780)))->flags14 = -0x240000;
                break;
            }
            break;
        }
        if ((pressed_buttons & 0x20) == 0) {
            break;
        }
        if (((S_800211A4_6 *)child)->unk_70 != 0) {
            ((S_800211A4_6 *)child)->unk_70 = 3;
        }
        effect->state = 10;
        break;
    }

    case 3:
    {
        EntityRec *motion;
        u16 *prim_angle;
        s16 *timer_ptr;
        EntityRec *motion_words;
        s32 x_speed;
        s32 current_y;
        s32 target_y;
        prim_angle = (u16 *)primitive;
        timer_ptr = &effect->timer;
        prim_angle[8] = (prim_angle[8] + 0x200) & 0xFFF;
        if (--*timer_ptr <= 0) {
            *timer_ptr = 10;
            motion = &D_80083780;
            motion_words = motion;
            target_y = 0x02A00000;
            x_speed = (0x03600000 - motion_words->x.v) / effect->timer;
            current_y = motion_words->y.v;
            motion_words->unk_0C = x_speed;
            motion_words->unk_10 = (target_y - current_y) / effect->timer;
            effect->state = 11;
        }
        break;
    }

    case 11:
    {
        u16 *prim_angle;
        u16 *timer_ptr;
        s32 timer_left;
        prim_angle = (u16 *)primitive;
        timer_ptr = (u16 *)&effect->timer;
        prim_angle[8] = (prim_angle[8] + 0x200) & 0xFFF;
        timer_left = *timer_ptr - 1;
        *timer_ptr = (s16)timer_left;
        if ((s16)timer_left <= 0) {
            ((EntityRec *)((u8 *)(&D_80083780)))->x.v = 0x03600000;
            ((EntityRec *)((u8 *)(&D_80083780)))->y.v = 0x02A00000;
            ((EntityRec *)((u8 *)(&D_80083780)))->unk_10 = 0;
            ((EntityRec *)((u8 *)(&D_80083780)))->unk_0C = 0;
            ((EntityRec *)((u8 *)(&D_80083780)))->flags14 = 0x00180000;
            effect->state = 12;
        }
        break;
    }

    case 12:
    {
        EntityRec *motion;
        s32 angle;
        motion = &D_80083780;
        angle = (((S_800211A4_5 *)primitive)->unk_10 + 0x200) & 0xFFF;
        ((S_800211A4_5 *)primitive)->unk_10 = angle;
        if (motion->z.v < (s32)0xFF000000 || angle != 0) {
            break;
        }
        motion->z.v = (s32)0xFF000000;
        effect->state = 4;
        func_80093D48(primitive, motion, ((u8 *)(&D_80082E80)), (s32)0xFF000000);
        func_80093C70();
        break;
    }

    case 4:
    {
        EntityRec *motion;
        if ((((s32)controls->unk_010) & 0x40) == 0 ||
            ((S_800211A4_6 *)child)->unk_70 != 2) {
            break;
        }
        SD_Call(0x50A);
        func_80093CEC(D_800D00A0);
        motion = &D_80083780;
        motion->unk_10 = 0x48000;
        motion->flags14 = (s32)0xFFF40000;
        effect->count = 0;
        effect->state = 5;
        break;
    }

    case 5:
    {
        EntityRec *motion;
        s32 old_count;
        s32 z_speed_limit;
        s32 frame_index;
        z_speed_limit = 0x9FFFF;
        motion = &D_80083780;
        motion->y.v += motion->unk_10;
        motion->z.v += motion->flags14;
        if (motion->flags14 <= z_speed_limit) {
            motion->flags14 += 0x20000;
        }
        old_count = (u16)effect->count;
        effect->count = (s16)(old_count + 1);
        frame_index = (s16)old_count;
        switch (frame_index) {

        case 0:
            func_80093CEC(D_800D00A8);
            break;
        case 5:
            func_80093CEC(D_800D00B8);
            break;
        case 20:
            SD_Call(0x508);
            {
                s32 y_speed = 0x18000;
                u8 *animation = D_800D0078;
                EntityRec *motion;
                motion = &D_80083780;
                motion->flags14 = (s32)0xFFF40000;
                motion->unk_10 = y_speed;
                func_80093CEC(animation);
            }
            break;
        case 25:
            func_80093CEC(D_800D00B8);
            break;
        case 21:
        case 37:
        case 49:
        case 62:
            func_80093CEC(D_800D00A8);
            break;
        case 36:
            SD_Call(0x508);
            {
                u8 *animation = D_800D0078;
                EntityRec *motion;
                motion = &D_80083780;
                motion->flags14 = (s32)0xFFF80000;
                motion->unk_10 = 0x20000;
                func_80093CEC(animation);
            }
            break;
        case 48:
            SD_Call(0x508);
            ((EntityRec *)((u8 *)(&D_80083780)))->flags14 = (s32)0xFFFC0000;
            func_80093CEC(D_800D0078);
            break;
        case 59:
            SD_Call(0x508);
            ((EntityRec *)((u8 *)(&D_80083780)))->flags14 = (s32)0xFFFC8000;
            func_80093CEC(D_800D0078);

        }

        if (((S_800211A4_6 *)child)->unk_70 != 3) {
            break;
        }
        {
            u8 *animation = D_800D0078;
            EntityRec *motion;
            motion = &D_80083780;
            motion->flags14 = (s32)0xFFFB0000;
            motion->unk_10 = 0;
            motion->z.v = (s32)0xFFC00000;
            func_80093CEC(animation);
        }
        effect->count = 0;
        effect->state = 6;
        break;
    }

    case 6:
    {
        EntityRec *motion;
        EntityRec *motion_words;
        s32 old_count;
        s32 count_or_addr;
        s32 frame_index;

        motion = &D_80083780;
        motion_words = motion;
        motion_words->z.v += motion_words->flags14;
        motion_words->flags14 += 0x10000;
        old_count = (u16)effect->count;
        count_or_addr = old_count + 1;
        effect->count = (s16)count_or_addr;
        frame_index = (s16)old_count;
        switch (frame_index) {

        case 0:
        case 11:
        case 19:
            func_80093CEC(D_800D00A8);
            break;
        case 5:
            func_80093CEC(D_800D00B8);
            break;
        case 10:
            SD_Call(0x508);
            ((EntityRec *)((u8 *)(&D_80083780)))->flags14 = (s32)0xFFFC0000;
            func_80093CEC(D_800D0078);
            break;
        case 18:
            SD_Call(0x508);
            {
                s32 z_speed;
                count_or_addr = (s32)(D_800834B8 + 0x2C8);
                z_speed = (s32)0xFFFD0000;
                ((S_800211A4_10 *)((u8 *)count_or_addr))->unk_14 = z_speed;
            }
        case 26:
            func_80093CEC(D_800D0078);
            break;
        }

        if (effect->count != 28) {
            break;
        }
        {
            u8 *animation = D_800D0078;
            EntityRec *motion;
            ((S_800211A4_6 *)child)->unk_70 = 4;
            motion = &D_80083780;
            motion->flags14 = 0;
            motion->z.v = (s32)0xFFC00000;
            func_80093CEC(animation);
        }
        effect->count = 3;
        effect->state = 7;
        break;
    }

    case 7:
    {
        s32 orbit_component;
        EntityRec *motion;
        EntityRec *motion_words;
        s16 *timer_ptr;
        orbit_component = effect->timer;
        orbit_component = func_800644B8(0x1000 - orbit_component);
        motion = &D_80083780;
        motion_words = motion;
        motion_words->x.v = (s32)((u32)(orbit_component * 5) << 9) + 0x03600000;
        timer_ptr = (s16 *)((u8 *)effect + 0x1A);
        orbit_component = func_80064584(0x1000 - *timer_ptr);
        motion_words->y.v = (s32)((u32)(orbit_component * 5) << 9) + 0x03600000;
        if (--effect->count == 0) {
            func_80093CEC(D_800D0080);
        }
        if (((S_800211A4_6 *)child)->unk_70 != 0) {
            break;
        }
        if (effect->phase == effect->phase2) {
            ((S_800211A4_6 *)child)->unk_70 = 6;
            effect->timer = 30;
            effect->state = 8;
        } else {
            effect->amount = 0;
            effect->state = 10;
        }
        break;
    }

    case 8:
    {
        s32 particle_index;
        s32 tick_dec;
        s32 timer_dec;
        s32 origin_xy;
        s32 angle;
        s32 payout_tens;
        s32 payout_hundreds;
        s32 hundreds_digit;
        s32 tens_digit;
        s32 ones_digit;
        s32 digit_sum;
        s32 random_value;
        s32 digit_count;
        u16 digit_count_raw;
        u8 *digit;
        tick_dec = (u16)effect->ticks - 2;
        effect->ticks = (s16)tick_dec;
        if ((s16)tick_dec < 0) {
            func_80093864();
            effect->ticks = 0;
            effect->flags |= 8;
        }
        timer_dec = (u16)effect->timer - 1;
        effect->timer = (s16)timer_dec;
        if ((s16)timer_dec > 0 || (effect->flags & 8) == 0) {
            break;
        }

        particle_index = (((S_800211A4_3 *)effect)->unk_14 * ((S_800211A4_3 *)effect)->unk_10) / 100;
        ((S_800211A4_3 *)effect)->unk_1A = 0xF0;
        payout_tens = particle_index / 10;
        ones_digit = particle_index - payout_tens * 10;
        digits[0] = (s16)ones_digit;
        digit_sum = (s16)ones_digit;
        payout_hundreds = payout_tens / 10;
        tens_digit = payout_tens - payout_hundreds * 10;
        digits[1] = (s16)tens_digit;
        digit_sum += (s16)tens_digit;
        hundreds_digit = payout_hundreds - (payout_hundreds / 10) * 10;
        digit_sum += (s16)hundreds_digit;
        digits[2] = (s16)hundreds_digit;
        if (digit_sum < 10) {
            if ((s16)hundreds_digit > 0) {
                digit_sum += 9;
                digits[2] = (s16)(hundreds_digit - 1);
                digits[1] = (s16)(tens_digit + 10);
            } else if ((s16)tens_digit > 0) {
                digit_sum += 9;
                digits[1] = (s16)(tens_digit - 1);
                digits[0] = (s16)(ones_digit + 10);
            }
        }
        effect->flags &= ~8;
        message.kind = 1;
        message.owner = effect;
        ((S_800211A4_11 *)(&message))->unk_1D = 0;
        message.unused = 8;
        particle_index = 0;
        while (particle_index < digit_sum) {
            do {
                random_value = func_80069EF8();
                message.x = (s16)(random_value % 3);
                digit = (u8 *)((s32)message.x * 2 + (s32)(u8 *)&frame);
                digit_count = ((S_800211A4_12 *)digit)->unk_70.s;
                digit_count_raw = ((S_800211A4_12 *)digit)->unk_70.u;
            } while (digit_count <= 0);
            do {
                ((S_800211A4_12 *)digit)->unk_70.s = digit_count_raw - 1;
            } while (0);
            origin_xy = 0x03600000;
            angle = (particle_index << 12) / digit_sum;
            scratch.a = origin_xy;
            scratch.b = origin_xy;
            scratch.c = (s32)0xFF800000;
            scratch.d = (s32)((u32)(func_800644B8(angle) * 5) << 6);
            scratch.e = (s32)((u32)(func_80064584(angle) * 5) << 6);
            scratch.f = (s32)0xFFF80000;
            func_80020570(&message, &scratch);
            particle_index++;
        }
        effect->state = 9;
        break;
    }

    case 9:
    {
        s32 timer_left;
        timer_left = (u16)effect->timer - 1;
        effect->timer = (s16)timer_left;
        if ((s16)timer_left > 0) {
            break;
        }
        func_800B1DBC(D_80024558[0]);
        effect->state = 0;
        effect->flags |= 2;
        break;
    }

    case 10:
    {
        s32 ticks_left;
        s32 money;
        if (((S_800211A4_3 *)effect)->unk_14 != 0) {
            money = D_80012D5C[0];
            if (effect->ticks < 2) {
                D_80012D5C[0] = money + 100;
            } else {
                D_80012D5C[0] = money + 200;
            }
        }
        ticks_left = (u16)effect->ticks - 2;
        effect->ticks = (s16)ticks_left;
        if ((s16)ticks_left > 0) {
            break;
        }
        func_800B1DBC(D_80024558[0]);
        effect->ticks = 0;
        effect->state = 0;
        effect->flags |= 0xA;
        func_80093D48(primitive, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)));
    }
    }

common_done:
    effect->flags &= ~1;
}
