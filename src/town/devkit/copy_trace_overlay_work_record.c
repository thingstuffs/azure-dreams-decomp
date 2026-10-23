#include "common.h"

/* Devkit debug code (sn_main.c, per the "mark" trace below). */

typedef struct OvWork {
    s32 unk_00;
    s32 unk_04;
    s32 kind;
    u8 pad_0C[0x28];
} OvWork;

typedef struct DevCallbacks {
    u8 pad_00[0x68];
    void (*print)(char *format, char *name, s32 value);
} DevCallbacks;

extern OvWork D_8070139C;            /* ov_work */
extern DevCallbacks *devkit_trace_methods;
extern char D_80700B50[];            /* "%s = %d\n" */
extern char D_80700B5C[];            /* "p->kind" */
extern char D_80700B64[];            /* "ov_work.kind" */
extern char D_80700B74[];            /* "mark: %s line %d\n" */
extern char D_80700B88[];            /* "sn_main.c" */

/* Copy the overlay work record, trace both kind fields and mark sn_main.c line 48. */
void copy_and_trace_overlay_work_record(OvWork *p) {
    D_8070139C = *p;
    devkit_trace_methods->print(D_80700B50, D_80700B5C, p->kind);
    devkit_trace_methods->print(D_80700B50, D_80700B64, D_8070139C.kind);
    devkit_trace_methods->print(D_80700B74, D_80700B88, 48);
}
