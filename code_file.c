#include <stdio.h>

int num_deg,den_deg,res_deg, i, j, current_num_deg, k=0, shift=0, first_flag=0; 
double coeff_num[100], coeff_den[100], result[100], mult[100], temp[100];

void coeff_input(int flag)
{
    if (flag == 0) //Numerator coefficients
    {
        for (i = 0; i<num_deg ; i++)
        {
            printf("Enter coefficient of x^%d : ", num_deg-i);
            scanf("%lf", &coeff_num[i]);
        }
        printf("Enter Constant Term : ");
        scanf("%lf", &coeff_num[i]);
    }
    else if (flag == 1) //Denominator coefficients
    {
        for (i = 0; i<den_deg ; i++)
        {
            printf("Enter coefficient of x^%d : ", den_deg-i);
            scanf("%lf", &coeff_den[i]);
        }        
        printf("Enter Constant Term : ");
        scanf("%lf", &coeff_den[i]);
    }
}

void subtract()
{
    //subtracting  mult from the numerator
    shift =0;
    for (i =0; i<current_num_deg; i++)
        temp[i] = coeff_num[i+1]-mult[i+1];
    
    current_num_deg--; //to work on the new numerator
    
    for (i =0; i<current_num_deg; i++)
    {
        if (temp[i]==0) //if the first coeff. of the subtraction is zero 
        {current_num_deg--; shift++;}
        
        else break;
    }
    
    for (i=0; i<current_num_deg+1; i++)
        coeff_num[i] = temp[i+shift];
}

void division()
{
    if (num_deg>=den_deg)
    {
        res_deg=num_deg-den_deg;
        current_num_deg=num_deg;
        while(current_num_deg>=den_deg)
        {
            result[k] = coeff_num[0]/coeff_den[0];
            for (j = 0; j<den_deg+1; j++) //for den
                mult[j] = result[k]*coeff_den[j];
                
            subtract(); //subtract mult from the numerator 
            k ++;  //to work on the next coeff. for the result
        }
    }
}

void printing(int deg,double coeff[])
{
    first_flag=0;
    for (i=0; i<deg;i++)
    {
        if (coeff[i]!=0) //not to print 0
        {
            if (deg-i != 1) //not to print x^1
            {
                if (first_flag == 1 && coeff[i]>0){
                    printf(" + ");
                    printf("%.2lf x^%d",coeff[i],deg-i);}
                if (first_flag == 1 && coeff[i]<0){
                    printf(" - ");
                    printf("%.2lf x^%d",-coeff[i],deg-i);}
                if (first_flag == 0)
                    printf("%.2lf x^%d",coeff[i],deg-i);
                first_flag = 1; //the first coefficient has been printed
            }
            else //printing coeff of x
            {
                if (first_flag == 1 && coeff[i]>0){
                    printf(" + ");
                    printf("%.2lf x",coeff[i]);}
                if (first_flag == 1 && coeff[i]<0){
                    printf(" - ");
                    printf("%.2lf x",-coeff[i]);}
                if (first_flag==0)
                    printf("%.2lf x",coeff[i]);
                first_flag = 1;
            }
        }
    }
    //printing const. term
    if (coeff[i]!=0){
        if (first_flag == 1 && coeff[i]>0){
            printf(" + ");
            printf("%.2lf",coeff[i]);}
        if (first_flag == 1 && coeff[i]<0){
            printf(" - ");
            printf("%.2lf",-coeff[i]);}
        if (first_flag==0)
            printf("%.2lf",coeff[i]);
    }    
}

void print_remainder()
{
    printf(" + (");
    printing(current_num_deg, coeff_num);
    printf(") / (");
    printing(den_deg, coeff_den);
    printf(")");
}

int main()
{
//Numerator input
    printf("Enter Numerator Degree : ");
    scanf("%d", &num_deg);
    coeff_input(0);
//Denominator input
    printf("Enter Denominator Degree : ");
    scanf("%d", &den_deg);
    coeff_input(1);
    
    division(); 
    
    printing(res_deg, result); //printing the result
    print_remainder();
    return 0;
}