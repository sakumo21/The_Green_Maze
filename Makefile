CCF = cc -Wall -Wextra -Werror -g3 #-g -fsanitize=address
FLAG = ./minilibx-linux/libmlx_Linux.a -lXext -lX11 -lm
NAME = cub3D
NAME_BONUS = cub3D_bonus
LIBFT = Libft/libft.a
GNL = Get_next_line/get_next_line.c Get_next_line/get_next_line_utils.c
FILES_BONUS =  bonus_files/mini-map/minimap.c bonus_files/mini-map/minimap2.c  bonus_files/parsing/parsing1.c bonus_files/parsing/parsing2.c bonus_files/parsing/parsing3.c bonus_files/parsing/parsing4.c bonus_files/parsing/parsing5.c bonus_files/parsing/parsing6.c bonus_files/parsing/map_parsing1.c bonus_files/parsing/map_parsing2.c bonus_files/parsing/map_parsing3.c bonus_files/main.c bonus_files/keys.c bonus_files/calculations.c bonus_files/coloring.c bonus_files/put_pixel.c bonus_files/cub3d_utils.c bonus_files/texturing.c bonus_files/texturing2.c bonus_files/movement.c bonus_files/cub3d_utils1.c
FILES =  mandatory_files/parsing/parsing1.c mandatory_files/parsing/parsing2.c mandatory_files/parsing/parsing3.c mandatory_files/parsing/parsing4.c mandatory_files/parsing/parsing5.c mandatory_files/parsing/parsing6.c mandatory_files/parsing/parsing7.c mandatory_files/parsing/map_parsing1.c mandatory_files/parsing/map_parsing2.c mandatory_files/parsing/map_parsing3.c mandatory_files/main.c mandatory_files/keys.c mandatory_files/calculations.c mandatory_files/coloring.c mandatory_files/put_pixel.c mandatory_files/cub3d_utils.c mandatory_files/texturing.c mandatory_files/texturing2.c mandatory_files/movement.c mandatory_files/cub3d_utils1.c

all : $(NAME)

$(LIBFT):
	@echo "Making $(notdir $@)... ⏳"
	@make -C Libft all > /dev/null
	@echo "Done ✅"

$(NAME) : $(FILES) $(LIBFT) $(GNL)
	@echo "Making $@... ⏳"
	@$(CCF) $(FILES) $(LIBFT) $(GNL) $(FLAG) -o $(NAME)
	@echo "Done ✅"

bonus: $(FILES_BONUS) $(LIBFT) $(GNL)
	@echo "Making $@... ⏳"
	@$(CCF) $(FILES_BONUS) $(LIBFT) $(GNL) $(FLAG) -o $(NAME_BONUS)
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
