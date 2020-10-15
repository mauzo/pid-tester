.ifndef _jobs_mk_included
_jobs_mk_included=YES

DEFAULT_JOBS?=	1

# We always want a -j option, because it puts make out of compat mode
# and makes it run shell scripts sensibly.
.if empty(.MAKEFLAGS:M-j*)

.MAKEFLAGS:	-j${DEFAULT_JOBS}

.endif

.endif
