#include <stdio.h>

void imprimir(float *output_, int size);
void imprimir(float *output_, int size){
    for(int x = 0; x< size; x++)
    {
        printf("%.6f\n", output_[x]);
    }
}

int main() {
    float b0 = 0.2347009086815551;
    float b1 = 0.4694018173631102;
    float b2 = 0.2347009086815551;

    float a1 = -0.1598795087668923;
    float a2 = 0.09868314349311275;

    float a[]= {1, a1, a2};
    float b[]= {b0, b1, b2};

    float input[] = {1, 0, 0, 0, 0, 0};
    float output[] = {0, 0, 0, 0, 0, 0};
    float padding[] = { 0, 0 };

    float* input_ = malloc(8 * sizeof(float)); // array to hold the result

    memcpy(input_,     padding, 2 * sizeof(float)); // copy 4 floats from x to total[0]...total[3]
    memcpy(input_ + 2, input, 6 * sizeof(float)); // copy 4 floats from y to total[4]...total[7]

    float* output_ = malloc(8 * sizeof(float)); // array to hold the result

    memcpy(output_,     padding, 2 * sizeof(float)); // copy 4 floats from x to total[0]...total[3]
    memcpy(output_ + 2, output, 6 * sizeof(float)); // copy 4 floats from y to total[4]...total[7]

    const int N = 8;
    const int filter_size = 2;

    //y[n] = b0*x[n] + b1*x[n-1] + b2*x[n-2] – a1*y[n-1] – a2*y[n-2]
    for (int i = 2; i < N; i++) {
        float acc = 0;
        for (int j = filter_size; j>=0; j--)
        {
            acc += input_[i-j] * b[j] - output_[i-j] * a[j];
        }
        output_[i] =acc;
    }
    imprimir(output_, 8);
    return 0;
}
