#include <stdio.h>

// Un filtro IIR bicuadrático (de segundo orden) en forma directa I tiene la siguiente implementacion

void imprimir(float *output_, int size);

// Para mostrar en pantalla los valores de los arreglos
void imprimir(float *output_, int size){
    for(int x = 0; x< size; x++)
    {
        printf("%.10f\n", output_[x]);
    }
}

float * iir_biquad(
        float input[], int input_size,
        float b0, float b1, float b2,
        float a0, float a1, float a2
        );

float * iir_biquad(float input[],const int input_size,
                   float b0, float b1, float b2,
                   float a0, float a1, float a2
)
{
    // Para construir los arreglos de coeficientes
    float a[]= {a0, a1, a2};
    float b[]= {b0, b1, b2};

    //Preparando los espacios en memoria que almacenan los calculos
    const int Bquad = 2; // El tamaño del filtro biquad siempre es 2
    float padding[] = { 0, 0}; // Arreglo para crear el espacio de condiciones iniciales como 0 flotante

    float* input_ = malloc((input_size + Bquad) * sizeof(float)); // Alocando espacio en memoria para el vector de entrada

    // Construyendo el vector para mantener la entrada. Inicialmente colocando las condiones iniciales
    memcpy(input_, padding, Bquad * sizeof(float));
    memcpy(input_ + Bquad, input, input_size * sizeof(float)); // Contruyendo vector de entrada junto con las condiciones iniciales

    // Construyendo el vector para mantener la salida temporal tomando en cuenta el espacio para las condiciones iniciales
    float* output_ = malloc((input_size + Bquad) * sizeof(float));

    float* output = malloc((input_size) * sizeof(float)); // Alocando espacio en memoria para el vector de salida
    memset(output, 0, input_size*sizeof(float)); // Definiendo inicialmente el arreglo de salida como 0 flotante

    memcpy(output_, padding, Bquad * sizeof(float)); // Contruyendo el espacio con condiciones inicials
    memcpy(output_ + Bquad, output, input_size * sizeof(float)); // Finalizando el espacio para el arreglo de salida
    // Espacio de memoria listos para el calculo

    const int N = input_size + Bquad;

    // Sección del algoritmo del flitro
    //y[n] = b0*x[n] + b1*x[n-1] + b2*x[n-2] – a1*y[n-1] – a2*y[n-2]
    // Para recordar: los taps o delays estan contenidos en input_ y output_
    // No se requiere tener variables adiciones (para los y[n-1, y[n-2]] o x[n-1], x[n-2]) que se actualizan en cada paso
    for (int i = Bquad; i < N; i++) {
        float acc = 0;
        for (int j = Bquad; j>=0; j--)
        {
            acc += input_[i-j] * b[j] - output_[i-j] * a[j];
        }
        output_[i] =acc;
    }
    // Del arreglo temporal de salida excepto el espacio de las condiciones iniciales
    memcpy(output, output_ + Bquad, input_size * sizeof(float));
    return output;
}

int main() {
    float b0 = 0.2513790015131591;
    float b1 = 0.5027580030263182;
    float b2 = 0.2513790015131591;

    float a0 = 1;
    float a1 = -0.17124071441396285;
    float a2 = 0.1767567204665992;

    float input[] = {1, 0, 0, 0, 0, 0,0,0};
    const int input_size = sizeof(input) / sizeof(float);
    float *output;

    // Llamando al flitro iir_biquad. Dados los parametros requeridos
    output = iir_biquad(input, input_size, b0, b1, b2, a0, a1, a2);

    imprimir(output, input_size);
    return 0;
}
