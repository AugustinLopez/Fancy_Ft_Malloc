int main()
{
	malloc(1);
	malloc(8);
	malloc(9);
	malloc(16);
	malloc(32);
	malloc(64);
	malloc(128);
	malloc(129);
	malloc(256);
	malloc(512);
	malloc(1024);
	malloc(1024 * 2);
	malloc(1024 * 4);
	malloc(1024 * 16);
	malloc(1024 * 1024);
	malloc(1024 * 1024 * 16);
	malloc(1024 * 1024 * 128);
	show_alloc_mem();
	return (0);
}
