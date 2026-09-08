#include "common.h"

typedef struct S_81978428_0 {
    u8 pad_00[0xF4];
    s32 unk_F4;
} S_81978428_0;   /* init_page in func_81978428 */

typedef struct S_81978428_1 {
    u16 unk_00;
} S_81978428_1;   /* self->part4 in func_81978428 */

typedef struct S_81978428_2 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0xE];
    u16 unk_A6;
    u8 unk_A8;
} S_81978428_2;   /* case0_global in func_81978428 */

typedef struct S_81978428_3 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_81978428_3;   /* angle_global in func_81978428 */

typedef struct S_81978428_4 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x3778];
    s32 unk_3780;
} S_81978428_4;   /* copy_page in func_81978428 */

typedef struct S_81978428_5 {
    u8 pad_00[0x2A];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x5C];
    union { s16 s; u16 u; } unk_88;   /* accessed as both */
} S_81978428_5;   /* player in func_81978428 */

typedef struct S_81978428_6 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
} S_81978428_6;   /* work in func_81978428 */

typedef struct S_81978428_7 {
    u8 pad_00[0x88];
    u16 unk_88;
} S_81978428_7;   /* fallback in func_81978428 */

typedef struct S_81978428_8 {
    u8 pad_00[0x1C];
    u32 unk_1C;
} S_81978428_8;   /* case3_object in func_81978428 */

typedef struct S_81978428_9 {
    u8 pad_00[0x1C];
    u32 unk_1C;
} S_81978428_9;   /* after_object in func_81978428 */

typedef struct S_81978428_10 {
    u8 pad_00[0xC];
    u32 unk_0C;
} S_81978428_10;   /* after_aux in func_81978428 */

typedef struct S_81978428_11 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
    u8 pad_10[0x1490];
    u32 unk_14A0;
} S_81978428_11;   /* tail_page in func_81978428 */

