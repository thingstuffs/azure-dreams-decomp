#!/usr/bin/env python3
"""Cooperative CPU split: lanes leave the same high-numbered CPUs for landings.

Run this from the same parent affinity on every cooperating lane. It affects
only the child, never other processes. Without a command it prints the split.
"""
import argparse
import json
import os


def core_sets(available, reserve=8):
    cpus = sorted(set(available))
    if not cpus or reserve < 1:
        raise ValueError('nonempty affinity and positive reserve required')
    count = min(reserve, len(cpus) - 1)
    return cpus[:-count] if count else cpus, cpus[-count:] if count else cpus


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--reserve', type=int, default=8)
    ap.add_argument('--role', choices=('lane', 'landing'), default='lane')
    ap.add_argument('command', nargs=argparse.REMAINDER)
    args = ap.parse_args()
    try:
        lane, landing = core_sets(os.sched_getaffinity(0), args.reserve)
    except ValueError as exc:
        ap.error(str(exc))
    command = args.command
    if command[:1] == ['--']:
        command = command[1:]
    if not command:
        print(json.dumps(dict(lane=lane, landing=landing)))
        return
    os.sched_setaffinity(0, lane if args.role == 'lane' else landing)
    os.execvp(command[0], command)


if __name__ == '__main__':
    main()
