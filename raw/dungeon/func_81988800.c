#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef s32 M2C_UNK;

extern M2C_UNK D_8002441C;
extern M2C_UNK D_80024648;
extern M2C_UNK D_80024B20;
extern M2C_UNK D_80024D58;
extern void *D_80024008[];
extern s32 D_800814A0;
extern void *D_800814A8;
extern u8 D_80082E80[];
extern u16 D_80082E94;
extern s32 D_80083460;
extern u8 D_80083498[];

extern s32 func_8003DE58();
extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_80053EF0();
extern void func_8009CE1C();
extern void *func_800A3F28();
extern void func_800A56E0();

#ifdef __mips__
static const u32 bank_words[] __asm__("func_80024000")
    __attribute__((section(".text.func_80024000"), aligned(4))) = {
    0x8002401C,
    0x00000000,
    0x80024080,
    0x800240E8,
    0x800241E8,
    0x80024224,
    0x800242EC,
};
__asm__(".globl func_80024000\n"
        ".size func_80024000, 1052");
#define BODY_NAME func_8002401C
#else
#define BODY_NAME func_80024000
#endif

void BODY_NAME(void *arg0, void *arg1)
{
    static void *const jt_keep[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
    };
    s16 position[3];
    register void *object ASM_REG("$16");
    register u8 *work ASM_REG("$17");
    register void *state ASM_REG("$18") = arg0;
    register void *base ASM_REG("$19");
    register void *out ASM_REG("$20") = arg1;
    void *global;
    u8 *fields;
    u16 timer;

    ASM_KEEP(state);
    timer = FIELD(state, u16, 0x50);
    ASM_KEEP(timer);
    base = FIELD(state, void *, 0);
    FIELD(state, u16, 0x50) = timer - 1;
    work = (u8 *)base - 0x20;
    if (0) {
        ASM_KEEP(state);
        ASM_KEEP(out);
        ASM_KEEP(base);
        ASM_KEEP(work);
        ASM_KEEP(object);
    }

    (void)jt_keep;
    {
        s32 dispatch = FIELD(state, s16, 0xA);

        if ((u32)dispatch >= 5) {
            goto done;
        }
        goto *D_80024008[(u32)dispatch];
    }

jt_c0:
        FIELD(D_800814A8, u8, 0x102) = 1;
        FIELD(D_800814A8, s32, 0xF4) = 0;
        FIELD(out, s32, 0) = FIELD(FIELD(work, void *, 8), s32, 0);
        FIELD(out, s32, 4) = FIELD(FIELD(work, void *, 8), s32, 4);
        FIELD(out, s32, 8) = FIELD(FIELD(work, void *, 8), s32, 8);
        FIELD(state, u16, 0xA)++;
jt_c1: {
        register u8 *spawn_fields ASM_REG("$4");

        if (0) {
            ASM_KEEP(spawn_fields);
        }
        if (FIELD(FIELD(state, void *, 4), u16, 0) & 0x80) {
            global = D_800814A8;
            FIELD(state, u16, 0x50) = 10;
            FIELD(global, u16, 0xA6)--;
            FIELD(global, u8, 0xA8) = FIELD(state, u8, 8);

            object = func_8003FD64(0x302, D_80083498);
            if (object != 0) {
                if (func_8003DE58(FIELD(FIELD(work, void *, 0xC), void *, 8),
                                   FIELD(work, void *, 0xC), position, 0) == 0) {
                    position[2] = 0;
                    position[1] = 0;
                    position[0] = 0;
                }
                FIELD(object, void *, 0x10) = &D_80024648;
                func_8004491C(object, &D_8002441C);
                FIELD(object, void *, 0x20) = state;
                spawn_fields = (u8 *)object + 0x20;

                FIELD(out, s32, 0) = FIELD(FIELD(work, void *, 8), s32, 0) +
                                      ((s32)position[0] << 16);
                FIELD(spawn_fields, s32, 0x1C) = FIELD(out, s32, 0);
                FIELD(out, s32, 4) = FIELD(FIELD(work, void *, 8), s32, 4) +
                                      ((s32)position[1] << 16);
                FIELD(spawn_fields, s32, 0x20) = FIELD(out, s32, 4);
                FIELD(out, s32, 8) = FIELD(FIELD(work, void *, 8), s32, 8) +
                                      ((s32)position[2] << 16);
                FIELD(spawn_fields, s32, 0x24) = FIELD(out, s32, 8);
            }
            FIELD(state, u16, 0xA)++;
        }
        goto done;
    }

jt_c2: {
        register s32 choice ASM_REG("$4");
        s32 result;

        if (0) {
            ASM_KEEP(choice);
        }
        if (FIELD(state, s16, 0x50) <= 0) {
            result = func_80053EF0(4);
            choice = 0x4300;
            if (result != 2) {
                choice = 0x300;
            }
            func_800A56E0(choice);
            FIELD(state, u16, 0x50) = 13;
            FIELD(state, u16, 0xA)++;
        }
        goto done;
    }

jt_c3: {
        register u8 *settings ASM_REG("$3");
        register u8 *loop_ptr ASM_REG("$4");
        register s32 counter ASM_REG("$3");

        if (0) {
            ASM_KEEP(settings);
            ASM_KEEP(loop_ptr);
            ASM_KEEP(counter);
        }
        if (FIELD(state, s16, 0x50) <= 0) {
            object = func_8003FD64(0x302, D_80083498);
            if (object != 0) {
                FIELD(object, void *, 0x10) = &D_80024B20;
                func_8004491C(object, &D_80024D58);
                settings = D_80082E80;
                position[0] = (FIELD(D_800814A8, u16, 0x2A) >> 9) & 7;
                work = (u8 *)object + 0x20;
                FIELD(work, s16, 4) = (settings[0x24] << 6) + 0x20;
                FIELD(work, s16, 6) = (settings[0x25] << 6) + 0x20;
                FIELD(work, u16, 8) = FIELD(out, u16, 0xA);
                loop_ptr = (u8 *)object + 0x4A;
                for (counter = 7; counter >= 0; counter--, loop_ptr -= 6) {
                    FIELD(loop_ptr, s16, 0x12) = 0;
                    FIELD(loop_ptr, s16, 0x10) = 0;
                    ASM_KEEP(counter);
                }
                FIELD(work, void *, 0) = state;
                FIELD(work, s16, 0x40) = 0;
            }
            FIELD(state, u16, 0x50) = 0x3D;
            FIELD(state, u16, 0xA)++;
        }
        goto done;
    }

jt_c4: {
        if (FIELD(state, s16, 0x50) == 8) {
            object = D_800814A8;
            if (object != 0) {
                register u8 *table ASM_REG("$2");

                out = object;
                table = (u8 *)0x80080000;
                ASM_KEEP(table);
                work = table + 0x2E80;
loop:
                object = func_800A3F28(work[0x24], work[0x25], out, object);
                if (object == 0) {
                    goto loop_done;
                }
                if (FIELD(object, s32, 0x1C) & 0x2000) {
                    goto loop;
                }
                func_8009CE1C(object, 0x10, FIELD(state, u8, 9), 10,
                             FIELD(base, s16, 0x2A), base, 2);
                goto loop;
loop_done:
                ;
            }
        }

        if ((D_80082E94 & 0x8000) || FIELD(state, s16, 0x50) < 0) {
            if (FIELD(state, s16, 0x52) & 0x8000) {
                FIELD(state, u16, 0x52) &= 0x7FFF;
            } else {
                register u8 *tail ASM_REG("$3");

                tail = (u8 *)&D_80083460;
                if (0) {
                    ASM_KEEP(tail);
                }
                FIELD(tail, s32, 0xC) = 0;
                FIELD(tail, u16, 0xA)--;
                FIELD(state, u16, -2) |= 0x8000;
                D_800814A0 |= 0x8000;
            }
        }
        goto done;
    }

done:
    ;
}
