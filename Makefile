BUILDDIR ?= build
COMPILE = g++ -O0 -std=c++14 -Igoogletest/googletest/include -Igoogletest/googlemock/include -Iinclude -Wall -Werror -Wno-unused-variable
LINK = g++ -pthread
SRC = $(wildcard */*.cpp) $(wildcard */*/*.cpp)
OBJ = $(addprefix $(BUILDDIR)/obj/,$(SRC:%=%.o))

ifeq ($(OS), Windows_NT)
	MKDIR = mkdir $(BUILDDIR)
	RMDIR = rmdir /s /q $(BUILDDIR) 
else
	MKDIR = mkdir -p $(BUILDDIR)
	RMDIR = rm -rf $(BUILDDIR) 
endif

all: $(BUILDDIR)/ut app

ut: $(BUILDDIR)/ut
	$(BUILDDIR)/ut

app: $(BUILDDIR)/app

clean:
	$(RMDIR)
	
$(BUILDDIR)/ut: $(BUILDDIR)/obj/googletest.o $(BUILDDIR)/obj/googlemock.o $(filter-out $(BUILDDIR)/obj/app/%,$(OBJ))
	$(LINK) $^ -o $@

$(BUILDDIR)/app: $(filter-out $(BUILDDIR)/obj/uts/%,$(OBJ))
	$(LINK) $^ -o $@

$(BUILDDIR)/obj/%.cpp.o: %.cpp
	@mkdir -p $(dir $@)
	$(COMPILE) -MMD -c $< -o $@

$(BUILDDIR)/obj/google%.o: googletest/google%
	@mkdir -p $(dir $@)
	$(COMPILE) $(addprefix -I, $(wildcard googletest/google*)) -MMD -c $</src/*-all.cc -o $@

-include $(OBJ:%.o=%.d)

%.hpp:
	@echo no $@
