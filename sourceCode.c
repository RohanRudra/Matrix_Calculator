#include<stdio.h>


void dimensionSameSize(int *row,int *col){
    printf("Enter the number of Rows : ");
    scanf("%d",&*row);
    printf("Enter the number of Columns : ");
    scanf("%d",&*col);
}

void dimensionDiffSize(int *row1,int *col1,int *row2,int *col2){
    printf("Enter the number of Rows for Matrix A :");
    scanf("%d",&*row1);
    printf("Enter the number of Columns for Matrix A :");
    scanf("%d",&*col1);
    printf("Enter the number of Rows for Matrix B :");
    scanf("%d",&*row2);
    printf("Enter the number of Columns for Matrix B :");
    scanf("%d",&*col2);
}


void inputMatrix(int arr[10][10],int row,int col){
    
    for(int i=0;i<row;i++){
        printf("Enter %d elements in Row %d : ",col,i+1);
        for(int j=0;j<col;j++){
            scanf("%d",&arr[i][j]);
        }
    }
}

void printMatrix(int arr[10][10],int row,int col){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("%d  ",arr[i][j]);
        }
        printf("\n");
    }
}

void matrixAdd(int arr1[10][10],int arr2[10][10],int row,int col){
    int sum[10][10];
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            sum[i][j] = arr1[i][j] + arr2[i][j];
        }
    }

    printMatrix(sum,row,col);
}

void matrixSubstract(int arr1[10][10],int arr2[10][10],int row,int col){
    int sub[10][10];
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            sub[i][j] = arr1[i][j] - arr2[i][j];
        }
    }

    printMatrix(sub,row,col);
}

void matrixScalarMultiply(int arr[10][10],int k,int row,int col){
    int scalMultiply[10][10];
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            scalMultiply[i][j] = k * arr[i][j];
        }
    }

    printMatrix(scalMultiply,row,col);
}

void matrixMultiply(int arr1[10][10],int arr2[10][10],int row1,int col1,int col2){
    int ans[10][10];
    for(int i=0;i<row1;i++){
        for(int j=0;j<col2;j++){
            ans[i][j] = 0;
        }
    }

    for(int i=0;i<row1;i++){
        for(int j=0;j<col2;j++){
            for(int k=0;k<col1;k++){
                ans[i][j] = ans[i][j] + arr1[i][k]*arr2[k][j] ;
            }
        }
    }

    printMatrix(ans,row1,col2);
}

void getCofactor(int arr[10][10],int temp[10][10],int a,int b,int n){
    int i = 0, j = 0;   
    for (int row = 0; row < n; row++){
        for (int col = 0; col < n; col++){

            if (row != a && col != b) {
                temp[i][j] = arr[row][col];
                j++;

                if (j == n - 1){
                    j = 0;
                    i++;
                }
            }
        }
    }
}


int determinant(int arr[10][10],int n){
    int det = 0;
    
    if (n == 1){
        return arr[0][0];
    }
 
    int temp[10][10];
    int sign = 1;

    for (int i=0;i<n;i++){
        getCofactor(arr, temp, 0, i, n);
        det += sign * arr[0][i] * determinant(temp, n - 1);

        sign = -sign;
    }
    return det;
}


void adjoint(int arr[10][10],int adj[10][10],int n){
//     if (n == 2) {
//         adj[0][0] = 1;
//     }
 
    int sign = 1, temp[10][10];
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            getCofactor(arr,temp,i,j,n);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
 
            adj[j][i] = (sign) * (determinant(temp,n-1));
        }
    }
}


void inverse(int arr[10][10],int n){
    float inverse[10][10];

    int det = determinant(arr,n);
    if(det == 0){
        printf("Singular matrix, Inverse cannot be found\n");
        return;
    }

    int adj[10][10];
    adjoint(arr,adj,n);
 
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            inverse[i][j] = (float)((float)(adj[i][j]) / (float)(det));
        }
    }
    
    for(int k=0;k<n;k++){
        for(int l=0;l<n;l++){
            printf("%.3f   ",inverse[k][l]);
        }
        printf("\n");
    }
}

void transpose(int arr[10][10],int row,int col){
    int ans[10][10];
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            ans[j][i] = arr[i][j];
        }
    }

    printMatrix(ans,col,row);
}

