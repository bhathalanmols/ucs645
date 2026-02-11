#include <iostream>
#include <cstdlib>
#include <ctime>

void correlate(int ny, int nx, const float* data, float* result);

int main(int argc, char* argv[])
{
    if(argc < 3) {
        std::cout << "Usage: ./correlate rows cols\n";
        return 0;
    }

    int ny = atoi(argv[1]);
    int nx = atoi(argv[2]);

    std::cout << "Matrix size: " << ny << " x " << nx << std::endl;

    float* data = new float[ny * nx];
    float* result = new float[ny * ny];

    srand(time(NULL));

    for(int i = 0; i < ny * nx; i++)
        data[i] = rand() % 100;

    correlate(ny, nx, data, result);

    std::cout << "Done computing correlation!\n";

    delete[] data;
    delete[] result;

    return 0;
}
