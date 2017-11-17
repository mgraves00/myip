# $Id$

PROG=		myip
CFLAGS+=	-I/usr/local/include -O0
LDFLAGS+=	-v -L/usr/local/lib -static
LDADD+=		-lkcgi -lkcgihtml -lz
MAN=		myip.1
WARNINGS=YES
BINGRP=		www
BINOWN=		www
BINDIR=		/var/www/cgi-bin

.include <bsd.prog.mk>
