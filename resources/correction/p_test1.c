int main(void)
{
	void	*m[300];
	int		i;

	i = 0;
	m[i++] = malloc(1024);
	m[i++] = malloc(1024);
	m[i++] = malloc(1024);
	i = 0;
	free(m[i++]);
	free(m[i++]);
	free(m[i++]);
	i = 0;
	while (i < 30)
	{
		m[i] = malloc(1024);
		memset(m[i], 0xff, 1024);
		free(m[i]);
		i++;
	}
	return (0);
}