void matrixCheck(int arr[10][10],int row,int col){
    int tp[10][10];
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            tp[j][i] = arr[i][j];
        }
    }

    //to check for symmetric
    int symcheck=1; 
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(tp[i][j] != arr[i][j]){
                symcheck = 0;
                break;
                break;
            }
        }
    }
    if(symcheck == 1){
        printf("\n ==> Matrix is Symmetric\n");
    }

    //to check for skew-symmetric
    int ssymcheck = 1;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(tp[i][j] != -1 * arr[i][j]){
                ssymcheck = 0;
                break;
                break;
            }
        }
    }
    if(ssymcheck == 1){
        printf("\n ==> Matrix is Skew-Symmetric\n");
    }

    if(symcheck == 0 && ssymcheck == 0){
        printf("* Matrix is neither Symmetric nor Skew-Symmetric *\n");
    }
  
}

void swap(int matrix[10][10],int r1,int r2, int col){
    int t;
    for(int i=0;i<col;i++){
        t=matrix[r1][i];
        matrix[r1][i]=matrix[r2][i];
        matrix[r2][i]=t;
    }

}

int rank(int a[10][10],int r1, int c1)
{
    int i,j,k;
    float ratio;
    for(i=0;i<c1;i++)
    {
       if(a[i][i]!=0)    /* Diagonal element is not zero */
     for(j=0;j<r1;j++)
       if (j!=i)
       {
          /* Make all the element above and nelow the current principal
         diagonal element zero */
          ratio = a[j][i]/a[i][i];
          for(k=0;k<c1;k++)
         a[j][k]-=ratio*a[i][k];
       }
       else
         printf("\n");
         /* principal Diagonal element is zero */
       else
       {
       for(j=i+1;j<r1;j++)
          if(a[j][i]!=0)
          {   /* Find non zero elements in the same column */
          swap(a,i,j,c1);
          break;
          }
          if(j==r1)
          {
          c1--;
          for(j=0;j<r1;j++)
             a[j][i] = a[j][c1];
          }
          i--;
         }
     }
   return  c1;
}


