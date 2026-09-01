USE_DEBUG = NO
USE_64BIT = NO
USE_UNICODE = NO
USE_CLANG = NO
# sadly, cygwin mingw does not support gdiplus...
USE_CYGWIN = NO

include der_libs\tool_select.mak

ifeq ($(USE_DEBUG),YES)
CFLAGS=-Wall -ggdb -O
LFLAGS=-mwindows
else
CFLAGS=-Wall -O3 -Weffc++ -c 
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

BASE:=wmetar
BIN=$(BASE).exe

LIBS=-lgdi32 -lcomctl32 -lcomdlg32

# Automatically parse the latest version block
VERSION := $(shell grep -oE '\[[0-9]+\.[0-9]+\]' CHANGELOG.md | head -n 1 | tr -d '[]')
DIST_ZIP := $(BASE)V$(VERSION).zip

# Force these action-only targets to always run
.PHONY: dist release update

#*******************************************************************
#  top-level build rules
#*******************************************************************
%.o: %.cpp
	$(TOOLS)\$(GNAME) $(CFLAGS) -c $< -o $@

all: $(BIN)

clean:
	rm -f $(BIN) $(OBJS) *.bak *.zip Output/*.exe

depend:
	makedepend $(CSRC)

dist:
	rm -f .zip
	zip $(DIST_ZIP) $(BIN) readme.md stations.txt metar_samples.txt LICENSE.txt CHANGELOG.md

# Your new automated release workflow
release: dist
	@cmd /C "@echo Preparing GitHub release for v$(VERSION)..."
	sed -n '/## \['$(VERSION)'\]/,/## \[/p' CHANGELOG.md | sed '$$d' > temp_notes.md
	gh release create v$(VERSION) ./$(DIST_ZIP) ./CHANGELOG.md --notes-file temp_notes.md
	rm temp_notes.md
	@cmd /C "@echo Release v$(VERSION) successfully uploaded to GitHub!"
	
# Your new update-in-place pipeline
update: dist
	@cmd /C "@echo Updating assets for existing release v$(VERSION)..."
	@# Uploads and overwrites the .zip file and CHANGELOG.md on GitHub
	gh release upload v$(VERSION) ./$(DIST_ZIP) ./CHANGELOG.md --clobber
	@cmd /C "@echo Release v$(VERSION) assets successfully updated on GitHub!"

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

rc.o: wmetar.rc
	$(TOOLS)\$(WRNAME) $< -O COFF -o $@

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
