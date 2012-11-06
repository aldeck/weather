TYPE = APP

NAME = Weather

SRCS = App.cpp
SRCS += MainWindow.cpp
SRCS += MainView.cpp

# mdsplib
HEADERS += mdsplib/include
SRCS += mdsplib/src/antoi.c
SRCS += mdsplib/src/dcdmetar.c
#SRCS += mdsplib/src/drvmetar.c
SRCS += mdsplib/src/prtdmetr.c
SRCS += mdsplib/src/stspack3.c
SRCS += mdsplib/src/charcmp.c
SRCS += mdsplib/src/dcdmtrmk.c
SRCS += mdsplib/src/fracpart.c
SRCS += mdsplib/src/stspack2.c

LIBS = be bnetapi stdc++

SYS_INCLUDES += /ExtData/haiku-serviceskit/headers/os/net

RDEFS = Weather.rdef

# include the makefile-engine
include $(BUILDHOME)/etc/makefile-engine
