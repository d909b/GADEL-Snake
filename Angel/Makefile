ANGEL_DISABLE_FMOD := $(shell sed -rn 's/^[[:space:]]*\#define[[:space:]]+ANGEL_DISABLE_FMOD[[:space:]]+([[:digit:]])[[:space:]]*$$/\1/p' AngelConfig.h)
ANGEL_DISABLE_DEVIL := $(shell sed -rn 's/^[[:space:]]*\#define[[:space:]]+ANGEL_DISABLE_DEVIL[[:space:]]+([[:digit:]])[[:space:]]*$$/\1/p' AngelConfig.h)
CXX = g++
CXXFLAGS =
TARGET = libangel.a
CWD := $(shell pwd)
CODE_DIR := $(shell dirname $(CWD))
ARCH := $(shell uname -m)
AR = ar rcu
RANLIB = ranlib
ifeq ($(ARCH),x86_64)
	CXXFLAGS += -fPIC
endif

INCLUDE = 							\
	-ILibraries/glfw-2.7.3/include				\
	-ILibraries/Box2D-2.2.1					\
	-ILibraries/FTGL/include				\
	-ILibraries/lua-5.2.1/src				\
	-IInfrastructure					\
	-I/usr/include/freetype2
ifneq ($(ANGEL_DISABLE_FMOD), 1)
	INCLUDE += -ILibraries/FMOD/inc
endif

LIBS = 								\
	Libraries/glfw-2.7.3/lib/x11/libglfw.a			\
	Libraries/Box2D-2.2.1/Build/Box2D/libBox2D.a		\
	Libraries/FTGL/unix/src/.libs/libftgl.a

SRCS =								\
	Actors/Actor.cpp					\
	Actors/FullScreenActor.cpp				\
	Actors/GridActor.cpp					\
	Actors/HUDActor.cpp					\
	Actors/ParticleActor.cpp				\
	Actors/PhysicsActor.cpp					\
	Actors/TextActor.cpp					\
	AI/BoundingShapes.cpp					\
	AI/Brain.cpp						\
	AIEvents/GotoAIEvent.cpp				\
	AIEvents/GotoTargetAIEvent.cpp				\
	AIEvents/NamedEventAIEvent.cpp				\
	AIEvents/TimerAIEvent.cpp				\
	AIEvents/TraversalAIEvent.cpp				\
	AI/PathFinder.cpp					\
	AI/Ray2.cpp						\
	AI/Sentient.cpp						\
	AI/SpatialGraph.cpp					\
	AI/Traversal.cpp					\
	Infrastructure/Camera.cpp				\
	Infrastructure/Color.cpp				\
	Infrastructure/Console.cpp				\
	Infrastructure/GameManager.cpp				\
	Infrastructure/Log.cpp					\
	Infrastructure/Preferences.cpp				\
	Infrastructure/RenderableIterator.cpp			\
	Infrastructure/SoundDevice.cpp				\
	Infrastructure/TagCollection.cpp			\
	Infrastructure/TextRendering.cpp			\
	Infrastructure/Textures.cpp				\
	Infrastructure/TuningVariable.cpp			\
	Infrastructure/Vector2.cpp				\
	Infrastructure/Vector3.cpp				\
	Infrastructure/World.cpp				\
	Input/Controller.cpp					\
	Input/Input.cpp						\
	Input/InputManager.cpp					\
	Input/MobileSimulator.cpp				\
	Input/MouseInput.cpp					\
	Input/MultiTouch.cpp					\
	Messaging/Message.cpp					\
	Messaging/Switchboard.cpp				\
	Scripting/LuaConsole.cpp				\
	Scripting/LuaModule.cpp					\
	Util/DrawUtil.cpp					\
	Util/FileUtil.cpp					\
	Util/MathUtil.cpp					\
	Util/StringUtil.cpp

all: $(TARGET)

FTGL:
ifeq ($(ARCH),x86_64)
	cd Libraries/FTGL/unix && (test -e Make.conf || \
		CXXFLAGS="-g -O2 -fPIC" ./configure) && make
else
	cd Libraries/FTGL/unix && (test -e Make.conf || ./configure) && make
endif

FTGL-clean:
	touch Libraries/FTGL/unix/Make.conf
	cd Libraries/FTGL/unix && make clean
	cd Libraries/FTGL/unix && rm -f config.log config.status ftgl.pc \
		Make.conf libtool demo/FTGLDemo docs/doc-stamp

MAKEFILE_X11 = Libraries/glfw-2.7.3/lib/x11/Makefile.x11

$(MAKEFILE_X11):
	cd Libraries/glfw-2.7.3 && sh ./compile.sh

GLFW: $(MAKEFILE_X11)
	cd Libraries/glfw-2.7.3/lib/x11 && make -f Makefile.x11 libglfw.a

GLFW-clean:
	cd Libraries/glfw-2.7.3 && make x11-clean

Box2D:
	cd Libraries/Box2D-2.2.1/Build && cmake .. && make Box2D

Box2D-clean:
	cd Libraries/Box2D-2.2.1/Build && make clean && rm -rf Box2D \
		CMakeCache.txt CMakeFiles cmake_install.cmake freeglut glui \
		HelloWorld Makefile Testbed

Lua:
	cd Libraries/angel-lua-build && make

Lua-clean:
	cd Libraries/angel-lua-build && make clean

libraries: FTGL GLFW Box2D

OBJS = $(patsubst %.cpp,%.o,$(SRCS))

%.o: %.cpp
	$(CXX) -c $(INCLUDE) -Wno-write-strings -Wno-deprecated $(CXXFLAGS) -o $@ $^

$(TARGET): libraries $(OBJS) Lua
	$(AR) $@ $(OBJS) $(LIBS)
	$(RANLIB) $@

clean: FTGL-clean GLFW-clean Box2D-clean Lua-clean
	rm -f $(OBJS) $(TARGET)
