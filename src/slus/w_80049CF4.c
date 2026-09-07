#include "common.h"

/* Fills in two consecutive 0xC-byte records starting at a0 from bytes of the
 * source buffer a1 (every-other byte: 0,2,4,6), each tagged with the same
 * constant "type" byte (0x48) but a different constant 4-byte "val". The
 * first record's id byte is left untouched (assumed already set by the
 * caller); the second record's id is explicitly set to 3. Returns a pointer
 * past the second record (a0 + 0x18). */
void *func_80049CF4(void *a0, void *a1)
{
    u8 *src = (u8 *)a1;

    *(u32 *)((u8 *)a0 + 4) = 0x586868;
    *((u8 *)a0 + 1) = 0x48;
    *((u8 *)a0 + 2) = src[0];
    *((u8 *)a0 + 3) = src[2];
    *((u8 *)a0 + 0xA) = src[4];
    *((u8 *)a0 + 0xB) = src[6];

    a0 = (u8 *)a0 + 0xC;

    *(u32 *)((u8 *)a0 + 4) = 0x98B8B8;
    *((u8 *)a0 + 1) = 0x48;
    *((u8 *)a0 + 2) = src[0];
    *((u8 *)a0 + 3) = src[2];
    *((u8 *)a0 + 0xA) = src[4];
    {
        u8 tmp;
        void *ret;

        tmp = src[6];
        *((u8 *)a0 + 0) = 3;
        ret = (u8 *)a0 + 0xC;
        *((u8 *)a0 + 0xB) = tmp;
        return ret;
    }
}
