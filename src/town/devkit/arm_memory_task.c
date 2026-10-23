#include "common.h"
extern void *town_action_resume_address;
void func_80400948(void);
s32 init_card_background_object();
s32 init_card_slot_object();
/* Cache the task's two computed fields and arm the D_804081AC handler. */
void arm_memory_task(void *task)
{
    s32 owner;
    owner = task - 0x20;
    *((s32 *) (((s8 *) task) + 0x20)) = init_card_background_object(owner, task + 0xC);
    *((s32 *) (((s8 *) task) + 0x24)) = init_card_slot_object(owner);
    func_80400948();
    *((void **) (((s8 *) task) + (-0x10))) = &town_action_resume_address;
}
/* MECHANISM: Preserved the seed's 0x20 frame, s0/s1 holds, and call/delay-slot shape.
   Replaced the float-rounded address literal with the declared global's address,
   producing retail's %hi/%lo lui+addiu pair and closing both substitutions. */
