#include <stdio.h>

#define MAX_LEN 200

float calculator(char* expr);   //计算器主体
int is_num(char c);     //数字判断
char optr_prio(char top, char now);   //运算符优先级比较
float operate(float num1, char op, float num2);     //进行单次运算
int main()
{
    char expr[MAX_LEN];
    char tag = '0';
    float result;

    printf("说明:\n**支持= - * / 括号\n表达式不带空格\n*输入e(end)结束\n");
    while (1) //重复执行计算过程
    {
        printf(">>>");
        scanf("%s",expr);       //输入表达式

        tag = expr[0];      //判断是否继续计算
        if (tag == 'e')
        {
            printf(">>> calculator end");   //结束计算
            break;
        }
        result = calculator(expr);
        printf("%f\n",result);
    }
    return 0;
}

float calculator(char* expr)
{
    /****************top指向当前元素*********************/

    int i = 0, nums_top = -1, optr_top = 0, error = 0;
    float nums[MAX_LEN] = {0};      //数字栈
    char optr[MAX_LEN];     //操作符栈
    optr[0] = '#';  //栈底结束标志

    while (optr_top != -1)     //无运算符
    {
        if (is_num(expr[i]))    //数字处理
        {
            if (expr[i-1] < '0' || expr[i-i] > '9' || nums_top == -1)     //后一位非数字
                nums_top ++;
            nums[nums_top] = nums[nums_top] * 10 + expr[i] - '0';
        }

        else
        {
            switch (optr_prio(optr[optr_top], expr[i]))
            {
                case '<':{      //当前运算符优先级高于栈顶，push
                            optr_top ++;
                            optr[optr_top] = expr[i];
                            break;
                         }
                case '=':{      //当前元素为 '#',pop

                           optr_top --;
                           break;
                         }
                case '>':{      //当前运算符优先级低于栈顶，进行计算，结果入栈

                            float num2 = nums[nums_top];
                            nums[nums_top] = 0;
                            nums_top --;    //pop数字2


                            float num1 = nums[nums_top];
                            nums[nums_top] = 0;
                            nums_top --;    //pop数字1

                            nums_top ++;
                            nums[nums_top] = operate(num1, optr[optr_top], num2);   //运算结果push

                            //optr_top --;
                            optr[optr_top] = expr[i];   //top操作符pop,当前操作符push

                            if (optr[optr_top] == ')')      //弹出括号
                                optr_top -= 2;
                            break;
                         }
                default: {      //表达式错误
                             printf("Expression error!\n");
                             error = 1;
                             break;
                         }
            }
        }
        if (error) break;

        if (expr[i] != '\0')
           i ++;
    }

    return nums[nums_top];
}

int is_num(char c)
{
    if (c >= '0' && c <= '9')
        return 1;
    else
        return 0;
}

char optr_prio(char top, char now)      //添加defaults
{
    char priority[7][7] =                   {
               //当前(now)运算符
              //  +   -   *   /   (   )  \0
    /*栈 + */    '>','>','<','<','<','>','>',

    /*顶 - */    '>','>','<','<','<','>','>',

    /*运 * */    '>','>','>','>','<','>','>',

    /*算 / */    '>','>','>','>','<','>','>',

    /*符 ( */    '<','<','<','<','<','=',' ',

    /*top) */    ' ',' ',' ',' ',' ',' ',' ',

    /*  #  */    '<','<','<','<','<',' ','=',
                                             };
    int i,j;

    switch (top)
    {
        case '+': i = 0; break;

        case '-': i = 1; break;

        case '*': i = 2; break;

        case '/': i = 3; break;

        case '(': i = 4; break;

        case ')': i = 5; break;

        case '#': i = 6; break;

        case '\0': i = 6; break;

        default: i = 5;  break;  //表达式子出错

    }

    switch (now)
    {
        case '+': j = 0; break;

        case '-': j = 1; break;

        case '*': j = 2; break;

        case '/': j = 3; break;

        case '(': j = 4; break;

        case ')': j = 5; break;

        case '\0': j = 6; break;

        default: j = 5;  break;     //表达式子出错

    }

    return (priority[i][j]);

}

float operate(float num1, char op, float num2)
{
    float re;
    switch (op)
    {
        case '+':{ re = num1 + num2; break;}
        case '-':{ re = num1 - num2; break;}
        case '*':{ re = num1 * num2; break;}
        case '/':{ re = num1 / num2; break;}
    }
    return re;
}






