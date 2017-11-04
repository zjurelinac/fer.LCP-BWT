CXX = g++

OPT_LVL = 9
DFLAGS = DEBUG USE_FAST_BV
DFLAGS_ = $(foreach flag,$(DFLAGS),-D$(flag))
CFLAGS = -std=c++14 -g -O$(OPT_LVL) -msse4.2 -Wall -Wextra -Wno-char-subscripts -I./src/include $(DFLAGS_)
LDFLAGS = -lsdsl -ldivsufsort

SDIR = src
IDIR = src/include
ODIR = build

EXEC = build/lcp_bwt
SRCS = $(wildcard $(SDIR)/*.cpp)
DEPS = $(wildcard $(IDIR)/*.h $(IDIR)/*.hpp)
OBJS = $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(SRCS))

all: .build $(EXEC)

.build:
	@mkdir -p build

$(EXEC): $(OBJS) $(DEPS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

clean:
	@\rm -r build