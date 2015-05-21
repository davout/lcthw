#include <unistd.h>
#include <apr_errno.h>
#include <apr_file_io.h>

#include "db.h"
#include "bstrlib.h"
#include "dbg.h"

static FILE *DB_open(const char *path, const char *mode)
{
  return fopen(path, mode);
}

static void DB_close(FILE *db)
{
  fclose(db);
}

static bstring DB_load()
{
  FILE *db = NULL;
  bstring data = NULL;

  db = DB_open(DB_FILE, "r");
  check(db, "Failed to open database: %s", DB_FILE);

  data = bread((bNread)fread, db);
  check(data, "Failed to read from DB file: %s", DB_FILE);

  DB_close(db);
  return(data);

error:
  if(db) DB_close(db);
  if(data) bdestroy(data);
  return NULL;
}

int DB_update(const char *url)
{
  if(DB_find(url)) {
    log_info("Already recorded as installed: %s", url);
  }

  FILE *db = DB_open(DB_FILE, "a+");
  check(db, "Failed to open database: %s", DB_FILE);

  bstring line = bfromcstr(url);
  check(line, "Failed to initialize bstring from URL");

  check(bconchar(line, '\n') == BSTR_OK, "Failed to terminate URL with \\n");

  int rc = fwrite(line->data, blength(line), 1, db);
  check(rc == 1, "Failed to append to the DB");

  return 0;

error:
  if(db) DB_close(db);
  return -1;
}

int DB_find(const char *url)
{
  int res = -1;
  bstring data = NULL;
  bstring line = NULL;

  check(url, "URL can't be NULL");

  line = bfromcstr(url);
  check(line, "Failed to initialize bstring from URL");

  data = DB_load();
  check(data, "Failed to load database: %s", DB_FILE);

  if(binstr(data, 0, line) == BSTR_ERR) {
    res = 0;
  } else {
    res = 1;
  }

error: // fall-through
  if(data) bdestroy(data);
  if(line) bdestroy(line);

  return res;
}

int DB_init() {
  apr_pool_t *p = NULL;

  check(apr_pool_initialize() == APR_SUCCESS,
      "Failed to initialize APR resource pool");

  check(apr_pool_create(&p, NULL) == APR_SUCCESS, 
      "Failed to create APR resource pool");

  if(access(DB_DIR, W_OK | X_OK) == -1) {
    apr_status_t rc = apr_dir_make_recursive(DB_DIR,
        APR_UREAD | APR_UWRITE | APR_UEXECUTE |
        APR_GREAD | APR_GWRITE | APR_GEXECUTE, p);

    check(rc == APR_SUCCESS, "Failed to make database dir: %s", DB_DIR);
  }

  if(access(DB_FILE, W_OK) == -1) {
    FILE *db = DB_open(DB_FILE, "w+");
    check(db, "Failed to open database: %s", DB_FILE);
    DB_close(db);
  }

  apr_pool_destroy(p);
  return 0;

error:
  if(p) apr_pool_destroy(p);
  return -1;
}

int DB_list()
{
  bstring data = DB_load();
  check(data, "Failed to read database: %s", DB_FILE);

  printf("%s", bdata(data));
  bdestroy(data);
  return 0;

error:
  return -1;
}

