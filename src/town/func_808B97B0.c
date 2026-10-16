#include "common.h"

/* Devkit debug code (sn_main.c line 48 trace) in the KSEG1-linked (0xA0700000) devkit image at file 0x8395EC; the same routine as
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

extern OvWork D_A0700B38;            /* ov_work */
extern DevCallbacks *D_A0700B50;
extern char D_A0700140[];            /* "%s = %d\n" */
extern char D_A070014C[];            /* "p->kind" */
extern char D_A0700154[];            /* "ov_work.kind" */
extern char D_A0700164[];            /* "mark: %s line %d\n" */
extern char D_A0700178[];            /* "sn_main.c" */

/* Copy the overlay work record, trace both kind fields, mark sn_main.c line 48 and flush. */
void func_A07007B0(OvWork *p) {
    D_A0700B38 = *p;
    D_A0700B50->print(D_A0700140, D_A070014C, p->kind);
    D_A0700B50->print(D_A0700140, D_A0700154, D_A0700B38.kind);
    D_A0700B50->print(D_A0700164, D_A0700178, 48);
    D_A0700B50->flush(0);
}
