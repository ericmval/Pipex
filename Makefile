
NAME =	pipex
CFLAGS =	-Wall -Wextra -Werror -g
SOURCES = src/main.c \
		src/proces.c

HEADER = pipex.h 

#pahs
HEADER_DIR = inc/
SRC_DIR = src/
LIBFT_DIR = libs/otherproject/libft/
PRINTF_DIR = libs/otherproject/printf/
LIBS_DIR = libs/


OBJECTS =	${SOURCES:.c=.o}

#metodo implicito
%.o:%.c $(HEADER)
	gcc ${CFLAGS}  -c $< -o $@


all:${NAME}


${NAME}::
	${MAKE} -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)libft.a ${LIBS_DIR}
	

${NAME}::
	${MAKE} -C $(PRINTF_DIR)
	cp $(PRINTF_DIR)libftprintf.a ${LIBS_DIR}

${NAME}:: ${OBJECTS}
	gcc  ${CFLAGS} ${SOURCES} -g -L ${LIBS_DIR} -lft -lftprintf -o ${NAME}


clean:
	rm -f ${SRC_DIR}${OBJECTS}
	make clean -C ${LIBFT_DIR}
	make clean -C ${PRINTF_DIR}

fclean:
	rm -f ${SRC_DIR}${NAME} ${OBJECTS}
	make fclean -C ${LIBFT_DIR}
	make fclean -C ${PRINTF_DIR}
	rm -f ${LIBS_DIR}*.a 

re:
	make fclean
	make fclean -C ${LIBFT_DIR}
	make fclean -C ${PRINTF_DIR}
	make

leak:
	gcc -g -fsanitize=address  ${SOURCES} -L ${LIBS_DIR} -lft -lftprintf -o testm
	valgrind ./testm t1 "grep e" "grep 2 -c" t2
	
	
