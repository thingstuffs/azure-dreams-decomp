#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct {
    void *part0;
    void *part4;
    u8 kind;
    u8 effect;
    s16 state;
    u8 pad0C[2];
    u16 angle;
    u16 counter;
    u8 pad12[2];
    void *object;
    s16 timer;
    s16 flag;
} State81978428;

typedef struct {
    s16 pad0;
    u16 x;
    s16 pad4;
    u16 y;
    s16 pad8;
    s16 z;
    u8 pad0C[8];
} Scratch81978428;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec81978428;

extern void *D_80024038[6];

extern u8 D_800814A8[12];
extern s32 D_800814A0[3];
extern u8 D_80082E80[];
extern u16 D_80082E94[5];
extern u8 D_80083460[16];
extern Vec81978428 D_80083780;
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];

extern void func_800243C0(void *, void *);
extern s32 func_80053EF0(s32);
extern void func_800A56E0(s32);
extern void *func_800A05A4();
extern u16 func_800BCAD0(void *);
extern s32 func_800A45D8(u16, u16, s16);
extern void func_80025A9C(void *, void *, void *);
extern void func_80025508(void *, void *);
extern void func_8009CE1C(void *, s32, u8, s32, s16, void *, s32);
extern void func_80025F5C(void) __attribute__((noreturn));
extern void func_800260F8(void) __attribute__((noreturn));
extern void func_80026040(void) __attribute__((noreturn));
extern void func_80026150(void) __attribute__((noreturn));
extern void func_80026154(void) __attribute__((noreturn));

