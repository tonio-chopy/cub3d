#include "test.h"

void	cub_handle_fatal(t_data *data, char *custom_msg)
{
	if (!custom_msg)
		perror("cub3d: ");
	else
		ft_printfd(2, custom_msg);
	cub_clean_data(data);
	exit(EXIT_FAILURE);
}
