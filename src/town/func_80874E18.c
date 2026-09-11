#include "common.h"

#ifdef NON_MATCHING
#define ({                                                                       register s32 zero ASM_REG("$0");                                   ASM_KEEP(zero);                                                      zero | (value);                                                      }) (value)
#else
#endif

#define FIELD(base, type, offset) (*(type)((u8 *)(base) + (offset)))

typedef struct {
    u8 pad[0xBBC];
    s16 values[1];
} InputTable;

typedef struct {
    u8 pad[0x30];
    s32 flags;
} State;

typedef struct {
    u8 pad[0x54];
    s32 (*callback)(s32);
} CallbackOwner;

extern InputTable D_80700000;
extern s16 D_80700BB2[];
extern State *D_80701968[3];
extern CallbackOwner *D_80701984[4];
extern CallbackOwner *D_80701984_ALT[4] __asm__("D_80701984");

#define STATE_ROOT D_80701968[0]

extern s32 func_80700D84(void);
extern void func_80700EEC() __attribute__((noreturn));
extern void func_80700F34() __attribute__((noreturn));
extern void func_80700F38(void) __attribute__((noreturn));
extern void func_80701060(s32 *word, s32 old_value);
extern s32 func_807018AC(s16 value);

s32 func_80874E18(s32 arg0) {
    s32 callback;
#ifndef NON_MATCHING
    s32 tail_arg;
#else
    s32 tail_arg;
#endif

    if (func_80700D84() > 0) {
        s16 value;
        s32 input_offset;
        s32 index;
        s32 *word;
        s32 old_value;
#ifndef NON_MATCHING
        register s32 zero_nf ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
#else
        s32 zero_nf = 0;
#endif

        input_offset = arg0 * 2;
        value = *(s16 *)((u8 *)&D_80700000 + 0xBBC + input_offset);
        index = value / 32;
        word = (s32 *)(index * 4 + (s32)STATE_ROOT);
        old_value = *word;
        *word = ((zero_nf | 1) << (value - (index << 5))) | old_value;
        func_80701060(word, old_value);
        func_80700F38();
    }

callback_path:
    callback = D_80701984[0]->callback(({                                                                       register s32 zero ASM_REG("$0");                                                                                         zero | (2);                                                      }));
    tail_arg = 0x40000000;
    if (callback != 0) {
        {
#ifndef NON_MATCHING
            void *state;
            register s32 new_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
#else
            void *state;
            s32 new_flags;
#endif
            state = (void *)STATE_ROOT;
            new_flags = FIELD(state, s32 *, 0x30) | tail_arg;
            do {
                FIELD(state, s32 *, 0x30) = new_flags;
            } while (0);
        }
        func_80700EEC(tail_arg);
    }

    {
#ifndef NON_MATCHING
        void *state;
        s32 clear_mask;
        s32 clear_value;
#else
        void *state;
        s32 clear_mask;
        s32 clear_value;
#endif
        state = (void *)STATE_ROOT;
        clear_mask = 0xBFFFFFFF;
        clear_value = FIELD(state, s32 *, 0x30);
        clear_value &= clear_mask;
        FIELD(state, s32 *, 0x30) = clear_value;
    }
    if (func_807018AC(D_80700BB2[0]) != 0) {
        goto zero_return;
    }

    callback = D_80701984_ALT[0]->callback(({                                                                       register s32 zero ASM_REG("$0");                                   ASM_KEEP(zero);                                                      zero | (2);                                                      }));
    if (callback == 0) {
        goto return_arg;
    }
    arg0 += 1;
    ASM_TAILSLOT_PIN_TIED(arg0);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    func_80700F34();

return_arg:
    return arg0;

zero_return:
    arg0 = 0;
    ASM_KEEP(arg0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    return arg0;
}
