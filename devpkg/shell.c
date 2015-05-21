#include "shell.h"
#include "dbg.h"
#include <stdarg.h>

int Shell_exec(Shell template, ...)
{
  apr_pool_t *p = NULL;
  int rc = -1;
  apr_status_t rv = APR_SUCCESS;
  va_list argp;
  const char *key = NULL;
  const char *arg = NULL;
  int i = 0;
  int replaced_args_count = 0;

  rv = apr_pool_create(&p, NULL);
  check(rv == APR_SUCCESS, "Failed to create memory pool.");

  va_start(argp, template);

  for(key = va_arg(argp, const char *);
      key != NULL;
      key = va_arg(argp, const char *))
  {
    arg = va_arg(argp, const char *);
    //check(arg, "Can't supply odd number of key/value pairs");

    for(i = 0; template.args[i] != NULL; i++) {
      if(strcmp(template.args[i], key) == 0) {
        template.args[i] = arg;
        replaced_args_count++;
        break; // found it
      }
    }
  }

  check(replaced_args_count == template.arg_count, 
      "Not all arguments were provided, expected %d, replaced %d.",
      template.arg_count,
      replaced_args_count);

  rc = Shell_run(p, &template);
  apr_pool_destroy(p);
  va_end(argp);
  return rc;

error:
  if(p) apr_pool_destroy(p);
  return rc;
}

int Shell_run(apr_pool_t *p, Shell *cmd)
{
  apr_procattr_t *attr;
  apr_status_t rv;
  apr_proc_t newproc;

  rv = apr_procattr_create(&attr, p);
  check(rv == APR_SUCCESS, "Failed to create proc attr.");

  rv = apr_procattr_io_set(attr, APR_NO_PIPE, APR_NO_PIPE, APR_NO_PIPE);
  check(rv == APR_SUCCESS, "Failed to set I/O of command.");

  rv = apr_procattr_dir_set(attr, cmd->dir);
  check(rv == APR_SUCCESS, "Failed to set command directory to %s.", cmd->dir);

  rv = apr_procattr_cmdtype_set(attr, APR_PROGRAM_PATH);
  check(rv == APR_SUCCESS, "Failed to set cmd type.");

  rv = apr_proc_create(&newproc, cmd->exe, cmd->args, NULL, attr, p);
  check(rv == APR_SUCCESS, "Failed to run command.");

  rv = apr_proc_wait(&newproc, &cmd->exit_code, &cmd->exit_why, APR_WAIT);
  check(rv == APR_CHILD_DONE, "Failed to wait for command to finish.");

  check(cmd->exit_code == 0, "%s exited badly with status %d", cmd->exe, cmd->exit_code);
  check(cmd->exit_why == APR_PROC_EXIT, "%s was killed or crashed.", cmd->exe);

  return 0;

error:
  return -1;
}

Shell CLEANUP_SH = {
  .exe = "rm",
  .dir = "/tmp",
  .args = { "rm", "-rf", "/tmp/pkg-build", "/tmp/pkg-src.tar.gz", 
    "/tmp/pkg-src.tar.bz2", "/tmp/DEPENDS", NULL },
  .arg_count = 0
};

Shell GIT_SH = {
  .exe = "git",
  .dir = "/tmp",
  .args = { "git", "clone", "URL", "pkg-build", NULL },
  .arg_count = 1
};

Shell TAR_SH = {
  .exe = "tar",
  .dir = "/tmp",
  .args = { "tar", "-xzf", "FILE", "--strip-components", "1", NULL },
  .arg_count = 1
};

Shell CURL_SH = {
  .exe = "curl",
  .dir = "/tmp",
  .args = { "curl", "-L", "-o", "TARGET", "URL", NULL },
  .arg_count = 2
};

Shell CONFIGURE_SH = {
  .exe = "./configure",
  .dir = "/tmp/pkg-build",
  .args = { "configure", "OPTS", NULL },
  .arg_count = 1
};

Shell MAKE_SH = {
  .exe = "make",
  .dir = "/tmp/pkg-build",
  .args = { "make", "OPTS", NULL },
  .arg_count = 1
};

Shell INSTALL_SH = {
  .exe = "sudo",
  .dir = "/tmp/pkg-build",
  .args = { "sudo", "make", "TARGET", NULL },
  .arg_count = 1
};

