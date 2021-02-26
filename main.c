# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include "get_next_line.c"
# include "ft_split.c"

typedef struct		s_tuple
{
	unsigned int	a;
	unsigned int	b;
}					t_tuple;

typedef struct		s_first_line
{
	unsigned int	duration;
	unsigned int	nb_inter;
	unsigned int	nb_streets;
	unsigned int	nb_cars;
	unsigned int	bonus;
}					t_first_line;

typedef struct		s_cars
{
	unsigned int	id_car;
	unsigned int	nb_path;
	char			**path;
}					t_cars;

typedef struct		s_streets
{
	unsigned int	id_street;
	unsigned int	start_inter;
	unsigned int	end_inter;
	char			*name;
	unsigned int	time_cross;
}					t_streets;

typedef struct		s_intersections
{
	unsigned int	id_inter;
	char			*from;
	char			*to;
	unsigned int	nb_cars;
	unsigned int	id_cars[1000];
}					t_intersections;

char				**streets_table;
char				is = 0;

int					check_street_exist(char	*name)
{
	int		i = 0;

	while(streets_table[i] != NULL)
	{
		if (!strcmp(streets_table[i], name))
			return (0);
		i++;
	}
	return (1);
}

unsigned int		calculate_intersections(t_cars *cars, t_first_line gener)
{
	unsigned int	nb_inter = 0;
	int				i = 0;
	int				j = 0;
	int				k = 0;

	streets_table = (char **)malloc(sizeof(char *) * gener.nb_streets);
	streets_table[is] = NULL;

	i = 0;
	while (i < gener.nb_cars)
	{
		j = 0;
		while (j < cars[i].nb_path)
		{
			if (check_street_exist(cars[i].path[j]))
			{
				streets_table[is] = strdup(cars[i].path[j]);
				is++;
				streets_table[is] = NULL;
			}
			j++;
		}
		i++;
	}
	while(streets_table[nb_inter] != NULL)
		nb_inter++;
	return (nb_inter);
}

// void				define_intersections(t_cars *cars, t_first_line gener, t_intersections *intersections, unsigned int inters)
// {
// 	unsigned int	nb_inter = 0;
// 	int				i = 0;
// 	int				j = 0;
// 	int				k = 0;

// 	while (i < gener.nb_cars)
// 	{
// 		j = 0;
// 		while (j < cars[i].nb_path)
// 		{
// 			if (!check_street_exist(cars, gener.nb_cars, cars[i].path[j], i, j))
// 			{
// 				intersections[k].from = strdup(cars[i].path[j]);
// 				intersections[k].id_inter = k;
// 				k++;
// 				nb_inter++;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

int 				main(int argv, char **args)
{
	t_cars				*cars;
	t_streets 			*streets;
	t_first_line		gener;
	unsigned int		output_inter;
	t_intersections		*intersections;
	
	//to read input file
	int			fd;
	char		*line;
	char		**tab;
	int			i = 0;
	int			j = 0;
	int			k;

	fd = open(args[1], O_RDONLY);
	if (fd == -1)
		exit(0);
	if (get_next_line(fd, &line))
	{
		tab = ft_split(line, ' ');
		gener.duration = atoi(tab[0]);
		gener.nb_inter = atoi(tab[1]);
		gener.nb_streets = atoi(tab[2]);
		gener.nb_cars = atoi(tab[3]);
		gener.bonus = atoi(tab[4]);
	}
	streets = (t_streets *)malloc(sizeof(t_streets) * gener.nb_streets);
	cars = (t_cars *)malloc(sizeof(t_cars) * gener.nb_cars);
	while (i < gener.nb_streets)
	{
		if (get_next_line(fd, &line))
		{
			tab = ft_split(line, ' ');
			streets[i].id_street = i;
			streets[i].start_inter = atoi(tab[0]);
			streets[i].end_inter = atoi(tab[1]);
			streets[i].name = strdup(tab[2]);
			streets[i].time_cross = atoi(tab[3]);
			i++;
		}
		else
			exit(0);
	}
	while (j < gener.nb_cars)
	{
		if (get_next_line(fd, &line))
		{
			tab = ft_split(line, ' ');
			cars[j].id_car = j;
			cars[j].nb_path = atoi(tab[0]);
			cars[j].path = (char **)malloc(sizeof(char *) * cars[j].nb_path);
			k = 0;
			while (k < cars[j].nb_path)
			{
				cars[j].path[k] = strdup(tab[k + 1]);
				k++;
			}
			j++;
		}
	}
	output_inter = calculate_intersections(cars, gener);
	printf("%d\n", output_inter);
	intersections = (t_intersections *)malloc(sizeof(t_intersections) * output_inter);
	//define_intersections(cars, gener, intersections, output_inter);
	i = 0;
	/*while (i < output_inter)
	{
		printf("%10d, %30s\n", intersections[i].id_inter, intersections[i].from);
		i++;
	}*/
	//printf("%d", output_inter);


	/*i = 0;
	j = 0;
	k = 0;
	// print file
	printf("%9d, %9d, %9d, %9d, %9d\n", gener.duration, gener.nb_inter, gener.nb_streets, gener.nb_cars, gener.bonus);
	while (i < gener.nb_streets)
	{
		printf("%9d, %9d, %9d, %30s, %9d\n", streets[i].id_street, streets[i].start_inter, streets[i].end_inter, streets[i].name, streets[i].time_cross);
		i++;
	}
	while (j < gener.nb_cars)
	{
		printf("%9d, %9d", cars[j].id_car, cars[j].nb_path);
		k = 0;
		while (k < cars[j].nb_path)
		{
			printf("%30s", cars[j].path[k]);
			k++;
		}
		printf("\n");
		j++;
	}*/
	
}
