#include "common.h"

/* Devkit debug code (sn_main.c line 47 trace) in the link-at-0 scene-test image A; the same routine as
 * func_80701194 (src/town/func_80880194.c, line 48) in the 0x80700000-linked image. */

typedef struct OvWork {
    s32 unk_00;
    s32 unk_04;
    s32 kind;
    u8 pad_0C[0x28];
} OvWork;

typedef struct DevCallbacks {
    u8 pad_00[0x64];
    void (*print)(char *format, char *name, s32 value);
    u8 pad_68[0x4];
    void (*flush)(s32 mode);
} DevCallbacks;

extern OvWork D_000045F8;            /* ov_work */
extern DevCallbacks *D_00004610;
extern char D_000034D0[];            /* "%s = %d\n" */
extern char D_000034DC[];            /* "p->kind" */
extern char D_000034E4[];            /* "ov_work.kind" */
extern char D_000034F4[];            /* "mark: %s line %d\n" */
extern char D_00003508[];            /* "sn_main.c" */

/* Copy the overlay work record, trace both kind fields, mark sn_main.c line 47 and flush. */
void func_80003CD0(OvWork *p) {
    D_000045F8 = *p;
    D_00004610->print(D_000034D0, D_000034DC, p->kind);
    D_00004610->print(D_000034D0, D_000034E4, D_000045F8.kind);
    D_00004610->print(D_000034F4, D_00003508, 47);
    D_00004610->flush(0);
}
