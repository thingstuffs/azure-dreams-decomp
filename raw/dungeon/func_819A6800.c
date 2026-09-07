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

void FUNC_819A6800_BODY(void *arg0, void *arg1)
{
    register u8 *self ASM_REG("$19") = (u8 *)arg0;
    register u8 *owner ASM_REG("$18") = FIELD(self, u8 *, 0);
    register u8 *record ASM_REG("$17") = FIELD(owner, u8 *, -0x14);
    register u8 *base ASM_REG("$16") = owner - 0x20;
    u16 timer;
    s32 state;
    static void *const keepalive[] = {
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
    (void)keepalive;
    goto *D_80024008[state];

state2:
    {
        void *created;
        void *counter_object;
        s16 scratch[3];
        register u8 *part ASM_REG("$4");
        register u8 *sub ASM_REG("$6");

        register u8 *global_page ASM_REG("$4") = (u8 *)&D_800814A0[2];
        register void *global_object ASM_REG("$3") = *(void **)global_page;
        void *global_object2;
        FIELD(global_object, u8, 0x102) = 1;
        global_object2 = *(void * volatile *)global_page;
        FIELD(global_object2, volatile u32, 0xF4) = 0;

        FIELD(arg1, u32, 0) = FIELD(FIELD(base, void *, 8), u32, 0);
        FIELD(arg1, u32, 4) = FIELD(FIELD(base, void *, 8), u32, 4);
        FIELD(arg1, u32, 8) = FIELD(FIELD(base, void *, 8), u32, 8);

        created = func_800A05A4(global_object2,
                                D_80082E80[0x24],
                                D_80082E80[0x25],
                                FIELD(global_object2, s16, 0x2A),
                                7);
        FIELD(owner, void *, 0x60) = created;
        if (created == 0) {
            FIELD(owner, u8, 0x72) = FIELD(record, u8, 0x24);
            FIELD(owner, u8, 0x73) = FIELD(record, u8, 0x25);
            return func_8002413C();
        } else {
            register u8 *created_record ASM_REG("$6") =
                FIELD(created, u8 *, -0x14);
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
        created = func_8003FD64(0x312, D_80083498);
        record = created;
        if (record == 0) {
            goto advance_state;
        }

        if (func_8003DE58(FIELD(FIELD(base, void *, 0x0C), void *, 8),
                          FIELD(base, void *, 0x0C), scratch, 0) == 0) {
            scratch[2] = 0;
            scratch[1] = 0;
            scratch[0] = 0;
        }
        FIELD(record, void *, 0x10) = D_800244BC;
        func_8004491C(record, D_80045340);
        sub = FIELD(record, u8 *, 0x0C);

        FIELD(FIELD(record, void *, 8), s32, 0) =
            FIELD(FIELD(base, void *, 8), s32, 0) + ((s32)scratch[0] << 16);
        FIELD(FIELD(record, void *, 8), s32, 4) =
            FIELD(FIELD(base, void *, 8), s32, 4) + ((s32)scratch[1] << 16);
        FIELD(FIELD(record, void *, 8), s32, 8) =
            FIELD(FIELD(base, void *, 8), s32, 8) + ((s32)scratch[2] << 16);

        part = record + 0x20;
        FIELD(part, u16, 0x0C) = FIELD(FIELD(record, void *, 8), u16, 2);
        FIELD(part, u16, 0x0E) = FIELD(FIELD(record, void *, 8), u16, 6);
        FIELD(part, u16, 0x10) = FIELD(FIELD(record, void *, 8), u16, 0x0A);

        FIELD(sub, u16, 0x1E) = 0x1000;
        FIELD(sub, u16, 0x1C) = 0x1000;
        FIELD(sub, u16, 0x10) = 0x20;
        FIELD(sub, u16, 0x14) |= 0x0C;
        FIELD(sub, void *, 0) = D_800DEE38;
        FIELD(sub, u32, 8) = FIELD(D_800DEE38, u32, 4);
        FIELD(sub, u8, 4) = 0;
        FIELD(sub, u8, 5) = 0;
        FIELD(sub, u32, 0x0C) = 0x00606060;
        FIELD(record, void *, 0x20) = self;
        FIELD(part, u16, 0x4C) = 0;
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
        register u16 timer ASM_REG("$3");
        ASM_KEEP(unused_state);
        timer = 10;
        FIELD(self, u16, 0x50) = timer;
    }
    return func_80024438();

state5:
    {
        s16 current = FIELD(self, s16, 0x50);
        if (current == 7) {
            if (FIELD(owner, void *, 0x60) != 0) {
                void *created = func_8003FD64(0x302, D_80083498);
                if (created != 0) {
                    u8 *part = (u8 *)created + 0x20;
                    register u32 owner_field ASM_REG("$3");
                    FIELD(created, void *, 0x10) = D_80024810;
                    func_8004491C(created, D_80024B20);
                    owner_field = FIELD(owner, u32, 0x60);
                    FIELD(part, u16, 0x3C) = 0;
                    FIELD(part, u16, 0x3E) = 0;
                    FIELD(part, u16, 0x32) = 0x1F;
                    FIELD(part, u16, 0x30) = 0x1F;
                    FIELD(part, u32, 0x34) = owner_field;
                    FIELD(part, u16, 0x40) = func_80066460(0, 1, 0x2C0, 0x100);
                    FIELD(part, u16, 0x42) = func_8006649C(0x60, 0x1F8);
                    FIELD(part, u32, 0x38) = 0x00404040;
                    FIELD(created, void *, 0x20) = self;
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
        register u16 final_state ASM_REG("$3");
        unused_state = FIELD(self, u16, 0x0A);
        ASM_KEEP(unused_state);
        final_state = 20;
        FIELD(self, u16, 0x50) = final_state;
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
