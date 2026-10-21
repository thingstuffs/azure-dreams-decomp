#ifndef SHARED_TOWN_ACTION_FLAG_H
#define SHARED_TOWN_ACTION_FLAG_H

/* Every observed access reads byte zero as an unsigned action-state flag.
 * No further storage extent is claimed. */
extern unsigned char town_action_state_flag;

#endif
