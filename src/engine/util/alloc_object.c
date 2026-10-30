#include "common.h"
#include "engine/audio/sequence.h"
#include "engine/util.h"
#include "sdk/libc.h"

#include "engine/resource.h"
extern s32 count_tagged_records(void *a0);

/* Allocate a 0x100-byte object holding a label's glyph entries, freeing it if the text yields none. */
void *create_label_glyph_entries(char *text, s32 glyph_style)
{
    void *entries;

    entries = create_callback_pair_default(0x100);
    if (entries != 0) {
        if (decode_fullwidth_text(entries, text, glyph_style) != 0) {
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
