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

/* Creates an object with the supplied value, pair and word data, and owner. */
void func_8080C24C(void *owner, PackedPair *pairs, PackedWord *words, s32 value)
{
    Object *object;
    s32 copy_index;
    PackedWord *src_word;
    u8 *word_dst_base;
    PackedPair *src_pair;
    u8 *pair_dst_base;

    object = func_800374FC(1, D_801328C8);
    copy_index = 1;
    if (object != 0) {
        object->value = value;
        src_word = words + 1;
        word_dst_base = (u8 *)object + 0x24;
        src_pair = pairs + 1;
        pair_dst_base = (u8 *)object + 0x28;
        do {
            *(PackedPair *)(pair_dst_base + 8) = *src_pair;
            *(PackedWord *)(word_dst_base + 0x18) = *src_word;
            src_word--;
            word_dst_base -= 4;
            src_pair--;
            pair_dst_base -= 8;
            copy_index--;
        } while (copy_index >= 0);
        object->owner = owner;
        func_8003BC18(object, D_805286B8);
    }
}
