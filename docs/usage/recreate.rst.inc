.. IMPORTANT: this file is auto-generated from borg's built-in help, do not edit!

.. _borg_recreate:

borg recreate
-------------
::

    borg recreate <options> REPOSITORY_OR_ARCHIVE PATH

positional arguments
    REPOSITORY_OR_ARCHIVE
        repository/archive to recreate
    PATH
        paths to recreate; patterns are supported

optional arguments
    ``--list``
        | output verbose list of items (files, dirs, ...)
    ``--filter STATUSCHARS``
        | only display items with the given status characters
    ``-p``, ``--progress``
        | show progress display while recreating archives
    ``-n``, ``--dry-run``
        | do not change anything
    ``-s``, ``--stats``
        | print statistics at end

`Common options`_
    |

Exclusion options
    ``-e PATTERN``, ``--exclude PATTERN``
        | exclude paths matching PATTERN
    ``--exclude-from EXCLUDEFILE``
        | read exclude patterns from EXCLUDEFILE, one per line
    ``--exclude-caches``
        | exclude directories that contain a CACHEDIR.TAG file (http://www.brynosaurus.com/cachedir/spec.html)
    ``--exclude-if-present FILENAME``
        | exclude directories that contain the specified file
    ``--keep-tag-files``
        | keep tag files of excluded caches/directories

Archive options
    ``--target TARGET``
        | create a new archive with the name ARCHIVE, do not replace existing archive (only applies for a single archive)
    ``-c SECONDS``, ``--checkpoint-interval SECONDS``
        | write checkpoint every SECONDS seconds (Default: 1800)
    ``--comment COMMENT``
        | add a comment text to the archive
    ``--timestamp yyyy-mm-ddThh:mm:ss``
        | manually specify the archive creation date/time (UTC). alternatively, give a reference file/directory.
    ``-C COMPRESSION``, ``--compression COMPRESSION``
        | select compression algorithm, see the output of the "borg help compression" command for details.
    ``--always-recompress``
        | always recompress chunks, don't skip chunks already compressed with the same algorithm.
    ``--compression-from COMPRESSIONCONFIG``
        | read compression patterns from COMPRESSIONCONFIG, see the output of the "borg help compression" command for details.
    ``--chunker-params CHUNK_MIN_EXP,CHUNK_MAX_EXP,HASH_MASK_BITS,HASH_WINDOW_SIZE``
        | specify the chunker parameters (or "default").

Description
~~~~~~~~~~~

Recreate the contents of existing archives.

This is an *experimental* feature. Do *not* use this on your only backup.

--exclude, --exclude-from and PATH have the exact same semantics
as in "borg create". If PATHs are specified the resulting archive
will only contain files from these PATHs.

Note that all paths in an archive are relative, therefore absolute patterns/paths
will *not* match (--exclude, --exclude-from, --compression-from, PATHs).

--compression: all chunks seen will be stored using the given method.
Due to how Borg stores compressed size information this might display
incorrect information for archives that were not recreated at the same time.
There is no risk of data loss by this.

--chunker-params will re-chunk all files in the archive, this can be
used to have upgraded Borg 0.xx or Attic archives deduplicate with
Borg 1.x archives.

USE WITH CAUTION.
Depending on the PATHs and patterns given, recreate can be used to permanently
delete files from archives.
When in doubt, use "--dry-run --verbose --list" to see how patterns/PATHS are
interpreted.

The archive being recreated is only removed after the operation completes. The
archive that is built during the operation exists at the same time at
"<ARCHIVE>.recreate". The new archive will have a different archive ID.

With --target the original archive is not replaced, instead a new archive is created.

When rechunking space usage can be substantial, expect at least the entire
deduplicated size of the archives using the previous chunker params.
When recompressing expect approx. (throughput / checkpoint-interval) in space usage,
assuming all chunks are recompressed.