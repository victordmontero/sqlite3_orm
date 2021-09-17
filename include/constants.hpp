#ifndef CONSTANTS_HPP_
#define CONSTANTS_HPP_

#define SQLITE3_ORM_OK			 0	 /* Success */
#define SQLITE3_ORM_ERROR        1   /* Generic error */
#define SQLITE3_ORM_INTERNAL     2   /* Internal logic error in SQLite */
#define SQLITE3_ORM_PERM         3   /* Access permission denied */
#define SQLITE3_ORM_ABORT        4   /* Callback routine requested an abort */
#define SQLITE3_ORM_BUSY         5   /* The database file is locked */
#define SQLITE3_ORM_LOCKED       6   /* A table in the database is locked */
#define SQLITE3_ORM_NOMEM        7   /* A malloc() failed */
#define SQLITE3_ORM_READONLY     8   /* Attempt to write a readonly database */
#define SQLITE3_ORM_INTERRUPT    9   /* Operation terminated by sqlite3_interrupt()*/
#define SQLITE3_ORM_IOERR       10   /* Some kind of disk I/O error occurred */
#define SQLITE3_ORM_CORRUPT     11   /* The database disk image is malformed */
#define SQLITE3_ORM_NOTFOUND    12   /* Unknown opcode in sqlite3_file_control() */
#define SQLITE3_ORM_FULL        13   /* Insertion failed because database is full */
#define SQLITE3_ORM_CANTOPEN    14   /* Unable to open the database file */
#define SQLITE3_ORM_PROTOCOL    15   /* Database lock protocol error */
#define SQLITE3_ORM_EMPTY       16   /* Internal use only */
#define SQLITE3_ORM_SCHEMA      17   /* The database schema changed */
#define SQLITE3_ORM_TOOBIG      18   /* String or BLOB exceeds size limit */
#define SQLITE3_ORM_CONSTRAINT  19   /* Abort due to constraint violation */
#define SQLITE3_ORM_MISMATCH    20   /* Data type mismatch */
#define SQLITE3_ORM_MISUSE      21   /* Library used incorrectly */
#define SQLITE3_ORM_NOLFS       22   /* Uses OS features not supported on host */
#define SQLITE3_ORM_AUTH        23   /* Authorization denied */
#define SQLITE3_ORM_FORMAT      24   /* Not used */
#define SQLITE3_ORM_RANGE       25   /* 2nd parameter to sqlite3_bind out of range */
#define SQLITE3_ORM_NOTADB      26   /* File opened that is not a database file */
#define SQLITE3_ORM_NOTICE      27   /* Notifications from sqlite3_log() */
#define SQLITE3_ORM_WARNING     28   /* Warnings from sqlite3_log() */
#define SQLITE3_ORM_ROW         100  /* sqlite3_step() has another row ready */
#define SQLITE3_ORM_DONE        101  /* sqlite3_step() has finished executing */

#endif