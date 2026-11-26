#include "common.h"
#include "town/devkit.h"
#include "town/data.h"

/* Development diagnostics for the overlay work record. */

extern OvWork D_8070139C;            /* ov_work */
extern char D_80700B50[];            /* Label and integer format. */
extern char D_80700B5C[];            /* Label for the source kind. */
extern char D_80700B64[];            /* Label for the copied kind. */
extern char D_80700B74[];            /* Format for a source-location trace. */
extern char D_80700B88[];            /* Source filename for the trace. */

/* Copy the overlay work record, trace both kind fields and log the original source location. */
void copy_and_trace_overlay_work_record(OvWork *p) {
    D_8070139C = *p;
    devkit_trace_methods->print(D_80700B50, D_80700B5C, p->kind);
    devkit_trace_methods->print(D_80700B50, D_80700B64, D_8070139C.kind);
    devkit_trace_methods->print(D_80700B74, D_80700B88, 48);
}
