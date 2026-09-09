#include "common.h"

#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef void (*Callback)(void);

typedef struct S_func_800362D0_0 {
    u8 pad_00[0x4D];
    u8 unk_4D;
    u8 pad_4E[0x1A];
    Callback unk_68;
    u8 pad_6C[0x08];
    union {
        u32 unk_74_u32;
        void *unk_74_ptr;
    } unk_74;
} S_func_800362D0_0;

typedef struct S_func_800362D0_1 {
    u8 pad_00[0x22];
    u16 unk_22;
    u8 pad_24[0x02];
    u8 unk_26;
    u8 unk_27;
    u8 pad_28[0x58];
    s32 unk_80;
} S_func_800362D0_1;

extern u8 D_80082040[];
extern u8 D_80082538[];

extern void func_80036ED4(void *arg0, void *arg1, s32 *arg2, s16 arg3,
                          s16 arg4, s32 arg5);
extern void func_80036350(void);

/* Initializes the object from its child data and sets the next callback. */
void func_800362D0(S_func_800362D0_0 *object) {
    u32 child_or_index;
    u8 child_byte;
    u8 index_base;
    s16 index_offset;

    child_or_index = object->unk_74.unk_74_u32;
    child_byte = ((S_func_800362D0_1 *)child_or_index)->unk_27;
    index_base = ((S_func_800362D0_1 *)child_or_index)->unk_26;
    child_or_index = ((S_func_800362D0_1 *)child_or_index)->unk_22;
    index_offset = child_or_index - (index_base - 1);
    object->unk_4D = child_byte;

    func_80036ED4(D_80082538, D_80082040, (s32 *)object, 1, index_offset,
                  ((S_func_800362D0_1 *)object->unk_74.unk_74_ptr)->unk_80);
    object->unk_68 = func_80036350;
}
