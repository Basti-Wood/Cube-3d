/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:02:21 by bstorck           #+#    #+#             */
/*   Updated: 2025/11/25 09:02:26 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

int	parse_xpm_header(int xpm_fd, t_texture *texture)
{
	int		i;
	char	*line;
	char	*header;
	char	**token;

	line = skip_lines(xpm_fd);
	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	header = ft_strdup(&line[i]);
	free(line);
	if (header == NULL)
		return (1);
	token = ft_split(header, ' ');
	free(header);
	if (token == NULL)
		return (1);
	texture->width = ft_atoi(token[0]);
	texture->height = ft_atoi(token[1]);
	texture->color_count = ft_atoi(token[2]);
	i = -1;
	while (token[++i])
		free(token[i]);
	free(token);
	return (0);
}

int	parse_hex_color(const char *line)
{
	int	i;
	int	r;
	int	g;
	int	b;

	if (line[0] != '#')
		return (-1);
	i = 0;
	while (++i < 7)
		if (!ft_isxdigit(line[i]))
			return (-1);
	r = hex_pair_to_int(line[1], line[2]);
	g = hex_pair_to_int(line[3], line[4]);
	b = hex_pair_to_int(line[5], line[5]);
	if (r == -1 || g == -1 || b == -1)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

int	parse_xpm_color_table_line(char *line, t_texture *texture)
{
	int	color;
	int	i;
	int	index;

	if (!line[1])
		return (1);
	index = (int)line[1] - 32;
	i = 2;
	while (line[i] && line[i] != '#')
		i++;
	if (!line[i])
		return (1);
	color = parse_hex_color(&line[i]);
	free(line);
	if (color == -1)
		return (1);
	texture->color_table[index] = color;
	return (0);
}

int	parse_xpm_color_table(int xpm_fd, t_texture *texture)
{
	char	*line;
	int		line_count;

	line_count = 0;
	while (line_count < texture->color_count)
	{
		line = skip_lines(xpm_fd);
		if (line == NULL)
			return (1);
		else
		{
			if (parse_xpm_color_table_line(line, texture))
				return (1);
			line_count++;
		}
	}
	return (0);
}

int	init_xpm_pixel_map(t_texture *texture)
{
	int	i;

	texture->pixel_map = (int **)malloc(sizeof(int *) * texture->height);
	if (!texture->pixel_map)
		return (1);
	i = -1;
	while (++i < texture->height)
	{
		texture->pixel_map[i] = (int *)malloc(sizeof(int) * texture->width);
		if (!texture->pixel_map[i])
			return (1);
	}
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	t_texture	tex;
// 	t_game		game;
// 	if (argc != 2)
// 		return (1);
// 	parse_xpm_file(argv[1], &tex, &game);
// 	return (0);
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
//
// #define MAX_COLORS 256
//
// typedef struct {
//     int width;
//     int height;
//     int num_colors;
//     char *color_map[MAX_COLORS];
//     char **image_data;
// } XPMImage;
//
// int read_xpm(const char *filename, XPMImage *image) {
//     FILE *file = fopen(filename, "r");
//     if (!file) {
//         perror("Failed to open XPM file");
//         return (-1);
//     }
//
//     // Read the header
//     char line[1024];
//     int line_count = 0;
//
//     while (fgets(line, sizeof(line), file)) {
//         // Skip comment lines (lines starting with /* or //)
//         if (line[0] == '/' || line[0] == '#')
// 			continue ;
//         if (line_count == 0)
// 		{
//             // Read the width, height,
//	and number of colors from the first line
//             sscanf(line, "%d %d %d", &image->width, &image->height,
//	&image->num_colors);
//         }
//         else if (line_count <= image->num_colors) {
//             // Read the color map
//             char *color_symbol = strtok(line, " ");
//             char *color_value = strtok(NULL, " ");
//             image->color_map[line_count - 1] = strdup(color_value);
//         }
//         else {
//             // Read the pixel data
//             image->image_data = (char **)malloc(image->height
//		* sizeof(char *));
//             image->image_data[line_count - image->num_colors
//	- 1] = strdup(line);
//         }
//         line_count++;
//     }
//
//     fclose(file);
//     return (0);
// }

// void free_xpm(XPMImage *image) {
//     // Free color map
//     for (int i = 0; i < image->num_colors; i++) {
//         free(image->color_map[i]);
//     }
//     // Free image data
//     for (int i = 0; i < image->height; i++) {
//         free(image->image_data[i]);
//     }
//     free(image->image_data);
// }
//
// void print_xpm(XPMImage *image) {
//     for (int i = 0; i < image->height; i++) {
//         printf("%s", image->image_data[i]);
//     }
// }
//
// int main() {
//     XPMImage image;
//     if (read_xpm("example.xpm", &image) == 0) {
//         print_xpm(&image);
//         free_xpm(&image);
//     } else {
//         printf("Error reading XPM file.\n");
//     }
//     return (0);
// }

// int	***init_textures(void)
// {
// 	int	i = 0;
// 	int	x = 0;
// 	int	y = 0;
// 	int ***texture = NULL;
//
// 	i = -1;
// 	while (++i < 8)
// 	{
// 		texture[i] = (int**)malloc(TEX_HEIGHT * sizeof(int*));
// 		y = -1;
// 		while (++y < TEX_HEIGHT)
// 			texture[i][y] = (int*)malloc(TEX_WIDTH * sizeof(int));
// 	}
// 	return (texture);
// }
