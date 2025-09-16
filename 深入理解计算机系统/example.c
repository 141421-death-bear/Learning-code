typedef struct {
    int a[2];
    double d;
} struct_t;

double fun(int i) {
    volatile struct_t s;
    s.d = 3.14;
    s.a[i] = 1073741824; /* Possibly out of bounds */
    return s.d;
}

int main() {
    int i = 0;
    printf("Enter an integer: ");
    scanf("%i", &i);
    printf("%f\n", fun(i));
    return 0;
}
