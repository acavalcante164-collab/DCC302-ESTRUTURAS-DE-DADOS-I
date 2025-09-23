/* Cálculo da media e da variância de 10 reais (segunda versão) */
#include <stdio.h>
/* Função para cálculo da média */ 
float media (int n, float* v )
{
    int i;
    float s = 0.0;
    for (i = 0; i < n; i++)
        s += v[i];
    return s/n;
}
/* Função para cálculo da variância */
float variancia (int n, float* v, float m)
{
    int i;
    float s = 0.0;
    for (i = 0; i < n; i++)
         s += (v[i] - m) * (v[i] - m);
    return s/n;
}
int main(void)
{
    int i, n;
    float *v;
    float med, var;

    scanf("%d", &n);
    //alocacao dinamica
    v = (float*) malloc(n*sizeof(float));
    if (v==NULL) {
        printf("memoria insuficiente.\n");
        return 1;
    }
    //Leitura dos valores
    for (i =0; i < n; i++)
        scanf("%f", &v[i]);
    med = media(n,v);
    var = variancia(n, v, med);
    printf("Media = %f      variancia = %f  \n", med, var);
    free(v);
    return 0;

}
