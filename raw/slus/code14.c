/* gcc 2.8.1 -O2 — own TU (func_8004D0E4: callback fwd-decl conflict) */
/* Registers/copies a 3-short position (x,y,z) from a nested pointer into the
 * global state table D_80083160 at offsets 0xBC/0xBE/0xC0. Sibling of
 * func_8004D09C (same D_80083160 fields, different source struct/offsets):
 * a0 is a pointer to a struct whose offset 0 holds a pointer to a small
 * struct of three shorts at offsets 0x0/0x2/0x4. */

struct Vec3s {
    short x;
    short y;
    short z;
};

struct S_Src {
    struct Vec3s *ptr; /* offset 0x0 */
};

/* declared >8 bytes to force %hi/%lo addressing (not $gp-relative) */
extern struct {
    char pad[0xBC];
    short field_BC;
    short field_BE;
    short field_C0;
} D_80083160;

void func_8004D0E4(struct S_Src *a0)
{
    struct Vec3s *p = a0->ptr;

    D_80083160.field_BC = p->x;
    D_80083160.field_BE = p->y;
    D_80083160.field_C0 = p->z;
}
