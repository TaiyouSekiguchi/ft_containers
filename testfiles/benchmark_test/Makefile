FT				=	ft_benchmark_test
FT_SRCS			=	main.cpp \
					Timer.cpp \
					VectorBenchmark.cpp \
					StackBenchmark.cpp \
					MapBenchmark.cpp
FT_OBJS_DIR		=	./ft_objs
FT_OBJS			=	$(addprefix $(FT_OBJS_DIR)/, $(FT_SRCS:.cpp=.o))
FT_DEPS			=	$(addprefix $(FT_OBJS_DIR)/, $(FT_SRCS:.cpp=.d))

STD				=	std_benchmark_test
STD_SRCS		=	main.cpp \
					Timer.cpp \
					VectorBenchmark.cpp \
					StackBenchmark.cpp \
					MapBenchmark.cpp
STD_OBJS_DIR	=	./std_objs
STD_OBJS		=	$(addprefix $(STD_OBJS_DIR)/, $(STD_SRCS:.cpp=.o))
STD_DEPS		=	$(addprefix $(STD_OBJS_DIR)/, $(STD_SRCS:.cpp=.d))

CXX				=	c++
#CXX				=	clang++
CXXFLAGS		=	-Wall -Wextra -Werror -std=c++98
CXXFLAGS		+=	-MMD -MP
#CXXFLAGS		+=	-g -fsanitize=address

RM				=	rm -f

.PHONY			:	all clean fclean re benchmark ft_benchmark std_benchmark

all				:	$(FT) $(STD)

$(FT)			:	$(FT_OBJS)
					$(CXX) $(FT_OBJS) $(CXXFLAGS) -o $@

$(FT_OBJS)		:	$(FT_OBJS_DIR)/%.o	:	%.cpp
					@[ -d $(FT_OBJS_DIR) ]
					$(CXX) $(CXXFLAGS) $(INCLUDE) -D FT=1 -c $< -o $@

$(STD)			:	$(STD_OBJS)
					$(CXX) $(STD_OBJS) $(CXXFLAGS) -o $@

$(STD_OBJS)		:	$(STD_OBJS_DIR)/%.o	:	%.cpp
					@[ -d $(STD_OBJS_DIR) ]
					$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

benchmark			: $(FT) $(STD)
					@./$(FT) > output/ft_benchmark.txt 2>output/ft_err.txt
					@./$(STD) > output/std_benchmark.txt 2>output/std_err.txt
					sh compare.sh

ft_benchmark		: $(FT)
					@./$(FT) > output/ft_benchmark.txt 2>output/ft_err.txt
					@cat output/ft_benchmark.txt
					@cat output/ft_err.txt

std_benchmark		: $(STD)
					@./$(STD) > output/std_benchmark.txt 2>output/std_err.txt
					@cat output/std_benchmark.txt
					@cat output/std_err.txt

clean			:
					$(RM) $(FT_OBJS) $(FT_DEPS) $(STD_OBJS) $(STD_DEPS)
					$(RM) output/ft_benchmark.txt output/std_benchmark.txt output/ft_err.txt output/std_err.txt

fclean			:
					$(RM) $(FT_OBJS) $(FT_DEPS) $(STD_OBJS) $(STD_DEPS) $(FT) $(STD)
					$(RM) output/ft_benchmark.txt output/std_benchmark.txt output/ft_err.txt output/std_err.txt

re				:	fclean all

-include $(FT_DEPS) $(STD_DEPS)
