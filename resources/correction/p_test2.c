int main(void)
{
	void *m[300];
	size_t	i;

	i = 0;
	while (i < 32)
	{
		m[i] = malloc(4097);
		memset(m[i], 0xff, 4097);
		i++;
	}
	i = 0;
	while (i < 32)
	{
		free(m[i]);
		i++;
	}
	return (0);
}
