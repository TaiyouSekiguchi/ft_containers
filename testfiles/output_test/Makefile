NAME			=	a.out
SRCS			=	main.cpp \
					Fixed.cpp \
					vector_test.cpp
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

test			:
					$(CXX) $(CXXFLAGS) $(SRCS) -D FT=1 -o $(NAME)
					@./$(NAME) > output/ft_output.txt 2>output/ft_err.txt
					$(CXX) $(CXXFLAGS) $(SRCS) -o $(NAME)
					@./$(NAME) > output/std_output.txt 2>output/std_err.txt
 # ret(1) cause make error.  ||: force ret(0)
					diff output/ft_output.txt output/std_output.txt ||:
					@echo "---ft_err.txt---"
					@cat output/ft_err.txt
					@echo "---std_err.txt---"
					@cat output/std_err.txt

test0			:
					$(CXX) $(CXXFLAGS) $(SRCS) -D FT=1 -o $(NAME)
					@./$(NAME) > output/ft_output.txt 2>output/ft_err.txt
					@cat output/ft_output.txt
					@cat output/ft_err.txt

test1			:
					$(CXX) $(CXXFLAGS) $(SRCS) -o $(NAME)
					@./$(NAME) > output/std_out 2>output/std_err.txt
					@cat output/std_output.txt
					@cat output/std_err.txt

clean			:
					$(RM) $(OBJS)
					$(RM) output/ft_output.txt output/std_output.txt output/ft_err.txt output/std_err.txt

fclean			:
					$(RM) $(OBJS) $(NAME)
					$(RM) output/ft_output.txt output/std_output.txt output/ft_err.txt output/std_err.txt

re				:	fclean all
