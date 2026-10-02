## Share a variable across blocks (r85_opus_nm1, 2026-10-01)
This is the reverse of rule B (a fresh local for each role). A value that lives in only one basic block is a local quantity: local-alloc colours it before global.c runs. On cdk, local-alloc.c 1598-1612 sorts a block's first three quantities by fixed slot numbers 0/1/2, not by their sorted positions, so the first-born quantity is always allocated first. When prio.py or alloc_need says the pinned value must be placed among the global values, host it in a variable that another block also uses. One function-scope variable for a call result that sibling blocks each declare does this; so does reusing another block's temp. The value then becomes one global allocno, and its refs and live length rank it where retail has it. Hosting a value in another role's variable is a spelling trade (owner ruling): record it, and a later rename is fine. Exact this way: 800B998C, 8197192C, 818B6AFC, 81844F2C.

Final comparison variant (r89, dungeon/80095160, cdk-G0): erasing REG $3 from a shared scratch leaves
the `if ((scratch >> 16) < 513)` temporaries local; they take v0 before global allocation, forcing the
return-result variable into a0. Write the real conversion and boolean back into the shared scratch:
`scratch >>= 16; scratch = scratch < 513; if (scratch) ...`. The local quantity disappears, scratch
stays in v1 and result regains v0: 4 -> 3 pins, exact. This is a local/global conflict repair, not a
priority-only swap. Evidence: docs/evidence/r89_80095160_rubber_duck.md. Avoid interpreting names
after a local union without checking RTL: the current variable-to-pseudo mapper shifts them.
