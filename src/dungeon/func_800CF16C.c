#include "common.h"

typedef struct {
    u8 pad12[0x12];
    s16 value12;
    u16 value14;
} Func800CF16CArg;

extern s32 fade_actor_to_removal(void *first_ptr, void *second_ptr, Func800CF16CArg *record, s32 value);
extern void decrement_event_counter(void);

void initialize_actor_action_data(void *first_ptr, void *second_ptr, Func800CF16CArg *record, s32 value) {
    if (fade_actor_to_removal(first_ptr, second_ptr, record, value) != 0) {
        decrement_event_counter();
        return;
    }

    record->value12 = 0x7E40;
    record->value14 |= 0x100;
}
