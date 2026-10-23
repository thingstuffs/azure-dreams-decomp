#!/usr/bin/env python3
"""Machine-wide compiler slots. Waiting consumes no make jobserver tokens beyond this recipe."""
import argparse
from contextlib import contextmanager
import fcntl
import json
import os
from pathlib import Path
import tempfile
import subprocess
import time


def slot_count():
    available = len(os.sched_getaffinity(0)) if hasattr(os, 'sched_getaffinity') else os.cpu_count() or 1
    count = int(os.environ.get('AZURE_COMPILE_LIMIT', max(1, available // 2)))
    if count < 1:
        raise ValueError('AZURE_COMPILE_LIMIT must be positive')
    return count


def slot_directory():
    return Path(os.environ.get('AZURE_COMPILE_SLOTS',
                str(Path('/tmp') / ('azure-compile-' + str(os.getuid())))))


def event(kind, slot, waited=0):
    path = os.environ.get('AZURE_COMPILE_LOG')
    if path:
        data = json.dumps(dict(event=kind, pid=os.getpid(), slot=slot,
                               time=time.time(), waited=waited)) + '\n'
        fd = os.open(path, os.O_WRONLY | os.O_CREAT | os.O_APPEND, 0o600)
        try:
            os.write(fd, data.encode())
        finally:
            os.close(fd)


@contextmanager
def acquire():
    if os.environ.get('AZURE_COMPILE_LIMIT_ENABLED', '0') == '0':
        yield None
        return
    # An exec wrapper carries the actual locked FD, not an untrusted boolean.
    inherited = os.environ.get('AZURE_COMPILE_SLOT_FD')
    if inherited:
        valid = False
        try:
            fd = int(inherited)
            expected = slot_directory() / os.environ['AZURE_COMPILE_SLOT_NAME']
            stat = os.fstat(fd)
            target = expected.stat()
            valid = (stat.st_dev, stat.st_ino) == (target.st_dev, target.st_ino)
        except (ValueError, OSError, KeyError):
            pass
        if not valid:
            raise ValueError('invalid inherited compile slot')
        yield fd
        return
    count, directory = slot_count(), slot_directory()
    directory.mkdir(parents=True, exist_ok=True)
    # Conflicting limits must never create a second, larger slot pool. Change
    # the limit only when all users have stopped, by removing this directory.
    with (directory/'config.lock').open('a+') as config_lock:
        fcntl.flock(config_lock, fcntl.LOCK_EX)
        config = directory/'limit'
        if config.exists() and config.read_text().strip() != str(count):
            raise ValueError('compile slot limit differs from active pool: ' + str(directory))
        if not config.exists():
            temporary = directory/'limit.tmp'
            temporary.write_text(str(count) + '\n')
            temporary.replace(config)
    started = time.monotonic()
    fd, name = None, None
    try:
        while fd is None:
            for index in range(count):
                name = 'slot-' + str((index + os.getpid()) % count)
                candidate = os.open(directory/name, os.O_RDWR | os.O_CREAT, 0o600)
                try:
                    fcntl.flock(candidate, fcntl.LOCK_EX | fcntl.LOCK_NB)
                    fd = candidate
                    break
                except BlockingIOError:
                    os.close(candidate)
            if fd is None:
                time.sleep(0.02)
        event('acquire', name, time.monotonic()-started)
        # Descendant wrappers share this slot without trying to take another.
        os.set_inheritable(fd, True)
        os.environ['AZURE_COMPILE_SLOT_FD'] = str(fd)
        os.environ['AZURE_COMPILE_SLOT_NAME'] = name
        yield fd
    finally:
        if fd is not None:
            event('release', name)
            os.environ.pop('AZURE_COMPILE_SLOT_FD', None)
            os.environ.pop('AZURE_COMPILE_SLOT_NAME', None)
            os.close(fd)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', nargs=argparse.REMAINDER)
    args = parser.parse_args()
    command = args.command[1:] if args.command[:1] == ['--'] else args.command
    if not command:
        parser.error('supply a command after --')
    with acquire() as fd:
        raise SystemExit(subprocess.call(command, pass_fds=(fd,) if fd is not None else ()))


if __name__ == '__main__':
    main()
