#include "common.h"

/* If arg0 already matches the current registered state (D_80080AF3), return 1
 * without doing anything. Otherwise, register callbacks for the new state's
 * table entry (D_8006E6F4[arg0]), copy D_8008148C into D_80081480, update
 * D_80080AF3 to arg0, run the pending-transition handlers, then spin on
 * func_8005405C(0) until it signals completion, and return 0. */
/* gp-relative scalar: current registered state index */
extern s8 D_80080AF3;

/* S_8006E6F4: array of 8-byte entries, indexed by state; forces %hi/%lo
 * addressing (accessed with a computed base + reused offsets). */
typedef struct {
    s32 field0; /* offset 0x0 */
    s32 field4; /* offset 0x4 */
} S_8006E6F4;
extern S_8006E6F4 D_8006E6F4[];

/* Same struct layout as established in src/w_8004425C.c / src/w_80043CD0.c /
 * src/w_80041AB0.c: only field_0 is accessed; padded past 8 bytes to force
 * %hi/%lo addressing instead of %gp_rel. */
struct S_80081480 { s32 field_0; s8 pad[8]; };
struct S_8008148C { s32 field_0; s8 pad[8]; };
extern struct S_80081480 D_80081480;
extern struct S_8008148C D_8008148C;
extern struct S_8008148C D_8008148C_alias2 asm("D_8008148C");

extern int func_8003E4FC(int a0, void *a1, int a2);
extern void DrawSync(s32 a0);
extern void func_8003F320(void);
extern void func_8003F5E0(int a0);
extern short func_80053DA8(int a0);
extern void func_800542BC(void);
extern s16 func_8005405C(s16 n);

s32 func_8004450C(s16 arg0)
{
    if (D_80080AF3 != arg0) {
        S_8006E6F4 *base = D_8006E6F4;
        S_8006E6F4 *entry = base + arg0;

        func_8003E4FC(6, (void *)entry->field4, 0);
        DrawSync(0);
        {
            void *tmp1 = entry->field0;
            D_80081480.field_0 = D_8008148C.field_0;
            func_8003E4FC(6, tmp1, 0);
        }
        D_80080AF3 = (s8)arg0;
        func_8003F320();
        func_8003F5E0(D_8008148C_alias2.field_0);
        func_80053DA8(0x11);
        func_800542BC();
        while (func_8005405C(0) != 1) {
        }
        return 0;
    }
    return 1;
}
