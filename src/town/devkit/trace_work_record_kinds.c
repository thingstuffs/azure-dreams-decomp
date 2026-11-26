#include "common.h"
#include "town/devkit.h"
#include "town/devkit/page_trace_methods_data.h"

/* Overlay work diagnostics in the uncached devkit image at TOWN +0x8395EC.
 * The trace also appears in the devkit image linked at 0x80700000. */

extern OvWork D_A0700B38;            /* ov_work */
extern char D_A0700140[];            /* Label and integer format. */
extern char D_A070014C[];            /* Label for the source kind. */
extern char D_A0700154[];            /* Label for the copied kind. */
extern char D_A0700164[];            /* Format for a source-location trace. */
extern char D_A0700178[];            /* Source filename for the trace. */

/* Copy the overlay work record, trace both kind fields, log the source location and flush the trace. */
void trace_work_record_kinds(OvWork *p) {
    D_A0700B38 = *p;
    devkit_page_trace_methods->print(D_A0700140, D_A070014C, p->kind);
    devkit_page_trace_methods->print(D_A0700140, D_A0700154, D_A0700B38.kind);
    devkit_page_trace_methods->print(D_A0700164, D_A0700178, 48);
    devkit_page_trace_methods->flush(0);
}
