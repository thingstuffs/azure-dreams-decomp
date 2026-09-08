#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *D_80024008[];
extern u8 D_800814A8[16];
extern u8 D_80082E80[];
extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_800244BC[];
extern u8 D_80024810[];
extern u8 D_80024B20[];
extern u8 D_800DEE38[];
extern u16 D_80082E94[];
extern u8 D_80083460[];
extern u32 D_800814A0[];

#define GLOBAL_OBJECT (*(void **)D_800814A8)

extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void *func_8003FD64(s32, void *);
extern s32 func_8003DE58(void *, void *, void *, s32);
extern void func_8004491C(void *, void *);
extern s32 func_80053EF0(s32);
extern void func_800A56E0(s32);
extern u16 func_80066460(s32, s32, s32, s32);
extern u16 func_8006649C(s32, s32);
extern void func_8009CE1C(void *, s32, s32, s32, s32, void *, s32);
extern void func_8002413C(void) __attribute__((noreturn));
extern void func_80024434(void) __attribute__((noreturn));
extern void func_80024438(void) __attribute__((noreturn));
extern void func_8002449C(void) __attribute__((noreturn));

#ifdef __mips__
static const u32 func_819A6800_table[] __asm__("func_819A6800")
    __attribute__((used, section(".text.func_819A6800"), aligned(4))) = {
    0x80024020,
    0,
    0x80024080,
    0x8002414C,
    0x800242C4,
    0x80024304,
    0x80024424,
    0x80024448,
};
__asm__(".globl func_819A6800\n.size func_819A6800, 1212");
#define FUNC_819A6800_BODY func_819A6800_body
#else
#define FUNC_819A6800_BODY func_819A6800
#endif

#ifdef __mips__
void FUNC_819A6800_BODY(void *, void *)
    __attribute__((section(".text.func_819A6800")));
#endif