int main(){
    int matrixA[10][10];
    int matrixB[10][10];
    int rowA,colA;
    int rowB,colB;
    int scalar;
    int order;

    int choice = 1;
    while(choice != 11){   
        
        printf("\n_________________________________________________________");
        printf("\n");
        printf("\n    *************************************************\n");
        printf("\t\t    MATRIX CALCULATOR");
        printf("\n    *************************************************\n");
        printf("\t1. Add two martices\n");
        printf("\t2. Subtract two matrices\n");
        printf("\t3. Scalar multiplication\n");
        printf("\t4. Multiply two matrices\n");
        printf("\t5. Determinant of a Matrix\n");
        printf("\t6. Inverse of Matrix\n");
        printf("\t7. Transpose of Matrix\n");
        printf("\t8. Symmetric Matrix check\n");
        printf("\t9. Adjoint of Matrix\n");
        printf("\t10. Rank of Square Matrix\n");
        printf("\t11. Exit\n\n");
        printf("Choice your option: ");
        scanf("%d",&choice);

        if(choice==11)
        {
            printf("\n\t\t**** THANK YOU ****\n\n");

            return 0;
        }

        switch(choice)
        {
            case 1:
            dimensionSameSize(&rowA,&colA);
            rowB = rowA;
            colB = colA;

            printf("\n\tEnter elements of Matrix A : \n", rowA, colA);
            printf("\t----------------------------\n");
            inputMatrix(matrixA,rowA,colA);
            printf("\nMatrix A :\n\n");
            printMatrix(matrixA,rowA,colA);

            printf("\n\tEnter elements of Matrix B : \n", rowB, colB);
            printf("\t----------------------------\n");
            inputMatrix(matrixB,rowB,colB);
            printf("\nMatrix B :\n\n");
            printMatrix(matrixB,rowB,colB);

            printf("\n\tMatrix A + Matrix B :\n");
            printf("\t-------------------\n\n");
            matrixAdd(matrixA,matrixB,rowA,colA);
            break;


            case 2:
            dimensionSameSize(&rowA,&colA);
            rowB = rowA;
            colB = colA;
            
            printf("\n\tEnter elements of Matrix A : \n", rowA, colA);
            printf("\t----------------------------\n");
            inputMatrix(matrixA,rowA,colA);
            printf("\nMatrix A :\n\n");
            printMatrix(matrixA,rowA,colA);

            printf("\n\tEnter elements of Matrix B : \n", rowB, colB);
            printf("\t----------------------------\n");
            inputMatrix(matrixB,rowB,colB);
            printf("\nMatrix B :\n\n");
            printMatrix(matrixB,rowB,colB);

            printf("\n\tMatrixA - MatrixB :\n");
            printf("\t-------------------\n\n");
            matrixSubstract(matrixA,matrixB,rowA,colA);
            break;


            case 3:    
            printf("\nEnter the scalar: ");
            scanf("%d",&scalar);

            dimensionSameSize(&rowA,&colA);
            printf("\n\tEnter Elements :\n", rowA, colA);
            printf("\t----------------\n");
            inputMatrix(matrixA,rowA,colA);
            printf("\nMatrix :\n\n");
            printMatrix(matrixA,rowA,colA);

            printf("\n\tThe Scalar Multiplication %d * Matrix :\n",scalar);
            printf("\t------------------------------------\n\n");
            matrixScalarMultiply(matrixA,scalar,rowA,colA);
            break;


            case 4:
            dimensionDiffSize(&rowA,&colA,&rowB,&colB);

            while (colA != rowB){
            printf("\nError!!\n");
            printf("Column of First Matrix not equal to Row of Second Matrix");
            dimensionDiffSize(&rowA,&colA,&rowB,&colB);
            }
            printf("\n\tEnter elements of Matrix A:\n", rowA, colA);
            printf("\t----------------------------\n");
            inputMatrix(matrixA,rowA,colA);
            printf("\nMatrix A :\n\n");
            printMatrix(matrixA,rowA,colA);

            printf("\n\tEnter elements of Matrix B:\n", rowB, colB);
            printf("\t----------------------------\n");
            inputMatrix(matrixB,rowB,colB);
            printf("\nMatrix B :\n\n");
            printMatrix(matrixB,rowB,colB);
            
            printf("\n\tMatrix A x Matrix B :\n");
            printf("\t-------------------\n\n");
            matrixMultiply(matrixA,matrixB,rowA,colA,colB);
            break;


            case 5:
            printf("Enter the order of Matrix:");
            scanf("%d",&order);
            rowA=order;
            colA=order;

            printf("\n\tEnter Elements :\n", rowA, colA);
            printf("\t----------------\n");
            inputMatrix(matrixA,rowA,colA);
            printf("\nMatrix :\n\n");
            printMatrix(matrixA,rowA,colA);

            printf("\nThe Determinant of Matrix is %d",determinant(matrixA,order));
            break;


            case 6:
            printf("Enter the order of Matrix:");
            scanf("%d",&order);
            rowA=order;
            colA=order;

            printf("\n\tEnter Elements :\n", rowA, colA);
            printf("\t----------------\n");
            inputMatrix(matrixA,rowA,colA);
            printf("\nMatrix :\n\n");
            printMatrix(matrixA,rowA,colA);

            printf("\n\tInverse of Matrix is :\n\n");
            printf("\t--------------------\n\n");
            inverse(matrixA,order);
            break;


            case 7:
            dimensionSameSize(&rowA,&colA);
            printf("\n\tEnter Elements :\n", rowA, colA);
            printf("\t----------------\n");
            inputMatrix(matrixA,rowA,colA);
            printf("\nMatrix :\n\n");
            printMatrix(matrixA,rowA,colA);

            printf("\n\tTranspose of given Matrix is :\n");
            printf("\t----------------------------\n\n");
            transpose(matrixA,rowA,colA);
            break;


            case 8:
            dimensionSameSize(&rowA,&colA);
            printf("\n\tEnter Elements :\n", rowA, colA);
            printf("\t----------------\n");
            inputMatrix(matrixA,rowA,colA);
            printf("\nMatrix :\n\n");
            printMatrix(matrixA,rowA,colA);

            matrixCheck(matrixA,rowA,colA);
            break;


            case 9:
            printf("Enter the order of Matrix:");
            scanf("%d",&order);
            rowA=order;
            colA=order;

            printf("\n\tEnter Elements :\n", rowA, colA);
            printf("\t----------------\n");
            inputMatrix(matrixA,rowA,colA);
            printf("\nMatrix :\n\n");
            printMatrix(matrixA,rowA,colA);
            
            int ans[10][10];
            printf("\n\tAdjoint of given Matrix is :\n");
            printf("\t----------------------------\n\n");
            adjoint(matrixA,ans,order);

            for(int i=0;i<rowA;i++){
                for(int j=0;j<colA;j++){
                    printf("%d ",ans[i][j]);
                }
                printf("\n");
            }   
            break;


            case 10:
            printf("Enter the order of Matrix:");
            scanf("%d",&order);
            rowA=order;
            colA=order;

            printf("\n\tEnter Elements :\n", rowA, colA);
            printf("\t----------------\n");
            inputMatrix(matrixA,rowA,colA);
            printf("\nMatrix :\n\n");
            printMatrix(matrixA,rowA,colA);

            printf("Rank of Matrix is %d",rank(matrixA,rowA,colA));
            printf("\n--------------------");
            break;


            default:
            printf("\t\tERROR !!\n");
            printf("\tPlease choose between 1 - 7 ");

        }
    }
    return 0;
}
