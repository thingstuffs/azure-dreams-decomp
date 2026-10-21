#ifndef TOWN_MENU_ALTERNATE_PAGE_RECORDS_G00619_H
#define TOWN_MENU_ALTERNATE_PAGE_RECORDS_G00619_H
/* inferred-strong G00619: alternate_page_records_g00619; shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_80035C0C, CL:town/func_800B5978, CL:town/func_800B5B74. */

/* Update alternate menu page bounds. */
#include "common.h"
#include "records/Rec_func_800B2DA0_arg1.h"

typedef struct {
    u8 pad00[0x1C];
    s32 current;
    s32 limit;
} State;

typedef struct {
    u8 pad00[0x98];
    void **primary;
    void **secondary;
} Outputs;

typedef struct {
    State * state;
    u8 pad04[0x10];
    u32 flags;
    u8 pad18[0x90];
    Outputs *outputs;
} Object;

/* extern */
struct Rec_func_800B2DA0_arg1;

extern u8 D_800786DC[];
extern u8 D_800786E8[];
void forward_paged_record_data(s32, void * *);
/* extern */
void update_linked_record_data(Rec_func_800B2DA0_arg1 *);
void prepare_linked_record_data(struct Rec_func_800B2DA0_arg1 *);

/* Functions defined in this translation unit. */
void update_alternate_menu_page_bounds(Object *obj);
void update_and_finalize_record(Rec_func_800B2DA0_arg1 *record);

#endif
