int main(void)
{
	void *m[150];
	int		i;

	i = 0;
	while (i < 100)
	{
		m[i] = malloc(1024);
		memset(m[i], 0xff, 1024);
		i++;
	}
	i = 0;
	while (i < 20)
	{
		free(m[i*2]);
		i++;
	}
	i = 15;
	while (i < 148)
	{
		m[i] = malloc(1023);
		i++;
	}
	return (0);
}
