int main(void)
{
	void *m[30];
	size_t	i;

	i = 0;
	while (i < 10)
	{
		m[i] = malloc(4097);
		memset(m[i], 0xff, 4097);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		free(m[i*2]);
		i++;
	}
	i = 15;
	while (i < 20)
	{
		m[i] = malloc(4097);
		i++;
	}
	return (0);
}
