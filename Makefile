TARGET?=$(shell $(CXX) -dumpmachine)

BIN=Rasterizer
CXXFLAGS=-O0 -g -Wall -Wno-unused-variable -Wno-unknown-pragmas
CFLAGS=$(CXXFLAGS)
CPPFLAGS=-Iexternals/include -Iinclude -MMD
LDFLAGS=-Lexternals/libs-$(TARGET)

ifeq ($(TARGET),x86_64-pc-cygwin)
# CYGWIN SPECIFICS
LDLIBS=-lglfw3 -lgdi32 -lglu32
externals/src/imgui_impl_opengl3.o: CXXFLAGS+="-DIMGUI_IMPL_OPENGL_LOADER_CUSTOM"
else ifneq (,$(filter x86_64%linux-gnu,$(TARGET)))
# LINUX SPECIFICS
LDLIBS=-lglfw3 -ldl -lX11 -lssl -lpthread -lGLU
endif

# PROGRAM OBJS
OBJS=src/App.o src/Camera.o src/Framebuffer.o src/main.o src/Renderer.o src/Scene.o src/Scene1.o src/Scene2.o src/Scene3.o src/Scene4.o src/Scene5.o src/myMaths.o src/texture.o src/Light.o src/Data_TheNobleCraftsman.o

# DO NOT MODIFY
# GLAD
OBJS+=externals/src/gl.o
# IMGUI
OBJS+=externals/src/imgui.o externals/src/imgui_demo.o externals/src/imgui_draw.o externals/src/imgui_widgets.o externals/src/imgui_tables.o
# IMGUI (backends)
OBJS+=externals/src/imgui_impl_glfw.o externals/src/imgui_impl_opengl3.o



DEPS=$(OBJS:.o=.d)

.PHONY: all clean

all: $(BIN)

-include $(DEPS)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

testMaths: tests/mathsTest.o src/myMaths.o
	g++ $(CFLAGS) $(LDFLAGS) $^ -o $@ && ./testMaths

clean:
	rm -f $(BIN) $(OBJS) $(DEPS) tests/mathsTest.d tests/mathsTest.o testMaths