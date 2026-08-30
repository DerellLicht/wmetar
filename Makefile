USE_DEBUG = NO

include der_libs\tool_select.mak

ifeq ($(USE_DEBUG),YES)
CFLAGS=-Wall -ggdb -O
LFLAGS=-mwindows
else
CFLAGS=-Wall -O3
LFLAGS=-mwindows -s
endif
CFLAGS += -Weffc++
CFLAGS += -Wno-write-strings
CFLAGS += -Wno-stringop-truncation
CFLAGS += -Wno-stringop-overflow
CFLAGS += -Wno-unused-but-set-variable
CFLAGS += -Wno-c++11-narrowing

LiFLAGS += -Ider_libs
CFLAGS += -Ider_libs
IFLAGS += -Ider_libs

# link library files
CSRC=der_libs/common_funcs.cpp \
der_libs/common_win.cpp \
der_libs/statbar.cpp \
der_libs/winmsgs.cpp \
der_libs/wthread.cpp \
der_libs/cterminal.cpp \
der_libs/vlistview.cpp 

# link application-specific sources
CSRC+=wmetar.cpp dcdmetar.cpp antoi.cpp charcmp.cpp dcdmtrmk.cpp fracpart.cpp \
prtdmetr.cpp stspack2.cpp stspack3.cpp station_name.cpp sendbfr.cpp

OBJS = $(CSRC:.cpp=.o) rc.o

BIN=wmetar.exe

LIBS=-lgdi32 -lcomctl32 -lcomdlg32

%.o: %.cpp
	$(TOOLS)\g++ $(CFLAGS) -c $< -o $@

#*******************************************************************
#  top-level build rules
#*******************************************************************
all: $(BIN)

clean:
	rm -f $(BIN) $(OBJS) *.bak *.zip Output/*.exe

depend:
	makedepend $(CSRC)

source:
	zip -D wmetar.src.zip *
	zip -r wmetar.src.zip ../der_libs/*
    
dist:
	rm -f wmetar.zip
	zip wmetar.zip wmetar.exe readme.txt stations.txt metar_samples.txt

clint:
	cmd /C "python ..\ClaudeLint.py --exclude der_libs --strip-arg=-Wno-stringop-* "
	
cppc:
	cmd /C "cppcheck --project=compile_commands.json --std=c++14 --suppressions-list=./.suppress.cppcheck"

check:
	cmd /C "d:\llvm\bin\clang-tidy.exe $(CSRC)"

#*******************************************************************
#  component build rules
#*******************************************************************
$(BIN): $(OBJS)
	$(TOOLS)/$(GNAME) $(OBJS) $(LFLAGS) -o $(BIN) $(LIBS) 
#	g++ $(LFLAGS) $(OBJS) -o $(BIN) $(LIBS)
#	\\InnoSetup5\iscc /Q wmetar.iss

rc.o: wmetar.rc
	windres $(RFLAGS) -O COFF $< -o $@

# DO NOT DELETE

der_libs/common_funcs.o: der_libs/common.h
der_libs/common_win.o: der_libs/common.h der_libs/commonw.h
der_libs/statbar.o: der_libs/common.h der_libs/commonw.h der_libs/statbar.h
der_libs/wthread.o: der_libs/wthread.h
der_libs/cterminal.o: der_libs/common.h der_libs/commonw.h
der_libs/cterminal.o: der_libs/cterminal.h der_libs/vlistview.h
der_libs/vlistview.o: der_libs/common.h der_libs/commonw.h
der_libs/vlistview.o: der_libs/vlistview.h
wmetar.o: resource.h der_libs/common.h der_libs/commonw.h wmetar.h
wmetar.o: metar_structs.h der_libs/statbar.h der_libs/cterminal.h
wmetar.o: der_libs/vlistview.h
dcdmetar.o: der_libs/common.h wmetar.h metar_structs.h
charcmp.o: wmetar.h
dcdmtrmk.o: wmetar.h metar_structs.h
fracpart.o: wmetar.h
prtdmetr.o: der_libs/common.h resource.h wmetar.h metar_structs.h
stspack2.o: wmetar.h
stspack3.o: wmetar.h
station_name.o: der_libs/common.h wmetar.h
sendbfr.o: resource.h der_libs/common.h der_libs/commonw.h wmetar.h
sendbfr.o: der_libs/wthread.h
