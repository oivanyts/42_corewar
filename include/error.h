//
// Created by actionfenix on 30.04.19.
//

#ifndef ERROR_H
# define ERROR_H

typedef enum e_error_code
{
	error_array_add,
    error_no_players,
    error_to_many_players,
    error_wrong_magic
} t_error_code;

void	handle_error(t_error_code n_err);

const char *error_table[4];

#endif
