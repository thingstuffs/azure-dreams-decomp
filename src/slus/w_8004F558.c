#include "common.h"

extern void func_8004FE78(void *arg0);

extern int D_800814A0;

/* Sub-object struct: a 16-bit flags field lives 0x2 bytes before arg0, and a
 * generic data pointer field lives 0x4 bytes after arg0. */
typedef struct {
    void *field_04;          /* offset 0x0 == arg0 + 0x4 */
} S_8004F558;

/* Recycles the object's data and sets bit 0x8000 in its flags and the global flags. */
void func_8004F558(void *object)
{
    S_8004F558 *data_slot = (S_8004F558 *)((unsigned char *)object + 0x4);
    unsigned short *flags = (unsigned short *)((unsigned char *)object - 0x2);

    func_8004FE78(data_slot->field_04);
    *flags |= 0x8000;
    D_800814A0 |= 0x8000;
}
