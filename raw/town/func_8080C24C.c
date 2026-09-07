#include "common.h"

typedef struct {
    s32 x;
    s32 y;
} __attribute__((packed)) PackedPair;

typedef struct {
    s32 value;
} __attribute__((packed)) PackedWord;

typedef struct {
    u8 pad_00[0x10];
    void *owner;
    u8 pad_14[0x10];
    s32 value;
    PackedPair pairs[2];
    PackedWord words[2];
} Object;

extern u8 D_801328C8[];
extern u8 D_805286B8[];
extern Object *func_800374FC(s32, void *);
extern void func_8003BC18(void *, void *);

void func_8080C24C(void *owner, PackedPair *pairs, PackedWord *words, s32 value)
{
    Object *object;
    s32 i;
    PackedWord *src_word;
    u8 *dst_word;
    PackedPair *src_pair;
    u8 *dst_pair;

    object = func_800374FC(1, D_801328C8);
    i = 1;
    if (object != 0) {
        object->value = value;
        src_word = words + 1;
        dst_word = (u8 *)object + 0x24;
        src_pair = pairs + 1;
        dst_pair = (u8 *)object + 0x28;
        do {
            *(PackedPair *)(dst_pair + 8) = *src_pair;
            *(PackedWord *)(dst_word + 0x18) = *src_word;
            src_word--;
            dst_word -= 4;
            src_pair--;
            dst_pair -= 8;
            i--;
        } while (i >= 0);
        object->owner = owner;
        func_8003BC18(object, D_805286B8);
    }
}
