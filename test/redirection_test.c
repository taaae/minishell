#include "parser.h"

int main()
{
    exec_pipeline("cat < file.txt | cat > file2.txt");
}