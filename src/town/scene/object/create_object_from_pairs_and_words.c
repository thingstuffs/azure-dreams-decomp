#include "common.h"
#include "town/scene/collection.h"
#include "town/scene/object.h"

typedef struct {
    u8 data[8];
} PackedPair;

typedef struct {
    u8 data[4];
} PackedWord;

typedef struct {
    u8 pad_00[0x10];
    void *callback;
    u8 pad_14[0x10];
    void *owner;
    PackedPair pairs[2];
    PackedWord words[2];
} Object;

extern u8 D_805286B8[];
extern Object *func_800374FC(s32, void *);
extern void func_8003BC18(void *, void *);

/* Create an object with its callback, pair and word data, and owner. */
void create_object_from_pairs_and_words(void *callback, void *pair_data, void *word_data, void *owner)
{
    Object *object;
    PackedPair *pairs = pair_data;
    PackedWord *words = word_data;
    s32 copy_index;
    PackedWord *src_word;
    u8 *word_dst_base;
    PackedPair *src_pair;
    u8 *pair_dst_base;

    object = func_800374FC(1, &scene_object_factory_data);
    copy_index = 1;
    if (object != 0) {
        object->owner = owner;
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
        object->callback = callback;
        func_8003BC18(object, D_805286B8);
    }
}
