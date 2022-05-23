#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

typedef struct
{
    int a ;
    int b ;
    int **elements;
} Matrix ;
Matrix mat[4];

int Ri=0, Ei =0, Ej =0 ;

//int a , b ,c , d ;
//int matrix1[a][b];
//int matrix2[c][d];

void Multiplication()
{

    int i, j, k;
    int result[mat[0].a][mat[1].b];

    for(i = 0; i < mat[0].a; ++i)
    {
        for(j = 0; j < mat[1].b; ++j)
        {
            result[i][j] = 0;
        }
    }
    //error size of array needs to be given correctly
    //int test ;
    for(i = 0; i <  mat[0].a; i++)
    {

        for(j = 0; j <  mat[1].b; j++)
        {

            for(k=0; k< mat[0].b; k++)
            {
                //printf(" %d X %d  + ", mat[0].elements[i][k],  mat[1].elements[k][j]);
                //test = (matrix1[i][k] * matrix2[k][j]);
                //printf("%d + " , test);
                result[i][j] =  result[i][j] + (mat[0].elements[i][k] * mat[1].elements[k][j]);

            }
            //printf("\n");

        }
    }
    printf("\n Matrix Result : \n");
    for (i = 0 ; i<mat[0].a ; i++ )
    {
        printf(" ");
        for (j = 0 ; j<mat[1].b ; j++ )
        {
            printf("%d    ", result[i][j]);
        }
        printf("\n\n");
    }

}
int reads(char *fileName)
{
    int Accepted = 0 ;
    FILE *fp;
    fp=fopen(fileName,"r");
    if (fp!=NULL)
    {
        while (!feof(fp))
        {
            int i, j;

            fscanf(fp, "%d %d\n", &mat[0].a, &mat[0].b);
            //int matrix1[a][b];


            mat[0].elements = malloc(sizeof(int*) * mat[0].a);
            for (i=0 ; i < mat[0].b ; i++ )
            {
                mat[0].elements[i]=malloc(sizeof(int) * mat[0].b);
            }

            for (i = 0 ; i<mat[0].a ; i++ )
            {
                for (j =0 ; j<mat[0].b ; j++ )
                {
                    fscanf(fp, "%d ", &mat[0].elements[i][j]);
                }
            }

            fscanf(fp, "%d %d\n", &mat[1].a, &mat[1].b);
            //int matrix2[c][d];

            mat[1].elements = malloc(sizeof(int*) * mat[1].a);
            for (i=0 ; i < mat[1].b ; i++ )
            {
                mat[1].elements[i]=malloc(sizeof(int) * mat[1].b);
            }

            for (i = 0 ; i<mat[1].a ; i++ )
            {
                for (j =0 ; j<mat[1].b ; j++ )
                {
                    fscanf(fp, "%d ", &mat[1].elements[i][j]);
                }
            }
            if (mat[0].b == mat[1].a)
            {

                printf(" Value Of A : %d \n Value Of B : %d \n\n", mat[0].a, mat[0].b );
                printf(" Matrix 1 : \n");
                for (i = 0 ; i<mat[0].a ; i++ )
                {
                    printf(" ");
                    for (j = 0 ; j<mat[0].b ; j++ )
                    {
                        printf("%d ", mat[0].elements[i][j]);
                    }
                    printf("\n");
                }

                printf("\n Value Of A : %d \n Value Of B : %d \n\n", mat[1].a, mat[1].b );
                printf(" Matrix 2 : \n");
                for (i = 0 ; i<mat[1].a ; i++ )
                {
                    printf(" ");
                    for (j = 0 ; j<mat[1].b; j++ )
                    {
                        printf("%d ", mat[1].elements[i][j]);
                    }
                    printf("\n");
                    Accepted = 1 ;
                }
            }
            else
            {
                printf("These Matrix can't be multiplied");
                Accepted = 0;
            }
        }
    }
    else
    {
        printf("File is empty\n");
        return 2 ;
    }
    fclose(fp);
    return Accepted ;

}

void output(int matno)
{
    int i, j ;
    mat[matno].a = mat[0].a ;
    mat[matno].b = mat[1].b ;

    mat[matno].elements = malloc(sizeof(int*) * mat[matno].a);
    for (i=0 ; i < mat[matno].b ; i++ )
    {
        mat[matno].elements[i]=malloc(sizeof(int) * mat[matno].b);
    }

    for(i = 0; i < mat[matno].a; ++i)
    {
        for(j = 0; j < mat[matno].b; ++j)
        {
            mat[matno].elements[i][j] = 0;
        }
    }
}

