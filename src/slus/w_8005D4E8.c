#include "common.h"

/* S_80079970: SPU-driver status/save-slot record. Offset 0 is read as a u16
 * "current shift/mode" value (this function, sibling func_8005D460); offset 4
 * is a s32 busy-flag save slot written by sibling func_8005E7E0
 * (D_80079970[1]). Padded past 8 bytes so hi/lo (not gp_rel) addressing is
 * used, matching the existing D_80079970[4] convention. */
typedef struct {
    u16 field0;
    u16 pad2;
    s32 field4;
    s32 pad8[2];
} S_80079970;
extern S_80079970 D_80079970;

/* S_80079980: pitch/shift-amount table shared with func_8005D9DC/
 * func_8005D1D0/func_8005D63C/func_8005D550/func_8005D460. Only field0 is
 * read here; padded past 8 bytes so hi/lo (not gp_rel) addressing is used. */
typedef struct {
    s32 field0;
    s32 pad4;
    s32 pad8;
} S_80079980;
extern S_80079980 D_80079980;

extern s32 func_8005D1D0();

/* Uploads a buffer to the current SPU transfer address and returns its size. */
s32 func_8005D4E8(s32 buffer_addr, s32 size)
{
    s32 upload_addr = buffer_addr;
    s32 upload_size = size;

    func_8005D1D0(2, (s32)D_80079970.field0 << D_80079980.field0);
    func_8005D1D0(0);
    func_8005D1D0(3, upload_addr, upload_size);

    return upload_size;
}
