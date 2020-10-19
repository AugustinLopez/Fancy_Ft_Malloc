int main(void)
{
	void	*m[300];
	int		i;

	while (i < 30)
	{
		m[i] = malloc(1024);
		printf("%3zu - %p\n", i, m[i]);
		memset(m[i], 0xff, 1024);
		printf("%3zu - %p\n", i, m[i]);
		free(m[i]);
		i++;
	}
	return (0);
}
