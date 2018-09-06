// file: main.c

extern int g_share;
extern int g_func(int a);

int main(){
	int a = 66;
	a = g_func(a);
	return 0;
}