typedef struct S_81978428_12_pre {
    u16 unk_00;
} S_81978428_12_pre;   /* the 0x2 bytes before self in func_81978428, addressed as self[-1] */



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
    State81978428 *self = arg0;
    s32 *out = arg1;
    void *work;
    s32 i;
    register u8 *map_y ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u8 *page_8008 ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 *x_table;
    u8 *tail_page;
    Scratch81978428 scratch;
    u8 *global;
    u8 *object;
    u8 *aux;
    register void *created ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u16 timer;
    s32 dispatch;
    s32 offset;
    register s32 delta ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 hard_zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

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
        u8 *init_page = (u8 *)0x80080000;
        u8 *case0_page;
        u8 *case0_global;
        u8 *angle_global;
        u16 next_state;

        ASM_KEEP(init_page);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        next_state = self->state;
        init_page = *(u8 **)(init_page + 0x14A8);
        self->counter = 0;
        next_state++;
        self->state = next_state;
        ((S_81978428_0 *)init_page)->unk_F4 = 0;
        func_800243C0((u8 *)self->part0 - 0x20, self->part4);
        if ((((S_81978428_1 *)(self->part4))->unk_00 & 0x80) == 0) {
            goto done;
        }
        case0_page = (u8 *)0x80080000;
        ASM_KEEP(case0_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        case0_global = *(u8 **)(case0_page + 0x14A8);
        self->timer = 10;
        ((S_81978428_2 *)case0_global)->unk_96 = 8;
        ((S_81978428_2 *)case0_global)->unk_A6--;
        ((S_81978428_2 *)case0_global)->unk_A8 = self->kind;
        angle_global = *(u8 **)(case0_page + 0x14A8);
        self->angle = ((S_81978428_3 *)angle_global)->unk_2A;
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
        u8 *copy_page = (u8 *)0x80080000;
        u8 *player;
        s32 call_angle;
        s32 copy_x;
        register s32 fifth_arg ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
#ifndef NON_MATCHING
        register s32 *call_sp ASM_REG("$29");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
#endif

        page_8008 = (u8 *)0x80080000;
        ASM_KEEP(copy_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(page_8008);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        copy_x = ((S_81978428_4 *)copy_page)->unk_3780;
        player = *(u8 **)(page_8008 + 0x14A8);
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        copy_page += 0x3780;
        ASM_KEEP(copy_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        out[0] = copy_x;
        out[1] = ((S_81978428_4 *)copy_page)->unk_04;
        out[2] = (s32)((S_81978428_5 *)player)->unk_88.s << 16;
        call_angle = ((S_81978428_5 *)player)->unk_2A.s;
        ASM_KEEP(call_angle);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        fifth_arg = 8;
#ifndef NON_MATCHING
        call_sp[4] = fifth_arg;
#endif
        created = (void *)0x80080000;
        ASM_KEEP_NV(created);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        map_y = (u8 *)created + 0x2E80;
        ASM_KEEP_NV(map_y);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
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
        ASM_KEEP(work);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        {
            register State81978428 *tail_arg ASM_REG("$4") = self;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            ASM_TAILSLOT_PIN_TIED(tail_arg);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_80025F5C();
        }
    }

    work = &scratch;
    ASM_KEEP(work);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    i = hard_zero;
    {
        u8 map_x_value;
        u8 map_y_value;

        tail_page = (u8 *)0x80070000;
        ASM_KEEP(tail_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        x_table = (s16 *)(tail_page - 0x3328);
        map_x_value = map_y[0x24];
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        tail_page = (u8 *)0x80070000;
        ASM_KEEP(tail_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ((S_81978428_6 *)work)->unk_02.s = (map_x_value << 6) + 0x20;
        map_y_value = map_y[0x25];
        map_y = tail_page - 0x3318;
        ((S_81978428_6 *)work)->unk_06.s = (map_y_value << 6) + 0x20;
    }

loop:
    {
        u8 *player;

        player = *(u8 **)(page_8008 + 0x14A8);
        offset = (((S_81978428_5 *)player)->unk_2A.u >> 8) & 0xE;
        delta = *(s16 *)((u32)offset + (u32)x_table);
        ((S_81978428_6 *)work)->unk_02.u += delta << 6;
        offset = (((S_81978428_5 *)player)->unk_2A.u >> 8) & 0xE;
        delta = *(s16 *)((u32)offset + (u32)map_y);
        ((S_81978428_6 *)work)->unk_06.u += delta << 6;
        ((S_81978428_6 *)work)->unk_0A.s = ((S_81978428_5 *)player)->unk_88.u;
    }
    ((S_81978428_6 *)work)->unk_0A.s = func_800BCAD0(work);
    if (((S_81978428_6 *)work)->unk_0A.u >= 0x201) {
        u8 *player;
        player = *(u8 **)(page_8008 + 0x14A8);
        ((S_81978428_6 *)work)->unk_0A.s = ((S_81978428_5 *)player)->unk_88.u;
    }

    if ((func_800A45D8(((S_81978428_6 *)work)->unk_02.s, ((S_81978428_6 *)work)->unk_06.s,
                        ((S_81978428_6 *)work)->unk_0A.u) << 16) != 0) {
        u8 *player;

        player = *(u8 **)(page_8008 + 0x14A8);
        offset = (((S_81978428_5 *)player)->unk_2A.u >> 8) & 0xE;
        delta = *(s16 *)((u32)offset + (u32)x_table);
        ((S_81978428_6 *)work)->unk_02.u -= delta << 6;
        offset = (((S_81978428_5 *)player)->unk_2A.u >> 8) & 0xE;
        delta = *(s16 *)((u32)offset + (u32)map_y);
        ((S_81978428_6 *)work)->unk_06.u -= delta << 6;
        ASM_KEEP(map_y);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ((S_81978428_6 *)work)->unk_0A.s = ((S_81978428_5 *)player)->unk_88.u;
        ((S_81978428_6 *)work)->unk_0A.s = func_800BCAD0(work);
        if (((S_81978428_6 *)work)->unk_0A.u < 0x201) {
            goto position_ready;
        }
        {
            u8 *fallback;
            fallback = *(u8 **)(page_8008 + 0x14A8);
            ((S_81978428_6 *)work)->unk_0A.s = ((S_81978428_7 *)fallback)->unk_88;
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
        u16 state_value = self->state;
        register u16 timer_value ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(state_value);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
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
        u16 state_value = 0x18;
        void *case2_object;

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
        u8 *case3_object = self->object;

        if (case3_object != 0) {
            u8 *case3_reload;
            register u8 *case3_aux ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            s16 case3_timer;

            ((S_81978428_8 *)case3_object)->unk_1C |= 0x10000000;
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
        u32 flag_value = 0x80080000;
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
        u8 *check_object = self->object;

        if (check_object != 0) {
            s32 ten = 10;
            s32 ten_again;
            ASM_KEEP(ten);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            ten_again = ten;
            func_8009CE1C(self->object, ten, self->effect, ten_again,
                          (s16)((self->angle << 9) + 0x800), self->part0, 1);
            {
                u32 mask = 0xEFFFFFFF;
                u32 color = 0x00808080;
                u8 *after_object = self->object;
                register u8 *after_aux ASM_REG("$6") =
                    *(u8 **)(after_object - 0x14);

                ((S_81978428_9 *)after_object)->unk_1C &= mask;
                ((S_81978428_10 *)after_aux)->unk_0C = color;
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
    ((S_81978428_11 *)tail_page)->unk_0C = 0;
    ((S_81978428_11 *)tail_page)->unk_0A--;
    ((S_81978428_12_pre *)self)[-1].unk_00 |= 0x8000;
    tail_page = (u8 *)0x80080000;
    ASM_KEEP(tail_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ((S_81978428_11 *)tail_page)->unk_14A0 |= 0x8000;
    func_80026154();

done:
    self->flag = 0;
    (void)keepalive;
}
