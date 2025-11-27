#include <stdio.h>

void merge(int a[], int l, int m, int r){
    int n1 = m-l+1;
    int n2 = r-m;

    int L[100], R[100];

    for(int i=0;i<n1;i++)
        L[i] = a[l+i];

    for(int j=0;j<n2;j++)
        R[j] = a[m+1+j];

    int i=0, j=0, k=l;

    while(i<n1 && j<n2){
        if(L[i] < R[j]){
            a[k] = L[i];
            i++;
        } else {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while(i<n1)
        a[k++] = L[i++];

    while(j<n2)
        a[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r){
    if(l < r){
        int mid = (l+r)/2;
        mergeSort(arr,l,mid);
        mergeSort(arr,mid+1,r);
        merge(arr,l,mid,r);
    }
}

int main(){
    int arr[] = {23, 7, 14, 55, 2, 31, 9, 44};
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("Before: ");
    for(int i=0;i<n;i++) printf("%d ", arr[i]);

    mergeSort(arr,0,n-1);

    printf("\nAfter: ");
    for(int i=0;i<n;i++) printf("%d ", arr[i]);

    printf("\n");

    return 0;
}
