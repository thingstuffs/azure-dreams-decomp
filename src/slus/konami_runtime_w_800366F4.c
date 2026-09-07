#include "common.h"

#include "common.h"

typedef struct Child {
    u8 unk00[0x26];
    u8 unk26;
    u8 unk27;
} Child;

typedef struct Object Object;

struct Object {
    u8 unk00[0x4D];
    u8 unk4D;
    u8 unk4E[0x26];
    Child *child;
};

extern u8 D_80083160[];
extern void func_80036880(Object *arg0, void *arg1, void *arg2);
extern void func_80053DA8(s32 arg0);

void func_800366F4(Object *arg0, void *arg1, void *arg2) {
    s32 next;
    s32 test;
    s32 cursor;
    s32 count;
    u32 flags;
    u8 *state;

    state = D_80083160;
    cursor = arg0->unk4D;
    flags = *(u32 *)(state + 0x10);
    if (flags & 0x2000) {
        goto move_up;
    }
    if (!(flags & 0x8000)) {
        goto after_move_up;
    }
move_up:
    next = cursor + 1;
    if (cursor & 1) {
        cursor -= 1;
    } else if (next < arg0->child->unk26) {
        cursor = next;
    }
    flags = *(u32 *)(state + 0x10);
after_move_up:

    if (flags & 0x4000) {
        next = cursor + 2;
        if (next < arg0->child->unk26) {
            cursor = next;
        } else {
            cursor %= 2;
        }
    } else {
        if (flags & 0x1000) {
            test = cursor - 2;
            if (test >= 0) {
                cursor = test;
            } else {
                count = arg0->child->unk26;
                if (!(count & 1)) {
                    cursor = (cursor % 2) + count - 2;
                } else if (cursor & 1) {
                    cursor = count - 2;
                } else {
                    cursor = count - 1;
                }
            }
        }
    }

    if (arg0->unk4D != cursor) {
        func_80053DA8(0x502);
        arg0->unk4D = cursor;
    }
    if (*(u32 *)(state + 0x10) & 0x40) {
        func_80036880(arg0, arg1, arg2);
    }
}
