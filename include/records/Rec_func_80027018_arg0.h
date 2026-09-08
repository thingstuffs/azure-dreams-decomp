/* Rec_func_80027018_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:main:func_80027018:arg0; 2 functions (main 2); span 0x100.
 * Reached as a parameter in: func_80027018:arg0 (1), func_800270E0:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_80027018_ARG0_H
#define REC_FUNC_80027018_ARG0_H

#include "common.h"
#include "m2c_compat.h"   /* M2C_UNK* views: rows that never needed the compat header still compile */

typedef struct Rec_func_80027018_arg0 {
    u8 pad_00[0xF0];
    union { M2C_UNK ** as_ppm; void * as_pv; } unk_F0;   /* read as M2C_UNK ** by 1, void * by 1 */
    union { M2C_UNK ** as_ppm; void * as_pv; } unk_F4;   /* read as M2C_UNK ** by 1, void * by 1 */
    union { void ** as_ppv; void * as_pv; } unk_F8;   /* read as void ** by 1, void * by 1 */
    union { void ** as_ppv; void * as_pv; } unk_FC;   /* read as void ** by 1, void * by 1 */
} Rec_func_80027018_arg0;

#endif
