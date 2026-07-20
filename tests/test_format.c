#include <betterc/format.h>
#include <stdio.h>

int main() {
    String test = format("{} {} {}!", "Hello World!", (void*)0xFFF, false);
    printf("%s\n", test.data);

    return 0;
}
