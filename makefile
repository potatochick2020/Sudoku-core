CC = clang++
CFLAGS = -Wall -pedantic -std=c++20

SOURCEDIR = Float
BUILDDIR = build
SRCS = $(wildcard $(SOURCEDIR)/*.c)
OBJS = $(addprefix $(BUILDDIR)/,$(notdir $(SRCS:.c=.o)))

all : dir cb 

dir :
    mkdir -p $(BUILDDIR)

cb : $(OBJS)
    $(CC) -o $@ $(CFLAGS) $(OBJS) 

$(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -rf cb $(BUILDDIR)