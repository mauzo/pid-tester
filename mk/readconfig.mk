.ifndef _readconfig_mk_included
_readconfig_mk_included=YES

config.mk: .EXEC
	sh ${.CURDIR}/config

config: .PHONY config.mk

.sinclude "config.mk"
.if !make(config) && !defined(_config_mk_included)
. error Run '${MAKE} config' first!
.endif

.endif
