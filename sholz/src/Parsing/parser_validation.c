#include "../../includes/cub3d.h"

static const char	*get_basename(const char *filename)
{
	const char	*basename;

	basename = ft_strrchr(filename, '/');
	if (!basename)
		basename = ft_strrchr(filename, '\\');
	if (basename)
		basename++;
	else
		basename = filename;
	return (basename);
}

static int	is_hidden_file(const char *basename)
{
	if (basename[0] == '.')
		return (1);
	return (0);
}

static int	check_extension(const char *basename)
{
	int	len;

	if (ft_strncmp(basename, ".cub", 5) == 0)
		return (0);
	len = ft_strlen(basename);
	if (len < 5 || ft_strncmp(basename + len - 4, ".cub", 5) != 0)
		return (0);
	return (1);
}

int	is_valid_filename(const char *filename)
{
	const char	*basename;

	if (!filename)
		return (0);
	basename = get_basename(filename);
	if (is_hidden_file(basename))
		return (0);
	if (!check_extension(basename))
		return (0);
	return (1);
}