/* Runs a timed object creation sequence with visual effects and final cleanup. */
void FUNC_819A6800_BODY(void *sequence, void *out_position)
{
    u8 *self = (u8 *)sequence;
    register u8 *owner ASM_REG("$18") = FIELD(self, u8 *, 0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *record = FIELD(owner, u8 *, -0x14);
    register u8 *owner_object ASM_REG("$16") = owner - 0x20;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 timer;
    s32 state;
    static void *const state_labels[] = {
        &&state2,
        &&state4,
        &&state5,
        &&state6,
        &&state7,
        &&advance_state,
    };

    timer = FIELD(self, u16, 0x50) - 1;
    state = FIELD(self, s16, 0x0A);
    FIELD(self, u16, 0x50) = timer;
    if ((u32)state >= 6U) {
        goto return_done;
    }
    (void)state_labels;
    goto *D_80024008[state];

state2:
    {
        void *new_object;
        void *counter_object;
        s16 position_offset[3];
        u8 *effect_data;
        register u8 *sprite ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        u8 *global_slot = (u8 *)&D_800814A0[2];
        void *global_object = *(void **)global_slot;
        void *reloaded_object;
        FIELD(global_object, u8, 0x102) = 1;
        reloaded_object = *(void * volatile *)global_slot;
        FIELD(reloaded_object, volatile u32, 0xF4) = 0;

        FIELD(out_position, u32, 0) = FIELD(FIELD(owner_object, void *, 8), u32, 0);
        FIELD(out_position, u32, 4) = FIELD(FIELD(owner_object, void *, 8), u32, 4);
        FIELD(out_position, u32, 8) = FIELD(FIELD(owner_object, void *, 8), u32, 8);

        new_object = func_800A05A4(reloaded_object,
                                D_80082E80[0x24],
                                D_80082E80[0x25],
                                FIELD(reloaded_object, s16, 0x2A),
                                7);
        FIELD(owner, void *, 0x60) = new_object;
        if (new_object == 0) {
            FIELD(owner, u8, 0x72) = FIELD(record, u8, 0x24);
            FIELD(owner, u8, 0x73) = FIELD(record, u8, 0x25);
            return func_8002413C();
        } else {
            register u8 *created_record ASM_REG("$6") =
                FIELD(new_object, u8 *, -0x14);
            FIELD(owner, u8, 0x72) = FIELD(created_record, u8, 0x24);
            FIELD(owner, u8, 0x73) = FIELD(created_record, u8, 0x25);
        }

        FIELD(self, volatile u16, 0x0A)++;
        if ((FIELD(FIELD(self, void * volatile, 4), u16, 0) & 0x80) == 0) {
            goto return_done;
        }

        counter_object = GLOBAL_OBJECT;
        FIELD(self, u16, 0x50) = 10;
        FIELD(counter_object, u16, 0xA6)--;
        FIELD(counter_object, u8, 0xA8) = FIELD(self, u8, 8);
        new_object = func_8003FD64(0x312, D_80083498);
        record = new_object;
        if (record == 0) {
            goto advance_state;
        }

        if (func_8003DE58(FIELD(FIELD(owner_object, void *, 0x0C), void *, 8),
                          FIELD(owner_object, void *, 0x0C), position_offset, 0) == 0) {
            position_offset[2] = 0;
            position_offset[1] = 0;
            position_offset[0] = 0;
        }
        FIELD(record, void *, 0x10) = D_800244BC;
        func_8004491C(record, D_80045340);
        sprite = FIELD(record, u8 *, 0x0C);

        FIELD(FIELD(record, void *, 8), s32, 0) =
            FIELD(FIELD(owner_object, void *, 8), s32, 0) + ((s32)position_offset[0] << 16);
        FIELD(FIELD(record, void *, 8), s32, 4) =
            FIELD(FIELD(owner_object, void *, 8), s32, 4) + ((s32)position_offset[1] << 16);
        FIELD(FIELD(record, void *, 8), s32, 8) =
            FIELD(FIELD(owner_object, void *, 8), s32, 8) + ((s32)position_offset[2] << 16);

        effect_data = record + 0x20;
        FIELD(effect_data, u16, 0x0C) = FIELD(FIELD(record, void *, 8), u16, 2);
        FIELD(effect_data, u16, 0x0E) = FIELD(FIELD(record, void *, 8), u16, 6);
        FIELD(effect_data, u16, 0x10) = FIELD(FIELD(record, void *, 8), u16, 0x0A);

        FIELD(sprite, u16, 0x1E) = 0x1000;
        FIELD(sprite, u16, 0x1C) = 0x1000;
        FIELD(sprite, u16, 0x10) = 0x20;
        FIELD(sprite, u16, 0x14) |= 0x0C;
        FIELD(sprite, void *, 0) = D_800DEE38;
        FIELD(sprite, u32, 8) = FIELD(D_800DEE38, u32, 4);
        FIELD(sprite, u8, 4) = 0;
        FIELD(sprite, u8, 5) = 0;
        FIELD(sprite, u32, 0x0C) = 0x00606060;
        FIELD(record, void *, 0x20) = self;
        FIELD(effect_data, u16, 0x4C) = 0;
    }
    return func_80024434();

state4:
    if ((s16)FIELD(self, u16, 0x50) > 0) {
        goto return_done;
    }
    {
        s32 mode = func_80053EF0(4);
        if (mode != 2) {
            mode = 0x300;
        } else {
            mode = 0x4300;
        }
        func_800A56E0(mode);
    }
    {
        u16 unused_state = FIELD(self, u16, 0x0A);
        register u16 timer ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(unused_state);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        timer = 10;
        FIELD(self, u16, 0x50) = timer;
    }
    return func_80024438();

state5:
    {
        s16 timer_left = FIELD(self, s16, 0x50);
        if (timer_left == 7) {
            if (FIELD(owner, void *, 0x60) != 0) {
                void *new_object = func_8003FD64(0x302, D_80083498);
                if (new_object != 0) {
                    u8 *effect_data = (u8 *)new_object + 0x20;
                    u32 target_object;
                    FIELD(new_object, void *, 0x10) = D_80024810;
                    func_8004491C(new_object, D_80024B20);
                    target_object = FIELD(owner, u32, 0x60);
                    FIELD(effect_data, u16, 0x3C) = 0;
                    FIELD(effect_data, u16, 0x3E) = 0;
                    FIELD(effect_data, u16, 0x32) = 0x1F;
                    FIELD(effect_data, u16, 0x30) = 0x1F;
                    FIELD(effect_data, u32, 0x34) = target_object;
                    FIELD(effect_data, u16, 0x40) = func_80066460(0, 1, 0x2C0, 0x100);
                    FIELD(effect_data, u16, 0x42) = func_8006649C(0x60, 0x1F8);
                    FIELD(effect_data, u32, 0x38) = 0x00404040;
                    FIELD(new_object, void *, 0x20) = self;
                }
            }
        }
    }
    if (FIELD(self, s16, 0x50) == 4) {
        func_8009CE1C(FIELD(owner, void *, 0x60),
                      10,
                      FIELD(self, u8, 9),
                      12,
                      FIELD(GLOBAL_OBJECT, s16, 0x2A),
                      owner,
                      2);
    }
    if ((FIELD(D_80082E94, u16, 0) & 0x8000) == 0 &&
        FIELD(self, s16, 0x50) >= 0) {
        goto return_done;
    }
    {
        u16 unused_state;
        register u16 cleanup_delay ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        unused_state = FIELD(self, u16, 0x0A);
        ASM_KEEP(unused_state);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        cleanup_delay = 20;
        FIELD(self, u16, 0x50) = cleanup_delay;
    }
    return func_80024438();

state6:
    if ((s16)FIELD(self, u16, 0x50) > 0) {
        goto return_done;
    }

advance_state:
    FIELD(self, u16, 0x0A)++;
    return func_8002449C();

state7:
    {
        s16 signed_flags = FIELD(self, s16, 0x52);
        u16 flags = FIELD(self, u16, 0x52);
        if ((signed_flags & 0x8000) != 0) {
            FIELD(self, u16, 0x52) = flags & 0x7FFF;
            return func_8002449C();
        }
    }
    {
        u8 *globals = D_80083460;
        FIELD(globals, u32, 0x0C) = 0;
        FIELD(globals, u16, 0x0A)--;
    }
    FIELD(self, u16, -2) |= 0x8000;
    D_800814A0[0] |= 0x8000;

return_done:
    return;
}
