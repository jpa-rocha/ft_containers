################################################################################
################################ COMPILER & FLAGS ##############################
################################################################################

CC =		g++

CFLAGS	=	-Wall -Wextra -Werror -Wshadow -std=c++98

DEBUG =		-Wall -Wextra -Werror -g -std=c++98 

VAL =		valgrind -s --leak-check=full --show-leak-kinds=all

################################################################################
################################## DIRECTORIES #################################
################################################################################

HEADER = 		./header

ITERATOR = 		./iterator/include/

VECTOR =		./vector/include/

MAP =			./execute/include/

STACK =			./stack/include/

SET =			./set/include/

TYPE_TRAITS = 	.utils/type_traits/

LEX_COMP =		.utils/lexicographical_compare/

CONVERSION =	.utils/conversions/

################################################################################
################################### LIBRARIES ##################################
################################################################################

FT_INC	=		-I $(ITERATOR)		\
				-I $(VECTOR)		\
				-I $(TYPE_TRAITS)	\
				-I $(LEX_COMP)		\
				-I $(CONVERSION)	\
				
INCLUDES = 		$(FT_INC)

################################################################################
################################## SRCS & OBJS #################################
################################################################################

SRCS	=	main.cpp		\

OBJS	=	$(SRCS:.cpp=.o)

################################################################################
#################################### PROGRAM ###################################
################################################################################

EXEC =		ft_containters

RUN =		./ft_containters

################################################################################
#################################### RULES #####################################
################################################################################

all:		$(EXEC)

$(EXEC):	$(OBJS)
		$(CC) $(OBJS) $(INCLUDES) -o $(EXEC) $(CFLAGS)

debug:	$(OBJS)
		$(CC) $(OBJS) $(INCLUDES) -o $(EXEC) $(DEBUG)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -g $(SRCS)

clean:
		rm -f $(OBJS)

fclean:		clean
		rm -f $(EXEC)

re:			fclean all

test: debug
	$(VAL) $(RUN)

.PHONY: all debug clean fclean re test