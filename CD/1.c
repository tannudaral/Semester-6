#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int isKeyword(char buffer[])
{
    int flag = 0, i;
    char keywords[32][10] = {
        "auto", "int", "double", "struct", "break", "else", "long", "switch",
        "case", "enum", "register", "typedef", "char", "extern", "return", "union", "const", "float", "short", "unsigned", "continue", "for", "signed", "void", "default", "goto", "sizeof", "volatile", "do", "if", "static", "while"};
    for (i = 0; i < 32; i++)
    {
        if (strcmp(keywords[i], buffer) == 0)
        {
            flag = 1;
            break;
        }
    }
    return flag;
}
int main()
{
    char ch, temp, token[15], operators[] = "+-*/%=";
    FILE *fp;
    int i, j = 0, lineflag = 0;
    fp = fopen("sample.txt", "r");
    if (fp == NULL)
    {
        printf("File not found/ not accessible.\n");
        exit(0);
    }
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '/')
        {
            temp = fgetc(fp);
            if (temp == '/')
            {
                while (ch != '\n')
                {
                    ch = fgetc(fp);
                }
                printf("Single line comment\n");
            }
            else if (temp == '*')
            {
                while (1)
                {
                    while (ch != '*')
                        ch = fgetc(fp);

                    ch = fgetc(fp);
                    if (ch == '/')
                    {
                        printf("Multi line comment\n");
                        break;
                    }
                }
                ch = fgetc(fp);
            }
        }
        if (ch == '#')
        {
            while (ch != '>')
            {
                ch = fgetc(fp);
            }
            printf("preprocessor directive\n");
        }
        for (i = 0; i < 6; i++)
        {
            if (ch == operators[i])
                printf("%c is an operator\n", ch);
        }
        if (ch == '"')
        {
            printf("Print ");
            printf("%c", ch);
            ch = fgetc(fp);
            while (ch != '"')
            {
                printf("%c", ch);
                ch = fgetc(fp);
            }
            printf("%c", ch);
            putchar('\n');
        }
        if (isalnum(ch))
        {
            token[j++] = ch;
        }
        else if ((ch == ' ' || ch == '\n') && (j != 0))
        {
            token[j] = '\0';
            j = 0;
            if (isKeyword(token) == 1)
                printf("%s is keyword\n", token);
            else
                printf("%s is identifier\n", token);
        }
    }
    fclose(fp);
    return 0;
}