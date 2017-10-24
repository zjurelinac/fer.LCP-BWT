CXX = g++
CFLAGS = -std=c++14 -O3 -Wall -Wextra -Wno-char-subscripts -I./src/include
LDFLAGS = -lsdsl -ldivsufsort

EXEC = build/lcp_bwt
SRCS = $(wildcard src/*.cpp)
DEPS = $(wildcard include/*.h include/*.hpp)
OBJS = $(patsubst src/%.cpp,build/%.o,$(SRCS))

all: .build $(EXEC)

.build:
	@mkdir -p build

$(EXEC) : $(OBJS) $(DEPS)
	@$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(OBJS) : $(SRCS) $(DEPS)
	@$(CXX) $(CFLAGS) $< -c -o $@

clean:
	@\rm -r build