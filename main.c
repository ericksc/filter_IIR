#include <stdio.h>

void imprimir(float *output_, int size);
void imprimir(float *output_, int size){
    for(int x = 0; x< size; x++)
    {
        printf("%.6f\n", output_[x]);
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
    float a[]= {a0, a1, a2};
    float b[]= {b0, b1, b2};

    const int Bquad = 2;
    float output[6] = {0};
    float padding[] = { 0, 0};

    float* input_ = malloc((input_size + Bquad) * sizeof(float)); // array to hold the result

    memcpy(input_,     padding, Bquad * sizeof(float)); // copy 4 floats from x to total[0]...total[3]
    memcpy(input_ + Bquad, input, input_size * sizeof(float)); // copy 4 floats from y to total[4]...total[7]

    float* output_ = malloc((input_size + Bquad) * sizeof(float)); // array to hold the result

    memcpy(output_,     padding, Bquad * sizeof(float)); // copy 4 floats from x to total[0]...total[3]
    memcpy(output_ + Bquad, output, input_size * sizeof(float)); // copy 4 floats from y to total[4]...total[7]

    const int N = input_size + Bquad;

    //y[n] = b0*x[n] + b1*x[n-1] + b2*x[n-2] – a1*y[n-1] – a2*y[n-2]
    for (int i = 2; i < N; i++) {
        float acc = 0;
        for (int j = Bquad; j>=0; j--)
        {
            acc += input_[i-j] * b[j] - output_[i-j] * a[j];
        }
        output_[i] =acc;
    }

    float* aa = malloc(input_size * sizeof(float)); // array to hold the result
    memcpy(aa, output_ + Bquad, input_size * sizeof(float)); // copy 4 floats from y to total[4]...total[7]
    return aa;
}

int main() {
    float b0 = 0.2347009086815551;
    float b1 = 0.4694018173631102;
    float b2 = 0.2347009086815551;

    float a0 = 1;
    float a1 = -0.1598795087668923;
    float a2 = 0.09868314349311275;

    float input[] = {1, 0, 0, 0, 0, 0};
    const int input_size = 6;
    float *output;
    output = iir_biquad(input, input_size, b0, b1, b2, a0, a1, a2);
    imprimir(output, input_size);
    return 0;
}
