FT				=	ft_test
FT_SRCS			=	main.cpp
FT_OBJS_DIR		=	./ft_objs
FT_OBJS			=	$(addprefix $(FT_OBJS_DIR)/, $(FT_SRCS:.cpp=.o))
FT_DEPS			=	$(addprefix $(FT_OBJS_DIR)/, $(FT_SRCS:.cpp=.d))

STD				=	std_test
STD_SRCS		=	main.cpp
STD_OBJS_DIR	=	./std_objs
STD_OBJS		=	$(addprefix $(STD_OBJS_DIR)/, $(STD_SRCS:.cpp=.o))
STD_DEPS		=	$(addprefix $(STD_OBJS_DIR)/, $(STD_SRCS:.cpp=.d))

#CXX				=	c++
CXX				=	clang++
CXXFLAGS		=	-Wall -Wextra -Werror -std=c++98
CXXFLAGS		+=	-MMD -MP
CXXFLAGS		+=	-g -fsanitize=address

INCLUDE_DIR		=	../../containers
INCLUDE			=	-I$(INCLUDE_DIR)

RM				=	rm -f

.PHONY			:	all clean fclean re

all				:	$(FT) $(STD)

$(FT)			:	$(FT_OBJS)
					$(CXX) $(FT_OBJS) $(CXXFLAGS) -o $@

$(FT_OBJS)		:	$(FT_OBJS_DIR)/%.o	:	%.cpp
					@[ -d $(FT_OBJS_DIR) ]
					$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(STD)			:	$(STD_OBJS)
					$(CXX) $(STD_OBJS) $(CXXFLAGS) -o $@

$(STD_OBJS)		:	$(STD_OBJS_DIR)/%.o	:	%.cpp
					@[ -d $(STD_OBJS_DIR) ]
					$(CXX) $(CXXFLAGS) $(INCLUDE) -D STD=1 -c $< -o $@

clean			:
					$(RM) $(FT_OBJS) $(FT_DEPS) $(STD_OBJS) $(STD_DEPS)

fclean			:
					$(RM) $(FT_OBJS) $(FT_DEPS) $(STD_OBJS) $(STD_DEPS) $(FT) $(STD)

re				:	fclean all

-include $(FT_DEPS) $(STD_DEPS)
