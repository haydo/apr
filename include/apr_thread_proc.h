/* ====================================================================
 * Copyright (c) 1999 The Apache Group.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the Apache Group
 *    for use in the Apache HTTP server project (http://www.apache.org/)."
 *
 * 4. The names "Apache Server" and "Apache Group" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache"
 *    nor may "Apache" appear in their names without prior written
 *    permission of the Apache Group.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the Apache Group
 *    for use in the Apache HTTP server project (http://www.apache.org/)."
 *
 * THIS SOFTWARE IS PROVIDED BY THE APACHE GROUP ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE APACHE GROUP OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Group.
 * For more information on the Apache Group and the Apache HTTP server
 * project, please see <http://www.apache.org/>.
 *
 */

#ifndef APR_THREAD_PROC_H
#define APR_THREAD_PROC_H

#include "apr_file_io.h"
#include "apr_general.h"
#include "apr_errno.h"
#include "apr_win.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum {APR_SHELLCMD, APR_PROGRAM} ap_cmdtype_e;
typedef enum {APR_WAIT, APR_NOWAIT} ap_wait_how_e;

#define APR_CANCEL_ASYNCH      1
#define APR_CANCEL_DEFER       2
#define APR_CANCEL_ENABLE      3
#define APR_CANCEL_DISABLE     4

typedef struct thread_t           ap_thread_t;
typedef struct threadattr_t       ap_threadattr_t;
typedef struct proc_t		  ap_proc_t;
typedef struct procattr_t         ap_procattr_t;

typedef struct threadkey_t        ap_key_t;

typedef void *(API_THREAD_FUNC *ap_thread_start_t)(void *);

/* Thread Function definitions */
ap_status_t ap_create_threadattr(ap_threadattr_t **, ap_context_t *);
ap_status_t ap_setthreadattr_detach(ap_threadattr_t *, ap_int32_t);
ap_status_t ap_getthreadattr_detach(ap_threadattr_t *);
ap_status_t ap_create_thread(ap_context_t *, ap_threadattr_t *, 
                             ap_thread_start_t, void *, ap_thread_t **);
ap_status_t ap_thread_exit(ap_thread_t *, ap_status_t *);
ap_status_t ap_thread_join(ap_thread_t *thd, ap_status_t *); 
ap_status_t ap_thread_detach(ap_thread_t *);

ap_status_t ap_cancel_thread(ap_thread_t *);
ap_status_t ap_setcanceltype(ap_context_t *, ap_int32_t);
ap_status_t ap_setcancelstate(ap_context_t *, ap_int32_t);
ap_status_t ap_get_threaddata(ap_thread_t *, char *, void *);
ap_status_t ap_set_threaddata(ap_thread_t *, void *, char *,
                              ap_status_t (*cleanup) (void *));

ap_status_t ap_create_thread_private(ap_context_t *, void (*dest)(void *), 
                                     ap_key_t **);
ap_status_t ap_get_thread_private(void **, ap_key_t *);
ap_status_t ap_set_thread_private(ap_key_t *, void *);
ap_status_t ap_delete_thread_private(ap_key_t *);
ap_status_t ap_get_threadkeydata(ap_key_t *, char *, void *);
ap_status_t ap_set_threadkeydata(ap_key_t *, void *, char *,
                                 ap_status_t (*cleanup) (void *));

/* Process Function definitions */
ap_status_t ap_createprocattr_init(ap_procattr_t **, ap_context_t *);
ap_status_t ap_setprocattr_io(ap_procattr_t *, ap_int32_t, ap_int32_t, 
                              ap_int32_t);
ap_status_t ap_setprocattr_dir(ap_procattr_t *, const char *);
ap_status_t ap_setprocattr_cmdtype(ap_procattr_t *, ap_cmdtype_e);
ap_status_t ap_setprocattr_detach(ap_procattr_t *, ap_int32_t);
ap_status_t ap_get_procdata(ap_proc_t *, char *, void *);
ap_status_t ap_set_procdata(ap_proc_t *, void *, char *,
                            ap_status_t (*cleanup) (void *));

ap_status_t ap_get_childin(ap_file_t **, ap_proc_t *);
ap_status_t ap_get_childout(ap_file_t **, ap_proc_t *);
ap_status_t ap_get_childerr(ap_file_t **, ap_proc_t *);

ap_status_t ap_fork(ap_proc_t **, ap_context_t *);
ap_status_t ap_create_process(ap_context_t *, char *, char *const [], char **, 
                              ap_procattr_t *, ap_proc_t **);
ap_status_t ap_wait_proc(ap_proc_t *, ap_wait_how_e);

ap_status_t ap_kill(ap_proc_t *, ap_int32_t);
#ifdef __cplusplus
}
#endif

#endif  /* ! APR_FILE_IO_H */








