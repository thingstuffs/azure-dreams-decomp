"""Fresh canonical module checks for accounting, using certificate batch workers.

No verdict or placement is persisted. AZURE_ACCOUNTING_WORKERS=1 selects the
original serial reader for parity measurements or constrained callers.
"""
import os
from pathlib import Path
import sys


def overlay_statuses(root):
    sys.path.insert(0, str(Path(root)/'tools/lanes'))
    from certify_batch import _statuses
    available=len(os.sched_getaffinity(0)) if hasattr(os, 'sched_getaffinity') else (os.cpu_count() or 1)
    workers=int(os.environ.get('AZURE_ACCOUNTING_WORKERS', max(1,min(12,available-available//3))))
    if workers < 1:
        raise ValueError('AZURE_ACCOUNTING_WORKERS must be positive')
    # certify_batch cancels its process group on a worker failure. Standalone
    # accounting CLIs need the same private-group boundary as its own CLI;
    # land_packages already starts every accounting child in a new session.
    if workers > 1 and os.getpgrp() != os.getpid():
        os.setsid()
    return _statuses(Path(root),workers,details=True)


def overlay_placements(root):
    from overlay_module_evidence import all_members
    return {a['id']:{'outcome':'applied','module':e['module']['key'],
                     'module_fingerprint':e['certificate']['fingerprint']['sha256']}
            for e in overlay_statuses(root) if e['valid'] for a in all_members(e['module'])}
