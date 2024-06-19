#include "common-headers.hh"

int yyparse();
int yylex(void);

lpmode mode;

int main (int argc, char **argv)
{
	struct argp argp = {options, parse_opt };
	int status = 0;

	argp_parse (&argp, argc, argv, 0, 0, 0);

	if (stop_after_scanning())
	{
		while (yylex());
		status = 0;
	}
	else
		status = yyparse();
	return status;

}
