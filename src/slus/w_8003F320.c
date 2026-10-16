#include "common.h"

extern int getCdCommandQueueDepth(void);
extern void func_8003CB08(void);
extern void func_80044618(int);
extern void func_8003E758(void);

/* Repeat the update sequence while getCdCommandQueueDepth reports pending work. */
void drainCdCommandQueue(void)
{
    while (getCdCommandQueueDepth()) {
        func_8003CB08();
        func_80044618(2);
        func_8003E758();
    }
}
