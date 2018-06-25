%.o : %.c
	gcc -c $< -o $@
