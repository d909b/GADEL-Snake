ANGEL_DISABLE_FMOD := $(shell sed -rn 's/^[[:space:]]*\#define[[:space:]]+ANGEL_DISABLE_FMOD[[:space:]]+([[:digit:]])[[:space:]]*$$/\1/p' ../Angel/AngelConfig.h)
ANGEL_DISABLE_DEVIL := $(shell sed -rn 's/^[[:space:]]*\#define[[:space:]]+ANGEL_DISABLE_DEVIL[[:space:]]+([[:digit:]])[[:space:]]*$$/\1/p' ../Angel/AngelConfig.h)
CXX = g++
TARGET = ClientGame
ARCH := $(shell uname -m)
ALLEGRO_LIBS := $(shell allegro-config --libs 2>/dev/null)
CWD := $(shell pwd)
CODE_DIR := $(shell dirname "$(CWD)")
LIBANGEL = ../Angel/libangel.a
LUA = ../Angel/Libraries/angel-lua-build/lua
WRAPPER = ../Angel/Scripting/Interfaces/AngelLuaWrapping.cpp

INCLUDE = 							\
	-I../Angel						\
	-I../Angel/Libraries/glfw-2.7.3/include			\
	-I../Angel/Libraries/Box2D-2.2.1			\
	-I../Angel/Libraries/FTGL/include			\
	-I../Angel/Libraries/lua-5.2.1/src			\
	-I/usr/include/freetype2
ifneq ($(ANGEL_DISABLE_FMOD), 1)
	INCLUDE += -I../Angel/Libraries/FMOD/inc
endif

LIBS = 									\
	$(LIBANGEL)							\
	../Angel/Libraries/glfw-2.7.3/lib/x11/libglfw.a			\
	../Angel/Libraries/Box2D-2.2.1/Build/Box2D/libBox2D.a		\
	../Angel/Libraries/FTGL/unix/src/.libs/libftgl.a		\
	../Angel/Libraries/angel-lua-build/liblua.a

ifneq ($(ANGEL_DISABLE_FMOD), 1)
	ifeq ($(ARCH),x86_64)
		LIBS += ../Angel/Libraries/FMOD/lib/libfmodex64.so
	else
		LIBS += ../Angel/Libraries/FMOD/lib/libfmodex.so
	endif
endif

SHLIBS = -lGL -lGLU -ldl -lfreetype -lXrandr -lX11 -lpthread -lrt
SHLIBS += $(ALLEGRO_LIBS)
ifeq ($(ANGEL_DISABLE_FMOD), 1)
	SHLIBS += -lopenal -lvorbisfile
endif
ifneq ($(ANGEL_DISABLE_DEVIL),1)
	SHLIBS += -lIL -lILU -lILUT
else
	SHLIBS += -lpng
endif

SYSSRCS = 							\
	$(WRAPPER)

SRCS =								\
	stdafx.cpp						\
	Main.cpp

SYSOBJS = $(patsubst %.cpp,%.o,$(SYSSRCS))
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

.PHONY: clean all SWIG-Wrapper

%.o: %.cpp
	$(CXX) -c $(INCLUDE) -Wno-write-strings -Wno-deprecated -o $@ $^

all: $(TARGET)

publish: $(TARGET)
	$(LUA) ../Tools/BuildScripts/publish_linux.lua -i $(CWD) -e ClientGame

SWIG-Wrapper:
	$(LUA) ../Tools/BuildScripts/swig_wrap.lua -p "$(CODE_DIR)"

$(WRAPPER): SWIG-Wrapper

$(TARGET): $(LIBANGEL) $(OBJS) $(SYSOBJS) $(WRAPPER)
	$(CXX) -o $@ $(OBJS) $(SYSOBJS) $(LIBS) $(SHLIBS)
	cp -p ../Angel/Scripting/EngineScripts/*.lua Resources/Scripts

clean:
	rm -f $(OBJS) $(SYSOBJS) $(TARGET) $(WRAPPER)
	rm -rf $(TARGET).appdir Published

$(LIBANGEL):
	cd ../Angel && make
