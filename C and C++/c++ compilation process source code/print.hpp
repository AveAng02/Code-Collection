
#ifdef __cplusplus
void printSum(int a, int b);
void printSum(float a, float b);
extern "C" {
#endif

void printSumInt(int a, int b);
void printSumFloat(float a, float b);

#ifdef __cplusplus
} // end extern "C"
#endif