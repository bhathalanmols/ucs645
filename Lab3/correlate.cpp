#include <cmath>
#include <omp.h>

void correlate(int ny, int nx, const float* data, float* result)
{
    #pragma omp parallel for schedule(static)
    for(int i = 0; i < ny; i++) {

        for(int j = 0; j <= i; j++) {

            double mean_i = 0.0;
            double mean_j = 0.0;

            for(int x = 0; x < nx; x++) {
                mean_i += data[x + i*nx];
                mean_j += data[x + j*nx];
            }

            mean_i /= nx;
            mean_j /= nx;

            double numerator = 0.0;
            double denom_i = 0.0;
            double denom_j = 0.0;

            for(int x = 0; x < nx; x++) {
                double a = data[x + i*nx] - mean_i;
                double b = data[x + j*nx] - mean_j;

                numerator += a * b;
                denom_i += a * a;
                denom_j += b * b;
            }

            double corr = numerator / sqrt(denom_i * denom_j);

            result[i + j*ny] = (float)corr;
        }
    }
}
