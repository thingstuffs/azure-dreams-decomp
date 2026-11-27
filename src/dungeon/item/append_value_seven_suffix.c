#include "common.h"
#include "dungeon/item.h"

extern u8 indefinite_article_a_text[];

/* Append two table bytes followed by two bytes of value 7. */
void *append_value_seven_suffix(u8 *dst) {
    *dst++ = indefinite_article_a_text[0];
    *dst++ = indefinite_article_a_text[1];
    *dst++ = 7;
    *dst++ = 7;
    return dst;
}
