CCF = cc -Wall -Wextra -Werror -g3 #-g -fsanitize=address
FLAG = ./minilibx-linux/libmlx_Linux.a -lXext -lX11 -lm
NAME = cub3D
LIBFT = Libft/libft.a
GNL = Get_next_line/get_next_line.c Get_next_line/get_next_line_utils.c
FILES =  mini-map/minimap.c  parsing/parsing1.c parsing/parsing2.c parsing/parsing3.c parsing/parsing4.c parsing/map_parsing1.c main.c keys.c calculations.c coloring.c put_pixel.c texturing.c movement.c

all : $(NAME)

$(LIBFT):
	@echo "Making $(notdir $@)... ⏳"
	@make -C Libft all > /dev/null
	@echo "Done ✅"

$(NAME) : $(FILES) $(LIBFT) $(GNL)
	@echo "Making $@... ⏳"
	@$(CCF) $(FILES) $(LIBFT) $(GNL) $(FLAG) -o $(NAME)
	@echo "Done ✅"

.PHONY: clean fclean re 

clean:
	@$(MAKE) -C Libft clean > /dev/null
	@echo "Cleaning executables...✅"

fclean: clean
	@$(MAKE) -C Libft fclean > /dev/null
	@rm -f $(NAME)
	@echo "Full clean done...✅"

re: fclean all
