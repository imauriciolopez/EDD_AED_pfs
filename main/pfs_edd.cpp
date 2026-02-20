#include "../include/pfs.hpp"
#include "../include/edd.hpp"
#include "../include/eda.hpp"
#include "../include/morais.hpp"
#include "../include/utils.hpp"

#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(int argc, char *argv[]){
    experimento(argv[1], argv[2], 2, true, false);
    return 0;
}
