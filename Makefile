# ---------------------------------------------------------------------------- #
# set path to your ft_container

PATH_TO_YOUR_CONTAINER := ../ft_containers/includes/

# ---------------------------------------------------------------------------- #
NAME	:= run_test
CXX		:= c++
INCLUDES:= -Isrcs/includes -I$(PATH_TO_YOUR_CONTAINER)
CXXFLAGS:= -Wall -Wextra -Werror -std=c++98 -pedantic-errors $(INCLUDES) -MMD -MP
DEFINES	:= -D_VECTOR -D_MAP -D_STACK -D_SET

# ---------------------------------------------------------------------------- #
# make
SRCS_	:= main.cpp \
		Log.cpp \
		UnitTester.cpp

SRCS_VECTOR	:= VectorTest.cpp \
			VectorTest_Basic.cpp \
			VectorTest_ElementAccess.cpp \
			VectorTest_Iterators.cpp \
			VectorTest_Capacity.cpp \
			VectorTest_NonMemberFunctions.cpp \
			VectorTest_Modifiers.cpp

SRCS_MAP	:= MapTest.cpp \
			MapTest_Basic.cpp \
			MapTest_ElementAccess.cpp \
			MapTest_Iterators.cpp \
			MapTest_Capacity.cpp \
			MapTest_Lookup.cpp \
			MapTest_Observers.cpp \
			MapTest_NonMemberFunctions.cpp \
			MapTest_Modifiers.cpp

SRCS_STACK	:= StackTest.cpp \
			StackTest_Basic.cpp \
			StackTest_Else.cpp \
			StackTest_Template.cpp \
			StackTest_NonMemberFunctions.cpp

SRCS_SET	:= SetTest.cpp \
			SetTest_Basic.cpp \
			SetTest_Iterators.cpp \
			SetTest_Capacity.cpp \
			SetTest_Lookup.cpp \
			SetTest_Observers.cpp \
			SetTest_NonMemberFunctions.cpp \
			SetTest_Modifiers.cpp

SRCS	:= $(SRCS_) \
			$(SRCS_VECTOR) \
			$(SRCS_MAP) \
			$(SRCS_STACK) \
			$(SRCS_SET)

# ---------------------------------------------------------------------------- #
# make single-container
ifdef VECTOR
DEFINES	:= -D_VECTOR
SRCS	:= $(SRCS_) $(SRCS_VECTOR)
NAME	:= vector_test
endif

ifdef MAP
DEFINES	:= -D_MAP
SRCS	:= $(SRCS_) $(SRCS_MAP)
NAME	:= map_test
endif

ifdef STACK
DEFINES	:= -D_STACK
SRCS	:= $(SRCS_) $(SRCS_STACK)
NAME	:= stack_test
endif

ifdef SET
DEFINES	:= -D_SET
SRCS	:= $(SRCS_) $(SRCS_SET)
NAME	:= set_test
endif

# ---------------------------------------------------------------------------- #
# make std
ifdef STD
DEFINES	+= -DSTD
NAME	:= std_test
endif

# ---------------------------------------------------------------------------- #
# make bench
ifdef BENCH
DEFINES	+= -DBENCH
NAME	:= bench_test
SRCS	:= $(SRCS_) \
		UnitTesterBench.cpp \
		VectorTest.cpp \
		VectorTest_Bench.cpp \
		MapTest.cpp \
		MapTest_Bench.cpp \
		StackTest.cpp \
		StackTest_Bench.cpp \
		SetTest.cpp \
		SetTest_Bench.cpp
endif

# ---------------------------------------------------------------------------- #
CXXFLAGS += $(DEFINES)
OBJS_DIR:= objs/
OBJS	:= $(addprefix $(OBJS_DIR), $(SRCS:.cpp=.o))
SRCS_DIR:= srcs
VPATH	:= $(SRCS_DIR) \
	$(SRCS_DIR)/vector \
	$(SRCS_DIR)/map \
	$(SRCS_DIR)/stack \
	$(SRCS_DIR)/set \
DEPS	:= $(OBJS:.o=.d)

# ---------------------------------------------------------------------------- #
# basic rules

.PHONY	: all clean fclean re test ft std vector map stack set

all	: $(NAME)  ## Compile test with ft

-include $(DEPS)

$(NAME)	: $(OBJS_DIR) $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $@ $(OBJS)
	@echo executable: $@

$(OBJS_DIR)%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -o $@ -c $<
	@echo compile: $<

$(OBJS_DIR):
	@-mkdir $@

clean	:  # Remove obj directory
	$(RM) -R $(OBJS_DIR)

fclean	: clean # Remove executable
	$(RM) $(NAME) std_test vector_test map_test stack_test set_test

re	: fclean all

# ---------------------------------------------------------------------------- #
# individual compilation

vector	:  ## Only compile vector
	make re VECTOR=1

map	:  ## Only compile map
	make re MAP=1

stack	:  ## Only compile stack
	make re STACK=1

set	:  ## Only compile set
	make re SET=1

# std individual compilation

vector-std	:  ## Only compile vector
	make re STD=1 VECTOR=1

map-std	:  ## Only compile map
	make re STD=1 MAP=1

stack-std	:  ## Only compile stack
	make re STD=1 STACK=1

set-std	:  ## Only compile set
	make re STD=1 SET=1

# ---------------------------------------------------------------------------- #
# advanced rules

ft	: re  ## Recompile test with ft

std	: ## Recompile test with std
	make re STD=1

bench	: ## Reompile benchmark test
	make re BENCH=1

help	: ## Display this help screen
	@grep -E '^[a-zA-Z_-]+.*:.*?## .*$$' Makefile \
	| awk 'BEGIN {FS = "\t:.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'