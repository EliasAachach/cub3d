/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:01:43 by elaachac          #+#    #+#             */
/*   Updated: 2021/06/04 16:02:03 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_flag4(int elem_flag, t_elems *elems)
{
	if (elem_flag == 'F')
	{
		if (elems->F_is_present == TRUE)
		{
			elems->double_elem = TRUE;
			return ;
		}
		else
			elems->F_is_present = TRUE;
		return ;
	}
	if (elem_flag == 'C')
	{
		if (elems->C_is_present == TRUE)
		{
			elems->double_elem = TRUE;
			return ;
		}
		else
			elems->C_is_present = TRUE;
		return ;
	}
}

void	check_flag3(int elem_flag, t_elems *elems)
{
	if (elem_flag == 'R')
	{
		if (elems->R_is_present == TRUE)
		{
			elems->double_elem = TRUE;
			return ;
		}
		else
			elems->R_is_present = TRUE;
		return ;
	}
	if (elem_flag == 'S')
	{
		if (elems->S_is_present == TRUE)
		{
			elems->double_elem = TRUE;
			return ;
		}
		else
			elems->S_is_present = TRUE;
		return ;
	}
	check_flag4(elem_flag, elems);
}

void	check_flag2(int elem_flag, t_elems *elems)
{
	if (elem_flag == 'W' + 'E')
	{
		if (elems->WE_is_present == TRUE)
		{
			elems->double_elem = TRUE;
			return ;
		}
		else
			elems->WE_is_present = TRUE;
		return ;
	}
	if (elem_flag == 'E' + 'A')
	{
		if (elems->EA_is_present == TRUE)
		{
			elems->double_elem = TRUE;
			return ;
		}
		else
			elems->EA_is_present = TRUE;
		return ;
	}
	check_flag3(elem_flag, elems);
}

void	check_flag(int elem_flag, t_elems *elems)
{
	if (elem_flag == 'N' + 'O')
	{
		if (elems->NO_is_present == TRUE)
		{
			elems->double_elem = TRUE;
			return ;
		}
		else
			elems->NO_is_present = TRUE;
		return ;
	}
	if (elem_flag == 'S' + 'O')
	{
		if (elems->SO_is_present == TRUE)
		{
			elems->double_elem = TRUE;
			return ;
		}
		else
			elems->SO_is_present = TRUE;
		return ;
	}
	check_flag2(elem_flag, elems);
}
