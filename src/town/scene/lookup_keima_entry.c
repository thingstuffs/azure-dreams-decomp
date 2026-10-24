#include "town/scene/entry_requests.h"

extern void *func_80016D10(void *, void *, s32, s32);
extern s32 func_80016C58(void *, s32, s32);
extern u8 D_80017904[];
extern u8 D_80017A94[];
extern u8 D_80018640[];
extern u8 D_80018C7E[];

/* Codes 50 and 21 select special records when the local entry check succeeds. */
void *lookup_keima_entry(s32 key, s32 unused, s32 code)
{
    s32 entry_code;
    void *result;

    entry_code = code;
    {
        void *lookup_data = D_80017904;
        result = func_80016D10(lookup_data, D_80017A94, key, entry_code);
        if (entry_code == 50) {
            if (func_80016C58(lookup_data, key, 50) != 0) {
                return D_80018640;
            }
        }
    }
    if (entry_code == 21) {
        if (func_80016C58(D_80017904, key, 21) != 0) {
            return D_80018C7E;
        }
    }
    return result;
}
