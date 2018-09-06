// file: a.c
int g_share = 1;

int g_func(int a){
	g_share += a;
	return a * 3;
}

int g_func2(){
    int a = 2;
    int b = g_func(3);
    return a + b;
}
