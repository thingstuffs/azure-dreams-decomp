# Town callback dispatch at 0x6f48d0

Complete singleton cohort (ledger index 63), one stock 2.7.2-cdk-G0 TU.
The proven rowbase maps [0x6f48d0,0x6f4928) to [0x800160d0,0x80016128).
The shared header owns the callback/data pair contract and both function declarations;
the existing shared root record and pointer declarations remain authoritative.
No initialized data or rodata is emitted; the root pointer and fallback handler are imports.
The indirect callback table comes through root->unk_40 and is not allocated here.
Review is pending; any scratch reviewer label is solely a private proof prerequisite.

Reviewer: orchestrator-r120 (2026-10-15): membership (complete ledger group, selector receipt placement), types (member declarations reconciled into the module header) and ownership (imports bound to proven maps; no storage ownership claimed) reviewed.
