#!/usr/bin/env python3
"""Public CLI/import facade for the gate-compatible source layout resolver."""
from gate.source_layout import *  # noqa: F401,F403

def physical_owner(row_or_id, root=ROOT):
    """Bootstrap the canonical gate imports for callers using only tools/."""
    from gate import overlay_module_gate  # installs the flat exported-gate import path
    from gate.source_layout import physical_owner as resolve
    rid = row_or_id if isinstance(row_or_id, str) else row_or_id['id']
    home = registry(root).get(rid, {}).get('source_row')
    if home:
        row_relative(rid, root)  # validate the same own-file home rule as source resolution
    return resolve(home or row_or_id, root)


if __name__ == "__main__":
    main()
