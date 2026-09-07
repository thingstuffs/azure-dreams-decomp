#include "common.h"

/* Recycles *((void*)arg0+4) into func_8004FE78, then sets the 0x8000 "used"
 * bit on both the flags field 2 bytes before arg0 and the global flags word
 * D_800814A0. */
extern void func_8004FE78(void *arg0);

extern int D_800814A0;

/* Sub-object struct: a 16-bit flags field lives 0x2 bytes before arg0, and a
 * generic data pointer field lives 0x4 bytes after arg0. */
typedef struct {
    void *field_04;          /* offset 0x0 == arg0 + 0x4 */
} S_8004F558;

void func_8004F558(void *arg0)
{
    S_8004F558 *ext = (S_8004F558 *)((unsigned char *)arg0 + 0x4);
    unsigned short *flags = (unsigned short *)((unsigned char *)arg0 - 0x2);

    func_8004FE78(ext->field_04);
    *flags |= 0x8000;
    D_800814A0 |= 0x8000;
}
