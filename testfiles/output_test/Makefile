NAME			=	a.out
SRCS			=	main.cpp \
					vector_test.cpp
OBJS_DIR		=	./objs
OBJS			=	$(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))

#CXX				=	c++
CXX				=	clang++
CXXFLAGS		=	-Wall -Wextra -Werror -std=c++98
#CXXFLAGS		+=	-g -fsanitize=address
RM				=	rm -f

.PHONY			:	all clean fclean re

all				:	$(NAME)

$(NAME)			:	$(OBJS)
					$(CXX) $(OBJS) $(CXXFLAGS) -o $@

$(OBJS_DIR)/%.o	:	%.cpp
					@[ -d $(OBJS_DIR) ]
					$(CXX) $(CXXFLAGS) -c $< -o $@

test:
	$(CXX) $(CXXFLAGS) $(SRCS) -D FT=1 -o $(NAME)
	@./$(NAME) > output/ft_output 2>output/ft_err
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(NAME)
	@./$(NAME) > output/std_output 2>output/std_err
 # ret(1) cause make error.  ||: force ret(0)
	diff output/ft_output output/std_output ||:
	@echo "---ft_err---"
	@cat output/ft_err
	@echo "---std_err---"
	@cat output/std_err

test0:
	$(CXX) $(CXXFLAGS)) $(SRCS) -DTEST=1 -o $(NAME)
	@./$(NAME) > output/ft_output 2>ft_err
	@cat ft_output
	@cat ft_err

test1:
	$(CXX) $(CXXFLAGS)) $(SRCS) -o $(NAME)
	@./$(NAME) > std_out 2>std_err
	@cat std_out
	@cat std_err

clean			:
					$(RM) $(OBJS)
					$(RM) output/ft_output output/std_output output/ft_err output/std_err

fclean			:
					$(RM) $(OBJS) $(NAME)

re				:	fclean all
