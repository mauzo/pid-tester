.ifndef _obj_mk_included
_obj_mk_included=YES

.if ${.OBJDIR} == ${.CURDIR}
_dummy!=    mkdir -p ${.CURDIR}/obj
.OBJDIR:    ${.CURDIR}/obj
.endif

.endif
