/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 19:22:07 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/15 19:22:07 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/miniRT.h"

void	free_rt(t_rt **rt);
void	free_string(char **string);
void	free_string_array(char ***array);

void	free_ambience(t_ambience **ambience);
