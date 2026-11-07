# Unjoined access-row classification

Each source access row receives one reason after exact-section and bijective
source/opcode matching. The priority is: no exact section; competing source or
retail instruction; missing debug line; unknown source offset or width; a
stack-local access still unjoined; macro expansion; unknown base; unproven
register on an otherwise matching line; displaced debug line or rebase; and
no matching retail access. The counts are mutually exclusive and include
stores as well as loads.

In the 12-TU effect probe, 3,690 of 10,252 rows remain unjoined after the
fixed-frame stack proof. The next work is ranked by currently held rows, which
are upper bounds on what another extension could unlock:

| Reason | Held rows |
| --- | ---: |
| Debug line or rebase | 1,407 |
| Base register not proven | 844 |
| No matching retail access | 689 |
| Base not proven | 315 |
| Unknown source offset or width | 143 |
| No unique source access | 100 |
| Stack local | 82 |
| No unique retail opcode | 64 |
| Macro expansion | 44 |
| No exact section | 2 |

The measurement run recorded base-kind and folder coverage after each
proof stage, including the town HUD probe. The full manifest's final reasons
are tabulated above.
