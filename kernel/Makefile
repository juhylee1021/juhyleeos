TARGET = kernel.elf

CXX = clang++

# each CXXFLAGS are... \
	Warnning evetrything as error \
	standard is C++17 \
	contain debug info \
	optimize level 2 \
	build for x86-64 architecture, in elf format \
	freestanding, because it's os \
	no redzone, no exception, no rtti
CXXFLAGS += -Wall -Wextra -Werror \
						-std=c++17 \
						-g \
						-O2 \
						--target=x86_64-elf \
						-ffreestanding \
						-mno-red-zone -fno-exceptions -fno-rtti
# make dependancy files
CPPFLAGS += -MD
#each LDFLAGS are... \
	entry point is KernelMain \
	no RElocation ReadOnly \
	image base is 0x100000 \
	static link
LDFLAGS += --entry=KernelMain \
					-z norelro \
					-image-base=0x100000 \
					--static

RM = rm -f

SRCS = main.cpp \
			 graphics.cpp \
			 font.cpp

OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

all: $(TARGET)

$(TARGET): $(OBJS) Makefile
	ld.lld $(LDFLAGS) -o $@ hankaku.o $(OBJS)

%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS) $(DEPS) $(TARGET)

re: clean
	@make all

-include $(DEPS)

.PHONY: all clean re
