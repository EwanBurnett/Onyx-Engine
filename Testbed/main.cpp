#include <cstdio>
#include <Onyx.h> 

int main() {
    printf("Onyx Version: %s\n", Onyx::GetVersionString().c_str());
    return 0; 
}