void *Rmult(void * row)
{
    int k, j ;
    for(j = 0; j <  mat[1].b; j++)
    {
        for(k=0; k< mat[0].b; k++)
        {
            //printf(" %d X %d  + ", mat[0].elements[Ri][k],  mat[1].elements[Ri][j]);
            //test = (matrix1[Ri][k] * matrix2[k][j]);
            //printf("%d + " , test);
            mat[2].elements[Ri][j] =  mat[2].elements[Ri][j] + (mat[0].elements[Ri][k] * mat[1].elements[k][j]);
        }
        //printf("\n");
        //printf("Element  = %d \n " , mat[2].elements[Ri][j] );
    }
    Ri++;
}

void *Emult(void * Element)
{
    int k;
    for(k=0; k< mat[0].b; k++)
    {
        mat[3].elements[Ei][Ej] =  mat[3].elements[Ei][Ej] + (mat[0].elements[Ei][k] * mat[1].elements[k][Ej]);
    }
    Ej++;
    if (Ej == mat[1].b)
    {
        Ej=0;
        Ei++;
    }
}

void printMatrix(int number)
{
    for (int i = 0 ; i<mat[number].a ; i++ )
    {
        printf(" ");
        for (int j = 0 ; j<mat[number].b ; j++ )
        {
            printf("%d    ", mat[number].elements[i][j]);
        }
        printf("\n\n");
    }
}

void Fmatrix(float time, int number)
{
    FILE *fp;
    fp=fopen("Output.txt","a");

    if (number == 2 )
    {
        fprintf(fp,"Row Matrix Multiplication : \n" );
    }
    else if (number == 3 )
    {
        fprintf(fp,"Element Matrix Multiplication : \n" );
    }
    for (int i = 0 ; i<mat[number].a ; i++ )
    {

        for (int j = 0 ; j<mat[number].b ; j++ )
        {
            fprintf(fp,"%d    ", mat[number].elements[i][j]);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp,"\n");
    fprintf(fp,"Time Taken : %f ", time);
    fprintf(fp,"\n");
    fclose(fp);
}


void  freeing(int matno)
{

    for (int i = 0 ; i < mat[matno].b ; i++ )
    {
    free(mat[matno].elements[i]);
    mat[matno].elements[i] = NULL ;
    }
    free(mat[matno].elements);
    mat[matno].elements  = NULL;
}
int main()
{
    char fileName[40];
    printf("Enter file name : " );
    scanf("%s",fileName);
    int Accepted = reads(fileName);
    // printf("Accepted = %d", Accepted );
    if (Accepted == 1)
    {
        Multiplication();

        output(2);

        clock_t Rstart, Rend ;
        double Rtime;

        int RowThreads = mat[0].b;
        pthread_t Rthreads[RowThreads];

        Rstart = clock();
        for (int i = 0; i < RowThreads ; i++)
        {
            pthread_create(&Rthreads[i], NULL, &Rmult, NULL);
        }
        //sleep(1);
        for (int i = 0; i < RowThreads; i++)
            pthread_join(Rthreads[i], NULL);

        Rend = clock();
        Rtime = (double) (Rend-Rstart) / CLOCKS_PER_SEC;


        printf("\n Row Matrix Result : \n");
        printMatrix(2);
        Fmatrix(Rtime, 2 );
        printf (" Row Multiplication Ended in  : %f Seconds \n\n", Rtime);

        output(3);

        clock_t Estart, Eend ;
        double Etime;

        int ElementThreads = mat[0].a * mat[1].b ;
        pthread_t Ethreads[ElementThreads];


        Estart = clock();
        for (int i = 0; i < ElementThreads ; i++)
        {
            pthread_create(&Ethreads[i], NULL, &Emult, NULL);
        }
        //sleep(1);
        for (int i = 0; i < ElementThreads ; i++)
            pthread_join(Ethreads[i], NULL);

        Eend = clock();
        Etime = (double) (Eend-Estart) / CLOCKS_PER_SEC;


        printf(" Element Matrix Result : \n");
        printMatrix(3);
        Fmatrix(Etime, 3 );
        printf(" Element Multiplication Ended in  : %f Seconds\n", Etime);

        freeing(0);
        freeing(1);
        freeing(2);
        freeing(3);


    }
    else if (Accepted == 0)
    {

        FILE *fp;
        fp=fopen("Output.txt","a");
        fprintf(fp,"These matrix can't be multiplied \n" );
        fclose(fp);
    }


    return 0;
}