void func_81978428(State81978428 *arg0, s32 *arg1)
{
    static void *const keepalive[] = {
        &&case0, &&case1, &&case2, &&case3, &&case4, &&case5,
    };
    register State81978428 *self ASM_REG("$17") = arg0;
    register s32 *out ASM_REG("$22") = arg1;
    register void *work ASM_REG("$16");
    register s32 i ASM_REG("$18");
    register u8 *map_y ASM_REG("$19");
    register u8 *page_8008 ASM_REG("$20");
    register s16 *x_table ASM_REG("$21");
    register u8 *tail_page ASM_REG("$3");
    Scratch81978428 scratch;
    u8 *global;
    u8 *object;
    u8 *aux;
    register void *created ASM_REG("$2");
    u16 timer;
    s32 dispatch;
    s32 offset;
    register s32 delta ASM_REG("$2");
    register s32 hard_zero ASM_REG("$0");

    timer = self->counter;
    dispatch = self->state;
    timer++;
    self->counter = timer;
    if ((u32)dispatch >= 6) {
        goto done;
    }
    {
        void *volatile *table = D_80024038;
        goto *table[dispatch];
    }

case0:
    {
        register u8 *init_page ASM_REG("$3") = (u8 *)0x80080000;
        register u8 *case0_page ASM_REG("$6");
        register u8 *case0_global ASM_REG("$5");
        register u8 *angle_global ASM_REG("$3");
        register u16 next_state ASM_REG("$2");

        ASM_KEEP(init_page);
        next_state = self->state;
        init_page = *(u8 **)(init_page + 0x14A8);
        self->counter = 0;
        next_state++;
        self->state = next_state;
        FIELD(init_page, s32, 0xF4) = 0;
        func_800243C0((u8 *)self->part0 - 0x20, self->part4);
        if ((FIELD(self->part4, u16, 0) & 0x80) == 0) {
            goto done;
        }
        case0_page = (u8 *)0x80080000;
        ASM_KEEP(case0_page);
        case0_global = *(u8 **)(case0_page + 0x14A8);
        self->timer = 10;
        FIELD(case0_global, u16, 0x96) = 8;
        FIELD(case0_global, u16, 0xA6)--;
        FIELD(case0_global, u8, 0xA8) = self->kind;
        angle_global = *(u8 **)(case0_page + 0x14A8);
        self->angle = FIELD(angle_global, u16, 0x2A);
        self->state++;
        if (func_80053EF0(4) != 2) {
            func_800A56E0(0x300);
            self->flag = 0;
            func_80026154();
        }
        func_800A56E0(0x4300);
        self->flag = 0;
        func_80026154();
    }

case1:
    timer = self->timer;
    timer--;
    self->timer = timer;
    if ((s32)((u32)timer << 16) > 0) {
        goto done;
    }

    {
        register u8 *copy_page ASM_REG("$2") = (u8 *)0x80080000;
        register u8 *player ASM_REG("$4");
        register s32 call_angle ASM_REG("$7");
        register s32 copy_x ASM_REG("$3");
        register s32 fifth_arg ASM_REG("$2");
#ifndef NON_MATCHING
        register s32 *call_sp ASM_REG("$29");
#endif

        page_8008 = (u8 *)0x80080000;
        ASM_KEEP(copy_page);
        ASM_KEEP(page_8008);
        copy_x = FIELD(copy_page, s32, 0x3780);
        player = *(u8 **)(page_8008 + 0x14A8);
        ASM_SCHED_BARRIER();
        copy_page += 0x3780;
        ASM_KEEP(copy_page);
        out[0] = copy_x;
        out[1] = FIELD(copy_page, s32, 4);
        out[2] = (s32)FIELD(player, s16, 0x88) << 16;
        call_angle = FIELD(player, s16, 0x2A);
        ASM_KEEP(call_angle);
        fifth_arg = 8;
        ASM_KEEP(fifth_arg);
#ifndef NON_MATCHING
        call_sp[4] = fifth_arg;
#endif
        created = (void *)0x80080000;
        ASM_KEEP_NV(created);
        map_y = (u8 *)created + 0x2E80;
        ASM_KEEP_NV(map_y);
#ifndef NON_MATCHING
        created = func_800A05A4(player, map_y[0x24], map_y[0x25], call_angle);
#else
        created = func_800A05A4(player, map_y[0x24], map_y[0x25],
                                call_angle, fifth_arg);
#endif
    }
    self->object = created;
    if (created != 0) {
        work = *(void **)((u8 *)created - 0x18);
        ASM_KEEP(work);
        {
            register State81978428 *tail_arg ASM_REG("$4") = self;
            ASM_TAILSLOT_PIN_TIED(tail_arg);
            func_80025F5C();
        }
    }

    work = &scratch;
    ASM_KEEP(work);
    ASM_KEEP(hard_zero);
    i = hard_zero;
    {
        u8 map_x_value;
        u8 map_y_value;

        tail_page = (u8 *)0x80070000;
        ASM_KEEP(tail_page);
        x_table = (s16 *)(tail_page - 0x3328);
        ASM_KEEP(x_table);
        map_x_value = map_y[0x24];
        ASM_SCHED_BARRIER();
        tail_page = (u8 *)0x80070000;
        ASM_KEEP(tail_page);
        FIELD(work, u16, 2) = (map_x_value << 6) + 0x20;
        map_y_value = map_y[0x25];
        map_y = tail_page - 0x3318;
        ASM_KEEP(map_y);
        FIELD(work, u16, 6) = (map_y_value << 6) + 0x20;
    }

loop:
    {
        register u8 *player ASM_REG("$4");

        player = *(u8 **)(page_8008 + 0x14A8);
        offset = (FIELD(player, u16, 0x2A) >> 8) & 0xE;
        delta = *(s16 *)((u32)offset + (u32)x_table);
        ASM_KEEP(delta);
        FIELD(work, s16, 2) += delta << 6;
        offset = (FIELD(player, u16, 0x2A) >> 8) & 0xE;
        delta = *(s16 *)((u32)offset + (u32)map_y);
        ASM_KEEP(delta);
        FIELD(work, s16, 6) += delta << 6;
        FIELD(work, u16, 0xA) = FIELD(player, u16, 0x88);
    }
    FIELD(work, u16, 0xA) = func_800BCAD0(work);
    if (FIELD(work, s16, 0xA) >= 0x201) {
        register u8 *player ASM_REG("$2");
        ASM_SCHED_BARRIER();
        player = *(u8 **)(page_8008 + 0x14A8);
        FIELD(work, u16, 0xA) = FIELD(player, u16, 0x88);
    }

    if ((func_800A45D8(FIELD(work, u16, 2), FIELD(work, u16, 6),
                        FIELD(work, s16, 0xA)) << 16) != 0) {
        register u8 *player ASM_REG("$4");

        ASM_SCHED_BARRIER();
        player = *(u8 **)(page_8008 + 0x14A8);
        offset = (FIELD(player, u16, 0x2A) >> 8) & 0xE;
        delta = *(s16 *)((u32)offset + (u32)x_table);
        ASM_KEEP(delta);
        FIELD(work, s16, 2) -= delta << 6;
        offset = (FIELD(player, u16, 0x2A) >> 8) & 0xE;
        delta = *(s16 *)((u32)offset + (u32)map_y);
        ASM_KEEP(delta);
        FIELD(work, s16, 6) -= delta << 6;
        ASM_KEEP(x_table);
        ASM_KEEP(map_y);
        FIELD(work, u16, 0xA) = FIELD(player, u16, 0x88);
        FIELD(work, u16, 0xA) = func_800BCAD0(work);
        if (FIELD(work, s16, 0xA) < 0x201) {
            goto position_ready;
        }
        {
            register u8 *fallback ASM_REG("$2");
            fallback = *(u8 **)(page_8008 + 0x14A8);
            FIELD(work, u16, 0xA) = FIELD(fallback, u16, 0x88);
            func_80025F5C();
        }
    }
    i++;
    if (i < 8) {
        goto loop;
    }

position_ready:
    func_80025A9C(self, out, work);
    {
        register u16 state_value ASM_REG("$2") = self->state;
        register u16 timer_value ASM_REG("$3");
        ASM_KEEP(state_value);
        timer_value = 0x10;
        self->timer = timer_value;
        func_800260F8();
    }

case2:
    timer = self->timer;
    timer--;
    self->timer = timer;
    if ((s32)((u32)timer << 16) > 0) {
        goto done;
    }
    {
        register u16 state_value ASM_REG("$2") = 0x18;
        register void *case2_object ASM_REG("$3");

        self->timer = state_value;
        state_value = self->state;
        case2_object = self->object;
        state_value++;
        self->state = state_value;
        if (case2_object != 0) {
            func_80025508(self, *(void **)((u8 *)case2_object - 0x18));
            self->flag = 0;
            func_80026154();
        }
    }
    goto done;

case3:
    {
        register u8 *case3_object ASM_REG("$4") = self->object;

        if (case3_object != 0) {
            register u8 *case3_reload ASM_REG("$3");
            register u8 *case3_aux ASM_REG("$6");
            s16 case3_timer;

            FIELD(case3_object, u32, 0x1C) |= 0x10000000;
            ASM_SCHED_BARRIER();
            case3_timer = self->timer;
            case3_reload = *(u8 *volatile *)((u8 *)self + 0x14);
            case3_aux = *(u8 **)(case3_reload - 0x14);
            if (case3_timer >= 0xC) {
                u8 value = case3_aux[0xE] + 8;
                case3_aux[0xE] = value;
                if (case3_aux[0xC] >= 0xE1) {
                    case3_aux[0xC] = 0xE0;
                    func_80026040();
                }
            } else {
                u8 value = case3_aux[0xE] - 8;
                case3_aux[0xE] = value;
                if (value < 0x80) {
                    case3_aux[0xE] = 0x80;
                }
            }
        }
    }

    {
        register u32 flag_value ASM_REG("$2") = 0x80080000;
        ASM_KEEP(flag_value);
        flag_value = *(u16 *)(flag_value + 0x2E94);
        if ((flag_value & 0x8000) == 0) {
            timer = self->timer;
            timer--;
            self->timer = timer;
            if ((s32)((u32)timer << 16) >= 0) {
                goto done;
            }
        }
    }

    {
        register u8 *check_object ASM_REG("$2") = self->object;

        if (check_object != 0) {
            register s32 ten ASM_REG("$5") = 10;
            register s32 ten_again ASM_REG("$7");
            ASM_KEEP(ten);
            ten_again = ten;
            func_8009CE1C(self->object, ten, self->effect, ten_again,
                          (s16)((self->angle << 9) + 0x800), self->part0, 1);
            {
                register u32 mask ASM_REG("$4") = 0xEFFFFFFF;
                register u32 color ASM_REG("$5") = 0x00808080;
                register u8 *after_object ASM_REG("$3") = self->object;
                register u8 *after_aux ASM_REG("$6") =
                    *(u8 **)(after_object - 0x14);

                FIELD(after_object, u32, 0x1C) &= mask;
                FIELD(after_aux, u32, 0xC) = color;
            }
        }
    }
case4:
    tail_page = (u8 *)0x80080000;
    if (self->flag != 0) {
        self->state++;
        func_80026150();
    }
    goto cleanup;

case5:
    tail_page = (u8 *)0x80080000;
    if (self->flag != 0) {
        goto done;
    }

cleanup:
    tail_page += 0x3460;
    ASM_KEEP(tail_page);
    FIELD(tail_page, s32, 0xC) = 0;
    FIELD(tail_page, u16, 0xA)--;
    FIELD(self, u16, -2) |= 0x8000;
    tail_page = (u8 *)0x80080000;
    ASM_KEEP(tail_page);
    FIELD(tail_page, u32, 0x14A0) |= 0x8000;
    func_80026154();

done:
    self->flag = 0;
    (void)keepalive;
}
