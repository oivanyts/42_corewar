NAME = libft.a
FLAGS = -Wall -Wextra -Werror
SRCS = ./src/form_num_char.c \
	./src/ft_array_print.c \
	./src/ft_atoi.c\
	./src/ft_atoi_hex.c\
	./src/ft_bzero.c\
	./src/ft_charlen.c\
	./src/ft_color_input.c\
	./src/ft_countletter.c\
	./src/ft_countwords.c\
	./src/ft_exp.c\
	./src/ft_isalnum.c\
	./src/ft_isalpha.c\
	./src/ft_isascii.c\
	./src/ft_isdigit.c\
	./src/ft_isprint.c\
	./src/ft_isspace.c\
	./src/ft_itoa.c\
	./src/ft_itoa_base.c\
	./src/ft_itoa_double.c\
	./src/ft_itoa_prntf.c\
	./src/ft_lstadd.c\
	./src/ft_lstaddback.c\
	./src/ft_lstaddhere.c\
	./src/ft_lstcpy.c\
	./src/ft_lstdel.c\
	./src/ft_lstdelone.c\
	./src/ft_lstiter.c\
	./src/ft_lstmap.c\
	./src/ft_lstnew.c\
	./src/ft_matrixalloc.c\
	./src/ft_max_number.c\
	./src/ft_memalloc.c\
	./src/ft_memccpy.c\
	./src/ft_memchr.c\
	./src/ft_memcmp.c\
	./src/ft_memcpy.c\
	./src/ft_memdel.c\
	./src/ft_memmove.c\
	./src/ft_memset.c\
	./src/ft_num_size.c\
	./src/ft_parcer_printf.c\
	./src/ft_print_list.c\
	./src/ft_printbits_printf.c\
	./src/ft_printf_fd.c\
	./src/ft_putchar.c\
	./src/ft_putchar_fd.c\
	./src/ft_putchar_u.c\
	./src/ft_putendl.c\
	./src/ft_putendl_fd.c\
	./src/ft_putnbr.c\
	./src/ft_putnbr_fd.c\
	./src/ft_putstr.c\
	./src/ft_putstr_fd.c\
	./src/ft_putstr_u.c\
	./src/ft_round_double.c\
	./src/ft_strcat.c\
	./src/ft_strchr.c\
	./src/ft_strclr.c\
	./src/ft_strcmp.c\
	./src/ft_strcpy.c\
	./src/ft_strdel.c\
	./src/ft_strdup.c\
	./src/ft_strdup_u.c\
	./src/ft_strequ.c\
	./src/ft_striter.c\
	./src/ft_striteri.c\
	./src/ft_strjoin.c\
	./src/ft_strlcat.c\
	./src/ft_strlen.c\
	./src/ft_strlen_u.c\
	./src/ft_strmap.c\
	./src/ft_strmapi.c\
	./src/ft_strncat.c\
	./src/ft_strncmp.c\
	./src/ft_strncpy.c\
	./src/ft_strndup.c\
	./src/ft_strndup_u.c\
	./src/ft_strnequ.c\
	./src/ft_strnew.c\
	./src/ft_strnstr.c\
	./src/ft_strnum_base.c\
	./src/ft_strrchr.c\
	./src/ft_strsplit.c\
	./src/ft_strstr.c\
	./src/ft_strsub.c\
	./src/ft_strtrim.c\
	./src/ft_swap.c\
	./src/ft_swap_d.c\
	./src/ft_tolower.c\
	./src/ft_toupper.c\
	./src/get_next_line.c\
	./src/printf.c

INC = 	./includes/libft.h

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Building of libft.a..."
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

%.o: %.c $(INC)
	gcc $(FLAGS) -I./includes -o $@ -c $<

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all