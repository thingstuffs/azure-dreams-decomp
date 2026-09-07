#include "common.h"

#ifdef NON_MATCHING
#define OR_ZERO(value) (value)
#else
#define OR_ZERO(value)                                                      \
    ({                                                                      \
        register s32 zero ASM_REG("$0");                                  \
        ASM_KEEP(zero);                                                     \
        zero | (value);                                                     \
    })
#endif

#define FIELD(base, type, offset) (*(type)((u8 *)(base) + (offset)))

typedef struct {
    u8 pad[0xBBC];
    s16 values[1];
} InputTable;

typedef struct {
    s32 words[12];
    s32 flags;
} State;

typedef struct {
    u8 pad[0x54];
    s32 (*callback)(s32);
} CallbackOwner;

extern InputTable D_80700000;
extern State *D_80701968[3];
extern CallbackOwner *D_80701984[4];

extern s32 func_80700D84(void);
extern void func_80701024() __attribute__((noreturn));
extern void func_80701028(void) __attribute__((noreturn));
extern s32 func_80701060(s32 *word, s32 old_value);

s32 func_80874F4C(s32 arg0) {
#ifndef NON_MATCHING
    register s32 value ASM_REG("$5");
    register s32 index ASM_REG("$3");
    register s32 old_value ASM_REG("$5");
    register s32 zero ASM_REG("$0");
#else
    s16 value;
    s32 index;
    s32 old_value;
    s32 zero = 0;
#endif
    s32 shift;
    s32 offset;
    s32 *word;
    s32 callback;
#ifndef NON_MATCHING
    register s32 tail_arg ASM_REG("$4");
#else
    s32 tail_arg;
#endif

    if (func_80700D84() < 2) {
        goto callback_path;
    }

    value = D_80700000.values[arg0];
    index = value;
    if (value < 0) {
        index = value + 31;
    }
    index >>= 5;
    offset = index * 4;
    word = (s32 *)(offset + (s32)D_80701968[0]);
    shift = value - (index << 5);
    old_value = *word;
    *word = ((zero | 1) << shift) | old_value;
    func_80701060(word, old_value);
    func_80701028();

callback_path:
    callback = D_80701984[0]->callback(OR_ZERO(2));
    tail_arg = 0x40000000;
    if (callback == 0) {
        goto clear_flags;
    }

    {
#ifndef NON_MATCHING
        register void *state ASM_REG("$2");
        register s32 new_flags ASM_REG("$3");
#else
        void *state;
        s32 new_flags;
#endif
        state = (void *)D_80701968[0];
        new_flags = FIELD(state, s32 *, 0x30) | tail_arg;
        ASM_TAILSLOT_PIN_TIED(tail_arg);
        FIELD(state, s32 *, 0x30) = new_flags;
    }
    func_80701024(tail_arg);

clear_flags:
    {
#ifndef NON_MATCHING
        register void *state ASM_REG("$4");
        register s32 clear_mask ASM_REG("$3");
        register s32 clear_value ASM_REG("$2");
#else
        void *state;
        s32 clear_mask;
        s32 clear_value;
#endif
        state = (void *)D_80701968[0];
        clear_mask = 0xBFFFFFFF;
        clear_value = FIELD(state, s32 *, 0x30);
        clear_value &= clear_mask;
        FIELD(state, s32 *, 0x30) = clear_value;
    }
    return arg0;
}
