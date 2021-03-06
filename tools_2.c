/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:18:33 by skarev            #+#    #+#             */
/*   Updated: 2018/11/15 15:18:33 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*get_room_by_name(t_lem *lem, char *name)
{
	t_room	*tmp;

	tmp = lem->rooms;
	while (tmp)
	{
		if (ft_strequ(tmp->name, name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	create_nghbrs(t_room *room, t_room *n)
{
	t_nghbr	*current;

	if (!room->nghbrs)
	{
		room->nghbrs = (t_nghbr*)ft_memalloc(sizeof(t_nghbr));
		room->nghbrs->neighbor = n;
		room->nghbrs->next = NULL;
	}
	else
	{
		current = room->nghbrs;
		while (current->next)
			current = current->next;
		current->next = (t_nghbr*)ft_memalloc(sizeof(t_nghbr));
		current->next->neighbor = n;
		current->next->next = NULL;
	}
}

t_room	*find_room_by_type(t_lem *lem, int type)
{
	t_room	*current;

	current = lem->rooms;
	while (current)
	{
		if (current->type == type)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	add_to_print(t_lem *lem, char *str)
{
	t_s		*current;

	if (!lem->print)
	{
		lem->print = (t_s*)ft_memalloc(sizeof(t_s));
		lem->print->str = ft_strdup(str);
		lem->print->next = NULL;
	}
	else
	{
		current = lem->print;
		while (current->next)
			current = current->next;
		current->next = (t_s*)ft_memalloc(sizeof(t_s));
		current->next->str = ft_strdup(str);
		current->next->next = NULL;
	}
}

void	print_map(t_lem *lem)
{
	t_s		*tmp;

	if (lem->flags && lem->flags->color_on == 1)
		write(1, "\x1b[36m", 5);
	while (lem->print)
	{
		tmp = lem->print;
		ft_putstr(tmp->str);
		write(1, "\n", 1);
		free(tmp->str);
		lem->print = lem->print->next;
		free(tmp);
	}
	write(1, "\n", 1);
	write(1, "\033[0m", 5);
}
