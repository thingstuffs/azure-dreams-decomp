#include "common.h"
#include "engine/audio/sequence.h"
#include "engine/util.h"
#include "sdk/libc.h"

#include "engine/resource.h"
extern s32 count_tagged_records(void *a0);

/* Allocates a 0x100-byte note buffer, decodes text, and frees the buffer if decoding produces no entries. */
void *alloc_object_100(char *text, s32 initial_octave)
{
    void *entries;

    entries = create_callback_pair_default(0x100);
    if (entries != 0) {
        if (decode_fullwidth_text(entries, text, initial_octave) != 0) {
            if (count_tagged_records(entries) < 0x16) {
                return entries;
            }
            puts(text);
            return entries;
        }
        flag_object_for_removal(entries);
        entries = 0;
    }

    return entries;
}
