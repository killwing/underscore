PROG = test
SRCS = test.cpp
DEPS = $(SRCS:.cpp=.d)
OBJS = $(SRCS:.cpp=.o)

CXX = clang++
C11FLAGS = -std=c++11 -stdlib=libc++
CXXFLAGS = $(C11FLAGS)
#CPPFLAGS = -std=c++11 -stdlib=libc++

all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

%.d: %.cpp
	$(CXX) -MM $(CPPFLAGS) $(C11FLAGS) $< > $@
	@sed -i 's/^\($*\)\.o:/\1.o $@:/' $@

-include $(DEPS)

clean:
	@$(RM) $(OBJS) $(DEPS) $(PROG)



