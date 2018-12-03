/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 11:11:34 by skarev            #+#    #+#             */
/*   Updated: 2018/11/20 11:11:34 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	bfs(t_lem *lem)
{
	t_room	*current;
	t_nghbr	*tmp;
	t_room	*start;
	t_room	*end;

	start = find_room_by_type(lem, 1);
	end = find_room_by_type(lem, 3);
	if (!start || !end)
		!start ? ft_error(NULL, NULL, ER11) : ft_error(NULL, NULL, ER12);
	add_to_queue(lem, start, 0);
	while (lem->queue /*&& lem->queue->room->type != 3*/)
	{
		current = lem->queue->room;
		dell_from_queue(lem, current);
		printf("del: %s --> ", current->name);
		tmp = current->nghbrs;
		while (tmp)
		{
			printf("%s -> ", tmp->neighbor->name);
			if (!is_in_queue(lem->queue, tmp->neighbor) && tmp->neighbor->visited == 0)
			{
				printf(" | add to Q %s curr %s -> deep %d | ", tmp->neighbor->name, current->name, current->deep);
				add_to_queue(lem, tmp->neighbor, current->deep + 1);
			}
			tmp = tmp->next;
		}
		printf("...\n");
	}
	t_room *ttmp = lem->rooms;
	while (ttmp)
	{
		printf("%s -> %d \n", ttmp->name, ttmp->deep);
		ttmp = ttmp->next;
	}
}

int		is_in_queue(t_q *queue, t_room *room)
{
	t_q		*tmp;

	tmp = queue;
	while (tmp)
	{
		if (ft_strequ(tmp->room->name, room->name))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_room		*find_room_by_type(t_lem *lem, int type)
{
	t_room		*current;

	current = lem->rooms;
	while(current)
	{
		if (current->type == type)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	add_to_queue(t_lem *lem, t_room *room, int deep)
{
	t_q	*current;
	
	if (!lem->queue)
	{
		lem->queue = (t_q*)ft_memalloc(sizeof(t_q));
		lem->queue->room = room;
		lem->queue->next = NULL;
		lem->queue->room->deep = deep;
	}
	else
	{
		current = lem->queue;
		while (current->next)
			current = current->next;
		current->next = (t_q*)ft_memalloc(sizeof(t_q));
		current->next->room = room;
		current->next->next = NULL;
		current->next->room->deep = deep;
	}
	
}

void	dell_from_queue(t_lem *lem, t_room *room)
{
	t_q		*head;
	
	room->visited = 1;
	head = lem->queue->next;
	lem->queue = NULL;
	lem->queue = head;
}