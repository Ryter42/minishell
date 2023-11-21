# include<stdio.h>

int	is_return(char *cmd)
{
	if (cmd[0] == '.' && cmd[1] == '.' && !cmd[2])
		return (1);
	else
		return (0);
}

int	main(void)
{
	char *str = "..";
	printf("%d\n", is_return(str));
}
