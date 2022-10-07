NAME			=	a.out
SRCS			=	main.cpp \
					Benchmark.cpp \
					Timer.cpp
OBJS_DIR		=	./objs
OBJS			=	$(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))

#CXX				=	c++
CXX				=	clang++
CXXFLAGS		=	-Wall -Wextra -Werror -std=c++98
CXXFLAGS		+=	-g -fsanitize=address
RM				=	rm -f

.PHONY			:	all clean fclean re

all				:	$(NAME)

$(NAME)			:	$(OBJS)
					$(CXX) $(OBJS) $(CXXFLAGS) -o $@

$(OBJS_DIR)/%.o	:	%.cpp
					@[ -d $(OBJS_DIR) ]
					$(CXX) $(CXXFLAGS) -c $< -o $@

benchmark			:
					$(CXX) $(CXXFLAGS) $(SRCS) -D FT=1 -o $(NAME)
					@./$(NAME) > output/ft_benchmark.txt 2>output/ft_err.txt
					$(CXX) $(CXXFLAGS) $(SRCS) -o $(NAME)
					@./$(NAME) > output/std_benchmark.txt 2>output/std_err.txt
					sh compare.sh

ft_benchmark		:
					$(CXX) $(CXXFLAGS) $(SRCS) -D FT=1 -o $(NAME)
					@./$(NAME) > output/ft_benchmark.txt 2>output/ft_err.txt
					@cat output/ft_benchmark.txt
					@cat output/ft_err.txt

std_benchmark		:
					$(CXX) $(CXXFLAGS) $(SRCS) -o $(NAME)
					@./$(NAME) > output/std_benchmark.txt 2>output/std_err.txt
					@cat output/std_benchmark.txt
					@cat output/std_err.txt

clean			:
					$(RM) $(OBJS)
					$(RM) output/ft_benchmark.txt output/std_benchmark.txt output/ft_err.txt output/std_err.txt

fclean			:
					$(RM) $(OBJS) $(NAME)
					$(RM) output/ft_benchmark.txt output/std_benchmark.txt output/ft_err.txt output/std_err.txt

re				:	fclean all
